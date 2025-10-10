#include "NeuroAPI.h"
#include "../neuron/NeuronManager.h"
#include "../synapse/SynapseBus.h"
#include "../core/Scheduler.h"
#include "../diagnostics/Diagnostics.h"
#include <cstdio>

// NeuroAPI.cpp
// Реалізація C++ інтерфейсу для NeuroSync OS Sparky
// Implementation of C++ interface for NeuroSync OS Sparky
// Реалізація C++ інтерфейсу для NeuroSync OS Sparky

// Глобальні екземпляри компонентів
// Global component instances
// Глобальні екземпляри компонентів
static NeuronManager* neuronManager = nullptr;
static SynapseBus* synapseBus = nullptr;
static Scheduler* scheduler = nullptr;
static NeuroSync::Diagnostics::Diagnostics* diagnostics = nullptr;

void neurosync_init() {
    // Ініціалізація всіх компонентів системи
    // Initialize all system components
    // Ініціалізувати всі компоненти системи
    
    if (neuronManager == nullptr) {
        neuronManager = new NeuronManager();
    }
    
    if (synapseBus == nullptr) {
        synapseBus = new SynapseBus();
    }
    
    if (scheduler == nullptr) {
        scheduler = new Scheduler();
    }
    
    if (diagnostics == nullptr) {
        diagnostics = new NeuroSync::Diagnostics::Diagnostics();
    }
    
    printf("[API] NeuroSync OS Sparky initialized\n");
    printf("[API] NeuroSync OS Sparky ініціалізовано\n");
    printf("[API] NeuroSync OS Sparky инициализирован\n");
}

int neurosync_create_neuron(void (*process_function)()) {
    // Створення нейрона через NeuronManager
    // Create neuron through NeuronManager
    // Створити нейрон через NeuronManager
    
    if (neuronManager != nullptr) {
        int neuronId = neuronManager->createNeuron(process_function);
        printf("[API] Created neuron with ID: %d\n", neuronId);
        printf("[API] Створено нейрон з ID: %d\n", neuronId);
        printf("[API] Создан нейрон с ID: %d\n", neuronId);
        return neuronId;
    }
    
    return -1; // Помилка / Error / Помилка
}

void neurosync_delete_neuron(int neuron_id) {
    // Видалення нейрона через NeuronManager
    // Delete neuron through NeuronManager
    // Видалити нейрон через NeuronManager
    
    if (neuronManager != nullptr) {
        neuronManager->deleteNeuron(neuron_id);
        printf("[API] Deleted neuron with ID: %d\n", neuron_id);
        printf("[API] Видалено нейрон з ID: %d\n", neuron_id);
        printf("[API] Удален нейрон с ID: %d\n", neuron_id);
    }
}

bool neurosync_create_connection(int neuron_a, int neuron_b, int weight) {
    // Створення зв'язку між нейронами через SynapseBus
    // Create connection between neurons through SynapseBus
    // Створити зв'язок між нейронами через SynapseBus
    
    if (synapseBus != nullptr) {
        bool result = synapseBus->createConnection(neuron_a, neuron_b, weight);
        printf("[API] Created connection between neurons %d and %d with weight %d\n", neuron_a, neuron_b, weight);
        printf("[API] Створено зв'язок між нейронами %d та %d з вагою %d\n", neuron_a, neuron_b, weight);
        printf("[API] Создана связь между нейронами %d и %d с весом %d\n", neuron_a, neuron_b, weight);
        return result;
    }
    
    return false; // Помилка / Error / Помилка
}

bool neurosync_send_message(int sender_id, int receiver_id, void* data, size_t data_size, int priority, int weight) {
    // Надсилання повідомлення через SynapseBus
    // Send message through SynapseBus
    // Надіслати повідомлення через SynapseBus
    
    if (synapseBus != nullptr) {
        // Конвертувати пріоритет
        // Convert priority
        // Конвертировать приоритет
        NeuroSync::Synapse::Priority::MessagePriority msgPriority;
        switch (priority) {
            case 0:
                msgPriority = NeuroSync::Synapse::Priority::MessagePriority::LOW;
                break;
            case 1:
                msgPriority = NeuroSync::Synapse::Priority::MessagePriority::NORMAL;
                break;
            case 2:
                msgPriority = NeuroSync::Synapse::Priority::MessagePriority::HIGH;
                break;
            case 3:
                msgPriority = NeuroSync::Synapse::Priority::MessagePriority::CRITICAL;
                break;
            default:
                msgPriority = NeuroSync::Synapse::Priority::MessagePriority::NORMAL;
                break;
        }
        
        bool result = synapseBus->sendMessage(sender_id, receiver_id, data, data_size, msgPriority, weight);
        printf("[API] Sent message from neuron %d to neuron %d\n", sender_id, receiver_id);
        printf("[API] Надіслано повідомлення від нейрона %d до нейрона %d\n", sender_id, receiver_id);
        printf("[API] Отправлено сообщение от нейрона %d к нейрону %d\n", sender_id, receiver_id);
        return result;
    }
    
    return false; // Помилка / Error / Помилка
}

