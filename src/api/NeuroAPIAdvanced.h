#ifndef NEURO_API_ADVANCED_H
#define NEURO_API_ADVANCED_H

#include <cstddef>

// NeuroAPIAdvanced.h
// Розширений C++ інтерфейс для NeuroSync OS Sparky
// Advanced C++ interface for NeuroSync OS Sparky
// Расширенный C++ интерфейс для NeuroSync OS Sparky

#ifdef __cplusplus
extern "C" {
#endif

// Типи нейронів
// Neuron types
// Типы нейронов
typedef enum {
    NEURON_TYPE_INPUT = 0,
    NEURON_TYPE_HIDDEN = 1,
    NEURON_TYPE_OUTPUT = 2,
    NEURON_TYPE_PROCESSING = 3,
    NEURON_TYPE_MEMORY = 4
} NeuroSyncNeuronType;

// Пріоритети повідомлень
// Message priorities
// Приоритеты сообщений
typedef enum {
    MESSAGE_PRIORITY_LOW = 0,
    MESSAGE_PRIORITY_NORMAL = 1,
    MESSAGE_PRIORITY_HIGH = 2,
    MESSAGE_PRIORITY_CRITICAL = 3
} NeuroSyncMessagePriority;

// Статистика системи
// System statistics
// Статистика системы
typedef struct {
    size_t totalMessagesSent;
    size_t totalMessagesReceived;
    size_t highPriorityMessages;
    size_t criticalPriorityMessages;
    size_t totalConnections;
    size_t activeConnections;
} NeuroSyncSystemStatistics;

// Створення нейрона з типом та ім'ям
// Create a neuron with type and name
// Создать нейрон с типом и именем
int neurosync_create_neuron_advanced(NeuroSyncNeuronType type, const char* name);

// Активувати нейрон
// Activate a neuron
// Активировать нейрон
bool neurosync_activate_neuron(int neuron_id);

// Деактивувати нейрон
// Deactivate a neuron
// Деактивировать нейрон
bool neurosync_deactivate_neuron(int neuron_id);

// Отримати кількість активних нейронів
// Get the number of active neurons
// Получить количество активных нейронов
int neurosync_get_active_neuron_count();

// Отримати загальну кількість нейронів
// Get the total number of neurons
// Получить общее количество нейронов
int neurosync_get_total_neuron_count();

// Надсилання повідомлення з розширеними параметрами
// Send message with advanced parameters
// Отправить сообщение с расширенными параметрами
bool neurosync_send_message_advanced(int sender_id, int receiver_id, 
                                   const void* data, size_t data_size,
                                   NeuroSyncMessagePriority priority, double weight);

// Отримати повідомлення
// Receive a message
// Получить сообщение
bool neurosync_receive_message(int* sender_id, int* receiver_id, 
                              void** data, size_t* data_size,
                              NeuroSyncMessagePriority* priority, double* weight);

// Оновити вагу зв'язку
// Update connection weight
// Обновить вес связи
bool neurosync_update_connection_weight(int neuron_a, int neuron_b, double weight);

// Отримати вагу зв'язку
// Get connection weight
// Получить вес связи
double neurosync_get_connection_weight(int neuron_a, int neuron_b);

// Активувати зв'язок
// Activate connection
// Активировать связь
bool neurosync_activate_connection(int neuron_a, int neuron_b);

// Деактивувати зв'язок
// Deactivate connection
// Деактивировать связь
bool neurosync_deactivate_connection(int neuron_a, int neuron_b);

// Отримати кількість з'єднань
// Get connection count
// Получить количество соединений
size_t neurosync_get_connection_count();

// Отримати кількість повідомлень у черзі
// Get message queue size
// Получить количество сообщений в очереди
size_t neurosync_get_message_queue_size();

// Отримати статистику системи
// Get system statistics
// Получить статистику системы
NeuroSyncSystemStatistics neurosync_get_system_statistics();

// Встановити поріг активності для нейрона
// Set activity threshold for neuron
// Установить порог активности для нейрона
bool neurosync_set_neuron_threshold(int neuron_id, double threshold);

// Отримати поріг активності нейрона
// Get neuron activity threshold
// Получить порог активности нейрона
double neurosync_get_neuron_threshold(int neuron_id);

// Встановити функцію зворотного виклику для нейрона
// Set callback function for neuron
// Установить функцию обратного вызова для нейрона
bool neurosync_set_neuron_callback(int neuron_id, void (*callback_function)());

// Отримати ідентифікатор нейрона за ім'ям
// Get neuron ID by name
// Получить идентификатор нейрона по имени
int neurosync_get_neuron_id_by_name(const char* name);

#ifdef __cplusplus
}
#endif

#endif // NEURO_API_ADVANCED_H