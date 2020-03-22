param([string]$command=$Args[0], [Int32]$number=$Args[1])
clear
$input_file_path="..\Input_Files\sample$number.c"
$program_name="compiler"
$gcc_path="C:\MinGW\bin\gcc.exe"

Write-Host "About To Execute Command:", $command
Write-Host "Running on the following sample: "$input_file_path
&$gcc_path -o $program_name $(Get-ChildItem -Path . *.c -name)
$exe="$pwd/$program_name.exe"
&$exe -$command $input_file_path