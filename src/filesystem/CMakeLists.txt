# CMakeLists.txt for filesystem module
# CMakeLists.txt для модуля файлової системи
# CMakeLists.txt для модуля файловой системы

# Додавання бібліотеки filesystem
# Add filesystem library
# Добавление библиотеки filesystem
add_library(filesystem
    FileSystem.cpp
)

# Встановлення властивостей C++17 (для std::filesystem)
# Set C++17 properties (for std::filesystem)
# Установка свойств C++17 (для std::filesystem)
target_compile_features(filesystem PUBLIC cxx_std_17)

# Встановлення властивостей бібліотеки
# Set library properties
# Установка свойств библиотеки
set_target_properties(filesystem PROPERTIES
    LINKER_LANGUAGE CXX
)

# Встановлення заголовочних файлів для інсталяції
# Set header files for installation
# Установка заголовочных файлов для установки
target_include_directories(filesystem PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Зв'язування з файловою системою
# Link with filesystem library
# Связывание с файловой системой
if(WIN32)
    # On Windows, we don't need to link to stdc++fs
    target_link_libraries(filesystem)
else()
    target_link_libraries(filesystem PUBLIC stdc++fs)
endif()

# Встановлення цілей для експорту
# Set export targets
# Установка целей для экспорта
install(TARGETS filesystem
    EXPORT NeuroSyncTargets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)

# Встановлення заголовочних файлів
# Install header files
# Установка заголовочных файлов
install(FILES FileSystem.h
    DESTINATION include/filesystem
)