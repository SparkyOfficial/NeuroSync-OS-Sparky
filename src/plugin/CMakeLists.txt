# src/plugin/CMakeLists.txt
# Система збірки для модуля плагінів NeuroSync OS Sparky
# Build system for NeuroSync OS Sparky plugin module
# Система збірки для модуля плагинов NeuroSync OS Sparky

# Створення бібліотеки для модуля плагінів
# Creating library for plugin module
# Создание библиотеки для модуля плагинов
add_library(plugin
    PluginSystem.cpp
)

# Встановлення властивостей бібліотеки
# Setting library properties
# Установка свойств библиотеки
set_target_properties(plugin PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

# Встановлення заголовочних файлів для інших модулів
# Setting header files for other modules
# Установка заголовочных файлов для других модулей
target_include_directories(plugin PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Лінкування з необхідними бібліотеками
# Linking with required libraries
# Линковка с необходимыми библиотеками
if(WIN32)
    # На Windows додаємо бібліотеку для роботи з DLL
    # On Windows add library for working with DLL
    # На Windows добавляем библиотеку для работы с DLL
    target_link_libraries(plugin)
    # Додаємо визначення для експорту символів
    # Add definition for symbol export
    # Добавляем определение для экспорта символов
    target_compile_definitions(plugin PRIVATE EXAMPLE_PLUGIN_EXPORTS)
else()
    # На Unix-подібних системах додаємо бібліотеку для роботи з shared libraries
    # On Unix-like systems add library for working with shared libraries
    # На Unix-подобных системах добавляем библиотеку для работы с shared libraries
    target_link_libraries(plugin ${CMAKE_DL_LIBS})
endif()