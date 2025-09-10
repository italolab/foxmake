@echo off

setlocal enabledelayedexpansion

.\cbuild.exe %1 --script=CBuildFile -var target=%2 -v

if not "%~3" == "" (
    set target=debug
    if not "%~4" == "" (
        set target=%4
    )

    .\build\cbuild.exe %3 --working-dir=run --script=CBuildFile-Run -var target=!target!
)