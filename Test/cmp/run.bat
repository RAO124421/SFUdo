@echo off

set PATH=C:\Qt\6.11.0\mingw_64\bin;%PATH%

echo Building...
cmake --build build

if %ERRORLEVEL% neq 0 (
    echo Build failed
    pause
    exit /b
)

echo Running app...

cd build

cmp.exe

pause