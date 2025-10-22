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
// Author: Андрій Будильников

// Глобальні екземпляри компонентів
// Global component instances
// Глобальні екземпляри компонентів
NeuronManager* neuronManager = nullptr;
NeuroSync::Synapse::SynapseBus* synapseBus = nullptr;
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
        synapseBus = new NeuroSync::Synapse::SynapseBus();
    }
    
    // Ініціалізація synapseBus
    // Initialize synapseBus
    // Инициализация synapseBus
    if (synapseBus != nullptr) {
        synapseBus->initialize();
        
        // Встановлення callback для обробки повідомлень
        // Set callback for message processing
        // Установка callback для обработки сообщений
        synapseBus->setMessageCallback([](const NeuroSync::Synapse::Priority::PriorityMessage& message) {
            // Обробка отриманого повідомлення
            // Process received message
            // Обработка полученного сообщения
            
            // Тут можна додати логіку для передачі повідомлення нейрону
            // Here you can add logic to deliver the message to a neuron
            // Здесь можно добавить логику для передачи сообщения нейрону
        });
        
        // Запуск обробки повідомлень
        // Start message processing
        // Запуск обработки сообщений
        synapseBus->start();
    }
    
    if (scheduler == nullptr) {
        scheduler = new Core::Scheduler();
    }
    
    if (diagnostics == nullptr) {
        diagnostics = new NeuroSync::Diagnostics::Diagnostics();
    }
}

int neurosync_create_neuron(void (*process_function)()) {
    // Створення нейрона через NeuronManager
    // Create neuron through NeuronManager
    // Створити нейрон через NeuronManager
    
    if (neuronManager != nullptr) {
        int neuronId = neuronManager->createNeuron(process_function);
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
    }
}

bool neurosync_create_connection(int neuron_a, int neuron_b, int weight) {
    // Створення зв'язку між нейронами через SynapseBus
    // Create connection between neurons through SynapseBus
    // Створити зв'язок між нейронами через SynapseBus
    
    if (synapseBus != nullptr) {
        bool result = synapseBus->createConnection(neuron_a, neuron_b, weight);
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
    }
    
    if (diagnostics != nullptr) {
        diagnostics->startTracing();
    }
}

void neurosync_stop() {
    // Зупинка системи через Scheduler
    // Stop system through Scheduler
    // Зупинити систему через Scheduler
    
    // Зупинка обробки повідомлень
    // Stop message processing
    // Остановка обработки сообщений
    if (synapseBus != nullptr) {
        synapseBus->stop();
        delete synapseBus;
        synapseBus = nullptr;
    }
    
    if (scheduler != nullptr) {
        scheduler->stop();
        delete scheduler;
        scheduler = nullptr;
    }
    
    if (diagnostics != nullptr) {
        diagnostics->stopTracing();
        delete diagnostics;
        diagnostics = nullptr;
    }
    
    if (neuronManager != nullptr) {
        delete neuronManager;
        neuronManager = nullptr;
    }
}

// Розширені функції API
// Advanced API functions
// Расширенные функции API
// These functions are implemented in NeuroAPIAdvanced.cpp