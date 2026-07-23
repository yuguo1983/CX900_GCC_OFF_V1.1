@echo off
REM CX900编译脚本 - 根目录版本
REM 自动检测编译环境并调用适当的编译批处理文件
REM 设置UTF-8编码以支持中文显示
chcp 65001 >nul 2>&1

setlocal enabledelayedexpansion

echo ================================================
echo CX900 编译工具
echo ================================================

REM 查找编译环境
set "COMPILE_DIR="
if exist "bin\x86\Debug\compile.bat" (
    set "COMPILE_DIR=bin\x86\Debug"
    echo 检测到Debug编译环境
) else if exist "bin\x86\cx900_tools\compile.bat" (
    set "COMPILE_DIR=bin\x86\cx900_tools"
    echo 检测到cx900_tools编译环境
) else if exist "bin\Debug\compile.bat" (
    set "COMPILE_DIR=bin\Debug"
    echo 检测到bin\Debug编译环境
) else if exist "bin\cx900_tools\compile.bat" (
    set "COMPILE_DIR=bin\cx900_tools"
    echo 检测到bin\cx900_tools编译环境
)

if "%COMPILE_DIR%"=="" (
    echo 错误: 找不到编译环境!
    echo 请确保以下目录存在:
    echo   - bin\x86\Debug\
    echo   - bin\x86\cx900_tools\
    echo   - bin\Debug\
    echo   - bin\cx900_tools\
    pause
    exit /b 1
)

echo.
echo ================================================
echo 编译环境信息
echo ================================================
echo 工作目录: %~dp0
echo 编译目录: %COMPILE_DIR%
echo.
echo GCC版本:
if exist "%COMPILE_DIR%\gcc-arm-none-eabi-10.3-2021.10\bin\arm-none-eabi-gcc.exe" (
    "%COMPILE_DIR%\gcc-arm-none-eabi-10.3-2021.10\bin\arm-none-eabi-gcc.exe" --version | findstr /R /C:"arm-none-eabi-gcc"
) else (
    echo GCC工具链未找到
)
echo.
echo ================================================
echo 开始编译...
echo ================================================

REM 设置PATH环境变量
set "PATH=%~dp0%COMPILE_DIR%\w64devkit\bin;%~dp0%COMPILE_DIR%\gcc-arm-none-eabi-10.3-2021.10\bin;%PATH%"
set "MAKEFILE_PATH=%~dp0%COMPILE_DIR%"

REM 切换到编译目录并执行make
pushd "%MAKEFILE_PATH%" 2>nul
if errorlevel 1 (
    echo 错误: 无法切换到编译目录: %MAKEFILE_PATH%
    cd /d "%~dp0"
    endlocal
    exit /b 1
)

make V=1

set MAKE_EXIT_CODE=%ERRORLEVEL%

REM 返回原目录
popd

if %MAKE_EXIT_CODE% EQU 0 (
    echo.
    echo ================================================
    echo 编译成功完成!
    echo ================================================
    echo 输出文件位置: %MAKEFILE_PATH%\build\
) else (
    echo.
    echo ================================================
    echo 编译失败! 错误代码: %MAKE_EXIT_CODE%
    echo ================================================
)

cd /d "%~dp0"
endlocal
exit /b %MAKE_EXIT_CODE%
