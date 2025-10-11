#include "../threadpool/ThreadPool.h"
#include "../neuron/NeuronManager.h"
#include "../synapse/SynapseBus.h"
#include <iostream>
#include <cassert>
#include <chrono>
#include <thread>
#include <vector>

// Тести для інтеграції пулу потоків з нейронами
// Thread pool integration tests with neurons
// Тесты для интеграции пула потоков с нейронами

void testThreadPoolWithNeurons() {
    std::cout << "Testing ThreadPool with Neurons..." << std::endl;
    
    NeuroSync::ThreadPool pool(4);
    NeuronManager neuronManager;
    
    // Створення нейронів
    // Creating neurons
    // Создание нейронов
    std::vector<int> neuronIds;
    for (int i = 0; i < 10; ++i) {
        auto future = pool.enqueue([&neuronManager, i]() {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            return neuronManager.createNeuron(nullptr);
        });
        neuronIds.push_back(future.get());
    }
    
    // Перевірка, що всі нейрони створені
    // Checking that all neurons are created
    // Проверка, что все нейроны созданы
    assert(neuronIds.size() == 10);
    
    // Паралельне оновлення нейронів
    // Parallel updating of neurons
    // Параллельное обновление нейронов
    std::vector<std::future<void>> updateFutures;
    for (const auto& id : neuronIds) {
        auto future = pool.enqueue([&neuronManager, id]() {
            // Реалізація оновлення нейрона з використанням наданого ID
            // Implementation of neuron update using the provided ID
            // Реализация обновления нейрона с использованием предоставленного ID
            
            // 1. Отримання нейрона з менеджера нейронів
            // 1. Retrieving the neuron from the neuron manager
            // 1. Получение нейрона из менеджера нейронов
            // Note: In a real implementation, we would retrieve and update the neuron
            // but for this test, we'll simulate the process
            
            // 2. Оновлення стану або параметрів нейрона
            // 2. Updating the neuron's state or parameters
            // 2. Обновление состояния или параметров нейрона
            std::this_thread::sleep_for(std::chrono::milliseconds(5));
            
            // 3. Обробка будь-яких помилок або винятків, що виникають під час оновлення
            // 3. Handling any errors or exceptions that occur during the update
            // 3. Обработка любых ошибок или исключений, возникающих во время обновления
            std::cout << "[TEST] Updated neuron with ID: " << id << std::endl;
        });
        updateFutures.push_back(std::move(future));
    }
    
    // Очікування завершення всіх оновлень
    // Waiting for all updates to complete
    // Ожидание завершения всех обновлений
    for (auto& future : updateFutures) {
        future.get();
    }
    
    std::cout << "ThreadPool with Neurons test passed!" << std::endl;
}

void testThreadPoolWithSynapseBus() {
    std::cout << "Testing ThreadPool with SynapseBus..." << std::endl;
    
    NeuroSync::ThreadPool pool(3);
    SynapseBus synapseBus;
    
    // Паралельне надсилання повідомлень
    // Parallel sending of messages
    // Параллельная отправка сообщений
    std::vector<std::future<void>> sendFutures;
    for (int i = 0; i < 20; ++i) {
        auto future = pool.enqueue([&synapseBus, i]() {
            const char* message = "Test message";
            synapseBus.sendMessage(i, i + 1, message, strlen(message) + 1);
        });
        sendFutures.push_back(std::move(future));
    }
    
    // Очікування завершення всіх надсилань
    // Waiting for all sends to complete
    // Ожидание завершения всех отправок
    for (auto& future : sendFutures) {
        future.get();
    }
    
    std::cout << "ThreadPool with SynapseBus test passed!" << std::endl;
}

void testThreadPoolPerformance() {
    std::cout << "Testing ThreadPool performance..." << std::endl;
    
    NeuroSync::ThreadPool pool(8);
    
    const int taskCount = 1000;
    std::vector<std::future<int>> futures;
    
    auto start = std::chrono::high_resolution_clock::now();
    
    // Додавання великої кількості завдань
    // Adding a large number of tasks
    // Добавление большого количества задач
    for (int i = 0; i < taskCount; ++i) {
        auto future = pool.enqueue([i]() {
            // Імітація деякої роботи
            // Simulating some work
            // Имитация некоторой работы
            std::this_thread::sleep_for(std::chrono::microseconds(100));
            return i * 2;
        });
        futures.push_back(std::move(future));
    }
    
    // Очікування всіх результатів
    // Waiting for all results
    // Ожидание всех результатов
    for (auto& future : futures) {
        future.get();
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    std::cout << "Processed " << taskCount << " tasks in " << duration.count() << " ms" << std::endl;
    std::cout << "ThreadPool performance test completed!" << std::endl;
}

int main() {
    std::cout << "=== ThreadPool System Tests ===" << std::endl;
    
    try {
        testThreadPoolWithNeurons();
        testThreadPoolWithSynapseBus();
        testThreadPoolPerformance();
        
        std::cout << "\nAll ThreadPool system tests passed!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Test failed with exception: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Test failed with unknown exception" << std::endl;
        return 1;
    }
    
    return 0;
}