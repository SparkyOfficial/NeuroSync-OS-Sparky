# CMakeLists.txt
# Система збірки для NeuroSync OS Sparky
# Build system for NeuroSync OS Sparky
# Система збірки для NeuroSync OS Sparky

cmake_minimum_required(VERSION 3.10)

# Назва проекту
# Project name
# Назва проекту
project(NeuroSync_OS_Sparky)

# Стандарт C++
# C++ standard
# Стандарт C++
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Вихідна директорія для виконуваних файлів
# Output directory for executables
# Вихідна директорія для виконуваних файлів
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Директорії з заголовочними файлами
# Header file directories
# Директорії з заголовочними файлами
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

# Додавання підкаталогів
# Adding subdirectories
# Додавання підкаталогів
add_subdirectory(src/core)
add_subdirectory(src/neuron)
add_subdirectory(src/synapse)
add_subdirectory(src/memory)
add_subdirectory(src/diagnostics)
add_subdirectory(src/api)

# Створення виконуваного файлу для прикладу
# Creating executable for example
# Створення виконуваного файлу для прикладу
add_executable(simple_example src/examples/simple_example.cpp)

# Створення виконуваного файлу для розширеного прикладу планувальника
# Creating executable for advanced scheduler example
# Створення виконуваного файлу для розширеного прикладу планувальника
add_executable(advanced_scheduler_example src/examples/advanced_scheduler_example.cpp)

# Створення виконуваного файлу для розширеного прикладу нейрона
# Creating executable for advanced neuron example
# Створення виконуваного файлу для розширеного прикладу нейрона
add_executable(advanced_neuron_example src/examples/advanced_neuron_example.cpp)

# Створення виконуваного файлу для розширеного прикладу синапса
# Creating executable for advanced synapse example
# Створення виконуваного файлу для розширеного прикладу синапса
add_executable(advanced_synapse_example src/examples/advanced_synapse_example.cpp)

# Створення виконуваного файлу для розширеного прикладу пам'яті
# Creating executable for advanced memory example
# Створення виконуваного файлу для розширеного прикладу пам'яті
add_executable(advanced_memory_example src/examples/advanced_memory_example.cpp)

# Створення виконуваного файлу для розширеного прикладу діагностики
# Creating executable for advanced diagnostics example
# Створення виконуваного файлу для розширеного прикладу діагностики
add_executable(advanced_diagnostics_example src/examples/advanced_diagnostics_example.cpp)

# Створення виконуваного файлу для тестів
# Creating executable for tests
# Створення виконуваного файлу для тестів
add_executable(test_neurosync src/tests/test_neurosync.cpp)

# Лінкування бібліотек
# Linking libraries
# Лінкування бібліотек
target_link_libraries(simple_example 
    core
    neuron
    synapse
    memory
    diagnostics
    api
)

target_link_libraries(advanced_scheduler_example 
    core
    neuron
    synapse
    memory
    diagnostics
    api
)

target_link_libraries(advanced_neuron_example 
    core
    neuron
    synapse
    memory
    diagnostics
    api
)

target_link_libraries(advanced_synapse_example 
    core
    neuron
    synapse
    memory
    diagnostics
    api
)

target_link_libraries(advanced_memory_example 
    core
    neuron
    synapse
    memory
    diagnostics
    api
)

target_link_libraries(advanced_diagnostics_example 
    core
    neuron
    synapse
    memory
    diagnostics
    api
)

target_link_libraries(test_neurosync 
    core
    neuron
    synapse
    memory
    diagnostics
    api
)