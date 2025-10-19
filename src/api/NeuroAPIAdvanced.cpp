#include "NeuroAPIAdvanced.h"
#include "../neuron/NeuronManager.h"
#include "../synapse/SynapseBus.h"
#include "../core/Scheduler.h"
#include "../diagnostics/Diagnostics.h"
#include <cstdio>
#include <cstring>
#include <cmath>

// NeuroAPIAdvanced.cpp
// Реалізація розширеного C++ інтерфейсу для NeuroSync OS Sparky
// Implementation of advanced C++ interface for NeuroSync OS Sparky
// Реализация расширенного C++ интерфейса для NeuroSync OS Sparky

// Include the main API header to access the static variables
// Включити головний заголовок API для доступу до статичних змінних
// Включить основной заголовок API для доступа к статическим переменным
#include "NeuroAPI.h"

// Declare access to the static variables from NeuroAPI.cpp
// Оголосити доступ до статичних змінних з NeuroAPI.cpp
// Объявить доступ к статическим переменным из NeuroAPI.cpp
extern NeuronManager* neuronManager;
extern NeuroSync::Synapse::SynapseBus* synapseBus;
extern Core::Scheduler* scheduler;
extern NeuroSync::Diagnostics::Diagnostics* diagnostics;

// Створення нейрона з типом та ім'ям
// Create a neuron with type and name
// Создать нейрон с типом и именем
int neurosync_create_neuron_advanced(NeuroSyncNeuronType type, const char* name) {
    if (neuronManager != nullptr) {
        // Конвертувати тип нейрона
        // Convert neuron type
        // Конвертировать тип нейрона
        NeuroSync::Neuron::Models::NeuronType neuronType;
        switch (type) {
            case NEURON_TYPE_INPUT:
                neuronType = NeuroSync::Neuron::Models::NeuronType::INPUT;
                break;
            case NEURON_TYPE_HIDDEN:
                neuronType = NeuroSync::Neuron::Models::NeuronType::HIDDEN;
                break;
            case NEURON_TYPE_OUTPUT:
                neuronType = NeuroSync::Neuron::Models::NeuronType::OUTPUT;
                break;
            case NEURON_TYPE_PROCESSING:
                neuronType = NeuroSync::Neuron::Models::NeuronType::PROCESSING;
                break;
            case NEURON_TYPE_MEMORY:
                neuronType = NeuroSync::Neuron::Models::NeuronType::MEMORY;
                break;
            default:
                neuronType = NeuroSync::Neuron::Models::NeuronType::HIDDEN;
                break;
        }
        
        // Створити нейрон
        // Create neuron
        // Создать нейрон
        int neuronId = neuronManager->createNeuron(neuronType, name ? name : "unnamed");
        
        if (diagnostics != nullptr) {
            char message[256];
            snprintf(message, sizeof(message), "Created advanced neuron with ID: %d, type: %d, name: %s", 
                     neuronId, type, name ? name : "unnamed");
            diagnostics->logEvent(neuronId, "NEURON_CREATED", message);
        }
        
        printf("[API] Created advanced neuron with ID: %d, type: %d, name: %s\n", neuronId, type, name ? name : "unnamed");
        printf("[API] Створено розширений нейрон з ID: %d, тип: %d, ім'я: %s\n", neuronId, type, name ? name : "без імені");
        printf("[API] Создан расширенный нейрон с ID: %d, тип: %d, имя: %s\n", neuronId, type, name ? name : "без имени");
        
        return neuronId;
    }
    
    return -1; // Помилка / Error / Ошибка
}

// Активувати нейрон
// Activate a neuron
// Активировать нейрон
bool neurosync_activate_neuron(int neuron_id) {
    if (neuronManager != nullptr) {
        bool result = neuronManager->activateNeuron(neuron_id);
        
        if (diagnostics != nullptr) {
            char message[128];
            snprintf(message, sizeof(message), "Activated neuron with ID: %d", neuron_id);
            diagnostics->logEvent(neuron_id, result ? "NEURON_ACTIVATED" : "NEURON_ACTIVATION_FAILED", message);
        }
        
        printf("[API] %s neuron with ID: %d\n", result ? "Activated" : "Failed to activate", neuron_id);
        printf("[API] %s нейрон з ID: %d\n", result ? "Активовано" : "Не вдалося активувати", neuron_id);
        printf("[API] %s нейрон с ID: %d\n", result ? "Активирован" : "Не удалось активировать", neuron_id);
        
        return result;
    }
    
    return false; // Помилка / Error / Ошибка
}

