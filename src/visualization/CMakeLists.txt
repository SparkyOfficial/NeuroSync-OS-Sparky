# CMakeLists.txt for visualization module
# CMakeLists.txt для модуля візуалізації
# CMakeLists.txt для модуля визуализации

# Додавання бібліотеки visualization
# Add visualization library
# Добавление библиотеки visualization
add_library(visualization
    VisualizationModule.cpp
)

# Встановлення властивостей C++14
# Set C++14 properties
# Установка свойств C++14
target_compile_features(visualization PUBLIC cxx_std_14)

# Встановлення властивостей бібліотеки
# Set library properties
# Установка свойств библиотеки
set_target_properties(visualization PROPERTIES
    LINKER_LANGUAGE CXX
)

# Встановлення заголовочних файлів для інсталяції
# Set header files for installation
# Установка заголовочных файлов для установки
target_include_directories(visualization PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Зв'язування з потоковими бібліотеками
# Link with threading libraries
# Связывание с потоковыми библиотеками
target_link_libraries(visualization
    ${CMAKE_THREAD_LIBS_INIT}
)

# Встановлення цілей для експорту
# Set export targets
# Установка целей для экспорта
install(TARGETS visualization
    EXPORT NeuroSyncTargets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)

# Встановлення заголовочних файлів
# Install header files
# Установка заголовочных файлов
install(FILES VisualizationModule.h
    DESTINATION include/visualization
)