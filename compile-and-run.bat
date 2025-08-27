@echo off

setlocal enabledelayedexpansion

set build=build
if not "%~2" == "" (
    if %2 == all (
        set build=buildall
    )
)

.\cbuild.exe %build% --settings-file=settings-windows.txt -var target=%1

if not "%~2" == "" (
    set build=build
    if not "%~3" == "" (
        set build=%3
    ) else if not %2 == all (
        set build=%2
    )

    .\build\cbuild.exe !build! --working-dir=run --settings-file=settings-windows.txt -var target=debug
)