<#
.SYNOPSIS
    CX900 编程工具 - 一键安装脚本
.DESCRIPTION
    可通过以下命令在线安装:
    irm https://raw.githubusercontent.com/yuguo1983/CX900_GCC_OFF_V1.1/main/install.ps1 | iex
    
    或本地运行:
    .\install.ps1
.NOTES
    需要管理员权限运行
    依赖: .NET Framework 4.6.1+
#>

#Requires -RunAsAdministrator

$ErrorActionPreference = 'Stop'
$Host.UI.RawUI.WindowTitle = 'CX900 编程工具 - 一键安装'

# 显式管理员检查（兼容 irm | iex 模式）
$currentPrincipal = New-Object Security.Principal.WindowsPrincipal([Security.Principal.WindowsIdentity]::GetCurrent())
if (-not $currentPrincipal.IsInRole([Security.Principal.WindowsBuiltInRole]::Administrator)) {
    Write-Host '错误：需要管理员权限！' -ForegroundColor Red
    Write-Host '请以管理员身份重新运行。' -ForegroundColor Yellow
    Write-Host ''
    Write-Host '  PowerShell (管理员): irm <URL> | iex' -ForegroundColor Cyan
    Read-Host '按回车键退出'
    exit 1
}

# ============================================
# 配置
# ============================================

# 判断运行模式：本地还是远程
$isRemote = $MyInvocation.MyCommand.Path -eq $null -or $MyInvocation.MyCommand.Path -eq ''
if ($isRemote) {
    Write-Host '>>> 远程安装模式 (irm | iex)' -ForegroundColor Cyan
    # 远程模式：脚本所在目录是临时目录，需要从源码包下载
    # 这里留空由后续逻辑处理
    $ScriptDir = $PSScriptRoot
} else {
    Write-Host '>>> 本地安装模式' -ForegroundColor Cyan
    $ScriptDir = Split-Path -Parent $MyInvocation.MyCommand.Path
}

$InstallDir  = "$env:ProgramFiles\CX900"
$StartMenu   = "$env:ProgramData\Microsoft\Windows\Start Menu\Programs\CX900"
$DesktopDir  = [Environment]::GetFolderPath('Desktop')

# ============================================
# 前置检查
# ============================================

# 检查 .NET Framework 4.6.1+
function Test-DotNet461 {
    $release = Get-ItemPropertyValue -Path 'HKLM:\SOFTWARE\Microsoft\NET Framework Setup\NDP\v4\Full' -Name 'Release' -ErrorAction SilentlyContinue
    return $release -ge 394254
}

if (-not (Test-DotNet461)) {
    Write-Warning '未检测到 .NET Framework 4.6.1 或更高版本！'
    $choice = Read-Host '是否立即下载安装？(y/n)'
    if ($choice -eq 'y') {
        Start-Process 'https://dotnet.microsoft.com/download/dotnet-framework/net461'
    }
    exit 1
}

# ============================================
# 安装函数
# ============================================

