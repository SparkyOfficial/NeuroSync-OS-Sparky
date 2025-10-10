# src/core/CMakeLists.txt
# CMake конфігурація для модуля Core
# CMake configuration for Core module
# CMake конфігурація для модуля Core

# Створення бібліотеки core
# Creating core library
# Створення бібліотеки core
add_library(core
    ${CMAKE_CURRENT_SOURCE_DIR}/Scheduler.cpp
)

# Встановлення заголовочних файлів
# Installing header files
# Встановлення заголовочних файлів
target_include_directories(core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})