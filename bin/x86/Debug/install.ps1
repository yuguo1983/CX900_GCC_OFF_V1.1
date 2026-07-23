<#
.SYNOPSIS
    CX900 编程工具 - 一键安装脚本
.DESCRIPTION
    在线安装（推荐，不需要安装 Git）:
    irm https://gitcode.com/denny168/CX900_GCC_OFF_V1.1/raw/main/bin/x86/Debug/install.ps1 | iex
    
    或 GitHub 镜像:
    irm https://raw.githubusercontent.com/yuguo1983/CX900_GCC_OFF_V1.1/main/bin/x86/Debug/install.ps1 | iex
    
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

# 检查是否安装了 Git（用于仓库克隆模式）
function Test-GitInstalled {
    try {
        $null = Get-Command git -ErrorAction Stop
        return $true
    } catch {
        return $false
    }
}

# ============================================
# 工具函数
# ============================================

# 使用 irm 下载 ZIP 并解压
function Download-AndExtract {
    param(
        [string]$Url,
        [string]$DestDir
    )

    $zipPath = "$env:TEMP\CX900_Install.zip"

    Write-Host "正在下载: $Url" -ForegroundColor Yellow
    try {
        # 下载 ZIP 文件
        Invoke-WebRequest -Uri $Url -OutFile $zipPath -UseBasicParsing -ErrorAction Stop
    } catch {
        throw "下载失败: $_"
    }

    # 解压
    Write-Host '正在解压...' -ForegroundColor Yellow
    try {
        # 使用 .NET 的 ZipFile 解压（需要 .NET 4.5+）
        Add-Type -AssemblyName System.IO.Compression.FileSystem
        [System.IO.Compression.ZipFile]::ExtractToDirectory($zipPath, $DestDir)
    } catch {
        # 如果 ZipFile 失败，尝试用 Expand-Archive
        try {
            Expand-Archive -Path $zipPath -DestinationPath $DestDir -Force
        } catch {
            throw "解压失败: $_"
        }
    }

    # 清理 ZIP 文件
    Remove-Item $zipPath -Force -ErrorAction SilentlyContinue

    # ZIP 解压后，文件在子目录中（因为仓库 zip 会包含顶层目录）
    # 查找顶层目录并移动文件
    $subDirs = Get-ChildItem -Path $DestDir -Directory
    if ($subDirs.Count -eq 1 -and $subDirs[0].Name -like 'CX900_GCC_OFF_V1.1*') {
        $topDir = $subDirs[0].FullName
        Write-Host "检测到 ZIP 顶层目录: $($subDirs[0].Name)" -ForegroundColor Gray
        # 移动所有内容到 DestDir
        Get-ChildItem -Path $topDir | ForEach-Object {
            $dest = Join-Path $DestDir $_.Name
            if ($_.PSIsContainer) {
                if (Test-Path $dest) { Remove-Item $dest -Recurse -Force }
                Move-Item -Path $_.FullName -Destination $dest -Force
            } else {
                if (Test-Path $dest) { Remove-Item $dest -Force }
                Move-Item -Path $_.FullName -Destination $dest -Force
            }
        }
        Remove-Item $topDir -Recurse -Force
    }

    # 确保 bin/x86/Debug 目录存在
    $distDir = Join-Path $DestDir "bin\x86\Debug"
    if (Test-Path $distDir) {
        # 如果源码目录结构存在，把分发文件从 bin/x86/Debug 复制到 DestDir 根目录
        Write-Host "检测到源码目录结构，正在提取分发文件..." -ForegroundColor Gray
        Get-ChildItem -Path $distDir | ForEach-Object {
            $dest = Join-Path $DestDir $_.Name
            if ($_.PSIsContainer) {
                if (Test-Path $dest) { Remove-Item $dest -Recurse -Force }
                Move-Item -Path $_.FullName -Destination $dest -Force
            } else {
                if (Test-Path $dest) { Remove-Item $dest -Force }
                Move-Item -Path $_.FullName -Destination $dest -Force
            }
        }
    }

    Write-Host '下载并解压完成！' -ForegroundColor Green
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

    # 2. 复制所有文件
    Write-Progress -Activity '正在安装 CX900' -Status '[2/5] 复制文件...' -PercentComplete 40
    Get-ChildItem -Path $SourceDir -Exclude '.git' | ForEach-Object {
        $dest = Join-Path $InstallDir $_.Name
        if ($_.PSIsContainer) {
            Copy-Item -Path $_.FullName -Destination $dest -Recurse -Force
        } else {
            Copy-Item -Path $_.FullName -Destination $dest -Force
        }
    }

    # 3. 创建快捷方式
    Write-Progress -Activity '正在安装 CX900' -Status '[3/5] 创建快捷方式' -PercentComplete 80

    $ws = New-Object -ComObject WScript.Shell

    # 开始菜单
    $null = New-Item -Path $StartMenu -ItemType Directory -Force
    $lnk = $ws.CreateShortcut("$StartMenu\CX900.lnk")
    $lnk.TargetPath = "$InstallDir\CX900.exe"
    $lnk.WorkingDirectory = $InstallDir
    $lnk.Save()

    # 桌面快捷方式
    $lnk = $ws.CreateShortcut("$DesktopDir\CX900.lnk")
    $lnk.TargetPath = "$InstallDir\CX900.exe"
    $lnk.WorkingDirectory = $InstallDir
    $lnk.Save()

    # 4. 创建卸载脚本
    Write-Progress -Activity '正在安装 CX900' -Status '[4/5] 创建卸载脚本' -PercentComplete 90
    $uninstall = @"
@echo off
chcp 65001 >nul
echo Uninstalling CX900, please wait...
rd /s /q "$InstallDir" 2>nul
del /q "$DesktopDir\CX900.lnk" 2>nul
rd /s /q "$StartMenu" 2>nul
echo Uninstall complete!
pause
"@
    [System.IO.File]::WriteAllText("$InstallDir\uninstall.bat", $uninstall, [System.Text.UTF8Encoding]::new($false))

    # 5. 完成
    Write-Progress -Activity '正在安装 CX900' -Status '完成' -PercentComplete 100

    Write-Host ''
    Write-Host '============================================' -ForegroundColor Green
    Write-Host '  安装完成！' -ForegroundColor Green
    Write-Host ''
    Write-Host "  安装路径: $InstallDir" -ForegroundColor White
    Write-Host "  桌面已创建快捷方式" -ForegroundColor White
    Write-Host ''
    Write-Host '  固件编译环境: w64devkit + gcc-arm-none-eabi' -ForegroundColor Cyan
    Write-Host '  编译方法: 双击 compile.bat' -ForegroundColor Cyan
    Write-Host '============================================' -ForegroundColor Green
    Write-Host ''
}

