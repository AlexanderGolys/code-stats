@echo off
git submodule update --remote --recursive
.\premake\premake5 --scene=main cmake
