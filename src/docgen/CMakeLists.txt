# CMakeLists.txt for Documentation Generator
# Генератор документації для NeuroSync OS Sparky
# Documentation generator for NeuroSync OS Sparky
# Генератор документации для NeuroSync OS Sparky

# Create the documentation generator library
# Створення бібліотеки генератора документації
# Создание библиотеки генератора документации
add_library(docgen
    DocumentationGenerator.cpp
)

# Specify include directories
# Визначення каталогів включення
# Определение каталогов включения
target_include_directories(docgen
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

# Link required libraries
# Підключення необхідних бібліотек
# Подключение необходимых библиотек
if(MSVC)
    # MSVC has filesystem support built-in
    target_link_libraries(docgen PUBLIC)
else()
    # GCC/Clang need explicit linking
    target_link_libraries(docgen PUBLIC stdc++fs)
endif()

# Compiler features
# Особливості компілятора
# Особенности компилятора
target_compile_features(docgen
    PUBLIC
        cxx_std_14
)

# Compiler flags
# Прапорці компілятора
# Флаги компилятора
if(MSVC)
    # Use MSVC-specific flags
    target_compile_options(docgen PRIVATE /W4)
else()
    # Use GCC/Clang flags
    target_compile_options(docgen PRIVATE -Wall -Wextra -pedantic)
endif()

# Create example executable
# Створення прикладу
# Создание примера
add_executable(docgen_example
    ../../src/examples/docgen_example.cpp
)

# Link documentation generator to example
# Підключення генератора документації до прикладу
# Подключение генератора документации к примеру
target_link_libraries(docgen_example
    PRIVATE
        docgen
)

# Create test executable
# Створення тесту
# Создание теста
add_executable(test_docgen
    ../../src/tests/test_docgen.cpp
)

# Link documentation generator to test
# Підключення генератора документації до тесту
# Подключение генератора документации к тесту
target_link_libraries(test_docgen
    PRIVATE
        docgen
)

# Add tests to CTest
# Додавання тестів до CTest
# Добавление тестов в CTest
enable_testing()
add_test(NAME test_docgen COMMAND test_docgen)