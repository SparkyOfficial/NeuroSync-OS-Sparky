# src/neuron/CMakeLists.txt
# CMake конфігурація для модуля Neuron
# CMake configuration for Neuron module
# CMake конфігурація для модуля Neuron

# Створення бібліотеки neuron
# Creating neuron library
# Створення бібліотеки neuron
add_library(neuron
    ${CMAKE_CURRENT_SOURCE_DIR}/NeuronManager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/models/NeuronModel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/lifecycle/NeuronLifecycleManager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/utils/NeuronUtils.cpp
)

# Встановлення залежностей
# Setting dependencies
# Встановлення залежностей
target_link_libraries(neuron core)

# Встановлення заголовочних файлів
# Installing header files
# Встановлення заголовочних файлів
target_include_directories(neuron PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/models
    ${CMAKE_CURRENT_SOURCE_DIR}/lifecycle
    ${CMAKE_CURRENT_SOURCE_DIR}/utils
)