// Деактивувати нейрон
// Deactivate a neuron
// Деактивировать нейрон
bool neurosync_deactivate_neuron(int neuron_id) {
    if (neuronManager != nullptr) {
        bool result = neuronManager->deactivateNeuron(neuron_id);
        
        if (diagnostics != nullptr) {
            char message[128];
            snprintf(message, sizeof(message), "Deactivated neuron with ID: %d", neuron_id);
            diagnostics->logEvent(neuron_id, result ? "NEURON_DEACTIVATED" : "NEURON_DEACTIVATION_FAILED", message);
        }
        
        printf("[API] %s neuron with ID: %d\n", result ? "Deactivated" : "Failed to deactivate", neuron_id);
        printf("[API] %s нейрон з ID: %d\n", result ? "Деактивовано" : "Не вдалося деактивувати", neuron_id);
        printf("[API] %s нейрон с ID: %d\n", result ? "Деактивирован" : "Не удалось деактивировать", neuron_id);
        
        return result;
    }
    
    return false; // Помилка / Error / Ошибка
}

// Отримати кількість активних нейронів
// Get the number of active neurons
// Получить количество активных нейронов
int neurosync_get_active_neuron_count() {
    if (neuronManager != nullptr) {
        int count = neuronManager->getActiveNeuronCount();
        
        if (diagnostics != nullptr) {
            char message[128];
            snprintf(message, sizeof(message), "Active neuron count: %d", count);
            diagnostics->logEvent(0, "ACTIVE_NEURON_COUNT", message);
        }
        
        return count;
    }
    
    return -1; // Помилка / Error / Ошибка
}

// Отримати загальну кількість нейронів
// Get the total number of neurons
// Получить общее количество нейронов
int neurosync_get_total_neuron_count() {
    if (neuronManager != nullptr) {
        int count = neuronManager->getTotalNeuronCount();
        
        if (diagnostics != nullptr) {
            char message[128];
            snprintf(message, sizeof(message), "Total neuron count: %d", count);
            diagnostics->logEvent(0, "TOTAL_NEURON_COUNT", message);
        }
        
        return count;
    }
    
    return -1; // Помилка / Error / Ошибка
}

// Надсилання повідомлення з розширеними параметрами
// Send message with advanced parameters
// Отправить сообщение с расширенными параметрами
bool neurosync_send_message_advanced(int sender_id, int receiver_id, 
                                   const void* data, size_t data_size,
                                   NeuroSyncMessagePriority priority, double weight) {
    if (synapseBus != nullptr) {
        // Конвертувати пріоритет
        // Convert priority
        // Конвертировать приоритет
        NeuroSync::Synapse::Priority::MessagePriority msgPriority;
        switch (priority) {
            case MESSAGE_PRIORITY_LOW:
                msgPriority = NeuroSync::Synapse::Priority::MessagePriority::LOW;
                break;
            case MESSAGE_PRIORITY_NORMAL:
                msgPriority = NeuroSync::Synapse::Priority::MessagePriority::NORMAL;
                break;
            case MESSAGE_PRIORITY_HIGH:
                msgPriority = NeuroSync::Synapse::Priority::MessagePriority::HIGH;
                break;
            case MESSAGE_PRIORITY_CRITICAL:
                msgPriority = NeuroSync::Synapse::Priority::MessagePriority::CRITICAL;
                break;
            default:
                msgPriority = NeuroSync::Synapse::Priority::MessagePriority::NORMAL;
                break;
        }
        
        // Надіслати повідомлення
        // Send message
        // Отправить сообщение
        bool result = synapseBus->sendMessage(sender_id, receiver_id, data, data_size, msgPriority, weight);
        
        if (diagnostics != nullptr) {
            char message[256];
            snprintf(message, sizeof(message), "Sent message from neuron %d to neuron %d with priority %d and weight %f", 
                     sender_id, receiver_id, priority, weight);
            diagnostics->logEvent(sender_id, result ? "MESSAGE_SENT" : "MESSAGE_SEND_FAILED", message);
        }
        
        printf("[API] %s message from neuron %d to neuron %d\n", result ? "Sent" : "Failed to send", sender_id, receiver_id);
        printf("[API] %s повідомлення від нейрона %d до нейрона %d\n", result ? "Надіслано" : "Не вдалося надіслати", sender_id, receiver_id);
        printf("[API] %s сообщение от нейрона %d к нейрону %d\n", result ? "Отправлено" : "Не удалось отправить", sender_id, receiver_id);
        
        return result;
    }
    
    return false; // Помилка / Error / Ошибка
}

