
cmake_minimum_required(VERSION 3.15)
project(copy)

# 项目信息↑

# 定义输出路径变量
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/.bin)

# 设置C++标准


add_executable(main main.cpp)
