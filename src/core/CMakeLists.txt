# src/core/CMakeLists.txt
# CMake конфігурація для модуля Core
# CMake configuration for Core module
# CMake конфігурація для модуля Core

# Створення бібліотеки core
# Creating core library
# Створення бібліотеки core
add_library(core
    ${CMAKE_CURRENT_SOURCE_DIR}/Scheduler.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/AdvancedScheduler.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/algorithms/PriorityBasedScheduling.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/algorithms/RoundRobinScheduling.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/algorithms/WeightedFairQueuingScheduling.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/utils/TaskManager.cpp
)

# Встановлення заголовочних файлів
# Installing header files
# Встановлення заголовочних файлів
target_include_directories(core PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/interfaces
    ${CMAKE_CURRENT_SOURCE_DIR}/algorithms
    ${CMAKE_CURRENT_SOURCE_DIR}/utils
)