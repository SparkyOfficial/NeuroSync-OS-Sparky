# CMakeLists.txt for Database Interface module
# Модуль інтерфейсу бази даних
# Модуль интерфейса базы данных

# Додавання бібліотеки інтерфейсу бази даних
# Add database interface library
# Добавление библиотеки интерфейса базы данных
add_library(database
    DatabaseInterface.cpp
)

# Встановлення властивостей бібліотеки
# Set library properties
# Установка свойств библиотеки
set_target_properties(database PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

# Встановлення заголовків для встановлення
# Set headers for installation
# Установка заголовков для установки
target_include_directories(database PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Встановлення залежностей
# Set dependencies
# Установка зависимостей
target_link_libraries(database PUBLIC
    neuron
    synapse
)

# Встановлення бібліотеки
# Install library
# Установка библиотеки
install(TARGETS database
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
)

# Встановлення заголовків
# Install headers
# Установка заголовков
install(FILES 
    DatabaseInterface.h
    DESTINATION include/database
)

# Додавання прикладів, якщо вони ввімкнені
# Add examples if enabled
# Добавление примеров, если они включены
if(BUILD_EXAMPLES)
    add_executable(database_example
        ../examples/database_example.cpp
    )
    
    target_link_libraries(database_example
        database
        neuron
        synapse
    )
    
    install(TARGETS database_example
        RUNTIME DESTINATION bin
    )
endif()

# Додавання тестів, якщо вони ввімкнені
# Add tests if enabled
# Добавление тестов, если они включены
if(BUILD_TESTS)
    add_executable(test_database
        ../tests/test_database.cpp
    )
    
    target_link_libraries(test_database
        database
        neuron
        synapse
    )
    
    install(TARGETS test_database
        RUNTIME DESTINATION bin
    )
endif()