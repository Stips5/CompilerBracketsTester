cmake_minimum_required(VERSION 3.6)
project(CompilerBracketsTester)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.c bracketTypes.h functionDefines.h structDefines.h)
add_executable(CompilerBracketsTester ${SOURCE_FILES})