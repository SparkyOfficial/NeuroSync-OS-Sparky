# CMakeLists.txt for Robotics Control module
# Модуль керування робототехнікою
# Модуль управления робототехникой

# Додавання бібліотеки керування робототехнікою
# Add robotics control library
# Добавление библиотеки управления робототехникой
add_library(robotics
    RoboticsControl.cpp
)

# Встановлення властивостей бібліотеки
# Set library properties
# Установка свойств библиотеки
set_target_properties(robotics PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

# Встановлення заголовків для встановлення
# Set headers for installation
# Установка заголовков для установки
target_include_directories(robotics PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Встановлення залежностей
# Set dependencies
# Установка зависимостей
target_link_libraries(robotics PUBLIC
    neuron
    neural_network
    event
)

# Встановлення бібліотеки
# Install library
# Установка библиотеки
install(TARGETS robotics
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
)

# Встановлення заголовків
# Install headers
# Установка заголовков
install(FILES 
    RoboticsControl.h
    DESTINATION include/robotics
)

# Додавання прикладів, якщо вони ввімкнені
# Add examples if enabled
# Добавление примеров, если они включены
if(BUILD_EXAMPLES)
    add_executable(robotics_example
        ../examples/robotics_example.cpp
    )
    
    target_link_libraries(robotics_example
        robotics
        neuron
        neural_network
        event
    )
    
    install(TARGETS robotics_example
        RUNTIME DESTINATION bin
    )
endif()

# Додавання тестів, якщо вони ввімкнені
# Add tests if enabled
# Добавление тестов, если они включены
if(BUILD_TESTS)
    add_executable(test_robotics
        ../tests/test_robotics.cpp
    )
    
    target_link_libraries(test_robotics
        robotics
        neuron
        neural_network
        event
    )
    
    install(TARGETS test_robotics
        RUNTIME DESTINATION bin
    )
endif()