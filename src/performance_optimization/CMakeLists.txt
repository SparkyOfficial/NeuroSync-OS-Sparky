# CMakeLists.txt for performance_optimization module
# CMakeLists.txt для модуля performance_optimization
# CMakeLists.txt для модуля performance_optimization

# Add library for performance_optimization
# Додавання бібліотеки для performance_optimization
# Добавление библиотеки для performance_optimization
add_library(performance_optimization
    PerformanceOptimizer.cpp
)

# Set include directories
# Встановлення каталогів включення
# Установка каталогов включения
target_include_directories(performance_optimization
    PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../core
        ${CMAKE_CURRENT_SOURCE_DIR}/../threadpool
        ${CMAKE_CURRENT_SOURCE_DIR}/../memory
        ${CMAKE_CURRENT_SOURCE_DIR}/../diagnostics
)

# Link libraries
# Зв'язування бібліотек
# Связывание библиотек
target_link_libraries(performance_optimization
    PUBLIC
        core
        threadpool
        memory
        diagnostics
)

# Set compile features
# Встановлення функцій компіляції
# Установка функций компиляции
target_compile_features(performance_optimization PUBLIC cxx_std_14)