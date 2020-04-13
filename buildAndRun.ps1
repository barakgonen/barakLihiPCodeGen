param([string]$command = $Args[0], [Int32]$number = $Args[1])

Function Pcode_Exe {
    &$exe -$command $input_file_path | Out-File -Encoding utf8 $output_file_path
    gcc -w -o $test_program_name $input_file_path
    $sample_number | Out-File -Encoding utf8 $sample_number_file
    .\output\test_program.exe | Out-File -Encoding utf8 $test_program_output_path
    node .\code\bla.js
}

clear
$sample_number = ""
$input_file_path = "Input_Files\sample$number.c"
$program_name = "output/compiler"
$gcc_path = "C:\MinGW\bin\gcc.exe"
$compiler_files = "compiler_files/"
$output_file_path = "$pwd//output/generated_pcode.txt"
$test_program_name = "$pwd//output/test_program"
$test_program_output_path = "$pwd//output/test_program_output.txt"
$sample_number_file = "$pwd//output/sample_number.txt"

&$gcc_path -w -o $program_name $compiler_files*.c
$exe = "$pwd/$program_name.exe"

if ($command -eq "Pcode")
{
    Write-Host "About To Execute Command:", $command
    Write-Host "Running on the following sample: "$input_file_path
    Pcode_Exe

}
elseif ($command -ne "") {
    Write-Host "About To Execute Command:", $command
    Write-Host "Running on the following sample: "$input_file_path
    &$exe -$command $input_file_path
}

Write-Host "Running sanity for all possible input files in the project"
$command = "Pcode"
for ($i =1 ; $i -le (Get-ChildItem -Filter *sample*.c -Recurse -File).Count; $i++)
{
    $input_file_path = "Input_Files\sample$i.c"
    $sample_number = $i
    Pcode_Exe
}
