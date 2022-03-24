# cmake 最低版本
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
# 声明项目名称
project(t LANGUAGES C)
# 增加可执行文件
add_executable(tool tool.c)

