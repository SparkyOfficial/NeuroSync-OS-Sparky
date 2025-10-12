# CMakeLists.txt for Database module
# Модуль бази даних
# Модуль базы данных

# Додавання бібліотеки бази даних
# Add database library
# Добавление библиотеки базы данных
add_library(db
    DatabaseInterface.cpp
)

# Встановлення властивостей бібліотеки
# Set library properties
# Установка свойств библиотеки
set_target_properties(db PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

# Встановлення заголовків для встановлення
# Set headers for installation
# Установка заголовков для установки
target_include_directories(db PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Встановлення залежностей
# Set dependencies
# Установка зависимостей
target_link_libraries(db PUBLIC
    neuron
    network_neural
)

# Встановлення бібліотеки
# Install library
# Установка библиотеки
install(TARGETS db
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
)

# Встановлення заголовків
# Install headers
# Установка заголовков
install(FILES 
    DatabaseInterface.h
    DESTINATION include/db
)

# Додавання тесту
# Add test
# Добавление теста
if(BUILD_TESTS)
    add_executable(test_db
        test_db.cpp
    )
    
    target_link_libraries(test_db
        db
        neuron
        network_neural
    )
    
    install(TARGETS test_db
        RUNTIME DESTINATION bin
    )
endif()