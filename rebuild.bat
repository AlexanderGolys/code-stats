@echo off
git submodule update --init --recursive
.\premake5 --scene=main cmake
