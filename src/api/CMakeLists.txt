# src/api/CMakeLists.txt
# CMake конфігурація для модуля API
# CMake configuration for API module
# CMake конфігурація для модуля API

# Створення бібліотеки api
# Creating api library
# Створення бібліотеки api
add_library(api
    ${CMAKE_CURRENT_SOURCE_DIR}/NeuroAPI.cpp
)

# Встановлення залежностей
# Setting dependencies
# Встановлення залежностей
target_link_libraries(api 
    core
    neuron
    synapse
    memory
    diagnostics
)

# Встановлення заголовочних файлів
# Installing header files
# Встановлення заголовочних файлів
target_include_directories(api PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})