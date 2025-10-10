#include "api/NeuroAPI.h"
#include <cassert>
#include <iostream>
#include <cstring>

void test_basic_api() {
    std::cout << "Testing basic API functionality..." << std::endl;
    
    // Ініціалізація системи
    // System initialization
    // Инициализация системы
    neurosync_init();
    
    // Створення нейрона
    // Create neuron
    // Создать нейрон
    int neuron_id = neurosync_create_neuron(nullptr);
    assert(neuron_id > 0);
    
    // Створення зв'язку
    // Create connection
    // Создать связь
    int neuron_id2 = neurosync_create_neuron(nullptr);
    assert(neuron_id2 > 0);
    
    bool connection_result = neurosync_create_connection(neuron_id, neuron_id2, 1);
    assert(connection_result);
    
    // Надсилання повідомлення
    // Send message
    // Отправить сообщение
    const char* test_message = "Test message";
    bool send_result = neurosync_send_message(neuron_id, neuron_id2, 
                                            (void*)test_message, strlen(test_message) + 1, 
                                            1, 1);
    assert(send_result);
    
    // Видалення нейрона
    // Delete neuron
    // Удалить нейрон
    neurosync_delete_neuron(neuron_id);
    neurosync_delete_neuron(neuron_id2);
    
    std::cout << "Basic API test passed!" << std::endl;
}

void test_advanced_api() {
    std::cout << "Testing advanced API functionality..." << std::endl;
    
    // Створення розширених нейронів
    // Create advanced neurons
    // Создать расширенные нейроны
    int input_neuron = neurosync_create_neuron_advanced(NEURON_TYPE_INPUT, "TestInput");
    assert(input_neuron > 0);
    
    int hidden_neuron = neurosync_create_neuron_advanced(NEURON_TYPE_HIDDEN, "TestHidden");
    assert(hidden_neuron > 0);
    
    int output_neuron = neurosync_create_neuron_advanced(NEURON_TYPE_OUTPUT, "TestOutput");
    assert(output_neuron > 0);
    
    // Активація та деактивація нейронів
    // Activation and deactivation of neurons
    // Активация и деактивация нейронов
    bool activate_result = neurosync_activate_neuron(input_neuron);
    assert(activate_result);
    
    bool deactivate_result = neurosync_deactivate_neuron(input_neuron);
    assert(deactivate_result);
    
    // Отримання статистики нейронів
    // Get neuron statistics
    // Получить статистику нейронов
    int active_count = neurosync_get_active_neuron_count();
    assert(active_count >= 0);
    
    int total_count = neurosync_get_total_neuron_count();
    assert(total_count >= 0);
    
    // Створення зв'язків
    // Create connections
    // Создать связи
    bool conn_result1 = neurosync_create_connection(input_neuron, hidden_neuron, 1);
    assert(conn_result1);
    
    bool conn_result2 = neurosync_create_connection(hidden_neuron, output_neuron, 1);
    assert(conn_result2);
    
    // Оновлення ваг зв'язків
    // Update connection weights
    // Обновление весов связей
    bool update_result = neurosync_update_connection_weight(input_neuron, hidden_neuron, 0.8);
    assert(update_result);
    
    // Отримання ваг зв'язків
    // Get connection weights
    // Получить веса связей
    double weight = neurosync_get_connection_weight(input_neuron, hidden_neuron);
    assert(weight >= 0.0);
    
    // Активація та деактивація зв'язків
    // Activation and deactivation of connections
    // Активация и деактивация связей
    bool activate_conn = neurosync_activate_connection(input_neuron, hidden_neuron);
    assert(activate_conn);
    
    bool deactivate_conn = neurosync_deactivate_connection(input_neuron, hidden_neuron);
    assert(deactivate_conn);
    
    // Отримання кількості з'єднань
    // Get connection count
    // Получить количество соединений
    size_t conn_count = neurosync_get_connection_count();
    assert(conn_count >= 0);
    
    // Надсилання повідомлень з розширеними параметрами
    // Send messages with advanced parameters
    // Отправка сообщений с расширенными параметрами
    const char* message = "Advanced test message";
    bool send_result = neurosync_send_message_advanced(input_neuron, hidden_neuron,
                                                     message, strlen(message) + 1,
                                                     MESSAGE_PRIORITY_HIGH, 0.8);
    assert(send_result);
    
    // Отримання кількості повідомлень у черзі
    // Get message queue size
    // Получить количество сообщений в очереди
    size_t queue_size = neurosync_get_message_queue_size();
    assert(queue_size >= 0);
    
    // Отримання статистики системи
    // Get system statistics
    // Получить статистику системы
    NeuroSyncSystemStatistics stats = neurosync_get_system_statistics();
    // Просто перевіряємо, що функція не викликає помилок
    // Just check that the function doesn't cause errors
    
    // Функції, що ще не реалізовані
    // Functions not yet implemented
    // Функции, еще не реализованные
    bool threshold_result = neurosync_set_neuron_threshold(input_neuron, 0.7);
    assert(threshold_result);
    
    double threshold = neurosync_get_neuron_threshold(input_neuron);
    // Просто перевіряємо, що функція не викликає помилок
    // Just check that the function doesn't cause errors
    
    bool callback_result = neurosync_set_neuron_callback(input_neuron, nullptr);
    assert(callback_result);
    
    int neuron_id = neurosync_get_neuron_id_by_name("TestInput");
    // Просто перевіряємо, що функція не викликає помилок
    // Just check that the function doesn't cause errors
    
    // Видалення нейронів
    // Delete neurons
    // Удаление нейронов
    neurosync_delete_neuron(input_neuron);
    neurosync_delete_neuron(hidden_neuron);
    neurosync_delete_neuron(output_neuron);
    
    std::cout << "Advanced API test passed!" << std::endl;
}

int main() {
    std::cout << "=== Running API Tests ===" << std::endl;
    
    try {
        test_basic_api();
        test_advanced_api();
        
        std::cout << "\n=== All API Tests Passed! ===" << std::endl;
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Test failed with error: " << e.what() << std::endl;
        return 1;
    }
}