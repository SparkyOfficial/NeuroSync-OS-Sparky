# src/synapse/CMakeLists.txt
# CMake конфігурація для модуля Synapse
# CMake configuration for Synapse module
# CMake конфігурація для модуля Synapse

# Створення бібліотеки synapse
# Creating synapse library
# Створення бібліотеки synapse
add_library(synapse
    ${CMAKE_CURRENT_SOURCE_DIR}/SynapseBus.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/priority/PriorityMessageQueue.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/utils/WeightedConnectionManager.cpp
)

# Встановлення залежностей
# Setting dependencies
# Встановлення залежностей
target_link_libraries(synapse core)

# Встановлення заголовочних файлів
# Installing header files
# Встановлення заголовочних файлів
target_include_directories(synapse PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/priority
    ${CMAKE_CURRENT_SOURCE_DIR}/utils
)