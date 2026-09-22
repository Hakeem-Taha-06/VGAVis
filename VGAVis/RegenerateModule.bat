@echo off
setlocal

:: Path to your MSYS2 root installation
set "MSYS2_PATH=C:\msys64"

:: Ensure MSYS2 exists
if not exist "%MSYS2_PATH%\usr\bin\bash.exe" (
    echo [ERROR] Could not find bash.exe at %MSYS2_PATH%\usr\bin\
    pause
    exit /b 1
)

:: Set MSYSTEM to MINGW64 so the correct /mingw64/bin path is active
set "MSYSTEM=MINGW64"
set "CHERE_INVOKING=1"

echo Running Verilator on vga_controller.v...

:: -l loads environment/paths; -c runs the commands inside bash
"%MSYS2_PATH%\usr\bin\bash.exe" -lc "verilator -Wno-fatal --cc vga_controller.v"

if %ERRORLEVEL% equ 0 (
    echo [SUCCESS] Verilation finished cleanly! obj_dir updated.
) else (
    echo [ERROR] Verilator failed with code %ERRORLEVEL%.
)

endlocal

PAUSE