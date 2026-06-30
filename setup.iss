; CX900 编程工具 - Inno Setup 安装脚本
; 使用 Inno Setup (https://jrsoftware.org/isinfo.php) 编译
; 编译方法：右键本文件 → Compile (或者 iscc setup.iss)

#define MyAppName "CX900 编程工具"
#define MyAppVersion "1.0.0"
#define MyAppPublisher "CX900"
#define MyAppExeName "CX900.exe"

[Setup]
; 基本设置
AppName={#MyAppName}
AppVersion={#MyAppVersion}
AppPublisher={#MyAppPublisher}
DefaultDirName={autopf}\CX900
DefaultGroupName=CX900
DisableProgramGroupPage=yes
OutputDir=.\Output
OutputBaseFilename=CX900_Setup_v{#MyAppVersion}
Compression=lzma
SolidCompression=yes
UninstallDisplayIcon={app}\{#MyAppExeName}
PrivilegesRequired=admin

; 安装前检查 .NET Framework 4.6.1
; 注: 取消注释下面这行需要准备 dotNetFx461.exe 放在本目录
; Checks: "dotnetversion"

[Languages]
Name: "chinesesimplified"; MessagesFile: "compiler:Languages\ChineseSimplified.isl"

[Tasks]
Name: "desktopicon"; Description: "创建桌面快捷方式"; GroupDescription: "快捷方式:"

[Files]
; 主程序及配置文件
Source: "CX900.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "CX900.exe.config"; DestDir: "{app}"; Flags: ignoreversion
Source: "CX900.pdb"; DestDir: "{app}"; Flags: ignoreversion

; 运行时库 (DLL)
Source: "*.dll"; DestDir: "{app}"; Flags: ignoreversion

; 配置文件
Source: "*.xml"; DestDir: "{app}"; Flags: ignoreversion
Source: "*.txt"; DestDir: "{app}"; Flags: ignoreversion

; 固件相关目录
Source: "Firmware\*"; DestDir: "{app}\Firmware"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "Module\*"; DestDir: "{app}\Module"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "USER\*"; DestDir: "{app}\USER"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "CMD\*"; DestDir: "{app}\CMD"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "Soft_Drive\*"; DestDir: "{app}\Soft_Drive"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "USB\*"; DestDir: "{app}\USB"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "YMODEM\*"; DestDir: "{app}\YMODEM"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "MALLOC\*"; DestDir: "{app}\MALLOC"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "GPU\*"; DestDir: "{app}\GPU"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "MB\*"; DestDir: "{app}\MB"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "FatFs\*"; DestDir: "{app}\FatFs"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "TEXT\*"; DestDir: "{app}\TEXT"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "Makefile"; DestDir: "{app}"; Flags: ignoreversion

[Icons]
Name: "{group}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"
Name: "{group}\卸载 {#MyAppName}"; Filename: "{uninstallexe}"
Name: "{commondesktop}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: desktopicon

[Run]
; 安装完成后勾选运行程序
Filename: "{app}\{#MyAppExeName}"; Description: "立即运行 {#MyAppName}"; Flags: postinstall nowait skipifsilent

; 可选：安装完成后打开说明文档
Filename: "{app}\codehelp.txt"; Description: "查看使用说明"; Flags: postinstall nowait skipifsilent shellexec

[Code]
// 检查 .NET Framework 4.6.1 是否已安装
function IsDotNet461Installed: Boolean;
var
  Release: DWORD;
begin
  Result := False;
  if RegQueryDWordValue(HKLM, 'SOFTWARE\Microsoft\NET Framework Setup\NDP\v4\Full', 'Release', Release) then
  begin
    Result := Release >= 394254; // .NET Framework 4.6.1 的 Release 值
  end;
end;

function InitializeSetup: Boolean;
var
  ErrCode: Integer;
begin
  if not IsDotNet461Installed then
  begin
    if MsgBox('本程序需要 .NET Framework 4.6.1 或更高版本。'#13#13'是否立即下载并安装？',
              mbConfirmation, MB_YESNO) = idYes then
    begin
      ShellExec('open', 'https://dotnet.microsoft.com/download/dotnet-framework/net461',
                '', '', SW_SHOW, ewNoWait, ErrCode);
    end;
    Result := False;
  end
  else
    Result := True;
end;
