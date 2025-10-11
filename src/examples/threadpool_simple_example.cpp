#include "../threadpool/ThreadPool.h"
#include <iostream>
#include <chrono>
#include <thread>

// Простий приклад використання пулу потоків
// Simple thread pool usage example
// Простой пример использования пула потоков

int main() {
    std::cout << "=== Simple ThreadPool Example ===" << std::endl;
    
    // Створення пулу потоків з 3 потоками
    // Creating thread pool with 3 threads
    // Создание пула потоков с 3 потоками
    NeuroSync::ThreadPool pool(3);
    
    std::cout << "ThreadPool created with " << pool.getThreadCount() << " threads" << std::endl;
    
    // Додавання простого завдання
    // Adding simple task
    // Добавление простой задачи
    auto future1 = pool.enqueue([]() {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        return 42;
    });
    
    // Додавання ще одного завдання
    // Adding another task
    // Добавление еще одной задачи
    auto future2 = pool.enqueue([]() {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        return 3.14;
    });
    
    // Додавання завдання без повернення значення
    // Adding task without return value
    // Добавление задачи без возврата значения
    auto future3 = pool.enqueue([]() {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "Task without return value completed!" << std::endl;
    });
    
    std::cout << "All tasks enqueued, waiting for results..." << std::endl;
    
    // Отримання результатів
    // Getting results
    // Получение результатов
    int result1 = future1.get();
    double result2 = future2.get();
    future3.get(); // Завдання без повернення значення
    
    std::cout << "Result 1: " << result1 << std::endl;
    std::cout << "Result 2: " << result2 << std::endl;
    
    // Демонстрація кількості завдань у черзі
    // Demonstrating queue size
    // Демонстрация количества задач в очереди
    std::cout << "Current queue size: " << pool.getQueueSize() << std::endl;
    
    // Додавання багатьох завдань одночасно
    // Adding many tasks simultaneously
    // Добавление многих задач одновременно
    std::cout << "\nEnqueuing 10 tasks..." << std::endl;
    std::vector<std::future<int>> futures;
    
    for (int i = 0; i < 10; ++i) {
        auto future = pool.enqueue([i]() {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            return i * i;
        });
        futures.push_back(std::move(future));
    }
    
    std::cout << "Queue size after enqueuing 10 tasks: " << pool.getQueueSize() << std::endl;
    
    // Отримання всіх результатів
    // Getting all results
    // Получение всех результатов
    std::cout << "Results: ";
    for (auto& future : futures) {
        std::cout << future.get() << " ";
    }
    std::cout << std::endl;
    
    std::cout << "\nSimple ThreadPool example completed!" << std::endl;
    
    return 0;
}