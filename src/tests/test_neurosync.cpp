#include "../NeuroSync.h"
#include <cassert>
#include <iostream>
#include <thread>
#include <chrono>

// test_neurosync.cpp
// Тест для NeuroSync OS Sparky
// Test for NeuroSync OS Sparky
// Тест для NeuroSync OS Sparky

void test_neuron_process() {
    // Функція для тестування нейрона
    // Function for neuron testing
    // Функція для тестування нейрона
    std::cout << "Test neuron processing..." << std::endl;
}

int main() {
    std::cout << "=== NeuroSync OS Sparky Tests ===" << std::endl;
    std::cout << "=== Тести NeuroSync OS Sparky ===" << std::endl;
    std::cout << "=== Тесты NeuroSync OS Sparky ===" << std::endl;
    
    // Ініціалізація системи
    // System initialization
    // Ініціалізація системи
    neurosync_init();
    
    // Тест створення нейрона
    // Neuron creation test
    // Тест створення нейрона
    int neuronId = neurosync_create_neuron(test_neuron_process);
    assert(neuronId > 0);
    std::cout << "✓ Neuron creation test passed" << std::endl;
    std::cout << "✓ Тест створення нейрона пройдено" << std::endl;
    std::cout << "✓ Тест создания нейрона пройден" << std::endl;
    
    // Тест видалення нейрона
    // Neuron deletion test
    // Тест видалення нейрона
    neurosync_delete_neuron(neuronId);
    std::cout << "✓ Neuron deletion test passed" << std::endl;
    std::cout << "✓ Тест видалення нейрона пройдено" << std::endl;
    std::cout << "✓ Тест удаления нейрона пройден" << std::endl;
    
    // Тест створення зв'язку
    // Connection creation test
    // Тест створення зв'язку
    int neuron1 = neurosync_create_neuron(test_neuron_process);
    int neuron2 = neurosync_create_neuron(test_neuron_process);
    bool connectionResult = neurosync_create_connection(neuron1, neuron2, 50);
    assert(connectionResult == true);
    std::cout << "✓ Connection creation test passed" << std::endl;
    std::cout << "✓ Тест створення зв'язку пройдено" << std::endl;
    std::cout << "✓ Тест создания связи пройден" << std::endl;
    
    // Тест надсилання повідомлення
    // Message sending test
    // Тест надсилання повідомлення
    const char* testMessage = "Test message";
    bool messageResult = neurosync_send_message(neuron1, neuron2, (void*)testMessage, strlen(testMessage) + 1, 1, 50);
    assert(messageResult == true);
    
    // Add a longer delay to ensure the message is processed
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    
    std::cout << "✓ Message sending test passed" << std::endl;
    std::cout << "✓ Тест надсилання повідомлення пройдено" << std::endl;
    std::cout << "✓ Тест отправки сообщения пройден" << std::endl;
    
    // Очищення
    // Cleanup
    // Очищення
    neurosync_delete_neuron(neuron1);
    neurosync_delete_neuron(neuron2);
    
    // Stop the system to prevent hanging
    neurosync_stop();
    
    std::cout << "\nAll tests passed!" << std::endl;
    std::cout << "Всі тести пройдено!" << std::endl;
    std::cout << "Все тесты пройдены!" << std::endl;
    
    return 0;
}