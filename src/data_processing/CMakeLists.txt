# CMakeLists.txt for data_processing module
# CMakeLists.txt для модуля data_processing
# CMakeLists.txt для модуля data_processing

# Add library for data_processing
# Додавання бібліотеки для data_processing
# Добавление библиотеки для data_processing
add_library(data_processing
    DataProcessor.cpp
)

# Set include directories
# Встановлення каталогів включення
# Установка каталогов включения
target_include_directories(data_processing
    PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}
)

# Set compile features
# Встановлення функцій компіляції
# Установка функций компиляции
target_compile_features(data_processing PUBLIC cxx_std_14)