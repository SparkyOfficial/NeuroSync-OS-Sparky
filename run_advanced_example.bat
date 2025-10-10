@echo off
:: run_advanced_example.bat
:: Скрипт запуску розширеного прикладу для NeuroSync OS Sparky
:: Advanced example run script for NeuroSync OS Sparky
:: Скрипт запуска расширенного примера для NeuroSync OS Sparky

echo === NeuroSync OS Sparky Advanced Example Runner ===
echo === Запуск розширеного прикладу NeuroSync OS Sparky ===
echo === Запуск расширенного примера NeuroSync OS Sparky ===

:: Перевірка наявності виконуваного файлу
:: Checking for executable file
:: Проверка наличия исполняемого файла
if not exist "_build\bin\Debug\advanced_scheduler_example.exe" (
    echo Error: Advanced example executable not found. Please build the project first.
    echo Помилка: Виконуваний файл розширеного прикладу не знайдено. Будь ласка, спочатку зберіть проект.
    echo Ошибка: Исполняемый файл расширенного примера не найден. Пожалуйста, сначала соберите проект.
    exit /b 1
)

:: Запуск розширеного прикладу
:: Running the advanced example
:: Запуск расширенного примера
echo Running advanced example...
echo Запуск розширеного прикладу...
echo Запуск расширенного примера...
_build\bin\Debug\advanced_scheduler_example.exe