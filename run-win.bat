@echo off
setlocal
set "scriptDir=%~dp0"
set "filePath=bin/dbg-win/run.exe"

if exist "%filePath%" (
    echo [SCRIPT]: File found %filePath%
    set ROOT_DIR=root
    "%filePath%"
) else (
    echo [SCRIPT]: ERROR - File NOT found %filePath%
    echo [SCRIPT]: Run build-win.bat before running this script
)
endlocal
