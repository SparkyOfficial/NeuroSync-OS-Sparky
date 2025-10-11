# src/logging/CMakeLists.txt
# Система збірки для модуля логування NeuroSync OS Sparky
# Build system for NeuroSync OS Sparky logging module
# Система збірки для модуля логирования NeuroSync OS Sparky

# Створення бібліотеки для модуля логування
# Creating library for logging module
# Создание библиотеки для модуля логирования
add_library(logging
    LoggingSystem.cpp
)

# Встановлення властивостей бібліотеки
# Setting library properties
# Установка свойств библиотеки
set_target_properties(logging PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

# Встановлення заголовочних файлів для інших модулів
# Setting header files for other modules
# Установка заголовочных файлов для других модулей
target_include_directories(logging PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Лінкування з необхідними бібліотеками
# Linking with required libraries
# Линковка с необходимыми библиотеками
if(WIN32)
    # На Windows додаємо бібліотеку для роботи з консолью
    # On Windows add library for working with console
    # На Windows добавляем библиотеку для работы с консолью
    target_link_libraries(logging)
else()
    # На Unix-подібних системах не потрібно додаткових бібліотек
    # On Unix-like systems no additional libraries needed
    # На Unix-подобных системах не нужны дополнительные библиотеки
endif()