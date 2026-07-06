@echo off
chcp 65001 >nul
echo Uninstalling CX900, please wait...
rd /s /q "C:\Program Files\CX900" 2>nul
del /q "C:\Users\Administrator\Desktop\CX900.lnk" 2>nul
rd /s /q "C:\ProgramData\Microsoft\Windows\Start Menu\Programs\CX900" 2>nul
echo Uninstall complete!
pause
