# CMakeLists.txt for Advanced Analytics module
# Модуль розширеної аналітики
# Модуль расширенной аналитики

# Додавання бібліотеки розширеної аналітики
# Add advanced analytics library
# Добавление библиотеки расширенной аналитики
add_library(advanced_analytics
    AdvancedAnalytics.cpp
)

# Встановлення властивостей бібліотеки
# Set library properties
# Установка свойств библиотеки
set_target_properties(advanced_analytics PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

# Встановлення заголовків для встановлення
# Set headers for installation
# Установка заголовков для установки
target_include_directories(advanced_analytics PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Встановлення залежностей
# Set dependencies
# Установка зависимостей
target_link_libraries(advanced_analytics PUBLIC
    neuron
    neural_network
)

# Встановлення бібліотеки
# Install library
# Установка библиотеки
install(TARGETS advanced_analytics
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
)

# Встановлення заголовків
# Install headers
# Установка заголовков
install(FILES 
    AdvancedAnalytics.h
    DESTINATION include/advanced_analytics
)

# Додавання прикладів, якщо вони ввімкнені
# Add examples if enabled
# Добавление примеров, если они включены
if(BUILD_EXAMPLES)
    add_executable(advanced_analytics_example
        ../examples/advanced_analytics_example.cpp
    )
    
    target_link_libraries(advanced_analytics_example
        advanced_analytics
        neuron
        neural_network
    )
    
    install(TARGETS advanced_analytics_example
        RUNTIME DESTINATION bin
    )
endif()

# Додавання тестів, якщо вони ввімкнені
# Add tests if enabled
# Добавление тестов, если они включены
if(BUILD_TESTS)
    add_executable(test_advanced_analytics
        ../tests/test_advanced_analytics.cpp
    )
    
    target_link_libraries(test_advanced_analytics
        advanced_analytics
        neuron
        neural_network
    )
    
    install(TARGETS test_advanced_analytics
        RUNTIME DESTINATION bin
    )
endif()