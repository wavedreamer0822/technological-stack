# CMakeList.txt: LxProj 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)

file(GLOB_RECURSE LxCodeUISrc ${PROJECT_SOURCE_DIR}/LxProj/*.cpp)
add_executable(LxCodeUI ${LxCodeUISrc})

include_sub_directories_recursively(LxCodeUI ${PROJECT_SOURCE_DIR}/LxProj) 


