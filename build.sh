#!/bin/bash

# Build script for NeuroSync OS Sparky
# Скрипт збірки для NeuroSync OS Sparky

echo "=== Building NeuroSync OS Sparky ==="

# Create build directory
# Створення директорії збірки
mkdir -p build
cd build

# Configure with CMake
# Конфігурація за допомогою CMake
cmake ..

# Build the project
# Збірка проекту
make -j$(nproc)

echo "=== Build completed successfully! ==="

echo "=== Running tests ==="
./bin/test_neurosync
./bin/advanced_memory_example

echo "=== All tests completed ==="