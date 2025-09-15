## How to build and run:
1. clone submodules by either running rebuild.bat (steps 1 & 2 bash script) or by running:
   ```bash
   git submodule update --init --recursive
   ```
2. generate CMake file with premake 5:
   ```bash
   .\premake5 cmake
   ```
3. Load and run CMakeProject from generated CMakeLists.txt in your IDE or run 
    ```bash
    cmake --build . [BuildConfiguration]
    ```
