# src/neuron/CMakeLists.txt
# CMake конфігурація для модуля Neuron
# CMake configuration for Neuron module
# CMake конфігурація для модуля Neuron

# Створення бібліотеки neuron
# Creating neuron library
# Створення бібліотеки neuron
add_library(neuron
    ${CMAKE_CURRENT_SOURCE_DIR}/NeuronManager.cpp
)

# Встановлення залежностей
# Setting dependencies
# Встановлення залежностей
target_link_libraries(neuron core)

# Встановлення заголовочних файлів
# Installing header files
# Встановлення заголовочних файлів
target_include_directories(neuron PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})