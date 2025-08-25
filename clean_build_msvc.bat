@echo off
REM Build script for Windows using Visual Studio 2019 and CMake

REM Set up Visual Studio environment
call "C:\Program Files (x86)\Microsoft Visual Studio\2019\BuildTools\VC\Auxiliary\Build\vcvars64.bat"

REM Add CMake to PATH
set PATH=C:\Program Files\CMake\bin;%PATH%

REM Change to project directory
cd /d "%~dp0"

REM Parse command line arguments
set CORE_CMAKE_FLAGS=-DBUILD_UNITTEST=ON -DBUILD_ALL_COMPONENTS=ON
:loop
if not "%1"=="" (
    set CORE_CMAKE_FLAGS=%1 %CORE_CMAKE_FLAGS%
    shift
    goto loop
)

REM Clean and create build directory
if exist build rmdir /s /q build
mkdir build
cd build

echo Starting clean build...
echo cmake flags: %CORE_CMAKE_FLAGS%

REM Configure with Visual Studio generator
cmake -G "Visual Studio 16 2019" -A x64 %CORE_CMAKE_FLAGS% ..
if %errorlevel% neq 0 (
    echo CMake configuration failed
    exit /b %errorlevel%
)

REM Build the project
cmake --build . --config Release
if %errorlevel% neq 0 (
    echo Build failed
    exit /b %errorlevel%
)

echo Build completed successfully

REM Copy the configs
if exist ..\config (
    if not exist bin mkdir bin
    copy ..\config\* bin\
    echo Config files copied to bin folder.
)

echo.
echo Build completed successfully!
echo Binaries are in: %cd%\Release
