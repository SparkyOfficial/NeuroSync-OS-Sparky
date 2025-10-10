@echo off
:: run_tests.bat
:: Скрипт запуску тестів для NeuroSync OS Sparky
:: Test run script for NeuroSync OS Sparky
:: Скрипт запуска тестов для NeuroSync OS Sparky

echo === NeuroSync OS Sparky Test Runner ===
echo === Запуск тестів NeuroSync OS Sparky ===
echo === Запуск тестов NeuroSync OS Sparky ===

:: Перевірка наявності виконуваного файлу тестів
:: Checking for test executable file
:: Проверка наличия исполняемого файла тестов
if not exist "_build\bin\Debug\test_neurosync.exe" (
    echo Error: Test executable not found. Please build the project first.
    echo Помилка: Виконуваний файл тестів не знайдено. Будь ласка, спочатку зберіть проект.
    echo Ошибка: Исполняемый файл тестов не найден. Пожалуйста, сначала соберите проект.
    exit /b 1
)

:: Запуск тестів
:: Running tests
:: Запуск тестов
echo Running tests...
echo Запуск тестів...
echo Запуск тестов...
_build\bin\Debug\test_neurosync.exe