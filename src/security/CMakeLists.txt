# CMakeLists.txt for security module
# CMakeLists.txt для модуля безпеки
# CMakeLists.txt для модуля безопасности

# Додавання бібліотеки security
# Add security library
# Добавление библиотеки security
add_library(security
    SecurityModule.cpp
)

# Встановлення властивостей C++14
# Set C++14 properties
# Установка свойств C++14
target_compile_features(security PUBLIC cxx_std_14)

# Встановлення властивостей бібліотеки
# Set library properties
# Установка свойств библиотеки
set_target_properties(security PROPERTIES
    LINKER_LANGUAGE CXX
)

# Встановлення заголовочних файлів для інсталяції
# Set header files for installation
# Установка заголовочных файлов для установки
target_include_directories(security PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Зв'язування з потоковими бібліотеками
# Link with threading libraries
# Связывание с потоковыми библиотеками
target_link_libraries(security
    ${CMAKE_THREAD_LIBS_INIT}
)

# Встановлення цілей для експорту
# Set export targets
# Установка целей для экспорта
install(TARGETS security
    EXPORT NeuroSyncTargets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)

# Встановлення заголовочних файлів
# Install header files
# Установка заголовочных файлов
install(FILES SecurityModule.h
    DESTINATION include/security
)