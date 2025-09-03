@echo off

setlocal enabledelayedexpansion

.\cbuild.exe %1 --settings-file=settings-windows.txt -var target=%2

if not "%~3" == "" (
    set target=debug
    if not "%~4" == "" (
        set target=%4
    )

    .\build\cbuild.exe %3 --working-dir=run --settings-file=settings-windows.txt -var target=!target!
)