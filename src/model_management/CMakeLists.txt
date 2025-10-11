# src/model_management/CMakeLists.txt
# CMake конфігурація для модуля управління моделями
# CMake configuration for model management module
# CMake конфигурация для модуля управления моделями

# Створення бібліотеки model_management
# Creating model_management library
# Создание библиотеки model_management
add_library(model_management
    ModelManager.cpp
)

# Встановлення залежностей
# Setting dependencies
# Установка зависимостей
target_link_libraries(model_management 
    neural_network
)

# Встановлення заголовочних файлів
# Installing header files
# Установка заголовочных файлов
target_include_directories(model_management PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../network_neural
)