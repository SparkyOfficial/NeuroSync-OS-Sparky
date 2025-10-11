# CMakeLists.txt for Computer Vision module
# Модуль комп'ютерного зору
# Модуль компьютерного зрения

# Додавання бібліотеки комп'ютерного зору
# Add computer vision library
# Добавление библиотеки компьютерного зрения
add_library(cv
    ComputerVision.cpp
)

# Встановлення властивостей бібліотеки
# Set library properties
# Установка свойств библиотеки
set_target_properties(cv PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

# Встановлення заголовків для встановлення
# Set headers for installation
# Установка заголовков для установки
target_include_directories(cv PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Встановлення залежностей
# Set dependencies
# Установка зависимостей
target_link_libraries(cv PUBLIC
    neuron
    synapse
    neural_network
)

# Встановлення бібліотеки
# Install library
# Установка библиотеки
install(TARGETS cv
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
)

# Встановлення заголовків
# Install headers
# Установка заголовков
install(FILES 
    ComputerVision.h
    DESTINATION include/cv
)

# Додавання прикладів, якщо вони ввімкнені
# Add examples if enabled
# Добавление примеров, если они включены
if(BUILD_EXAMPLES)
    add_executable(cv_example
        ../examples/cv_example.cpp
    )
    
    target_link_libraries(cv_example
        cv
        neuron
        synapse
        neural_network
    )
    
    install(TARGETS cv_example
        RUNTIME DESTINATION bin
    )
endif()

# Додавання тестів, якщо вони ввімкнені
# Add tests if enabled
# Добавление тестов, если они включены
if(BUILD_TESTS)
    add_executable(test_cv
        ../tests/test_cv.cpp
    )
    
    target_link_libraries(test_cv
        cv
        neuron
        synapse
        neural_network
    )
    
    install(TARGETS test_cv
        RUNTIME DESTINATION bin
    )
endif()