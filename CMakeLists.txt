cmake_minimum_required(VERSION 3.28)
project(Algo LANGUAGES C CXX)

# 启用编译命令导出（供clangd使用）
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 设置C++和C标准
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 禁用C++20模块支持（避免clangd错误）
set(CMAKE_CXX_SCAN_FOR_MODULES OFF)

# 为clangd添加所有源文件（不实际构建，仅用于生成compile_commands.json）
file(GLOB_RECURSE ALL_SOURCES
    "leetcode/*.cpp"
    "luogu/*.cpp" 
    "codeforces/*.cpp"
    "utils/*.cpp"
    "templates/*.cpp"
)

# 为每个源文件创建一个虚拟目标（仅用于clangd索引）
foreach(source_file ${ALL_SOURCES})
    get_filename_component(target_name ${source_file} NAME_WE)
    add_executable(${target_name}_dummy ${source_file})
endforeach()