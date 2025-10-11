# CMakeLists.txt for Audio Processing module
# Модуль обробки аудіо
# Модуль обработки аудио

# Додавання бібліотеки обробки аудіо
# Add audio processing library
# Добавление библиотеки обработки аудио
add_library(audio
    AudioProcessing.cpp
)

# Встановлення властивостей бібліотеки
# Set library properties
# Установка свойств библиотеки
set_target_properties(audio PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

# Встановлення заголовків для встановлення
# Set headers for installation
# Установка заголовков для установки
target_include_directories(audio PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Встановлення залежностей
# Set dependencies
# Установка зависимостей
target_link_libraries(audio PUBLIC
    neuron
    synapse
    neural_network
)

# Встановлення бібліотеки
# Install library
# Установка библиотеки
install(TARGETS audio
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
)

# Встановлення заголовків
# Install headers
# Установка заголовков
install(FILES 
    AudioProcessing.h
    DESTINATION include/audio
)

# Додавання прикладів, якщо вони ввімкнені
# Add examples if enabled
# Добавление примеров, если они включены
if(BUILD_EXAMPLES)
    add_executable(audio_example
        ../examples/audio_example.cpp
    )
    
    target_link_libraries(audio_example
        audio
        neuron
        synapse
        neural_network
    )
    
    install(TARGETS audio_example
        RUNTIME DESTINATION bin
    )
endif()

# Додавання тестів, якщо вони ввімкнені
# Add tests if enabled
# Добавление тестов, если они включены
if(BUILD_TESTS)
    add_executable(test_audio
        ../tests/test_audio.cpp
    )
    
    target_link_libraries(test_audio
        audio
        neuron
        synapse
        neural_network
    )
    
    install(TARGETS test_audio
        RUNTIME DESTINATION bin
    )
endif()