# ============================================
# 下载仓库 ZIP（使用 irm，不需要 Git）
# ============================================

function Download-RepositoryViaIRM {
    $tempDir = "$env:TEMP\CX900_Install"

    # 清理临时目录
    if (Test-Path $tempDir) { Remove-Item $tempDir -Recurse -Force }
    $null = New-Item -Path $tempDir -ItemType Directory -Force

    # 下载地址列表（按优先级）
    $urls = @(
        # 1. GitCode（国内主站，速度快）
        'https://gitcode.com/denny168/CX900_GCC_OFF_V1.1/-/archive/main/CX900_GCC_OFF_V1.1-main.zip',
        # 2. GitHub（国际镜像）
        'https://github.com/yuguo1983/CX900_GCC_OFF_V1.1/archive/refs/heads/main.zip'
    )

    $downloaded = $false
    foreach ($url in $urls) {
        try {
            Download-AndExtract -Url $url -DestDir $tempDir
            $downloaded = $true
            break
        } catch {
            Write-Warning "从 $url 下载失败: $_"
            Write-Host '尝试下一个镜像...' -ForegroundColor Yellow
            continue
        }
    }

    if (-not $downloaded) {
        throw '所有下载地址均失败！请检查网络连接。'
    }

    return $tempDir
}

# ============================================
# 主流程
# ============================================

try {
    if ($isRemote) {
        # 远程模式：使用 irm 下载 ZIP（不需要 Git）
        Write-Host '>>> 正在通过 irm 下载仓库...' -ForegroundColor Yellow
        Write-Host '    (无需安装 Git，自动从 GitCode/GitHub 下载)' -ForegroundColor Gray
        $sourceDir = Download-RepositoryViaIRM
        Install-CX900 -SourceDir $sourceDir

        # 清理
        Remove-Item $sourceDir -Recurse -Force -ErrorAction SilentlyContinue
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
    Write-Host '请尝试以下方法:' -ForegroundColor Yellow
    Write-Host '  1. 检查网络连接' -ForegroundColor White
    Write-Host '  2. 以管理员身份运行' -ForegroundColor White
    Write-Host '  3. 下载 ZIP 手动解压后运行 .\install.ps1' -ForegroundColor White
    Write-Host ''
    Read-Host '按回车键退出'
    exit 1
}

Read-Host '按回车键退出'