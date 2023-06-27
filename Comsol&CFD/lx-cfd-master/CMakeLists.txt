# CMakeList.txt: 顶层 CMake 项目文件，在此处执行全局配置
# 并包含子项目。
#
cmake_minimum_required (VERSION 3.8)

project("LxProj")

set(CMAKE_CXX_STANDARD 20)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/Out)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/Out)


if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set(ReleaseMode off)
    if(ReleaseMode)
        set(CMAKE_BUILD_TYPE "Release")
    else()
        set(CMAKE_BUILD_TYPE "Debug")
    endif()
    message("Build Types;${CMAKE_BUILD_TYPE}")
    SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
    SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")
endif()


function(include_sub_directories_recursively targetProj rootDir)
    if (IS_DIRECTORY ${rootDir})               # 当前路径是一个目录吗，是的话就加入到包含目录
        #message("Project:"${targetProj}" include dir: " ${rootDir})
        target_include_directories(${targetProj} PUBLIC ${rootDir})
        file(GLOB ALL_SUB RELATIVE ${rootDir} ${rootDir}/*) # 获得当前目录下的所有文件，让如ALL_SUB列表中
        foreach(sub ${ALL_SUB})
            include_sub_directories_recursively(${targetProj} ${rootDir}/${sub}) # 对子目录递归调用，包含
        endforeach()
    endif()
endfunction()
# 包含子项目。
add_subdirectory ("LxProj")

