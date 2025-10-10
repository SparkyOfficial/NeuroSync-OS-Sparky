# src/diagnostics\CMakeLists.txt
# CMake конфігурація для модуля Diagnostics
# CMake configuration for Diagnostics module
# CMake конфігурація для модуля Diagnostics

# Створення бібліотеки diagnostics
# Creating diagnostics library
# Створення бібліотеки diagnostics
add_library(diagnostics
    ${CMAKE_CURRENT_SOURCE_DIR}/Diagnostics.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Profiler.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Visualizer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/PerformanceMonitor.cpp
)

# Встановлення залежностей
# Setting dependencies
# Встановлення залежностей
target_link_libraries(diagnostics core)

# Встановлення заголовочних файлів
# Installing header files
# Встановлення заголовочних файлів
target_include_directories(diagnostics PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})