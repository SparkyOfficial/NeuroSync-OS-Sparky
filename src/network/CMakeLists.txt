# src/network/CMakeLists.txt
# CMake конфігурація для модуля Network
# CMake configuration for Network module
# CMake конфігурація для модуля Network

# Створення бібліотеки network
# Creating network library
# Створення бібліотеки network
add_library(network
    ${CMAKE_CURRENT_SOURCE_DIR}/NeuralNetwork.cpp
)

# Встановлення залежностей
# Setting dependencies
# Встановлення залежностей
target_link_libraries(network 
    core
    neuron
    synapse
    memory
    diagnostics
)

# Встановлення заголовочних файлів
# Installing header files
# Встановлення заголовочних файлів
target_include_directories(network PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})