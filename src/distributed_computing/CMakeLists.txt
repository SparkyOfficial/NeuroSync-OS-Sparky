# CMakeLists.txt for distributed_computing module
# CMakeLists.txt для модуля distributed_computing
# CMakeLists.txt для модуля distributed_computing

# Add library for distributed_computing
# Додавання бібліотеки для distributed_computing
# Добавление библиотеки для distributed_computing
add_library(distributed_computing
    DistributedManager.cpp
)

# Set include directories
# Встановлення каталогів включення
# Установка каталогов включения
target_include_directories(distributed_computing
    PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../network
        ${CMAKE_CURRENT_SOURCE_DIR}/../core
        ${CMAKE_CURRENT_SOURCE_DIR}/../threadpool
        ${CMAKE_CURRENT_SOURCE_DIR}/../security
)

# Link libraries
# Зв'язування бібліотек
# Связывание библиотек
target_link_libraries(distributed_computing
    PUBLIC
        network
        core
        threadpool
        security
)

# Set compile features
# Встановлення функцій компіляції
# Установка функций компиляции
target_compile_features(distributed_computing PUBLIC cxx_std_14)