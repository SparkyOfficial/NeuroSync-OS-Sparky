# CMakeLists.txt for NLP module
# Модуль обробки природної мови
# Модуль обработки естественного языка

# Додавання бібліотеки NLP
# Add NLP library
# Добавление библиотеки NLP
add_library(nlp
    NaturalLanguageProcessing.cpp
)

# Встановлення властивостей бібліотеки
# Set library properties
# Установка свойств библиотеки
set_target_properties(nlp PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

# Встановлення заголовків для встановлення
# Set headers for installation
# Установка заголовков для установки
target_include_directories(nlp PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Встановлення залежностей
# Set dependencies
# Установка зависимостей
target_link_libraries(nlp PUBLIC
    neuron
    synapse
)

# Встановлення бібліотеки
# Install library
# Установка библиотеки
install(TARGETS nlp
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
)

# Встановлення заголовків
# Install headers
# Установка заголовков
install(FILES 
    NaturalLanguageProcessing.h
    DESTINATION include/nlp
)

# Додавання прикладів, якщо вони ввімкнені
# Add examples if enabled
# Добавление примеров, если они включены
if(BUILD_EXAMPLES)
    add_executable(nlp_example
        ../examples/nlp_example.cpp
    )
    
    target_link_libraries(nlp_example
        nlp
        neuron
        synapse
    )
    
    install(TARGETS nlp_example
        RUNTIME DESTINATION bin
    )
endif()

# Додавання тестів, якщо вони ввімкнені
# Add tests if enabled
# Добавление тестов, если они включены
if(BUILD_TESTS)
    add_executable(test_nlp
        ../tests/test_nlp.cpp
    )
    
    target_link_libraries(test_nlp
        nlp
        neuron
        synapse
    )
    
    install(TARGETS test_nlp
        RUNTIME DESTINATION bin
    )
endif()