void neurosync_start() {
    // Запуск системи через Scheduler
    // Start system through Scheduler
    // Запустити систему через Scheduler
    
    if (scheduler != nullptr) {
        scheduler->start();
        printf("[API] NeuroSync OS Sparky started\n");
        printf("[API] NeuroSync OS Sparky запущено\n");
        printf("[API] NeuroSync OS Sparky запущен\n");
    }
    
    if (diagnostics != nullptr) {
        diagnostics->startTracing();
    }
}

void neurosync_stop() {
    // Зупинка системи через Scheduler
    // Stop system through Scheduler
    // Зупинити систему через Scheduler
    
    if (scheduler != nullptr) {
        scheduler->stop();
        printf("[API] NeuroSync OS Sparky stopped\n");
        printf("[API] NeuroSync OS Sparky зупинено\n");
        printf("[API] NeuroSync OS Sparky остановлен\n");
    }
    
    if (diagnostics != nullptr) {
        diagnostics->stopTracing();
    }
}

// Розширені функції API
// Advanced API functions
// Расширенные функции API

// Створення нейрона з типом та ім'ям
// Create a neuron with type and name
// Создать нейрон с типом и именем
int neurosync_create_neuron_advanced(NeuroSyncNeuronType type, const char* name) {
    return ::neurosync_create_neuron_advanced(type, name);
}

// Активувати нейрон
// Activate a neuron
// Активировать нейрон
bool neurosync_activate_neuron(int neuron_id) {
    return ::neurosync_activate_neuron(neuron_id);
}

// Деактивувати нейрон
// Deactivate a neuron
// Деактивировать нейрон
bool neurosync_deactivate_neuron(int neuron_id) {
    return ::neurosync_deactivate_neuron(neuron_id);
}

// Отримати кількість активних нейронів
// Get the number of active neurons
// Получить количество активных нейронов
int neurosync_get_active_neuron_count() {
    return ::neurosync_get_active_neuron_count();
}

// Отримати загальну кількість нейронів
// Get the total number of neurons
// Получить общее количество нейронов
int neurosync_get_total_neuron_count() {
    return ::neurosync_get_total_neuron_count();
}

// Надсилання повідомлення з розширеними параметрами
// Send message with advanced parameters
// Отправить сообщение с расширенными параметрами
bool neurosync_send_message_advanced(int sender_id, int receiver_id, 
                                   const void* data, size_t data_size,
                                   NeuroSyncMessagePriority priority, double weight) {
    return ::neurosync_send_message_advanced(sender_id, receiver_id, data, data_size, priority, weight);
}

// Отримати повідомлення
// Receive a message
// Получить сообщение
bool neurosync_receive_message(int* sender_id, int* receiver_id, 
                              void** data, size_t* data_size,
                              NeuroSyncMessagePriority* priority, double* weight) {
    return ::neurosync_receive_message(sender_id, receiver_id, data, data_size, priority, weight);
}

// Оновити вагу зв'язку
// Update connection weight
// Обновить вес связи
bool neurosync_update_connection_weight(int neuron_a, int neuron_b, double weight) {
    return ::neurosync_update_connection_weight(neuron_a, neuron_b, weight);
}

// Отримати вагу зв'язку
// Get connection weight
// Получить вес связи
double neurosync_get_connection_weight(int neuron_a, int neuron_b) {
    return ::neurosync_get_connection_weight(neuron_a, neuron_b);
}

// Активувати зв'язок
// Activate connection
// Активировать связь
bool neurosync_activate_connection(int neuron_a, int neuron_b) {
    return ::neurosync_activate_connection(neuron_a, neuron_b);
}

// Деактивувати зв'язок
// Deactivate connection
// Деактивировать связь
bool neurosync_deactivate_connection(int neuron_a, int neuron_b) {
    return ::neurosync_deactivate_connection(neuron_a, neuron_b);
}

// Отримати кількість з'єднань
// Get connection count
// Получить количество соединений
size_t neurosync_get_connection_count() {
    return ::neurosync_get_connection_count();
}

// Отримати кількість повідомлень у черзі
// Get message queue size
// Получить количество сообщений в очереди
size_t neurosync_get_message_queue_size() {
    return ::neurosync_get_message_queue_size();
}

// Отримати статистику системи
// Get system statistics
// Получить статистику системы
NeuroSyncSystemStatistics neurosync_get_system_statistics() {
    return ::neurosync_get_system_statistics();
}

// Встановити поріг активності для нейрона
// Set activity threshold for neuron
// Установить порог активности для нейрона
bool neurosync_set_neuron_threshold(int neuron_id, double threshold) {
    return ::neurosync_set_neuron_threshold(neuron_id, threshold);
}

// Отримати поріг активності нейрона
// Get neuron activity threshold
// Получить порог активности нейрона
double neurosync_get_neuron_threshold(int neuron_id) {
    return ::neurosync_get_neuron_threshold(neuron_id);
}

// Встановити функцію зворотного виклику для нейрона
// Set callback function for neuron
// Установить функцию обратного вызова для нейрона
bool neurosync_set_neuron_callback(int neuron_id, void (*callback_function)()) {
    return ::neurosync_set_neuron_callback(neuron_id, callback_function);
}

// Отримати ідентифікатор нейрона за ім'ям
// Get neuron ID by name
// Получить идентификатор нейрона по имени
int neurosync_get_neuron_id_by_name(const char* name) {
    return ::neurosync_get_neuron_id_by_name(name);
}