# src/event/CMakeLists.txt
# Система збірки для модуля подій NeuroSync OS Sparky
# Build system for NeuroSync OS Sparky event module
# Система збірки для модуля событий NeuroSync OS Sparky

# Створення бібліотеки для модуля подій
# Creating library for event module
# Создание библиотеки для модуля событий
add_library(event
    EventSystem.cpp
)

# Встановлення властивостей бібліотеки
# Setting library properties
# Установка свойств библиотеки
set_target_properties(event PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

# Встановлення заголовочних файлів для інших модулів
# Setting header files for other modules
# Установка заголовочных файлов для других модулей
target_include_directories(event PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)