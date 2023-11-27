# CMakeList.txt: member_manage_system 的 CMake 项目
#
cmake_minimum_required (VERSION 3.28.0)


project ("member_manage_system")

#“自定义头文件”的路径
include_directories("${PROJECT_SOURCE_DIR}/include")


#将src下的cpp源文件添加到变量中方便引用
aux_source_directory("${PROJECT_SOURCE_DIR}/src" mySources)

# 将源代码添加到此项目的可执行文件。
add_executable (member_manage_system ${mySources})

#编译转码成GBK可执行文件，方便在Windows测试
target_compile_options(member_manage_system PRIVATE -fexec-charset=GBK)

#目标执行文件生成在项目目录下的bin目录
set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/bin")