// Отримати повідомлення
// Receive a message
// Получить сообщение
bool neurosync_receive_message(int* sender_id, int* receiver_id, 
                              void** data, size_t* data_size,
                              NeuroSyncMessagePriority* priority, double* weight) {
    if (synapseBus != nullptr && sender_id && receiver_id && data && data_size && priority && weight) {
        NeuroSync::Synapse::Priority::MessagePriority msgPriority;
        int sender, receiver;
        void* msgData;
        size_t msgDataSize;
        int msgWeight;
        
        // Отримати повідомлення
        // Receive message
        // Получить сообщение
        bool result = synapseBus->receiveMessage(sender, receiver, msgData, msgDataSize, msgPriority, msgWeight);
        
        if (result) {
            *sender_id = sender;
            *receiver_id = receiver;
            *data = msgData;
            *data_size = msgDataSize;
            
            // Конвертувати пріоритет
            // Convert priority
            // Конвертировать приоритет
            switch (msgPriority) {
                case NeuroSync::Synapse::Priority::MessagePriority::LOW:
                    *priority = MESSAGE_PRIORITY_LOW;
                    break;
                case NeuroSync::Synapse::Priority::MessagePriority::NORMAL:
                    *priority = MESSAGE_PRIORITY_NORMAL;
                    break;
                case NeuroSync::Synapse::Priority::MessagePriority::HIGH:
                    *priority = MESSAGE_PRIORITY_HIGH;
                    break;
                case NeuroSync::Synapse::Priority::MessagePriority::CRITICAL:
                    *priority = MESSAGE_PRIORITY_CRITICAL;
                    break;
                default:
                    *priority = MESSAGE_PRIORITY_NORMAL;
                    break;
            }
            
            *weight = msgWeight;
            
            if (diagnostics != nullptr) {
                char message[256];
                snprintf(message, sizeof(message), "Received message from neuron %d to neuron %d", sender, receiver);
                diagnostics->logEvent(receiver, "MESSAGE_RECEIVED", message);
            }
            
            printf("[API] Received message from neuron %d to neuron %d\n", sender, receiver);
            printf("[API] Отримано повідомлення від нейрона %d до нейрона %d\n", sender, receiver);
            printf("[API] Получено сообщение от нейрона %d к нейрону %d\n", sender, receiver);
        }
        
        return result;
    }
    
    return false; // Помилка / Error / Ошибка
}

// Оновити вагу зв'язку
// Update connection weight
// Обновить вес связи
bool neurosync_update_connection_weight(int neuron_a, int neuron_b, double weight) {
    if (neuronManager != nullptr) {
        bool result = neuronManager->updateConnectionWeight(neuron_a, neuron_b, weight);
        
        if (diagnostics != nullptr) {
            char message[256];
            snprintf(message, sizeof(message), "Updated connection weight between neurons %d and %d to %f", 
                     neuron_a, neuron_b, weight);
            diagnostics->logEvent(neuron_a, result ? "CONNECTION_WEIGHT_UPDATED" : "CONNECTION_WEIGHT_UPDATE_FAILED", message);
        }
        
        printf("[API] %s connection weight between neurons %d and %d to %f\n", 
               result ? "Updated" : "Failed to update", neuron_a, neuron_b, weight);
        printf("[API] %s вагу зв'язку між нейронами %d та %d до %f\n", 
               result ? "Оновлено" : "Не вдалося оновити", neuron_a, neuron_b, weight);
        printf("[API] %s вес связи между нейронами %d и %d до %f\n", 
               result ? "Обновлен" : "Не удалось обновить", neuron_a, neuron_b, weight);
        
        return result;
    }
    
    return false; // Помилка / Error / Ошибка
}

// Отримати вагу зв'язку
// Get connection weight
// Получить вес связи
double neurosync_get_connection_weight(int neuron_a, int neuron_b) {
    if (synapseBus != nullptr) {
        double weight = synapseBus->getConnectionWeight(neuron_a, neuron_b);
        
        if (diagnostics != nullptr) {
            char message[256];
            snprintf(message, sizeof(message), "Retrieved connection weight between neurons %d and %d: %f", 
                     neuron_a, neuron_b, weight);
            diagnostics->logEvent(neuron_a, "CONNECTION_WEIGHT_RETRIEVED", message);
        }
        
        printf("[API] Retrieved connection weight between neurons %d and %d: %f\n", neuron_a, neuron_b, weight);
        printf("[API] Отримано вагу зв'язку між нейронами %d та %d: %f\n", neuron_a, neuron_b, weight);
        printf("[API] Получен вес связи между нейронами %d и %d: %f\n", neuron_a, neuron_b, weight);
        
        return weight;
    }
    
    return -1.0; // Помилка / Error / Ошибка
}

