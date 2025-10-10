@echo off
REM Build script for NeuroSync OS Sparky on Windows
REM Скрипт збірки для NeuroSync OS Sparky на Windows

echo === Building NeuroSync OS Sparky ===

REM Create build directory
REM Створення директорії збірки
if not exist "build" mkdir build
cd build

REM Configure with CMake
REM Конфігурація за допомогою CMake
cmake ..

REM Build the project
REM Збірка проекту
cmake --build . --config Release

echo === Build completed successfully! ===

echo === Running tests ===
bin\Release\test_neurosync.exe
bin\Release\advanced_memory_example.exe

echo === All tests completed ===