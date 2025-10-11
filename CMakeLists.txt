cmake_minimum_required(VERSION 3.10)

# Project information
# Інформація про проект
# Информация о проекте
project(NeuroSync_OS_Sparky VERSION 1.0.0 LANGUAGES CXX)

# C++ standard
# Стандарт C++
# Стандарт C++
set(CMAKE_CXX_STANDARD 17)
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
add_subdirectory(src/ml_pipeline)
add_subdirectory(src/data_processing)
add_subdirectory(src/model_management)
add_subdirectory(src/performance_optimization)
add_subdirectory(src/distributed_computing)
add_subdirectory(src/analytics)
add_subdirectory(src/nlp)
add_subdirectory(src/cv)
add_subdirectory(src/audio)
add_subdirectory(src/advanced_nn)
add_subdirectory(src/quantum)
add_subdirectory(src/database)
add_subdirectory(src/advanced_analytics)
add_subdirectory(src/robotics)
add_subdirectory(src/db)

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

add_executable(scheduler_example src/examples/scheduler_example.cpp)
target_link_libraries(scheduler_example PRIVATE core)
target_include_directories(scheduler_example PRIVATE src/core)

add_executable(weighted_fair_queuing_example src/examples/weighted_fair_queuing_example.cpp)
target_link_libraries(weighted_fair_queuing_example PRIVATE core)
target_include_directories(weighted_fair_queuing_example PRIVATE src/core)

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

add_executable(ml_pipeline_example src/examples/ml_pipeline_example.cpp)
target_link_libraries(ml_pipeline_example PRIVATE ml_pipeline data_processing model_management neural_network core)
target_include_directories(ml_pipeline_example PRIVATE src/ml_pipeline src/data_processing src/model_management src/network_neural)

add_executable(performance_optimization_example src/examples/performance_optimization_example.cpp)
target_link_libraries(performance_optimization_example PRIVATE performance_optimization core threadpool memory diagnostics)
target_include_directories(performance_optimization_example PRIVATE src/performance_optimization src/core src/threadpool src/memory src/diagnostics)

add_executable(distributed_computing_example src/examples/distributed_computing_example.cpp)
target_link_libraries(distributed_computing_example PRIVATE distributed_computing network core threadpool security)
target_include_directories(distributed_computing_example PRIVATE src/distributed_computing src/network src/core src/threadpool src/security)

add_executable(analytics_example src/examples/analytics_example.cpp)
target_link_libraries(analytics_example PRIVATE analytics diagnostics core memory logging)
target_include_directories(analytics_example PRIVATE src/analytics src/diagnostics src/core src/memory src/logging)

add_executable(ai_assistant_example src/examples/ai_assistant_example.cpp)
target_link_libraries(ai_assistant_example PRIVATE neuron synapse neural_network memory event logging config core)
target_include_directories(ai_assistant_example PRIVATE src/neuron src/synapse src/network_neural src/memory src/event src/logging src/config)

add_executable(nlp_example src/examples/nlp_example.cpp)
target_link_libraries(nlp_example PRIVATE nlp neuron neural_network core)
target_include_directories(nlp_example PRIVATE src/nlp src/neuron src/network_neural)

add_executable(cv_example src/examples/cv_example.cpp)
target_link_libraries(cv_example PRIVATE cv neuron neural_network core)
target_include_directories(cv_example PRIVATE src/cv src/neuron src/network_neural)

add_executable(audio_example src/examples/audio_example.cpp)
target_link_libraries(audio_example PRIVATE audio neuron neural_network core)
target_include_directories(audio_example PRIVATE src/audio src/neuron src/network_neural)

add_executable(advanced_nn_example src/examples/advanced_nn_example.cpp)
target_link_libraries(advanced_nn_example PRIVATE advanced_nn neural_network neuron core)
target_include_directories(advanced_nn_example PRIVATE src/advanced_nn src/network_neural src/neuron)

add_executable(database_example src/examples/database_example.cpp)
target_link_libraries(database_example PRIVATE database neuron synapse core)
target_include_directories(database_example PRIVATE src/database src/neuron src/synapse)

add_executable(advanced_analytics_example src/examples/advanced_analytics_example.cpp)
target_link_libraries(advanced_analytics_example PRIVATE advanced_analytics neuron neural_network core)
target_include_directories(advanced_analytics_example PRIVATE src/advanced_analytics src/neuron src/network_neural)

add_executable(robotics_example src/examples/robotics_example.cpp)
target_link_libraries(robotics_example PRIVATE robotics neuron neural_network event core)
target_include_directories(robotics_example PRIVATE src/robotics src/neuron src/network_neural src/event)

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
target_include_directories(test_config PRIVATE src/config)
add_test(NAME test_config COMMAND test_config)

add_executable(test_advanced_nn src/tests/test_advanced_nn.cpp)
target_link_libraries(test_advanced_nn PRIVATE advanced_nn neural_network neuron synapse api core)
target_include_directories(test_advanced_nn PRIVATE src/advanced_nn src/network_neural src/neuron src/synapse src/api)
add_test(NAME test_advanced_nn COMMAND test_advanced_nn)

add_executable(test_database src/tests/test_database.cpp)
target_link_libraries(test_database PRIVATE database neuron synapse core)
target_include_directories(test_database PRIVATE src/database src/neuron src/synapse)
add_test(NAME test_database COMMAND test_database)

add_executable(test_advanced_analytics src/tests/test_advanced_analytics.cpp)
target_link_libraries(test_advanced_analytics PRIVATE advanced_analytics neuron neural_network core)
target_include_directories(test_advanced_analytics PRIVATE src/advanced_analytics src/neuron src/network_neural)
add_test(NAME test_advanced_analytics COMMAND test_advanced_analytics)

add_executable(test_robotics src/tests/test_robotics.cpp)
target_link_libraries(test_robotics PRIVATE robotics neuron neural_network event core)
target_include_directories(test_robotics PRIVATE src/robotics src/neuron src/network_neural src/event)
add_test(NAME test_robotics COMMAND test_robotics)

# Installation
# Встановлення
# Установка
install(TARGETS neuron synapse api core memory diagnostics plugin logging threadpool filesystem network security visualization event config neural_network advanced_nn database advanced_analytics robotics db
        DESTINATION lib)