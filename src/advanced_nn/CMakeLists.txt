# src/advanced_nn/CMakeLists.txt
# CMake конфігурація для модуля розширених нейронних мереж
# CMake configuration for advanced neural networks module
# CMake конфигурация для модуля расширенных нейронных сетей

# Створення бібліотеки advanced_nn
# Creating advanced_nn library
# Создание библиотеки advanced_nn
add_library(advanced_nn
    AdvancedNeuralNetworks.cpp
)

# Встановлення залежностей
# Setting dependencies
# Установка зависимостей
target_link_libraries(advanced_nn 
    neural_network
)

# Встановлення заголовочних файлів
# Installing header files
# Установка заголовочных файлов
target_include_directories(advanced_nn PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../network_neural
)