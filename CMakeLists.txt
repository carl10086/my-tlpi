cmake_minimum_required(VERSION 3.17)
project(hello C)

set(CMAKE_C_STANDARD 99)

add_executable(t_mmap ./mmap/t_mmap.c lib/tlpi_hdr.h lib/error_functions.h lib/error_functions.c procexec/t_fork.c)
add_executable(t_fork ./procexec/t_fork.c lib/tlpi_hdr.h lib/error_functions.h lib/error_functions.c procexec/t_fork.c)
