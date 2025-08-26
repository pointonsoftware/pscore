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
set BUILD_CONFIG=Release

:loop
if not "%1"=="" (
    if "%1"=="--config" (
        shift
        if not "%1"=="" (
            if /i "%1"=="debug" (
                set BUILD_CONFIG=Debug
            ) else if /i "%1"=="release" (
                set BUILD_CONFIG=Release
            ) else (
                echo Invalid config value: %1
                echo Valid values are: debug, release
                exit /b 1
            )
            shift
        ) else (
            echo --config parameter requires a value (debug or release)
            exit /b 1
        )
    ) else (
        set CORE_CMAKE_FLAGS=%1 %CORE_CMAKE_FLAGS%
        shift
    )
    goto loop
)

REM Clean and create build directory
if exist build rmdir /s /q build
mkdir build
cd build

echo Starting clean build...
echo Build config: %BUILD_CONFIG%
echo cmake flags: %CORE_CMAKE_FLAGS%

REM Configure with Visual Studio generator
cmake -G "Visual Studio 16 2019" -A x64 %CORE_CMAKE_FLAGS% ..
if %errorlevel% neq 0 (
    echo CMake configuration failed
    exit /b %errorlevel%
)

REM Build the project
cmake --build . --config %BUILD_CONFIG%
if %errorlevel% neq 0 (
    echo Build failed
    exit /b %errorlevel%
)

echo Build completed successfully

REM Copy the configs
if exist ..\config (
    if not exist bin\%BUILD_CONFIG% mkdir bin\%BUILD_CONFIG%
    copy ..\config\* bin\%BUILD_CONFIG%\
    echo Config files copied to bin\%BUILD_CONFIG% folder.
)

echo.
echo Build completed successfully!
echo Binaries are in: %cd%\%BUILD_CONFIG%
