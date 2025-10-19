#include "NeuroAPI.h"
#include "../neuron/NeuronManager.h"
#include "../synapse/SynapseBus.h"
#include "../core/Scheduler.h"
#include "../diagnostics/Diagnostics.h"
#include <cstdio>
#include <iostream>

// NeuroAPI.cpp
// Реалізація C++ інтерфейсу для NeuroSync OS Sparky
// Implementation of C++ interface for NeuroSync OS Sparky
// Реалізація C++ інтерфейсу для NeuroSync OS Sparky

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
    
    std::cout << "[API] Initializing NeuroSync OS Sparky..." << std::endl;
    
    if (neuronManager == nullptr) {
        std::cout << "[API] Creating neuron manager" << std::endl;
        neuronManager = new NeuronManager();
    }
    
    if (synapseBus == nullptr) {
        std::cout << "[API] Creating synapse bus" << std::endl;
        synapseBus = new NeuroSync::Synapse::SynapseBus();
    }
    
    // Ініціалізація synapseBus
    // Initialize synapseBus
    // Инициализация synapseBus
    if (synapseBus != nullptr) {
        std::cout << "[API] Initializing synapse bus" << std::endl;
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
            
            // Для тестів просто виводимо повідомлення
            // For tests just output the message
            // Для тестов просто выводим сообщение
            // printf("Received message from neuron %d to neuron %d\n", message.senderId, message.receiverId);
        });
        
        // Запуск обробки повідомлень
        // Start message processing
        // Запуск обработки сообщений
        std::cout << "[API] Starting synapse bus" << std::endl;
        synapseBus->start();
    }
    
    if (scheduler == nullptr) {
        std::cout << "[API] Creating scheduler" << std::endl;
        scheduler = new Core::Scheduler();
    }
    
    if (diagnostics == nullptr) {
        std::cout << "[API] Creating diagnostics" << std::endl;
        diagnostics = new NeuroSync::Diagnostics::Diagnostics();
    }
    
    std::cout << "[API] NeuroSync OS Sparky initialized" << std::endl;
    std::cout << "[API] NeuroSync OS Sparky ініціалізовано" << std::endl;
    std::cout << "[API] NeuroSync OS Sparky инициализирован" << std::endl;
}

int neurosync_create_neuron(void (*process_function)()) {
    // Створення нейрона через NeuronManager
    // Create neuron through NeuronManager
    // Створити нейрон через NeuronManager
    
    std::cout << "[API] Creating neuron" << std::endl;
    
    if (neuronManager != nullptr) {
        int neuronId = neuronManager->createNeuron(process_function);
        std::cout << "[API] Created neuron with ID: " << neuronId << std::endl;
        std::cout << "[API] Створено нейрон з ID: " << neuronId << std::endl;
        std::cout << "[API] Создан нейрон с ID: " << neuronId << std::endl;
        return neuronId;
    }
    
    return -1; // Помилка / Error / Помилка
}

void neurosync_delete_neuron(int neuron_id) {
    // Видалення нейрона через NeuronManager
    // Delete neuron through NeuronManager
    // Видалити нейрон через NeuronManager
    
    std::cout << "[API] Deleting neuron with ID: " << neuron_id << std::endl;
    
    if (neuronManager != nullptr) {
        neuronManager->deleteNeuron(neuron_id);
        std::cout << "[API] Deleted neuron with ID: " << neuron_id << std::endl;
        std::cout << "[API] Видалено нейрон з ID: " << neuron_id << std::endl;
        std::cout << "[API] Удален нейрон с ID: " << neuron_id << std::endl;
    }
}

bool neurosync_create_connection(int neuron_a, int neuron_b, int weight) {
    // Створення зв'язку між нейронами через SynapseBus
    // Create connection between neurons through SynapseBus
    // Створити зв'язок між нейронами через SynapseBus
    
    std::cout << "[API] Creating connection between neurons " << neuron_a << " and " << neuron_b << std::endl;
    
    if (synapseBus != nullptr) {
        bool result = synapseBus->createConnection(neuron_a, neuron_b, weight);
        std::cout << "[API] Created connection between neurons " << neuron_a << " and " << neuron_b << " with weight " << weight << std::endl;
        std::cout << "[API] Створено зв'язок між нейронами " << neuron_a << " та " << neuron_b << " з вагою " << weight << std::endl;
        std::cout << "[API] Создана связь между нейронами " << neuron_a << " и " << neuron_b << " с весом " << weight << std::endl;
        return result;
    }
    
    return false; // Помилка / Error / Помилка
}

bool neurosync_send_message(int sender_id, int receiver_id, void* data, size_t data_size, int priority, int weight) {
    // Надсилання повідомлення через SynapseBus
    // Send message through SynapseBus
    // Надіслати повідомлення через SynapseBus
    
    std::cout << "[API] Sending message from neuron " << sender_id << " to neuron " << receiver_id << std::endl;
    
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
        std::cout << "[API] Message send result: " << result << std::endl;
        // Removed printf statements to avoid hanging
        return result;
    }
    
    return false; // Помилка / Error / Помилка
}

void neurosync_start() {
    // Запуск системи через Scheduler
    // Start system through Scheduler
    // Запустити систему через Scheduler
    
    std::cout << "[API] Starting NeuroSync OS Sparky..." << std::endl;
    
    if (scheduler != nullptr) {
        scheduler->start();
        std::cout << "[API] NeuroSync OS Sparky started" << std::endl;
        std::cout << "[API] NeuroSync OS Sparky запущено" << std::endl;
        std::cout << "[API] NeuroSync OS Sparky запущен" << std::endl;
    }
    
    if (diagnostics != nullptr) {
        diagnostics->startTracing();
    }
}

void neurosync_stop() {
    // Зупинка системи через Scheduler
    // Stop system through Scheduler
    // Зупинити систему через Scheduler
    
    std::cout << "[API] Stopping NeuroSync OS Sparky..." << std::endl;
    
    // Зупинка обробки повідомлень
    // Stop message processing
    // Остановка обработки сообщений
    if (synapseBus != nullptr) {
        std::cout << "[API] Stopping synapse bus..." << std::endl;
        synapseBus->stop();
        std::cout << "[API] Deleting synapse bus..." << std::endl;
        delete synapseBus;
        synapseBus = nullptr;
    }
    
    if (scheduler != nullptr) {
        std::cout << "[API] Stopping scheduler..." << std::endl;
        scheduler->stop();
        delete scheduler;
        scheduler = nullptr;
        std::cout << "[API] NeuroSync OS Sparky stopped" << std::endl;
        std::cout << "[API] NeuroSync OS Sparky зупинено" << std::endl;
        std::cout << "[API] NeuroSync OS Sparky остановлен" << std::endl;
    }
    
    if (diagnostics != nullptr) {
        std::cout << "[API] Stopping diagnostics..." << std::endl;
        diagnostics->stopTracing();
        delete diagnostics;
        diagnostics = nullptr;
    }
    
    if (neuronManager != nullptr) {
        std::cout << "[API] Deleting neuron manager..." << std::endl;
        delete neuronManager;
        neuronManager = nullptr;
    }
    
    std::cout << "[API] All components stopped." << std::endl;
}

// Розширені функції API
// Advanced API functions
// Расширенные функции API
// These functions are implemented in NeuroAPIAdvanced.cpp