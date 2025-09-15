---@diagnostic disable: undefined-global
require "cmake"  -- enable Premake's CMake exporter

workspace "Renderer"
    configurations { "Debug", "Profile", "Dist" }
    architecture "x64"
    location "build"
    filter "action:cmake"
        location "."
    filter {}

-- Options
newoption {
    trigger = "scene",
    value = "SCENE_NAME",
    description = "Single .cpp file to build from src/render-projects"
}
local configFile = "config/build_config.json"
local config = dofile(configFile)
if not config then error("Failed to read/parse config file: " .. configFile) end

local dialect = config.cpp_dialect or "C++23"
local project_dirs = config.projects_dir or "src"

local selectedScene = _OPTIONS["scene"] or "main"

local scenePath = path.join(project_dirs, selectedScene .. ".cpp")
if not os.isfile(scenePath) then error("Scene source not found: " .. scenePath) end

startproject(selectedScene)

local outdir = selectedScene .. "/build-%{cfg.architecture}"
local isbell_dir = "external/isbell/src/isbell"

local inc = {
    isbell_dir,
    isbell_dir .. "/utils",
    isbell_dir .. "/engine",
    isbell_dir .. "/geometry",
    isbell_dir .. "/physics",
    isbell_dir .. "/openglAPI",
    isbell_dir .. "/file-management",
    isbell_dir .. "/include",
    "external/glew-2.1.0/include",
    "external/glfw-3.4/include",
    "external/glm-0.9.1.7",
    "external/spdlog-1.x/include",
    "external/nuklear/include",
    "src",
    "src/code-analysis",
    "src/gui",
    "src/tests",
}

-- Use a more readable format for Windows system libraries
local winlibs = {
    "opengl32",
    "gdi32",
    "user32",
    "shell32",
    "ole32",
    "uuid",
    "winmm",
    "imm32"
}

-----------------------
-- Engine static library
-----------------------
project "engine"
    location "build/engine-build"
    kind "StaticLib"
    language "C++"
    cppdialect(dialect)
    staticruntime "off"
    targetdir ("build/engine-build/%{cfg.architecture}/bin")
    objdir    ("build/engine-build/%{cfg.architecture}/obj")

    files {
        isbell_dir .. "/**.hpp",
        isbell_dir .. "/**.cpp",

        "external/glew-2.1.0/src/glew.c",
        "external/glfw-3.4/src/**.c",
        "external/glm-0.9.7.1/glm/**.hpp",
        "external/nuklear/include/*.h",
    }

    removefiles {
        isbell_dir .. "/**_dep.**",
    }

    includedirs(inc)

    filter "system:windows"
        systemversion "latest"
        defines { "_WINDOWS", "WIN32_LEAN_AND_MEAN", "NOMINMAX", "GLEW_STATIC", "_GLFW_WIN32" }
    filter {}

    filter "configurations:Debug"
        defines { "DEBUG" }
        runtime "Debug"
        symbols "On"
    filter "configurations:Profile"
        defines { "NDEBUG" }
        runtime "Release"
        symbols "On"
        optimize "Speed"
        linktimeoptimization "On"
    filter "configurations:Dist"
        defines { "NDEBUG" }
        runtime "Release"
        symbols "Off"
        optimize "Speed"
        linktimeoptimization "On"
    filter {}



-----------------------
-- Scene application (Console)
-----------------------
project(selectedScene)
    location ("build/" .. selectedScene)
    language "C++"
    cppdialect(dialect)
    staticruntime "off"
    kind "ConsoleApp"

    links { "engine" } -- Link the static library

    filter "system:windows"
        systemversion "latest"
        defines { "_WINDOWS", "WIN32_LEAN_AND_MEAN", "NOMINMAX", "GLEW_STATIC", "_GLFW_WIN32" }
        links(winlibs)
    filter {}

    targetdir ("build/" .. selectedScene .. "/bin/build-%{cfg.architecture}")
    objdir    ("build/" .. selectedScene .. "/obj/build-%{cfg.architecture}")

    files {
        scenePath, "src/**.hpp", "src/**.cpp"
    }
    removefiles {
        "src/tests/**"
    }

    includedirs(inc)

    filter "configurations:Debug"
        defines { "DEBUG" }
        runtime "Debug"
        symbols "On"
    filter "configurations:Profile"
        defines { "NDEBUG" }
        runtime "Release"
        symbols "On"
        optimize "Speed"
        linktimeoptimization "On"
    filter "configurations:Dist"
        defines { "NDEBUG" }
        runtime "Release"
        symbols "Off"
        optimize "Speed"
        linktimeoptimization "On"
    filter {}


project "unitTests"
    location ("build/tests")
    language "C++"
    cppdialect(dialect)
    staticruntime "off"
    kind "ConsoleApp"

    links { "engine" }

    filter "system:windows"
        systemversion "latest"
        defines { "_WINDOWS", "WIN32_LEAN_AND_MEAN", "NOMINMAX", "GLEW_STATIC", "_GLFW_WIN32" }
        links(winlibs)
    filter {}

    targetdir ("build/tests/bin/build-%{cfg.architecture}")
    objdir    ("build/tests/obj/build-%{cfg.architecture}")

    files { "src/tests/**.hpp",
            "src/tests/**.cpp"
    }

    removefiles {
        scenePath
    }

    includedirs(inc)

    filter "configurations:Debug"
        defines { "DEBUG" }
        runtime "Debug"
        symbols "On"
    filter "configurations:Profile"
        defines { "NDEBUG" }
        runtime "Release"
        symbols "On"
        optimize "Speed"
        linktimeoptimization "On"
    filter "configurations:Dist"
        defines { "NDEBUG" }
        runtime "Release"
        symbols "Off"
        optimize "Speed"
        linktimeoptimization "On"
    filter {}
