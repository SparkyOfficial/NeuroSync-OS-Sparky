# src/quantum/CMakeLists.txt
# CMake конфігурація для модуля квантових обчислень
# CMake configuration for quantum computing module
# CMake конфигурация для модуля квантовых вычислений

# Створення бібліотеки quantum
# Creating quantum library
# Создание библиотеки quantum
add_library(quantum
    QuantumComputing.cpp
)

# Встановлення залежностей
# Setting dependencies
# Установка зависимостей
target_link_libraries(quantum 
)

# Встановлення заголовочних файлів
# Installing header files
# Установка заголовочных файлов
target_include_directories(quantum PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
)