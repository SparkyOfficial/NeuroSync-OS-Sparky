cmake_minimum_required(VERSION 3.10)

# Project information
# Інформація про проект
# Информация о проекте
project(NeuroSync_OS_Sparky VERSION 1.0.0 LANGUAGES CXX)

# C++ standard
# Стандарт C++
# Стандарт C++
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Compiler flags
# Прапорці компілятора
# Флаги компилятора
if(MSVC)
    # Use MSVC-specific flags
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
else()
    # Use GCC/Clang flags
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")
endif()

# Add source directories
# Додавання каталогів джерел
# Добавление каталогов исходников
add_subdirectory(src/core)
add_subdirectory(src/neuron)
add_subdirectory(src/synapse)
add_subdirectory(src/memory)
add_subdirectory(src/diagnostics)
add_subdirectory(src/api)
add_subdirectory(src/network_neural)
add_subdirectory(src/event)
add_subdirectory(src/config)
add_subdirectory(src/plugin)
add_subdirectory(src/logging)
add_subdirectory(src/threadpool)
add_subdirectory(src/filesystem)
add_subdirectory(src/network)
add_subdirectory(src/security)
add_subdirectory(src/visualization)
add_subdirectory(src/testing)
add_subdirectory(src/benchmark)
add_subdirectory(src/docgen)

# Examples
# Приклади
# Примеры
add_executable(neuron_example src/examples/simple_example.cpp)
target_link_libraries(neuron_example PRIVATE neuron synapse api core)
target_include_directories(neuron_example PRIVATE src/neuron)

add_executable(synapse_example src/examples/advanced_synapse_example.cpp)
target_link_libraries(synapse_example PRIVATE synapse core)
target_include_directories(synapse_example PRIVATE src/synapse)

add_executable(memory_example src/examples/advanced_memory_example.cpp)
target_link_libraries(memory_example PRIVATE memory core)
target_include_directories(memory_example PRIVATE src/memory)

add_executable(diagnostics_example src/examples/advanced_diagnostics_example.cpp)
target_link_libraries(diagnostics_example PRIVATE diagnostics core)
target_include_directories(diagnostics_example PRIVATE src/diagnostics)

add_executable(api_example src/examples/advanced_api_example.cpp)
target_link_libraries(api_example PRIVATE api core)
target_include_directories(api_example PRIVATE src/api)

add_executable(neural_network_example src/examples/neural_network_example.cpp)
target_link_libraries(neural_network_example PRIVATE neural_network neuron synapse core)
target_include_directories(neural_network_example PRIVATE src/network_neural)

add_executable(event_system_example src/examples/event_example.cpp)
target_link_libraries(event_system_example PRIVATE event neuron synapse core)
target_include_directories(event_system_example PRIVATE src/event)

add_executable(config_example src/examples/config_example.cpp)
target_link_libraries(config_example PRIVATE config core)
target_include_directories(config_example PRIVATE src/config)

add_executable(plugin_example src/examples/plugin_example.cpp)
target_link_libraries(plugin_example PRIVATE plugin core)
target_include_directories(plugin_example PRIVATE src/plugin)

add_executable(logging_example src/examples/logging_example.cpp)
target_link_libraries(logging_example PRIVATE logging core)
target_include_directories(logging_example PRIVATE src/logging)

add_executable(threadpool_example src/examples/threadpool_example.cpp)
target_link_libraries(threadpool_example PRIVATE threadpool core)
target_include_directories(threadpool_example PRIVATE src/threadpool)

add_executable(filesystem_example src/examples/filesystem_example.cpp)
target_link_libraries(filesystem_example PRIVATE filesystem core)
target_include_directories(filesystem_example PRIVATE src/filesystem)

add_executable(network_example src/examples/network_example.cpp)
target_link_libraries(network_example PRIVATE network core)
target_include_directories(network_example PRIVATE src/network)

add_executable(security_example src/examples/security_example.cpp)
target_link_libraries(security_example PRIVATE security core)
target_include_directories(security_example PRIVATE src/security)

