param([Int32]$number=1)
clear
C:\MinGW\bin\gcc.exe -o compiler .\ctree.c .\heap.c .\nmetab.c .\prnttree.c .\symtab.c .\token.c .\tree.c .\dsm_extension.c .\treestk.c .\lexer.c .\gram.c .\CodeGenerator.c
.\compiler.exe -AST ..\Input_Files\sample$number.c