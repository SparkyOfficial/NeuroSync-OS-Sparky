# CMakeLists.txt for threadpool module
# CMakeLists.txt для модуля пулу потоків
# CMakeLists.txt для модуля пула потоков

# Додавання бібліотеки threadpool
# Add threadpool library
# Добавление библиотеки threadpool
add_library(threadpool
    ThreadPool.cpp
)

# Встановлення властивостей C++14
# Set C++14 properties
# Установка свойств C++14
target_compile_features(threadpool PUBLIC cxx_std_14)

# Встановлення властивостей бібліотеки
# Set library properties
# Установка свойств библиотеки
set_target_properties(threadpool PROPERTIES
    LINKER_LANGUAGE CXX
)

# Встановлення заголовочних файлів для інсталяції
# Set header files for installation
# Установка заголовочных файлов для установки
target_include_directories(threadpool PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Зв'язування з потоковими бібліотеками
# Link with threading libraries
# Связывание с потоковыми библиотеками
target_link_libraries(threadpool
    ${CMAKE_THREAD_LIBS_INIT}
)

# Встановлення цілей для експорту
# Set export targets
# Установка целей для экспорта
install(TARGETS threadpool
    EXPORT NeuroSyncTargets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)

# Встановлення заголовочних файлів
# Install header files
# Установка заголовочных файлов
install(FILES ThreadPool.h
    DESTINATION include/threadpool
)