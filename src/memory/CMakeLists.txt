# src/memory/CMakeLists.txt
# CMake конфігурація для модуля Memory
# CMake configuration for Memory module
# CMake конфігурація для модуля Memory

# Створення бібліотеки memory
# Creating memory library
# Створення бібліотеки memory
add_library(memory
    ${CMAKE_CURRENT_SOURCE_DIR}/MemoryCore.cpp
)

# Встановлення заголовочних файлів
# Installing header files
# Встановлення заголовочних файлів
target_include_directories(memory PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})