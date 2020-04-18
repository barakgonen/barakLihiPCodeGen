param([string]$command = $Args[0], [string]$Input_File_Path = $Args[1])

Function Pcode_Exe {
    &$exe -$command $Input_File_Path | Out-File -Encoding utf8 $output_file_path
    if ($should_use_modified -eq "true"){
        gcc -w -o $test_program_name $modifided_input_file
    }
    else {
        gcc -w -o $test_program_name $Input_File_Path
    }
    .\output\test_program.exe | Out-File -Encoding utf8 $test_program_output_path
    $sample_number | Out-File -Encoding utf8 $sample_number_file
    node .\code\bla.js
}

Function Run_Sanity_On_HW_1 {
    Get-ChildItem "Input_Files/HW1" -Filter *.c -Recurse | Sort-Object | Foreach-Object {
        $content = $_.FullName
        $Input_File_Path = $content
        $sample_number=$content.Split('\', 8)[7]
        $command = "Pcode"
        Pcode_Exe
    }
}

Function Run_Sanity_On_HW_2 {
    Get-ChildItem "Input_Files/HW2" -Filter *.c -Recurse | Sort-Object | Foreach-Object {
        if ($_ -match "MOD") { 
        }
        else{
            $content = $_.FullName
            $Input_File_Path = $content
            $sample_number=$content.Split('\', 8)[7]
            $n = $sample_number.Split('\',3)[2] -replace '\D+(\d+)','$1'.Split('.')[0]
            if ($n -eq "02.c")
            {
                $should_use_modified = "true"
                $modifided_input_file = "Input_Files/HW2/sample02MOD.c"
            }
            elseif ($n -eq "05.c")
            {
                $should_use_modified = "true"
                $modifided_input_file = "Input_Files/HW2/sample05MOD.c"
            }
            elseif ($n -eq "06.c")
            {
                $should_use_modified = "true"
                $modifided_input_file = "Input_Files/HW2/sample06MOD.c"
            }
            elseif ($n -eq "09.c")
            {
                $should_use_modified = "true"
                $modifided_input_file = "Input_Files/HW2/sample09MOD.c"
            }
            $command = "Pcode"
            Pcode_Exe
            $should_use_modified = "false";
            $modifided_input_file = "";
        }
        
    }
}

Function Run_Sanity_On_HW_3 {
    Get-ChildItem "Input_Files/HW3" -Filter *.c -Recurse | Sort-Object | Foreach-Object {
        $content = $_.FullName
        $Input_File_Path = $content
        $sample_number=$content.Split('\', 8)[7]
        $command = "Pcode"
        Pcode_Exe
    }
}
$path = "$pwd//output/"

If (!(test-path $path))
{
    md $path
}

clear
$sample_number = ""
$program_name = "output/compiler"
$gcc_path = "C:\MinGW\bin\gcc.exe"
$compiler_files = "compiler_files/"
$output_file_path = "$pwd//output/generated_pcode.txt"
$test_program_name = "$pwd//output/test_program"
$test_program_output_path = "$pwd//output/test_program_output.txt"
$sample_number_file = "$pwd//output/sample_number.txt"
$modifided_input_file = ""

&$gcc_path -w -o $program_name $compiler_files*.c
$exe = "$pwd/$program_name.exe"

if ($command -eq "HW1"){
    Run_Sanity_On_HW_1
    exit
}
elseif($command -eq "HW2"){
    Run_Sanity_On_HW_2
    exit
}
elseif($command -eq "HW3"){
    Run_Sanity_On_HW_3
    exit
}
elseif ($command -eq "Pcode")
{
    Write-Host "About To Execute Command:", $command
    Write-Host "Running on the following sample: "$Input_File_Path
    &$exe -$command $Input_File_Path
    exit
    $sample_number=$Input_File_Path
    Pcode_Exe
}
elseif ($command -ne "") {
    Write-Host "About To Execute Command:", $command
    Write-Host "Running on the following sample: "$Input_File_Path
    &$exe -$command $Input_File_Path
}

Write-Host "Running sanity for all possible input files in the project"
Run_Sanity_On_HW_1
Run_Sanity_On_HW_2
Run_Sanity_On_HW_3