add_executable(visualization_example src/examples/visualization_example.cpp)
target_link_libraries(visualization_example PRIVATE visualization core)
target_include_directories(visualization_example PRIVATE src/visualization)

# Tests
# Тести
# Тесты
enable_testing()

add_executable(test_neuron src/tests/test_neurosync.cpp)
target_link_libraries(test_neuron PRIVATE neuron synapse api core)
target_include_directories(test_neuron PRIVATE src/neuron)
add_test(NAME test_neuron COMMAND test_neuron)

add_executable(test_synapse src/tests/test_neurosync.cpp)
target_link_libraries(test_synapse PRIVATE synapse api core)
target_include_directories(test_synapse PRIVATE src/synapse)
add_test(NAME test_synapse COMMAND test_synapse)

add_executable(test_memory src/tests/test_memory.cpp)
target_link_libraries(test_memory PRIVATE memory core)
target_include_directories(test_memory PRIVATE src/memory)
add_test(NAME test_memory COMMAND test_memory)

add_executable(test_diagnostics src/tests/test_diagnostics.cpp)
target_link_libraries(test_diagnostics PRIVATE diagnostics core)
target_include_directories(test_diagnostics PRIVATE src/diagnostics)
add_test(NAME test_diagnostics COMMAND test_diagnostics)

add_executable(test_api src/tests/test_api.cpp)
target_link_libraries(test_api PRIVATE api core)
target_include_directories(test_api PRIVATE src/api)
add_test(NAME test_api COMMAND test_api)

add_executable(test_neural_network src/tests/test_neurosync.cpp)
target_link_libraries(test_neural_network PRIVATE neural_network neuron synapse api core)
target_include_directories(test_neural_network PRIVATE src/network_neural)
add_test(NAME test_neural_network COMMAND test_neural_network)

add_executable(test_event_system src/tests/test_event_system.cpp)
target_link_libraries(test_event_system PRIVATE event neuron synapse core)
target_include_directories(test_event_system PRIVATE src/event)
add_test(NAME test_event_system COMMAND test_event_system)

add_executable(test_config src/tests/test_config_manager.cpp)
target_link_libraries(test_config PRIVATE config core)
target_include_directories(test_config PRIVATE src/config)
add_test(NAME test_config COMMAND test_config)

add_executable(test_plugin src/tests/test_plugin_system.cpp)
target_link_libraries(test_plugin PRIVATE plugin core)
target_include_directories(test_plugin PRIVATE src/plugin)
add_test(NAME test_plugin COMMAND test_plugin)

add_executable(test_logging src/tests/test_logging_system.cpp)
target_link_libraries(test_logging PRIVATE logging core)
target_include_directories(test_logging PRIVATE src/logging)
add_test(NAME test_logging COMMAND test_logging)

add_executable(test_threadpool src/tests/test_threadpool_system.cpp)
target_link_libraries(test_threadpool PRIVATE threadpool neuron synapse core)
target_include_directories(test_threadpool PRIVATE src/threadpool)
add_test(NAME test_threadpool COMMAND test_threadpool)

add_executable(test_filesystem src/tests/test_filesystem.cpp)
target_link_libraries(test_filesystem PRIVATE filesystem core)
target_include_directories(test_filesystem PRIVATE src/filesystem)
add_test(NAME test_filesystem COMMAND test_filesystem)

add_executable(test_network src/tests/test_network.cpp)
target_link_libraries(test_network PRIVATE network core)
target_include_directories(test_network PRIVATE src/network)
add_test(NAME test_network COMMAND test_network)

add_executable(test_security src/tests/test_security.cpp)
target_link_libraries(test_security PRIVATE security core)
target_include_directories(test_security PRIVATE src/security)
add_test(NAME test_security COMMAND test_security)

add_executable(test_visualization src/tests/test_visualization.cpp)
target_link_libraries(test_visualization PRIVATE visualization core)
target_include_directories(test_visualization PRIVATE src/visualization)
add_test(NAME test_visualization COMMAND test_visualization)