# CX900 编程工具

CX900 是一款基于 GD32F303VET6 的嵌入式编程工具软件，支持 GCC 编译器，提供图形化编程界面和固件管理功能。

## 一键安装

### 方法一：在线安装（推荐）

以**管理员身份**打开 PowerShell，执行以下命令：

**GitCode（国内主站，速度快）：**
```powershell
irm https://gitcode.com/denny168/CX900_GCC_OFF_V1.1/raw/main/bin/x86/Debug/install.ps1 | iex
```

**GitHub 镜像：**
```powershell
irm https://raw.githubusercontent.com/yuguo1983/CX900_GCC_OFF_V1.1/main/bin/x86/Debug/install.ps1 | iex
```

安装脚本会自动完成以下操作：
1. 使用 `irm` 从 GitCode 或 GitHub 下载仓库 ZIP（无需安装 Git）
2. 解压并复制文件到 `C:\Program Files\CX900`
3. 创建桌面快捷方式和开始菜单
4. 创建卸载脚本

### 方法二：本地安装

1. 下载 ZIP 并解压
2. 右键点击 `install.ps1` → **使用 PowerShell 运行**（以管理员身份）
3. 或打开管理员 PowerShell，进入目录后执行：
   ```powershell
   .\install.ps1
   ```

### 系统要求

- Windows 7 或更高版本
- .NET Framework 4.6.1 或更高版本
- 管理员权限（用于安装到 Program Files）
- 在线安装需要网络连接

## 卸载

- 开始菜单 → CX900 → 运行 `uninstall.bat`
- 或直接删除 `C:\Program Files\CX900` 目录和桌面快捷方式

## 固件编译

安装目录中包含完整的固件编译环境：

- **w64devkit**：Windows 下的 GCC 工具链
- **gcc-arm-none-eabi-10.3**：ARM 交叉编译器
- **GD32F30x 标准外设库**

编译方法：
1. 进入安装目录（如 `C:\Program Files\CX900`）
2. 双击 `compile.bat`
3. 编译输出在 `build/` 目录中

## 目录结构

```
CX900_GCC_OFF_V1.1/
├── bin/x86/Debug/          # 编译环境 + 分发文件
│   ├── CX900.exe           # 主程序
│   ├── install.ps1         # 安装脚本
│   ├── compile.bat         # 固件编译脚本
│   ├── Firmware/           # GD32 固件库
│   ├── Module/             # 功能模块源码
│   ├── Template/           # 项目模板
│   ├── USER/               # 用户代码
│   ├── w64devkit/          # GCC 编译工具链
│   └── gcc-arm-none-eabi/  # ARM 交叉编译器
├── *.cs                    # C# 源码（Visual Studio 项目）
├── CX900.sln               # Visual Studio 解决方案
├── CX900.csproj            # 项目文件
├── compile.bat             # 根目录编译脚本（自动检测环境）
└── README.md               # 本说明文件
```

## 源码开发

本项目为 Visual Studio 项目（.NET Framework），使用 C# 开发。

1. 打开 `CX900.sln`
2. 编译运行（F5）
3. 固件修改在 `bin/x86/Debug/` 下的 `Firmware/`、`Module/`、`USER/` 等目录

## 仓库地址

- **GitCode（主仓库）：** https://gitcode.com/denny168/CX900_GCC_OFF_V1.1
- **GitHub 镜像：** https://github.com/yuguo1983/CX900_GCC_OFF_V1.1

## 许可证

本项目为开源项目，仅供学习参考。