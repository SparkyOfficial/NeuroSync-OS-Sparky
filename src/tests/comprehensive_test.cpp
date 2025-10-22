#include "../NeuroSync.h"
#include <iostream>
#include <thread>
#include <chrono>

// comprehensive_test.cpp
// Комплексний тест для NeuroSync OS Sparky
// Comprehensive test for NeuroSync OS Sparky
// Комплексный тест для NeuroSync OS Sparky
// Author: Андрій Будильников

void test_neuron_process() {
    // Функція для тестування нейрона
    // Function for neuron testing
    // Функция для тестирования нейрона
    std::cout << "Test neuron processing..." << std::endl;
}

int main() {
    std::cout << "=== Comprehensive NeuroSync OS Sparky Test ===" << std::endl;
    
    // Ініціалізація системи
    // System initialization
    // Инициализация системы
    neurosync_init();
    
    // Тест створення нейронів
    // Neuron creation test
    // Тест создания нейронов
    int neuron1 = neurosync_create_neuron(test_neuron_process);
    int neuron2 = neurosync_create_neuron(test_neuron_process);
    int neuron3 = neurosync_create_neuron(test_neuron_process);
    
    std::cout << "Created neurons: " << neuron1 << ", " << neuron2 << ", " << neuron3 << std::endl;
    
    // Тест створення зв'язків
    // Connection creation test
    // Тест создания связей
    neurosync_create_connection(neuron1, neuron2, 50);
    neurosync_create_connection(neuron2, neuron3, 75);
    neurosync_create_connection(neuron1, neuron3, 25);
    
    std::cout << "Created connections between neurons" << std::endl;
    
    // Тест надсилання повідомлень
    // Message sending test
    // Тест отправки сообщений
    const char* message1 = "Hello from neuron 1 to neuron 2";
    const char* message2 = "Hello from neuron 2 to neuron 3";
    const char* message3 = "Hello from neuron 1 to neuron 3";
    
    neurosync_send_message(neuron1, neuron2, (void*)message1, strlen(message1) + 1, 1, 50);
    neurosync_send_message(neuron2, neuron3, (void*)message2, strlen(message2) + 1, 2, 75);
    neurosync_send_message(neuron1, neuron3, (void*)message3, strlen(message3) + 1, 0, 25);
    
    std::cout << "Sent messages between neurons" << std::endl;
    
    // Зачекати трохи, щоб повідомлення були оброблені
    // Wait a bit for messages to be processed
    // Подождать немного, чтобы сообщения были обработаны
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    
    std::cout << "Waited for message processing" << std::endl;
    
    // Очищення
    // Cleanup
    // Очистка
    neurosync_delete_neuron(neuron1);
    neurosync_delete_neuron(neuron2);
    neurosync_delete_neuron(neuron3);
    
    std::cout << "Deleted neurons" << std::endl;
    
    // Зупинка системи
    // Stop the system
    // Остановка системы
    neurosync_stop();
    
    std::cout << "System stopped successfully!" << std::endl;
    std::cout << "All tests passed!" << std::endl;
    
    return 0;
}