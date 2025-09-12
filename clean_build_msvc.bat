@echo off
setlocal EnableExtensions
REM Build script for Windows using Visual Studio 2019 and CMake - equivalent to do.sh

REM Set up Visual Studio environment
call "C:\Program Files (x86)\Microsoft Visual Studio\2019\BuildTools\VC\Auxiliary\Build\vcvars64.bat"

REM Locate CMake without modifying PATH (avoid extremely long PATH from vcvars)
set "CMAKE_EXE=cmake"
if exist "C:\Program Files\CMake\bin\cmake.exe" set "CMAKE_EXE=C:\Program Files\CMake\bin\cmake.exe"
if exist "C:\Program Files (x86)\CMake\bin\cmake.exe" set "CMAKE_EXE=C:\Program Files (x86)\CMake\bin\cmake.exe"

REM Change to project directory
cd /d "%~dp0"

REM Define environment variables (equivalent to do.sh)
set "SCRIPT_DIR=%~dp0"
set "BUILD_DIR=%SCRIPT_DIR%build"
set "LIB_DIR=%BUILD_DIR%\lib"
set "BIN_DIR=%BUILD_DIR%\bin"

REM Default settings
set "CORE_CMAKE_FLAGS=-DBUILD_UNITTEST=ON -DBUILD_ALL_COMPONENTS=ON"
set "BUILD_CONFIG=Release"

REM Functions equivalent to do.sh
goto :parse_args

:show_help
echo Usage: %0 [flag]
echo Flags:
echo    -h, --help       Display this help message
echo    -b, --build      Build cmake, then build bins and libs
echo    -c, --clean      Clean the build directory
echo    -p, --profile    Begin profiling
echo    -a, --rbapp      Rebuild the console app
echo    -l, --rblib      Rebuild the core lib
echo    --config         Set build config (debug^|release)
exit /b 0

:clean_build
echo Cleaning build directory...
if exist "%BUILD_DIR%" rmdir /s /q "%BUILD_DIR%"
echo Cleaned!
exit /b 0

:rebuild_app
if not exist "%BUILD_DIR%" (
    echo Build directory does not exist. Run full build first.
    exit /b 1
)
cd "%BUILD_DIR%"
"%CMAKE_EXE%" --build . --config %BUILD_CONFIG% --target console_app
if %errorlevel% neq 0 (
    echo Rebuild app failed
    exit /b %errorlevel%
)
echo Console app rebuilt successfully
exit /b 0

:rebuild_lib
if not exist "%BUILD_DIR%" (
    echo Build directory does not exist. Run full build first.
    exit /b 1
)
cd "%BUILD_DIR%"
"%CMAKE_EXE%" --build . --config %BUILD_CONFIG% --target core
if %errorlevel% neq 0 (
    echo Rebuild lib failed
    exit /b %errorlevel%
)
echo Core lib rebuilt successfully
exit /b 0

:full_build
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
exit /b 0

:begin_profile
echo Profiling functionality not yet implemented
exit /b 0

:parse_args
REM Parse command line arguments
:arg_loop
if "%1"=="" goto :default_action
if "%1"=="-h" goto :show_help
if "%1"=="--help" goto :show_help
if "%1"=="-b" goto :full_build
if "%1"=="--build" goto :full_build
if "%1"=="-c" goto :clean_build
if "%1"=="--clean" goto :clean_build
if "%1"=="-p" goto :begin_profile
if "%1"=="--profile" goto :begin_profile
if "%1"=="-a" goto :rebuild_app
if "%1"=="--rbapp" goto :rebuild_app
if "%1"=="-l" goto :rebuild_lib
if "%1"=="--rblib" goto :rebuild_lib
if "%1"=="--config" (
    if "%2"=="debug" (
        set "BUILD_CONFIG=Debug"
        shift
        shift
        goto :arg_loop
    ) else if "%2"=="release" (
        set "BUILD_CONFIG=Release"
        shift
        shift
        goto :arg_loop
    ) else (
        echo Invalid config value: %2
        echo Valid values are: debug, release
        exit /b 1
    )
)
echo Invalid argument: %1
call :show_help
exit /b 1

:default_action
REM Default action when no arguments provided (equivalent to do.sh behavior)
call :show_help
endlocal
