@echo off
:: run_example.bat
:: Скрипт запуску прикладу для NeuroSync OS Sparky
:: Example run script for NeuroSync OS Sparky
:: Скрипт запуска примера для NeuroSync OS Sparky

echo === NeuroSync OS Sparky Example Runner ===
echo === Запуск прикладу NeuroSync OS Sparky ===
echo === Запуск примера NeuroSync OS Sparky ===

:: Перевірка наявності виконуваного файлу
:: Checking for executable file
:: Проверка наличия исполняемого файла
if not exist "_build\bin\Debug\simple_example.exe" (
    echo Error: Example executable not found. Please build the project first.
    echo Помилка: Виконуваний файл прикладу не знайдено. Будь ласка, спочатку зберіть проект.
    echo Ошибка: Исполняемый файл примера не найден. Пожалуйста, сначала соберите проект.
    exit /b 1
)

:: Запуск прикладу
:: Running the example
:: Запуск примера
echo Running example...
echo Запуск прикладу...
echo Запуск примера...
_build\bin\Debug\simple_example.exe