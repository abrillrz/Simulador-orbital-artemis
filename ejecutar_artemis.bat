
@echo off
cd /d "%~dp0"

echo ========================================
echo    SIMULADOR ORBITAL ARTEMIS
echo ========================================
echo.



if errorlevel 1 (
    echo.
    echo ERROR: No se pudo compilar el programa.
    pause
    exit /b 1
)

echo.
echo Iniciando simulador...
echo.

simulador_artemis.exe

echo.
pause
