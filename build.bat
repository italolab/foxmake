
@echo off

set VERSION=1.0
set SO=windows
set ARCH=x64

set APP_FILE_NAME=cbuild

set BUILD_FOLDER=build
set APP_FOLDER=cbuild-%VERSION%-%SO%-%ARCH%

set APP_DIR=%BUILD_FOLDER%\%APP_FOLDER%

set LIB_FILE=lib\windows\libcbtest.a

rem LIMPANDO...

if exist %APP_DIR% (
    rmdir /s /q %APP_DIR%
    echo Removido: %APP_DIR%
)

if exist %APP_DIR%.zip (
    del %APP_DIR%.zip
    echo Removido: %APP_DIR%.zip
)

mkdir %APP_DIR%

rem COMPILANDO...

echo.
echo Compilando...
echo.

.\cbuild.exe build --script=CBuildFile -var target=release

rem COPIANDO HEADERS PARA PASTA INCLUDE

echo.
echo Copiando headers para pasta include
mkdir %APP_DIR%\include
xcopy include\* %APP_DIR%\include /E /I /Y

rem COPIANDO STATIC LIBRARY DO CBTEST PARA PASTA LIB

echo.
echo Copiando libcbtest.a para pasta lib
mkdir %APP_DIR%\lib
copy %LIB_FILE% %APP_DIR%\lib

rem EMPACOTANDO EM .ZIP

set CURR_DIR=%cd%

cd %BUILD_FOLDER%

echo.
echo Empacotando... %APP_DIR%.zip

tar acvf %APP_FOLDER%.zip %APP_FOLDER%
echo Finalizado.

cd %CURR_DIR%

rem BUILD CONCLUIDO

echo.
echo Build concluido!