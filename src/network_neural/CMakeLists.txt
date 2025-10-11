# src/network_neural/CMakeLists.txt
# CMake конфігурація для модуля Neural Network
# CMake configuration for Neural Network module
# CMake конфігурація для модуля Neural Network

# Створення бібліотеки neural_network
# Creating neural_network library
# Створення бібліотеки neural_network
add_library(neural_network
    ${CMAKE_CURRENT_SOURCE_DIR}/NeuralNetwork.cpp
)

# Встановлення залежностей
# Setting dependencies
# Встановлення залежностей
target_link_libraries(neural_network 
    neuron
    synapse
)

# Встановлення заголовочних файлів
# Installing header files
# Встановлення заголовочних файлів
target_include_directories(neural_network PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})