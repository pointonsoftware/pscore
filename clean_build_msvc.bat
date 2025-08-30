@echo off
setlocal EnableExtensions
REM Build script for Windows using Visual Studio 2019 and CMake

REM Set up Visual Studio environment
call "C:\Program Files (x86)\Microsoft Visual Studio\2019\BuildTools\VC\Auxiliary\Build\vcvars64.bat"

REM Locate CMake without modifying PATH (avoid extremely long PATH from vcvars)
set "CMAKE_EXE=cmake"
if exist "C:\Program Files\CMake\bin\cmake.exe" set "CMAKE_EXE=C:\Program Files\CMake\bin\cmake.exe"
if exist "C:\Program Files (x86)\CMake\bin\cmake.exe" set "CMAKE_EXE=C:\Program Files (x86)\CMake\bin\cmake.exe"

REM Change to project directory
cd /d "%~dp0"

REM Parse command line arguments
set "CORE_CMAKE_FLAGS=-DBUILD_UNITTEST=ON -DBUILD_ALL_COMPONENTS=ON"
set "BUILD_CONFIG=Release"

REM Simple argument parsing
if "%1"=="--config" (
    if "%2"=="debug" (
        set "BUILD_CONFIG=Debug"
    ) else if "%2"=="release" (
        set "BUILD_CONFIG=Release"
    ) else (
        echo Invalid config value: %2
        echo Valid values are: debug, release
        exit /b 1
    )
)

REM Clean and create build directory
if exist build rmdir /s /q build
mkdir build
cd build

echo Starting clean build...
echo Build config: %BUILD_CONFIG%
echo cmake flags: %CORE_CMAKE_FLAGS%

REM Configure with Visual Studio generator
"%CMAKE_EXE%" -G "Visual Studio 16 2019" -A x64 -DCMAKE_BUILD_CONFIG=%BUILD_CONFIG% %CORE_CMAKE_FLAGS% ..
if %errorlevel% neq 0 (
    echo CMake configuration failed
    exit /b %errorlevel%
)

REM Build the project
"%CMAKE_EXE%" --build . --config %BUILD_CONFIG%
if %errorlevel% neq 0 (
    echo Build failed
    exit /b %errorlevel%
)

echo Build completed successfully

REM Copy the configs
if exist "..\config" (
    if not exist "bin\%BUILD_CONFIG%" mkdir "bin\%BUILD_CONFIG%"
    copy /Y "..\config\*" "bin\%BUILD_CONFIG%\"
    echo Config files copied to bin\%BUILD_CONFIG% folder.
)

echo.
echo Build completed successfully!
echo Binaries are in: %cd%\bin\%BUILD_CONFIG%
endlocal
