@echo off
:: build.bat
:: Скрипт збірки для NeuroSync OS Sparky
:: Build script for NeuroSync OS Sparky
:: Скрипт збірки для NeuroSync OS Sparky

echo === NeuroSync OS Sparky Build Script ===
echo === Скрипт збірки NeuroSync OS Sparky ===
echo === Скрипт сборки NeuroSync OS Sparky ===

:: Створення директорії збірки
:: Creating build directory
:: Создание директории сборки
if not exist "_build" mkdir _build
cd _build

:: Генерація файлів збірки
:: Generating build files
:: Генерация файлов сборки
cmake ..

:: Компіляція проекту
:: Compiling the project
:: Компиляция проекта
cmake --build .

echo.
echo Build completed!
echo Збірка завершена!
echo Сборка завершена!
echo.
echo To run the example, execute: _build\bin\simple_example.exe
echo Щоб запустити приклад, виконайте: _build\bin\simple_example.exe
echo Чтобы запустить пример, выполните: _build\bin\simple_example.exe