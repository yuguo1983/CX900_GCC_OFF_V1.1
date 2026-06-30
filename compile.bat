@echo off
REM 设置UTF-8编码以支持中文显示
chcp 65001 >nul 2>&1

setlocal enabledelayedexpansion

pushd "%~dp0" 2>nul
if errorlevel 1 (
    echo 错误: 无法切换到目录: %~dp0
    exit /b 1
)

set "path=%cd%\w64devkit\bin;%cd%\gcc-arm-none-eabi-10.3-2021.10\bin;%path%"
set "MAKEFILE_PATH=%cd%"

echo ================================================
echo 编译环境信息
echo ================================================
echo 工作目录: %MAKEFILE_PATH%
echo GCC版本:
arm-none-eabi-gcc --version | findstr /R /C:"arm-none-eabi-gcc"
echo.
echo ================================================
echo 开始编译...
echo ================================================

make V=1

set "MAKE_EXIT_CODE=%ERRORLEVEL%"

REM 返回原目录
popd

if %MAKE_EXIT_CODE% EQU 0 (
    echo.
    echo ================================================
    echo 编译成功完成!
    echo ================================================
) else (
    echo.
    echo ================================================
    echo 编译失败! 错误代码: %MAKE_EXIT_CODE%
    echo ================================================
)

endlocal
exit /b %MAKE_EXIT_CODE%


