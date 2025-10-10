#include "api/NeuroAPI.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <vector>

// Приклад функції обробки для нейрона
// Example processing function for neuron
// Пример функции обработки для нейрона
void example_neuron_process() {
    std::cout << "Neuron processing function executed" << std::endl;
}

// Функція для симуляції активності нейронів
// Function to simulate neuron activity
// Функция для симуляции активности нейронов
void simulate_neuron_activity(int neuron_id) {
    std::cout << "Simulating activity for neuron " << neuron_id << std::endl;
    
    // Активувати нейрон
    // Activate neuron
    // Активировать нейрон
    neurosync_activate_neuron(neuron_id);
    
    // Симулювати деяку роботу
    // Simulate some work
    // Симулировать некоторую работу
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    
    // Деактивувати нейрон
    // Deactivate neuron
    // Деактивировать нейрон
    neurosync_deactivate_neuron(neuron_id);
}

int main() {
    std::cout << "=== Advanced API Example for NeuroSync OS Sparky ===" << std::endl;
    
    try {
        // Ініціалізація системи
        // System initialization
        // Инициализация системы
        neurosync_init();
        
        std::cout << "System initialized" << std::endl;
        
        // Створення розширених нейронів
        // Create advanced neurons
        // Создать расширенные нейроны
        int input_neuron = neurosync_create_neuron_advanced(NEURON_TYPE_INPUT, "InputNeuron");
        int hidden_neuron1 = neurosync_create_neuron_advanced(NEURON_TYPE_HIDDEN, "HiddenNeuron1");
        int hidden_neuron2 = neurosync_create_neuron_advanced(NEURON_TYPE_HIDDEN, "HiddenNeuron2");
        int output_neuron = neurosync_create_neuron_advanced(NEURON_TYPE_OUTPUT, "OutputNeuron");
        int processing_neuron = neurosync_create_neuron_advanced(NEURON_TYPE_PROCESSING, "ProcessingNeuron");
        int memory_neuron = neurosync_create_neuron_advanced(NEURON_TYPE_MEMORY, "MemoryNeuron");
        
        std::cout << "Created neurons:" << std::endl;
        std::cout << "  Input Neuron: " << input_neuron << std::endl;
        std::cout << "  Hidden Neuron 1: " << hidden_neuron1 << std::endl;
        std::cout << "  Hidden Neuron 2: " << hidden_neuron2 << std::endl;
        std::cout << "  Output Neuron: " << output_neuron << std::endl;
        std::cout << "  Processing Neuron: " << processing_neuron << std::endl;
        std::cout << "  Memory Neuron: " << memory_neuron << std::endl;
        
        // Отримати статистику нейронів
        // Get neuron statistics
        // Получить статистику нейронов
        int active_count = neurosync_get_active_neuron_count();
        int total_count = neurosync_get_total_neuron_count();
        
        std::cout << "Neuron statistics:" << std::endl;
        std::cout << "  Active neurons: " << active_count << std::endl;
        std::cout << "  Total neurons: " << total_count << std::endl;
        
        // Створення зв'язків між нейронами
        // Create connections between neurons
        // Создать связи между нейронами
        neurosync_create_connection(input_neuron, hidden_neuron1, 0.8);
        neurosync_create_connection(hidden_neuron1, hidden_neuron2, 0.7);
        neurosync_create_connection(hidden_neuron2, output_neuron, 0.9);
        neurosync_create_connection(input_neuron, processing_neuron, 0.6);
        neurosync_create_connection(processing_neuron, memory_neuron, 0.5);
        
        std::cout << "Created connections between neurons" << std::endl;
        
        // Отримати кількість з'єднань
        // Get connection count
        // Получить количество соединений
        size_t connection_count = neurosync_get_connection_count();
        std::cout << "Total connections: " << connection_count << std::endl;
        
        // Активація та деактивація нейронів
        // Activation and deactivation of neurons
        // Активация и деактивация нейронов
        neurosync_activate_neuron(input_neuron);
        neurosync_activate_neuron(hidden_neuron1);
        neurosync_activate_neuron(hidden_neuron2);
        
        std::cout << "Activated input and hidden neurons" << std::endl;
        
        // Оновлення ваг зв'язків
        // Update connection weights
        // Обновление весов связей
        neurosync_update_connection_weight(input_neuron, hidden_neuron1, 0.85);
        neurosync_update_connection_weight(hidden_neuron1, hidden_neuron2, 0.75);
        
        std::cout << "Updated connection weights" << std::endl;
        
        // Отримати ваги зв'язків
        // Get connection weights
        // Получить веса связей
        double weight1 = neurosync_get_connection_weight(input_neuron, hidden_neuron1);
        double weight2 = neurosync_get_connection_weight(hidden_neuron1, hidden_neuron2);
        
        std::cout << "Connection weights:" << std::endl;
        std::cout << "  Input -> Hidden1: " << weight1 << std::endl;
        std::cout << "  Hidden1 -> Hidden2: " << weight2 << std::endl;
        
        // Надсилання повідомлень з розширеними параметрами
        // Send messages with advanced parameters
        // Отправка сообщений с расширенными параметрами
        const char* message_data = "Hello from input neuron";
        neurosync_send_message_advanced(input_neuron, hidden_neuron1, 
                                      message_data, strlen(message_data) + 1,
                                      MESSAGE_PRIORITY_HIGH, 0.8);
        
        const char* response_data = "Hello from hidden neuron";
        neurosync_send_message_advanced(hidden_neuron1, hidden_neuron2,
                                      response_data, strlen(response_data) + 1,
                                      MESSAGE_PRIORITY_NORMAL, 0.7);
        
        std::cout << "Sent messages between neurons" << std::endl;
        
        // Отримати кількість повідомлень у черзі
        // Get message queue size
        // Получить количество сообщений в очереди
        size_t queue_size = neurosync_get_message_queue_size();
        std::cout << "Message queue size: " << queue_size << std::endl;
        
        // Отримати статистику системи
        // Get system statistics
        // Получить статистику системы
        NeuroSyncSystemStatistics stats = neurosync_get_system_statistics();
        std::cout << "System statistics:" << std::endl;
        std::cout << "  Total messages sent: " << stats.totalMessagesSent << std::endl;
        std::cout << "  Total messages received: " << stats.totalMessagesReceived << std::endl;
        std::cout << "  High priority messages: " << stats.highPriorityMessages << std::endl;
        std::cout << "  Critical priority messages: " << stats.criticalPriorityMessages << std::endl;
        std::cout << "  Total connections: " << stats.totalConnections << std::endl;
        std::cout << "  Active connections: " << stats.activeConnections << std::endl;
        
        // Симуляція активності нейронів у потоках
        // Simulate neuron activity in threads
        // Симуляция активности нейронов в потоках
        std::vector<std::thread> threads;
        threads.emplace_back(simulate_neuron_activity, input_neuron);
        threads.emplace_back(simulate_neuron_activity, hidden_neuron1);
        threads.emplace_back(simulate_neuron_activity, hidden_neuron2);
        
        // Очікування завершення потоків
        // Wait for threads to complete
        // Ожидание завершения потоков
        for (auto& thread : threads) {
            thread.join();
        }
        
        std::cout << "All neuron activities completed" << std::endl;
        
        // Отримати оновлену статистику
        // Get updated statistics
        // Получить обновленную статистику
        active_count = neurosync_get_active_neuron_count();
        total_count = neurosync_get_total_neuron_count();
        
        std::cout << "Updated neuron statistics:" << std::endl;
        std::cout << "  Active neurons: " << active_count << std::endl;
        std::cout << "  Total neurons: " << total_count << std::endl;
        
        // Встановлення порогів активності (ще не реалізовано)
        // Set activity thresholds (not yet implemented)
        // Установка порогов активности (еще не реализовано)
        neurosync_set_neuron_threshold(input_neuron, 0.7);
        double threshold = neurosync_get_neuron_threshold(input_neuron);
        std::cout << "Set and retrieved threshold for input neuron: " << threshold << std::endl;
        
        // Встановлення функції зворотного виклику (ще не реалізовано)
        // Set callback function (not yet implemented)
        // Установка функции обратного вызова (еще не реализовано)
        neurosync_set_neuron_callback(input_neuron, example_neuron_process);
        std::cout << "Set callback function for input neuron" << std::endl;
        
        // Отримання ідентифікатора нейрона за ім'ям (ще не реалізовано)
        // Get neuron ID by name (not yet implemented)
        // Получение идентификатора нейрона по имени (еще не реализовано)
        int neuron_id = neurosync_get_neuron_id_by_name("InputNeuron");
        std::cout << "Retrieved neuron ID by name 'InputNeuron': " << neuron_id << std::endl;
        
        // Видалення нейронів
        // Delete neurons
        // Удаление нейронов
        neurosync_delete_neuron(input_neuron);
        neurosync_delete_neuron(hidden_neuron1);
        neurosync_delete_neuron(hidden_neuron2);
        neurosync_delete_neuron(output_neuron);
        neurosync_delete_neuron(processing_neuron);
        neurosync_delete_neuron(memory_neuron);
        
        std::cout << "Deleted all neurons" << std::endl;
        
        std::cout << "Advanced API example completed successfully!" << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}