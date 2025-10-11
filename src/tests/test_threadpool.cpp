#include "../threadpool/ThreadPool.h"
#include <iostream>
#include <cassert>
#include <chrono>
#include <thread>

// Тести для пулу потоків
// Thread pool tests
// Тесты для пула потоков

void testThreadPoolCreation() {
    std::cout << "Testing ThreadPool creation..." << std::endl;
    
    // Створення пулу потоків з 2 потоками
    // Creating thread pool with 2 threads
    // Создание пула потоков с 2 потоками
    NeuroSync::ThreadPool pool(2);
    
    // Перевірка кількості потоків
    // Checking thread count
    // Проверка количества потоков
    assert(pool.getThreadCount() == 2);
    
    std::cout << "ThreadPool creation test passed!" << std::endl;
}

void testTaskExecution() {
    std::cout << "Testing task execution..." << std::endl;
    
    NeuroSync::ThreadPool pool(4);
    
    // Додавання простого завдання
    // Adding simple task
    // Добавление простой задачи
    auto future = pool.enqueue([]() {
        return 42;
    });
    
    // Отримання результату
    // Getting result
    // Получение результата
    int result = future.get();
    assert(result == 42);
    
    std::cout << "Task execution test passed!" << std::endl;
}

void testMultipleTasks() {
    std::cout << "Testing multiple tasks..." << std::endl;
    
    NeuroSync::ThreadPool pool(4);
    
    const int taskCount = 100;
    std::vector<std::future<int>> futures;
    
    // Додавання кількох завдань
    // Adding multiple tasks
    // Добавление нескольких задач
    for (int i = 0; i < taskCount; ++i) {
        auto future = pool.enqueue([i]() {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
            return i * i;
        });
        futures.push_back(std::move(future));
    }
    
    // Перевірка результатів
    // Checking results
    // Проверка результатов
    for (int i = 0; i < taskCount; ++i) {
        int result = futures[i].get();
        assert(result == i * i);
    }
    
    std::cout << "Multiple tasks test passed!" << std::endl;
}

void testThreadPoolStop() {
    std::cout << "Testing ThreadPool stop..." << std::endl;
    
    NeuroSync::ThreadPool pool(2);
    
    // Додавання завдання
    // Adding task
    // Добавление задачи
    auto future = pool.enqueue([]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        return 123;
    });
    
    // Зупинка пулу
    // Stopping pool
    // Остановка пула
    pool.stop();
    
    // Отримання результату має працювати навіть після зупинки
    // Getting result should work even after stop
    // Получение результата должно работать даже после остановки
    int result = future.get();
    assert(result == 123);
    
    std::cout << "ThreadPool stop test passed!" << std::endl;
}

void testThreadPoolRestart() {
    std::cout << "Testing ThreadPool restart..." << std::endl;
    
    NeuroSync::ThreadPool pool(2);
    
    // Додавання завдання
    // Adding task
    // Добавление задачи
    auto future1 = pool.enqueue([]() {
        return 100;
    });
    
    int result1 = future1.get();
    assert(result1 == 100);
    
    // Перезапуск пулу
    // Restarting pool
    // Перезапуск пула
    pool.restart();
    
    // Додавання ще одного завдання після перезапуску
    // Adding another task after restart
    // Добавление еще одной задачи после перезапуска
    auto future2 = pool.enqueue([]() {
        return 200;
    });
    
    int result2 = future2.get();
    assert(result2 == 200);
    
    assert(pool.getThreadCount() == 2);
    
    std::cout << "ThreadPool restart test passed!" << std::endl;
}

void testExceptionHandling() {
    std::cout << "Testing exception handling..." << std::endl;
    
    NeuroSync::ThreadPool pool(2);
    
    // Додавання завдання, яке викидає виняток
    // Adding task that throws exception
    // Добавление задачи, которая бросает исключение
    auto future = pool.enqueue([]() {
        throw std::runtime_error("Test exception");
        return 42;
    });
    
    // Перевірка обробки винятку
    // Checking exception handling
    // Проверка обработки исключения
    try {
        future.get();
        assert(false); // Має бути виняток
        // Should be exception
        // Должно быть исключение
    } catch (const std::runtime_error& e) {
        assert(std::string(e.what()) == "Test exception");
    }
    
    std::cout << "Exception handling test passed!" << std::endl;
}

int main() {
    std::cout << "=== ThreadPool Tests ===" << std::endl;
    
    try {
        testThreadPoolCreation();
        testTaskExecution();
        testMultipleTasks();
        testThreadPoolStop();
        testThreadPoolRestart();
        testExceptionHandling();
        
        std::cout << "\nAll ThreadPool tests passed!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Test failed with exception: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Test failed with unknown exception" << std::endl;
        return 1;
    }
    
    return 0;
}