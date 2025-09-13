@echo off

set VERSION=1.0
set SO=windows
set ARCH=x64

setlocal enabledelayedexpansion

.\foxmake.exe %1 --script=foxMakeFile -var target=%2

if not "%~3" == "" (
    set target=debug
    if not "%~4" == "" (
        set target=%4
    )

    .\build\foxmake-%VERSION%-%SO%-%ARCH%\foxmake.exe %3 --working-dir=run --script=foxMakeFile-Run -var target=!target!
)