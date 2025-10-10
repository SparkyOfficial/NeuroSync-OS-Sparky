@echo off
:: run_advanced_neuron_example.bat
:: Скрипт запуску розширеного прикладу нейрона для NeuroSync OS Sparky
:: Advanced neuron example run script for NeuroSync OS Sparky
:: Скрипт запуска расширенного примера нейрона для NeuroSync OS Sparky

echo === NeuroSync OS Sparky Advanced Neuron Example Runner ===
echo === Запуск розширеного прикладу нейрона NeuroSync OS Sparky ===
echo === Запуск расширенного примера нейрона NeuroSync OS Sparky ===

:: Перевірка наявності виконуваного файлу
:: Checking for executable file
:: Проверка наличия исполняемого файла
if not exist "_build\bin\Debug\advanced_neuron_example.exe" (
    echo Error: Advanced neuron example executable not found. Please build the project first.
    echo Помилка: Виконуваний файл розширеного прикладу нейрона не знайдено. Будь ласка, спочатку зберіть проект.
    echo Ошибка: Исполняемый файл расширенного примера нейрона не найден. Пожалуйста, сначала соберите проект.
    exit /b 1
)

:: Запуск розширеного прикладу нейрона
:: Running the advanced neuron example
:: Запуск расширенного примера нейрона
echo Running advanced neuron example...
echo Запуск розширеного прикладу нейрона...
echo Запуск расширенного примера нейрона...
_build\bin\Debug\advanced_neuron_example.exe