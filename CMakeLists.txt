cmake_minimum_required(VERSION 3.16)
project(untitled C)

set(CMAKE_C_STANDARD 11)
FILE(GLOB SRCFILES compiler_files/*.c)
ADD_EXECUTABLE(compiler ${SRCFILES})