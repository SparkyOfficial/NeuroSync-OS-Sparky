# CMakeLists.txt for analytics module
# CMakeLists.txt для модуля analytics
# CMakeLists.txt для модуля analytics

# Add library for analytics
# Додавання бібліотеки для analytics
# Добавление библиотеки для analytics
add_library(analytics
    RealTimeAnalytics.cpp
)

# Set include directories
# Встановлення каталогів включення
# Установка каталогов включения
target_include_directories(analytics
    PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../diagnostics
        ${CMAKE_CURRENT_SOURCE_DIR}/../core
        ${CMAKE_CURRENT_SOURCE_DIR}/../memory
        ${CMAKE_CURRENT_SOURCE_DIR}/../logging
)

# Link libraries
# Зв'язування бібліотек
# Связывание библиотек
target_link_libraries(analytics
    PUBLIC
        diagnostics
        core
        memory
        logging
)

# Set compile features
# Встановлення функцій компіляції
# Установка функций компиляции
target_compile_features(analytics PUBLIC cxx_std_14)