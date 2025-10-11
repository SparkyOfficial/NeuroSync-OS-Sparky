#include "ThreadPool.h"
#include <algorithm>
#include <iostream>

// ThreadPool.cpp
// Реалізація пулу потоків для NeuroSync OS Sparky
// Thread pool implementation for NeuroSync OS Sparky
// Реализация пула потоков для NeuroSync OS Sparky

namespace NeuroSync {

    // Конструктор
    // Constructor
    // Конструктор
    ThreadPool::ThreadPool(size_t threads)
        : stopFlag(false), activeThreads(0) {
        // Створення робочих потоків
        // Creating worker threads
        // Создание рабочих потоков
        for (size_t i = 0; i < threads; ++i) {
            workers.emplace_back(
                [this] {
                    // Основний цикл робочого потоку
                    // Main worker thread loop
                    // Основной цикл рабочего потока
                    while (true) {
                        std::function<void()> task;

                        {
                            std::unique_lock<std::mutex> lock(this->queueMutex);
                            
                            // Очікування на нове завдання або сигнал зупинки
                            // Waiting for new task or stop signal
                            // Ожидание новой задачи или сигнала остановки
                            this->condition.wait(lock,
                                [this] { 
                                    return this->stopFlag.load() || !this->tasks.empty(); 
                                });

                            // Вихід, якщо пул зупинено і немає завдань
                            // Exit if pool is stopped and no tasks
                            // Выход, если пул остановлен и нет задач
                            if (this->stopFlag.load() && this->tasks.empty()) {
                                return;
                            }

                            // Отримання завдання з черги
                            // Getting task from queue
                            // Получение задачи из очереди
                            if (!this->tasks.empty()) {
                                task = std::move(this->tasks.front());
                                this->tasks.pop();
                                
                                // Збільшення лічильника активних потоків
                                // Increment active threads counter
                                // Увеличение счетчика активных потоков
                                this->activeThreads.fetch_add(1);
                            }
                        }

                        // Виконання завдання
                        // Executing task
                        // Выполнение задачи
                        if (task) {
                            try {
                                task();
                            } catch (...) {
                                // Обробка винятків
                                // Exception handling
                                // Обработка исключений
                                std::cerr << "Exception in thread pool task" << std::endl;
                            }
                            
                            // Зменшення лічильника активних потоків
                            // Decrement active threads counter
                            // Уменьшение счетчика активных потоков
                            this->activeThreads.fetch_sub(1);
                        }
                    }
                }
            );
        }
    }

    // Ініціалізація пулу потоків
    // Initialize thread pool
    // Инициализация пула потоков
    bool ThreadPool::initialize() {
        // Пул потоків вже ініціалізовано в конструкторі
        // Thread pool is already initialized in constructor
        // Пул потоков уже инициализирован в конструкторе
        return true;
    }

    // Деструктор
    // Destructor
    // Деструктор
    ThreadPool::~ThreadPool() {
        stop();
        
        // Очікування завершення всіх потоків
        // Waiting for all threads to finish
        // Ожидание завершения всех потоков
        for (std::thread &worker : workers) {
            if (worker.joinable()) {
                worker.join();
            }
        }
    }

    // Отримання кількості потоків
    // Get thread count
    // Получение количества потоков
    size_t ThreadPool::getThreadCount() const {
        return workers.size();
    }

    // Отримання кількості завдань у черзі
    // Get queue size
    // Получение количества задач в очереди
    size_t ThreadPool::getQueueSize() {
        std::lock_guard<std::mutex> lock(queueMutex);
        return tasks.size();
    }

    // Зупинка пулу потоків
    // Stop thread pool
    // Остановка пула потоков
    void ThreadPool::stop() {
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            stopFlag.store(true);
        }
        condition.notify_all();
    }

    // Перезапуск пулу потоків
    // Restart thread pool
    // Перезапуск пула потоков
    void ThreadPool::restart() {
        // Зупинка поточного пулу
        // Stopping current pool
        // Остановка текущего пула
        stop();
        
        // Очікування завершення всіх потоків
        // Waiting for all threads to finish
        // Ожидание завершения всех потоков
        for (std::thread &worker : workers) {
            if (worker.joinable()) {
                worker.join();
            }
        }
        
        // Очищення стану
        // Clearing state
        // Очистка состояния
        workers.clear();
        {
            std::lock_guard<std::mutex> lock(queueMutex);
            while (!tasks.empty()) {
                tasks.pop();
            }
        }
        
        // Скидання прапорців
        // Resetting flags
        // Сброс флагов
        stopFlag.store(false);
        activeThreads.store(0);
        
        // Перестворення потоків
        // Recreating threads
        // Пересоздание потоков
        for (size_t i = 0; i < workers.size(); ++i) {
            workers.emplace_back(
                [this] {
                    while (true) {
                        std::function<void()> task;

                        {
                            std::unique_lock<std::mutex> lock(queueMutex);
                            this->condition.wait(lock,
                                [this] { 
                                    return this->stopFlag.load() || !this->tasks.empty(); 
                                });

                            if (this->stopFlag.load() && this->tasks.empty()) {
                                return;
                            }

                            if (!this->tasks.empty()) {
                                task = std::move(this->tasks.front());
                                this->tasks.pop();
                                this->activeThreads.fetch_add(1);
                            }
                        }

                        if (task) {
                            try {
                                task();
                            } catch (...) {
                                std::cerr << "Exception in thread pool task" << std::endl;
                            }
                            this->activeThreads.fetch_sub(1);
                        }
                    }
                }
            );
        }
    }

} // namespace NeuroSync