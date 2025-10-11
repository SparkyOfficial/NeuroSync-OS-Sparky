# src/ml_pipeline/CMakeLists.txt
# CMake конфігурація для модуля конвеєра машинного навчання
# CMake configuration for machine learning pipeline module
# CMake конфигурация для модуля конвейера машинного обучения

# Створення бібліотеки ml_pipeline
# Creating ml_pipeline library
# Создание библиотеки ml_pipeline
add_library(ml_pipeline
    MLPipeline.cpp
)

# Встановлення залежностей
# Setting dependencies
# Установка зависимостей
target_link_libraries(ml_pipeline 
    neural_network
    data_processing
    model_management
)

# Встановлення заголовочних файлів
# Installing header files
# Установка заголовочных файлов
target_include_directories(ml_pipeline PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../network_neural
    ${CMAKE_CURRENT_SOURCE_DIR}/../data_processing
    ${CMAKE_CURRENT_SOURCE_DIR}/../model_management
)