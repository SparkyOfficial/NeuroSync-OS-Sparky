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
NeuronManager* neuronManager = nullptr;
SynapseBus* synapseBus = nullptr;
Core::Scheduler* scheduler = nullptr;
NeuroSync::Diagnostics::Diagnostics* diagnostics = nullptr;

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
        scheduler = new Core::Scheduler();
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
// These functions are implemented in NeuroAPIAdvanced.cpp

