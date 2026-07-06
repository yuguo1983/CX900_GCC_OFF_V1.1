# PowerShell 语法检查脚本
# 使用 System.Management.Automation.Language.Parser 做静态分析

$files = @(
    'install.ps1',
    'install.bat'
)

$errors = @()

foreach ($file in $files) {
    $path = Join-Path $PSScriptRoot $file
    if (-not (Test-Path $path)) {
        $errors += "[MISSING] $file - 文件不存在"
        continue
    }
    
    if ($file -like '*.ps1') {
        # PowerShell 静态语法解析
        $content = Get-Content $path -Raw
        $tokens = $null
        $parseErrors = $null
        $ast = [System.Management.Automation.Language.Parser]::ParseInput($content, [ref]$tokens, [ref]$parseErrors)
        if ($parseErrors) {
            foreach ($err in $parseErrors) {
                $errors += "[PS PARSE ERROR] $($file):$($err.Extent.StartLine) - $($err.Message)"
            }
        } else {
            Write-Host "[OK] $file - PowerShell 语法正确" -ForegroundColor Green
        }
    }
    
    if ($file -like '*.bat') {
        # 读取并验证基本结构
        $lines = Get-Content $path
        $inParenthesis = 0
        for ($i = 0; $i -lt $lines.Count; $i++) {
            $line = $lines[$i]
            # 检查括号匹配
            if ($line -match '\(') { $inParenthesis++ }
            if ($line -match '\)') { $inParenthesis-- }
        }
        if ($inParenthesis -ne 0) {
            $errors += "[BAT ERROR] $file - 括号不匹配 (差额: $inParenthesis)"
        } else {
            Write-Host "[OK] $file - 批处理括号匹配" -ForegroundColor Green
        }
    }
}

# 验证 Inno Setup 脚本
$issPath = Join-Path $PSScriptRoot 'setup.iss'
if (Test-Path $issPath) {
    $issContent = Get-Content $issPath -Raw
    # 检查关键节
    $sections = @('[Setup]','[Languages]','[Tasks]','[Files]','[Icons]','[Run]','[Code]')
    foreach ($sec in $sections) {
        if ($issContent -notmatch [regex]::Escape($sec)) {
            $errors += "[ISS WARNING] setup.iss - 缺少节: $sec"
        }
    }
    if ($errors.Count -eq 0 -or ($errors.Count -gt 0 -and ($errors | Where-Object {$_ -like '*setup.iss*'}).Count -eq 0)) {
        Write-Host "[OK] setup.iss - 基本结构完整" -ForegroundColor Green
    }
}

Write-Host ""

if ($errors.Count -gt 0) {
    Write-Host "发现 $($errors.Count) 个问题:" -ForegroundColor Yellow
    foreach ($err in $errors) {
        Write-Host "  $err" -ForegroundColor Red
    }
    exit 1
} else {
    Write-Host "✅ 所有文件语法验证通过！" -ForegroundColor Green
    exit 0
}
