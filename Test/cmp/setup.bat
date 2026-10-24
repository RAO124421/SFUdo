@echo off

cmake -B build ^
-G "MinGW Makefiles" ^
-DCMAKE_TOOLCHAIN_FILE=D:/Bashdot/projects/dot3/server/v1/header/vcpkg/scripts/buildsystems/vcpkg.cmake ^
-DCMAKE_PREFIX_PATH=C:/Qt/6.11.0/mingw_64 ^
-DVCPKG_TARGET_TRIPLET=x64-mingw-dynamic

pause