// logging_example.cpp
// Приклад використання системи логування / Logging system usage example / Пример использования системы логирования
// NeuroSync OS Sparky

#include "../logging/LoggingSystem.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <vector>

using namespace NeuroSync::Logging;

void workerThread(int id) {
    // Функція для робочого потоку
    // Function for worker thread
    // Функция для рабочего потока
    gLogger.info("WorkerThread", "Thread " + std::to_string(id) + " started");
    
    // Імітуємо роботу
    // Simulate work
    // Имитируем работу
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    
    gLogger.debug("WorkerThread", "Thread " + std::to_string(id) + " doing work");
    
    // Імітуємо можливу помилку
    // Simulate possible error
    // Имитируем возможную ошибку
    if (id % 3 == 0) {
        gLogger.warning("WorkerThread", "Thread " + std::to_string(id) + " encountered a warning");
    }
    
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    
    gLogger.info("WorkerThread", "Thread " + std::to_string(id) + " completed");
}

int main() {
    std::cout << "NeuroSync OS Sparky - Logging System Example" << std::endl;
    std::cout << "===========================================" << std::endl;
    
    // Ініціалізація системи логування
    // Initialize logging system
    // Инициализация системы логирования
    if (!gLogger.initialize()) {
        std::cerr << "Failed to initialize logging system" << std::endl;
        return 1;
    }
    
    std::cout << "Logging system initialized successfully" << std::endl;
    
    // Встановлення рівня логування
    // Set logging level
    // Установка уровня логирования
    gLogger.setLogLevel(LogLevel::LOG_DEBUG);
    std::cout << "Logging level set to DEBUG" << std::endl;
    
    // Отримання кількості виводів
    // Get output count
    // Получение количества выводов
    std::cout << "Number of log outputs: " << gLogger.getOutputCount() << std::endl;
    
    // Запис логів різних рівнів
    // Write logs of different levels
    // Запись логов разных уровней
    gLogger.debug("Main", "This is a debug message");
    gLogger.info("Main", "This is an info message");
    gLogger.warning("Main", "This is a warning message");
    gLogger.error("Main", "This is an error message");
    gLogger.critical("Main", "This is a critical message");
    
    // Додавання файлового виводу
    // Add file output
    // Добавление файлового вывода
    auto fileOutput = std::make_shared<FileLogOutput>("example.log");
    if (gLogger.addLogOutput(fileOutput)) {
        std::cout << "File output added successfully" << std::endl;
        gLogger.info("Main", "File output added successfully");
    } else {
        std::cout << "Failed to add file output" << std::endl;
    }
    
    std::cout << "Number of log outputs after adding file output: " << gLogger.getOutputCount() << std::endl;
    
    // Створення кількох потоків
    // Create multiple threads
    // Создание нескольких потоков
    std::vector<std::thread> threads;
    for (int i = 1; i <= 5; ++i) {
        threads.emplace_back(workerThread, i);
    }
    
    // Очікування завершення потоків
    // Wait for threads to complete
    // Ожидание завершения потоков
    for (auto& t : threads) {
        if (t.joinable()) {
            t.join();
        }
    }
    
    // Запис логу після завершення потоків
    // Write log after threads complete
    // Запись лога после завершения потоков
    gLogger.info("Main", "All worker threads completed");
    
    // Видалення файлового виводу
    // Remove file output
    // Удаление файлового вывода
    if (gLogger.removeLogOutput(LogOutputType::FILE)) {
        std::cout << "File output removed successfully" << std::endl;
    } else {
        std::cout << "Failed to remove file output" << std::endl;
    }
    
    std::cout << "Number of log outputs after removing file output: " << gLogger.getOutputCount() << std::endl;
    
    // Закриття всіх виводів
    // Close all outputs
    // Закрытие всех выводов
    gLogger.closeAllOutputs();
    
    std::cout << "\nLogging system example completed successfully!" << std::endl;
    
    return 0;
}