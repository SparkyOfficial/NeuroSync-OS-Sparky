# CMakeLists.txt for network module
# CMakeLists.txt для модуля мережевої комунікації
# CMakeLists.txt для модуля сетевой коммуникации

# Додавання бібліотеки network
# Add network library
# Добавление библиотеки network
add_library(network
    NetworkCommunication.cpp
)

# Встановлення властивостей C++14
# Set C++14 properties
# Установка свойств C++14
target_compile_features(network PUBLIC cxx_std_14)

# Встановлення властивостей бібліотеки
# Set library properties
# Установка свойств библиотеки
set_target_properties(network PROPERTIES
    LINKER_LANGUAGE CXX
)

# Встановлення заголовочних файлів для інсталяції
# Set header files for installation
# Установка заголовочных файлов для установки
target_include_directories(network PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Зв'язування з потоковими бібліотеками
# Link with threading libraries
# Связывание с потоковыми библиотеками
target_link_libraries(network
    ${CMAKE_THREAD_LIBS_INIT}
)

# Встановлення цілей для експорту
# Set export targets
# Установка целей для экспорта
install(TARGETS network
    EXPORT NeuroSyncTargets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)

# Встановлення заголовочних файлів
# Install header files
# Установка заголовочных файлов
install(FILES NetworkCommunication.h
    DESTINATION include/network
)