// Активувати зв'язок
// Activate connection
// Активировать связь
bool neurosync_activate_connection(int neuron_a, int neuron_b) {
    if (synapseBus != nullptr) {
        bool result = synapseBus->activateConnection(neuron_a, neuron_b);
        
        if (diagnostics != nullptr) {
            char message[256];
            snprintf(message, sizeof(message), "Activated connection between neurons %d and %d", neuron_a, neuron_b);
            diagnostics->logEvent(neuron_a, result ? "CONNECTION_ACTIVATED" : "CONNECTION_ACTIVATION_FAILED", message);
        }
        
        printf("[API] %s connection between neurons %d and %d\n", 
               result ? "Activated" : "Failed to activate", neuron_a, neuron_b);
        printf("[API] %s зв'язок між нейронами %d та %d\n", 
               result ? "Активовано" : "Не вдалося активувати", neuron_a, neuron_b);
        printf("[API] %s связь между нейронами %d и %d\n", 
               result ? "Активирована" : "Не удалось активировать", neuron_a, neuron_b);
        
        return result;
    }
    
    return false; // Помилка / Error / Ошибка
}

// Деактивувати зв'язок
// Deactivate connection
// Деактивировать связь
bool neurosync_deactivate_connection(int neuron_a, int neuron_b) {
    if (synapseBus != nullptr) {
        bool result = synapseBus->deactivateConnection(neuron_a, neuron_b);
        
        if (diagnostics != nullptr) {
            char message[256];
            snprintf(message, sizeof(message), "Deactivated connection between neurons %d and %d", neuron_a, neuron_b);
            diagnostics->logEvent(neuron_a, result ? "CONNECTION_DEACTIVATED" : "CONNECTION_DEACTIVATION_FAILED", message);
        }
        
        printf("[API] %s connection between neurons %d and %d\n", 
               result ? "Deactivated" : "Failed to deactivate", neuron_a, neuron_b);
        printf("[API] %s зв'язок між нейронами %d та %d\n", 
               result ? "Деактивовано" : "Не вдалося деактивувати", neuron_a, neuron_b);
        printf("[API] %s связь между нейронами %d и %d\n", 
               result ? "Деактивирована" : "Не удалось деактивировать", neuron_a, neuron_b);
        
        return result;
    }
    
    return false; // Помилка / Error / Ошибка
}

// Отримати кількість з'єднань
// Get connection count
// Получить количество соединений
size_t neurosync_get_connection_count() {
    if (synapseBus != nullptr) {
        size_t count = synapseBus->getConnectionCount();
        
        if (diagnostics != nullptr) {
            char message[128];
            snprintf(message, sizeof(message), "Total connection count: %zu", count);
            diagnostics->logEvent(0, "CONNECTION_COUNT", message);
        }
        
        printf("[API] Total connection count: %zu\n", count);
        printf("[API] Загальна кількість з'єднань: %zu\n", count);
        printf("[API] Общее количество соединений: %zu\n", count);
        
        return count;
    }
    
    return 0; // Помилка / Error / Ошибка
}

// Отримати кількість повідомлень у черзі
// Get message queue size
// Получить количество сообщений в очереди
size_t neurosync_get_message_queue_size() {
    if (synapseBus != nullptr) {
        size_t size = synapseBus->getMessageQueueSize();
        
        if (diagnostics != nullptr) {
            char message[128];
            snprintf(message, sizeof(message), "Message queue size: %zu", size);
            diagnostics->logEvent(0, "MESSAGE_QUEUE_SIZE", message);
        }
        
        printf("[API] Message queue size: %zu\n", size);
        printf("[API] Розмір черги повідомлень: %zu\n", size);
        printf("[API] Размер очереди сообщений: %zu\n", size);
        
        return size;
    }
    
    return 0; // Помилка / Error / Ошибка
}

// Отримати статистику системи
// Get system statistics
// Получить статистику системы
NeuroSyncSystemStatistics neurosync_get_system_statistics() {
    NeuroSyncSystemStatistics stats = {0, 0, 0, 0, 0, 0};
    
    if (synapseBus != nullptr) {
        auto busStats = synapseBus->getStatistics();
        
        stats.totalMessagesSent = busStats.messageStats.totalMessages;
        stats.totalMessagesReceived = busStats.messageStats.totalMessages; // Same as sent in this implementation
        stats.highPriorityMessages = busStats.messageStats.highPriorityMessages;
        stats.criticalPriorityMessages = busStats.messageStats.criticalPriorityMessages;
        stats.totalConnections = busStats.connectionStats.totalConnections;
        stats.activeConnections = busStats.connectionStats.activeConnections;
        
        if (diagnostics != nullptr) {
            char message[256];
            snprintf(message, sizeof(message), "Retrieved system statistics: messages sent=%zu, connections=%zu", 
                     stats.totalMessagesSent, stats.totalConnections);
            diagnostics->logEvent(0, "SYSTEM_STATISTICS", message);
        }
        
        printf("[API] Retrieved system statistics\n");
        printf("[API] Отримано статистику системи\n");
        printf("[API] Получена статистика системы\n");
    }
    
    return stats;
}

