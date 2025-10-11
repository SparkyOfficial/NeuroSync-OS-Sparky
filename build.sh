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
# The tests are now in the root of the build directory
if [ -f "./test_api" ]; then
    echo "Running API tests..."
    ./test_api
else
    echo "API test executable not found"
fi

if [ -f "./memory_example" ]; then
    echo "Running memory example..."
    ./memory_example
else
    echo "Memory example executable not found"
fi

echo "=== All tests completed ==="