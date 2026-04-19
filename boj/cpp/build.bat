@echo off
setlocal
if "%~1"=="" (
    echo Usage: build.bat ^<problem_number^> [--run]
    exit /b 1
)

set "SRC=%~dp0%~1.cpp"
set "EXE=%~dp0%~1.exe"
set "OBJ=%~dp0%~1.obj"

if not exist "%SRC%" (
    echo Source not found: %SRC%
    exit /b 1
)

if not defined VCINSTALLDIR (
    call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat" >nul
    if errorlevel 1 exit /b 1
)

cl /nologo /EHsc /std:c++17 /Fe:"%EXE%" /Fo:"%OBJ%" "%SRC%" /link /DEBUG:NONE
if errorlevel 1 exit /b 1

if /i "%~2"=="--run" (
    echo.
    echo --- run ---
    "%EXE%"
)
