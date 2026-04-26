# lg.ps1 - 洛谷题目快速测试脚本
param(
    [Parameter(Position=0)]
    [string]$FileName,
    
    [Parameter(Position=1)]
    [string]$InputFile = "input.in",
    
    [Parameter(Position=2)]
    [string]$OutputFile = "output.out"
)

if (-not $FileName) {
    $cppFiles = Get-ChildItem -Filter "*.cpp" | Select-Object -First 1
    if ($cppFiles) {
        $FileName = $cppFiles.BaseName
        Write-Host "Auto-detected file: $FileName" -ForegroundColor Yellow
    } else {
        Write-Host "Error: No C++ file found and no filename provided." -ForegroundColor Red
        Write-Host "Usage: .\lg.ps1 <filename> [input_file] [output_file]" -ForegroundColor Cyan
        Write-Host "Example: .\lg.ps1 luogu_P2756_pilot-pairing-problem" -ForegroundColor Cyan
        exit 1
    }
}

$sourceFile = "${FileName}.cpp"
$executable = "${FileName}.exe"
$inputPath = $InputFile
$outputPath = $OutputFile

if (-not (Test-Path $sourceFile)) {
    Write-Host "Error: Source file '$sourceFile' not found!" -ForegroundColor Red
    exit 1
}

$hasInput = $false
if (Test-Path $inputPath) {
    $inputContent = Get-Content $inputPath -Raw
    if (-not [string]::IsNullOrWhiteSpace($inputContent)) {
        $hasInput = $true
        Write-Host "Input file found: $inputPath" -ForegroundColor Green
    } else {
        Write-Host "Warning: Input file '$inputPath' is empty." -ForegroundColor Yellow
        Write-Host "Please add test input to the file." -ForegroundColor Cyan
    }
} else {
    Write-Host "Input file '$inputPath' not found. Creating empty file..." -ForegroundColor Yellow
    New-Item -Path $inputPath -ItemType File -Force | Out-Null
    Write-Host "Created empty input file: $inputPath" -ForegroundColor Green
    Write-Host "Please add test input to the file before running." -ForegroundColor Cyan
}

if (Test-Path $outputPath) {
    $outputContent = Get-Content $outputPath -Raw
    if (-not [string]::IsNullOrWhiteSpace($outputContent)) {
        Write-Host "Output file found: $outputPath" -ForegroundColor Green
    } else {
        Write-Host "Output file '$outputPath' is empty." -ForegroundColor Yellow
    }
} else {
    Write-Host "Output file '$outputPath' not found. Creating empty file..." -ForegroundColor Yellow
    New-Item -Path $outputPath -ItemType File -Force | Out-Null
    Write-Host "Created empty output file: $outputPath" -ForegroundColor Green
}

if (-not $hasInput) {
    Write-Host "`nNo input data available. Please add test input to '$inputPath' and run again." -ForegroundColor Red
    exit 0
}

Write-Host "`nCompiling $sourceFile ..." -ForegroundColor Cyan
g++ $sourceFile -o $executable

if ($LASTEXITCODE -ne 0) {
    Write-Host "Compilation failed!" -ForegroundColor Red
    exit $LASTEXITCODE
}
Write-Host "Compilation successful!" -ForegroundColor Green

Write-Host "`nRunning $executable ..." -ForegroundColor Cyan
Write-Host "----------------------------------------" -ForegroundColor Gray

$programOutput = Get-Content $inputPath | & ".\$executable" | Out-String

Write-Host $programOutput
Write-Host "----------------------------------------" -ForegroundColor Gray

$shouldCompare = $false
$expectedOutput = $null

if (Test-Path $outputPath) {
    $expectedOutput = Get-Content $outputPath -Raw
    if (-not [string]::IsNullOrWhiteSpace($expectedOutput)) {
        $shouldCompare = $true
        Write-Host "`nComparing with expected output..." -ForegroundColor Cyan
    } else {
        Write-Host "`nOutput file '$outputPath' is empty, skipping comparison." -ForegroundColor Yellow
    }
}

if ($shouldCompare) {
    $actualOutput = $programOutput.Trim()
    $expectedOutput = $expectedOutput.Trim()
    
    if ($actualOutput -eq $expectedOutput) {
        Write-Host "✓ Output matches expected result!" -ForegroundColor Green
    } else {
        Write-Host "✗ Output differs from expected result!" -ForegroundColor Red
        Write-Host "`n【Expected】" -ForegroundColor Yellow
        Write-Host $expectedOutput
        Write-Host "`n【Actual】" -ForegroundColor Yellow
        Write-Host $actualOutput
    }
} else {
    Write-Host "`n【Program Output】" -ForegroundColor Cyan
    Write-Host $programOutput
}

Write-Host "`nDelete executable? (y/N): " -ForegroundColor Cyan -NoNewline
$response = Read-Host
if ($response -eq 'y' -or $response -eq 'Y') {
    Remove-Item $executable
    Write-Host "Deleted $executable" -ForegroundColor Green
}

Write-Host "`nDone!" -ForegroundColor Green