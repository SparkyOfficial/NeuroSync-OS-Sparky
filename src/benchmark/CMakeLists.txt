# CMakeLists.txt for Benchmark Suite
# Набір тестів продуктивності для NeuroSync OS Sparky
# Benchmark suite for NeuroSync OS Sparky
# Набор тестов производительности для NeuroSync OS Sparky

# Create the benchmark library
# Створення бібліотеки тестів продуктивності
# Создание библиотеки тестов производительности
add_library(benchmark_suite
    BenchmarkSuite.cpp
)

# Specify include directories
# Визначення каталогів включення
# Определение каталогов включения
target_include_directories(benchmark_suite
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

# Link required libraries
# Підключення необхідних бібліотек
# Подключение необходимых библиотек
if(WIN32)
    # Windows doesn't need explicit pthread linking
    target_link_libraries(benchmark_suite
        PUBLIC
    )
else()
    # Unix systems need pthread
    target_link_libraries(benchmark_suite
        PUBLIC
            pthread
    )
endif()

# Compiler features
# Особливості компілятора
# Особенности компилятора
target_compile_features(benchmark_suite
    PUBLIC
        cxx_std_14
)

# Create example executable
# Створення прикладу
# Создание примера
add_executable(benchmark_example
    ../../src/examples/benchmark_example.cpp
)

# Link benchmark suite to example
# Підключення набору тестів продуктивності до прикладу
# Подключение набора тестов производительности к примеру
target_link_libraries(benchmark_example
    PRIVATE
        benchmark_suite
)

# Create test executable
# Створення тесту
# Создание теста
add_executable(test_benchmark_suite
    ../../src/tests/test_benchmark_suite.cpp
)

# Link benchmark suite to test
# Підключення набору тестів продуктивності до тесту
# Подключение набора тестов производительности к тесту
target_link_libraries(test_benchmark_suite
    PRIVATE
        benchmark_suite
)

# Add tests to CTest
# Додавання тестів до CTest
# Добавление тестов в CTest
enable_testing()
add_test(NAME test_benchmark_suite COMMAND test_benchmark_suite)