function Install-CX900 {
    param([string]$SourceDir)

    Write-Host '============================================' -ForegroundColor Green
    Write-Host '  CX900 编程工具 - 正在安装...' -ForegroundColor Green
    Write-Host '============================================' -ForegroundColor Green
    Write-Host ''

    # 1. 创建目录
    Write-Progress -Activity '正在安装 CX900' -Status '[1/5] 创建目录' -PercentComplete 20
    $null = New-Item -Path $InstallDir -ItemType Directory -Force

    # 2. 复制主程序
    Write-Progress -Activity '正在安装 CX900' -Status '[2/5] 复制主程序' -PercentComplete 40
    Copy-Item -Path "$SourceDir\CX900.exe"       -Destination $InstallDir -Force
    Copy-Item -Path "$SourceDir\CX900.exe.config" -Destination $InstallDir -Force
    Copy-Item -Path "$SourceDir\CX900.pdb"       -Destination $InstallDir -Force

    # 3. 复制 DLL
    Write-Progress -Activity '正在安装 CX900' -Status '[3/5] 复制运行时库' -PercentComplete 60
    Get-ChildItem -Path "$SourceDir\*.dll" | Copy-Item -Destination $InstallDir -Force

    # 4. 复制配置文件
    Get-ChildItem -Path "$SourceDir\*.xml", "$SourceDir\*.txt" | Copy-Item -Destination $InstallDir -Force

    # 5. 复制固件相关目录
    Write-Progress -Activity '正在安装 CX900' -Status '[4/5] 复制固件与模块' -PercentComplete 80
    $dirs = @('Firmware', 'Module', 'USER', 'CMD', 'Soft_Drive', 'USB', 'YMODEM', 'MALLOC', 'GPU', 'MB', 'FatFs', 'TEXT')
    foreach ($d in $dirs) {
        $src = "$SourceDir\$d"
        if (Test-Path $src) {
            Copy-Item -Path $src -Destination $InstallDir -Recurse -Force
        }
    }
    if (Test-Path "$SourceDir\Makefile") {
        Copy-Item -Path "$SourceDir\Makefile" -Destination $InstallDir -Force
    }

    # 6. 创建快捷方式
    Write-Progress -Activity '正在安装 CX900' -Status '[5/5] 创建快捷方式' -PercentComplete 95

    $ws = New-Object -ComObject WScript.Shell

    # 开始菜单
    $null = New-Item -Path $StartMenu -ItemType Directory -Force
    $lnk = $ws.CreateShortcut("$StartMenu\CX900.lnk")
    $lnk.TargetPath = "$InstallDir\CX900.exe"
    $lnk.WorkingDirectory = $InstallDir
    $lnk.Save()

    # 桌面
    $lnk = $ws.CreateShortcut("$DesktopDir\CX900.lnk")
    $lnk.TargetPath = "$InstallDir\CX900.exe"
    $lnk.WorkingDirectory = $InstallDir
    $lnk.Save()

    # 7. 创建卸载脚本
    $uninstall = @"
@echo off
chcp 65001 >nul
echo 正在卸载 CX900...
rd /s /q "$InstallDir" 2>nul
del /q "$DesktopDir\CX900.lnk" 2>nul
rd /s /q "$StartMenu" 2>nul
echo 卸载完成！
pause
"@
    [System.IO.File]::WriteAllText("$InstallDir\uninstall.bat", $uninstall, [System.Text.Encoding]::UTF8)

    Write-Progress -Activity '正在安装 CX900' -Status '完成' -PercentComplete 100

    Write-Host ''
    Write-Host '============================================' -ForegroundColor Green
    Write-Host '  安装完成！' -ForegroundColor Green
    Write-Host ''
    Write-Host "  安装路径: $InstallDir" -ForegroundColor White
    Write-Host "  桌面已创建快捷方式" -ForegroundColor White
    Write-Host '============================================' -ForegroundColor Green
    Write-Host ''
}

# ============================================
# 主流程
# ============================================

try {
    if ($isRemote) {
        # 远程模式：从 AtomGit 克隆仓库（国内速度快，稳定可靠）
        Write-Host '>>> 正在克隆仓库...' -ForegroundColor Yellow
        $cloneDir = "$env:TEMP\CX900_Install"
        $repoUrl = 'https://atomgit.com/denny168/CX900_GCC_OFF_V1.1.git'

        # 清理临时目录
        if (Test-Path $cloneDir) { Remove-Item $cloneDir -Recurse -Force }

        try {
            & git clone --depth 1 $repoUrl $cloneDir 2>&1
        } catch {
            Write-Error '克隆仓库失败！请检查网络连接。'
            exit 1
        }

        Install-CX900 -SourceDir $cloneDir

        # 清理
        Remove-Item $cloneDir -Recurse -Force -ErrorAction SilentlyContinue
    } else {
        # 本地模式
        Install-CX900 -SourceDir $ScriptDir
    }
}
catch {
    Write-Host ''
    Write-Host '安装失败！' -ForegroundColor Red
    Write-Host "错误: $_" -ForegroundColor Red
    Write-Host ''
    Read-Host '按回车键退出'
    exit 1
}

Read-Host '按回车键退出'
