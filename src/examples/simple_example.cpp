#include "../NeuroSync.h"
#include <cstring>
#include <iostream>

// simple_example.cpp
// Простий приклад використання NeuroSync OS Sparky
// Simple example of using NeuroSync OS Sparky
// Простий приклад використання NeuroSync OS Sparky

// Функція обробки для першого нейрона
// Processing function for the first neuron
// Функція обробки для першого нейрона
void neuron1_process() {
    std::cout << "Neuron 1 processing..." << std::endl;
    std::cout << "Нейрон 1 обробляє..." << std::endl;
    std::cout << "Нейрон 1 обрабатывает..." << std::endl;
}

// Функція обробки для другого нейрона
// Processing function for the second neuron
// Функція обробки для другого нейрона
void neuron2_process() {
    std::cout << "Neuron 2 processing..." << std::endl;
    std::cout << "Нейрон 2 обробляє..." << std::endl;
    std::cout << "Нейрон 2 обрабатывает..." << std::endl;
}

int main() {
    std::cout << "=== NeuroSync OS Sparky Example ===" << std::endl;
    std::cout << "=== Приклад NeuroSync OS Sparky ===" << std::endl;
    std::cout << "=== Пример NeuroSync OS Sparky ===" << std::endl;
    
    // Ініціалізація системи
    // System initialization
    // Ініціалізація системи
    neurosync_init();
    
    // Створення нейронів
    // Creating neurons
    // Створення нейронів
    int neuron1 = neurosync_create_neuron(neuron1_process);
    int neuron2 = neurosync_create_neuron(neuron2_process);
    
    std::cout << "Created neurons: " << neuron1 << ", " << neuron2 << std::endl;
    std::cout << "Створені нейрони: " << neuron1 << ", " << neuron2 << std::endl;
    std::cout << "Созданные нейроны: " << neuron1 << ", " << neuron2 << std::endl;
    
    // Створення зв'язку між нейронами
    // Creating connection between neurons
    // Створення зв'язку між нейронами
    neurosync_create_connection(neuron1, neuron2, 50);
    
    // Надсилання повідомлення
    // Sending a message
    // Надсилання повідомлення
    const char* message = "Hello from neuron 1!";
    neurosync_send_message(neuron1, neuron2, (void*)message, strlen(message) + 1, 1, 50);
    
    // Запуск системи
    // Starting the system
    // Запуск системи
    neurosync_start();
    
    // Імітація роботи протягом деякого часу
    // Simulating work for some time
    // Імітація роботи протягом деякого часу
    for (int i = 0; i < 5; i++) {
        // Реалізація реальної обробки
        // Implement real processing
        // Реалізація реальної обробки
        
        // Отримання статистики системи
        // Get system statistics
        // Получение статистики системы
        NeuroSyncSystemStatistics stats = neurosync_get_system_statistics();
        
        std::cout << "Iteration " << i + 1 << ":" << std::endl;
        std::cout << "  Messages sent: " << stats.totalMessagesSent << std::endl;
        std::cout << "  Messages received: " << stats.totalMessagesReceived << std::endl;
        std::cout << "  Active connections: " << stats.activeConnections << std::endl;
        
        // Надсилання додаткових повідомлень
        // Send additional messages
        // Отправка дополнительных сообщений
        const char* additional_message = "Additional message from neuron 1!";
        neurosync_send_message(neuron1, neuron2, (void*)additional_message, strlen(additional_message) + 1, 1, 50);
        
        // Отримання кількості активних нейронів
        // Get the number of active neurons
        // Получение количества активных нейронов
        int active_neurons = neurosync_get_active_neuron_count();
        std::cout << "  Active neurons: " << active_neurons << std::endl;
        
        // Затримка для спостереження
        // Delay for observation
        // Задержка для наблюдения
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    
    // Зупинка системи
    // Stopping the system
    // Зупинка системи
    neurosync_stop();
    
    // Видалення нейронів
    // Deleting neurons
    // Видалення нейронів
    neurosync_delete_neuron(neuron1);
    neurosync_delete_neuron(neuron2);
    
    std::cout << "Example completed!" << std::endl;
    std::cout << "Приклад завершено!" << std::endl;
    std::cout << "Пример завершен!" << std::endl;
    
    return 0;
}