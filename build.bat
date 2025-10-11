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
REM The tests are now in the Release directory, not bin\Release
if exist "Release\test_api.exe" (
    echo Running API tests...
    Release\test_api.exe
) else (
    echo API test executable not found
)

if exist "Release\memory_example.exe" (
    echo Running memory example...
    Release\memory_example.exe
) else (
    echo Memory example executable not found
)

echo === All tests completed ===