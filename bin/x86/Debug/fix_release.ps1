<#
.SYNOPSIS
    Fix GitHub Release CX900.zip asset
.DESCRIPTION
    Replace corrupted release asset with correct CX900_Setup.zip
#>
$ErrorActionPreference = 'Stop'
Write-Host '>>> Getting GitHub Token...' -ForegroundColor Cyan
$credInput = "protocol=https
host=github.com
"
$result = ($credInput | & git credential fill) 2>$null
$token = ""
foreach ($line in $result) {
    if ($line -match '^password=(.+)$') { $token = $matches[1] }
}
if (-not $token) {
    Write-Error 'Failed to get GitHub Token!'
    exit 1
}
$owner = 'yuguo1983'
$repo = 'CX900_GCC_OFF_V1.1'
$tag = 'v1.1.0'
$headers = @{ Authorization = "Bearer $token" }
Write-Host '>>> Getting Release info...' -ForegroundColor Cyan
$release = Invoke-RestMethod -Uri "https://api.github.com/repos/$owner/$repo/releases/tags/$tag" -Headers $headers
Write-Host "  Release ID: $($release.id)" -ForegroundColor Gray
$oldAsset = $release.assets | Where-Object { $_.name -eq 'CX900.zip' }
if ($oldAsset) {
    Write-Host '>>> Deleting corrupted asset...' -ForegroundColor Yellow
    Invoke-RestMethod -Uri "https://api.github.com/repos/$owner/$repo/releases/assets/$($oldAsset.id)" -Headers $headers -Method Delete
    Write-Host "  Deleted asset (ID: $($oldAsset.id))" -ForegroundColor Green
}
$zipPath = Join-Path $PSScriptRoot 'CX900_Setup.zip'
if (-not (Test-Path $zipPath)) {
    Write-Error "File not found: $zipPath"
    exit 1
}
$zipBytes = [System.IO.File]::ReadAllBytes($zipPath)
$zipSize = [math]::Round($zipBytes.Count / 1MB, 2)
Write-Host "  Local zip: ${zipSize}MB" -ForegroundColor Gray
Write-Host '>>> Uploading correct zip...' -ForegroundColor Cyan
$uploadUrl = "https://uploads.github.com/repos/$owner/$repo/releases/$($release.id)/assets?name=CX900.zip"
$uploadHeaders = @{
    Authorization = "Bearer $token"
    'Content-Type' = 'application/zip'
}
$result = Invoke-RestMethod -Uri $uploadUrl -Headers $uploadHeaders -Method Post -Body $zipBytes
Write-Host ''
Write-Host '============================================' -ForegroundColor Green
Write-Host '  Release fixed successfully!' -ForegroundColor Green
Write-Host "  Download URL: $($result.browser_download_url)" -ForegroundColor White
Write-Host '============================================' -ForegroundColor Green
Write-Host ''
Write-Host 'Now run the remote install command:' -ForegroundColor Cyan
Write-Host "  irm https://raw.githubusercontent.com/yuguo1983/CX900_GCC_OFF_V1.1/v1.1.0/install.ps1 | iex" -ForegroundColor White