// Встановити поріг активності для нейрона
// Set activity threshold for neuron
// Установить порог активности для нейрона
bool neurosync_set_neuron_threshold(int neuron_id, double threshold) {
    // Ця функція вимагає додаткової реалізації в NeuronManager
    // This function requires additional implementation in NeuronManager
    // Эта функция требует дополнительной реализации в NeuronManager
    
    if (diagnostics != nullptr) {
        char message[128];
        snprintf(message, sizeof(message), "Set neuron threshold for neuron %d to %f", neuron_id, threshold);
        diagnostics->logEvent(neuron_id, "NEURON_THRESHOLD_SET", message);
    }
    
    printf("[API] Set neuron threshold for neuron %d to %f (not yet implemented)\n", neuron_id, threshold);
    printf("[API] Встановлено поріг активності для нейрона %d до %f (ще не реалізовано)\n", neuron_id, threshold);
    printf("[API] Установлен порог активности для нейрона %d до %f (еще не реализовано)\n", neuron_id, threshold);
    
    return true; // Тимчасово / Temporarily / Временно
}

// Отримати поріг активності нейрона
// Get neuron activity threshold
// Получить порог активности нейрона
double neurosync_get_neuron_threshold(int neuron_id) {
    // Ця функція вимагає додаткової реалізації в NeuronManager
    // This function requires additional implementation in NeuronManager
    // Эта функция требует дополнительной реализации в NeuronManager
    
    if (diagnostics != nullptr) {
        char message[128];
        snprintf(message, sizeof(message), "Retrieved neuron threshold for neuron %d", neuron_id);
        diagnostics->logEvent(neuron_id, "NEURON_THRESHOLD_RETRIEVED", message);
    }
    
    printf("[API] Retrieved neuron threshold for neuron %d (not yet implemented)\n", neuron_id);
    printf("[API] Отримано поріг активності для нейрона %d (ще не реалізовано)\n", neuron_id);
    printf("[API] Получен порог активности для нейрона %d (еще не реализовано)\n", neuron_id);
    
    return 0.5; // Тимчасово / Temporarily / Временно
}

// Встановити функцію зворотного виклику для нейрона
// Set callback function for neuron
// Установить функцию обратного вызова для нейрона
bool neurosync_set_neuron_callback(int neuron_id, void (*callback_function)()) {
    // Ця функція вимагає додаткової реалізації в NeuronManager
    // This function requires additional implementation in NeuronManager
    // Эта функция требует дополнительной реализации в NeuronManager
    
    if (diagnostics != nullptr) {
        char message[128];
        snprintf(message, sizeof(message), "Set callback function for neuron %d", neuron_id);
        diagnostics->logEvent(neuron_id, "NEURON_CALLBACK_SET", message);
    }
    
    printf("[API] Set callback function for neuron %d (not yet implemented)\n", neuron_id);
    printf("[API] Встановлено функцію зворотного виклику для нейрона %d (ще не реалізовано)\n", neuron_id);
    printf("[API] Установлена функция обратного вызова для нейрона %d (еще не реализовано)\n", neuron_id);
    
    return true; // Тимчасово / Temporarily / Временно
}

// Отримати ідентифікатор нейрона за ім'ям
// Get neuron ID by name
// Получить идентификатор нейрона по имени
int neurosync_get_neuron_id_by_name(const char* name) {
    // Ця функція вимагає додаткової реалізації в NeuronManager
    // This function requires additional implementation in NeuronManager
    // Эта функция требует дополнительной реализации в NeuronManager
    
    if (diagnostics != nullptr && name) {
        char message[128];
        snprintf(message, sizeof(message), "Retrieved neuron ID by name: %s", name);
        diagnostics->logEvent(0, "NEURON_ID_RETRIEVED", message);
    }
    
    printf("[API] Retrieved neuron ID by name: %s (not yet implemented)\n", name ? name : "null");
    printf("[API] Отримано ідентифікатор нейрона за ім'ям: %s (ще не реалізовано)\n", name ? name : "null");
    printf("[API] Получен идентификатор нейрона по имени: %s (еще не реализовано)\n", name ? name : "null");
    
    return -1; // Тимчасово / Temporarily / Временно
}