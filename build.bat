@echo off

REM Se ejecuta en la terminal usando ".\build.bat" // ejecuta todos los cpp juntos

setlocal EnableDelayedExpansion

set FILES=

for %%f in (cpp\*.cpp) do (
    set FILES=!FILES! %%f
)

echo Compilando:
echo main.cpp !FILES!

g++ -std=c++17 -Wall -Wextra main.cpp !FILES! -Iheader -o main.exe

if %ERRORLEVEL% NEQ 0 (
    echo.
    echo Error de compilacion
    exit /b
)

echo.
echo Compilacion exitosa

echo.
echo Ejecutando...
echo.

.\main.exe