#include "NeuronLifecycleManager.h"
#include <algorithm>
#include <iostream>

// NeuronLifecycleManager.cpp
// Реализация менеджера жизненного цикла нейронов для NeuroSync OS Sparky
// Implementation of neuron lifecycle manager for NeuroSync OS Sparky
// Реалізація менеджера життєвого циклу нейронів для NeuroSync OS Sparky

namespace NeuroSync {
namespace Neuron {
namespace Lifecycle {

    NeuronLifecycleManager::NeuronLifecycleManager() 
        : neuronIdCounter(1), initialized(false) {
        // Конструктор менеджера жизненного цикла нейронов
        // Constructor of neuron lifecycle manager
        // Конструктор менеджера життєвого циклу нейронів
    }

    NeuronLifecycleManager::~NeuronLifecycleManager() {
        // Деструктор менеджера жизненного цикла нейронов
        // Destructor of neuron lifecycle manager
        // Деструктор менеджера життєвого циклу нейронів
        
        // Очистка всех нейронов
        // Clear all neurons
        // Очищення всіх нейронів
        for (auto& pair : neurons) {
            delete pair.second;
        }
        neurons.clear();
    }

    bool NeuronLifecycleManager::initialize() {
        // Инициализация менеджера жизненного цикла нейронов
        // Initialize neuron lifecycle manager
        // Ініціалізація менеджера життєвого циклу нейронів
        
        // Проверка, не инициализирован ли уже менеджер
        // Check if manager is already initialized
        // Перевірка, чи не ініціалізовано вже менеджер
        if (initialized) {
            return true;
        }
        
        // Инициализация счетчика ID
        // Initialize ID counter
        // Ініціалізація лічильника ID
        neuronIdCounter = 1;
        
        initialized = true;
        return true;
    }

    int NeuronLifecycleManager::createNeuron(Models::NeuronType type, const std::string& name) {
        // Создание нового нейрона
        // Create a new neuron
        // Створення нового нейрона
        
        // Проверка инициализации
        // Check initialization
        // Перевірка ініціалізації
        if (!initialized) {
            return -1;
        }
        
        // Генерация ID для нового нейрона
        // Generate ID for new neuron
        // Генерація ID для нового нейрона
        int neuronId = neuronIdCounter++;
        
        // Создание нового нейрона
        // Create new neuron
        // Створення нового нейрона
        Models::NeuronModel* neuron = new Models::NeuronModel(neuronId, type, name);
        
        // Добавление нейрона в карту
        // Add neuron to map
        // Додавання нейрона до карти
        {
            std::lock_guard<std::mutex> lock(neuronsMutex);
            neurons[neuronId] = neuron;
        }
        
        return neuronId;
    }

    bool NeuronLifecycleManager::deleteNeuron(int neuronId) {
        // Удаление нейрона
        // Delete a neuron
        // Видалення нейрона
        
        // Проверка инициализации
        // Check initialization
        // Перевірка ініціалізації
        if (!initialized) {
            return false;
        }
        
        // Поиск нейрона по ID
        // Find neuron by ID
        // Пошук нейрона за ID
        std::lock_guard<std::mutex> lock(neuronsMutex);
        auto it = neurons.find(neuronId);
        if (it != neurons.end()) {
            // Удаление нейрона
            // Delete neuron
            // Видалення нейрона
            delete it->second;
            neurons.erase(it);
            return true;
        }
        
        return false; // Нейрон не найден / Neuron not found / Нейрон не знайдено
    }

    Models::NeuronModel* NeuronLifecycleManager::getNeuron(int neuronId) {
        // Получение нейрона по ID
        // Get neuron by ID
        // Отримання нейрона за ID
        
        // Проверка инициализации
        // Check initialization
        // Перевірка ініціалізації
        if (!initialized) {
            return nullptr;
        }
        
        // Поиск нейрона по ID
        // Find neuron by ID
        // Пошук нейрона за ID
        std::lock_guard<std::mutex> lock(neuronsMutex);
        auto it = neurons.find(neuronId);
        if (it != neurons.end()) {
            return it->second;
        }
        
        return nullptr; // Нейрон не найден / Neuron not found / Нейрон не знайдено
    }

    bool NeuronLifecycleManager::activateNeuron(int neuronId) {
        // Активация нейрона
        // Activate a neuron
        // Активація нейрона
        
        // Получение нейрона
        // Get neuron
        // Отримання нейрона
        Models::NeuronModel* neuron = getNeuron(neuronId);
        if (neuron != nullptr) {
            return neuron->activate();
        }
        
        return false; // Нейрон не найден / Neuron not found / Нейрон не знайдено
    }

    bool NeuronLifecycleManager::deactivateNeuron(int neuronId) {
        // Деактивация нейрона
        // Deactivate a neuron
        // Деактивація нейрона
        
        // Получение нейрона
        // Get neuron
        // Отримання нейрона
        Models::NeuronModel* neuron = getNeuron(neuronId);
        if (neuron != nullptr) {
            neuron->deactivate();
            return true;
        }
        
        return false; // Нейрон не найден / Neuron not found / Нейрон не знайдено
    }

    bool NeuronLifecycleManager::setNeuronStatus(int neuronId, Models::NeuronStatus status) {
        // Установка статуса нейрона
        // Set neuron status
        // Встановлення статусу нейрона
        
        // Получение нейрона
        // Get neuron
        // Отримання нейрона
        Models::NeuronModel* neuron = getNeuron(neuronId);
        if (neuron != nullptr) {
            neuron->setStatus(status);
            return true;
        }
        
        return false; // Нейрон не найден / Neuron not found / Нейрон не знайдено
    }

    Models::NeuronStatus NeuronLifecycleManager::getNeuronStatus(int neuronId) {
        // Получение статуса нейрона
        // Get neuron status
        // Отримання статусу нейрона
        
        // Получение нейрона
        // Get neuron
        // Отримання нейрона
        Models::NeuronModel* neuron = getNeuron(neuronId);
        if (neuron != nullptr) {
            return neuron->getStatus();
        }
        
        return Models::NeuronStatus::CREATED; // Нейрон не найден, возвращаем CREATED / Neuron not found, return CREATED / Нейрон не знайдено, повертаємо CREATED
    }

    bool NeuronLifecycleManager::addConnection(int sourceNeuronId, int targetNeuronId, double weight) {
        // Добавление связи между нейронами
        // Add connection between neurons
        // Додавання зв'язку між нейронами
        
        // Получение исходного нейрона
        // Get source neuron
        // Отримання вихідного нейрона
        Models::NeuronModel* sourceNeuron = getNeuron(sourceNeuronId);
        if (sourceNeuron != nullptr) {
            sourceNeuron->addConnection(targetNeuronId, weight);
            return true;
        }
        
        return false; // Исходный нейрон не найден / Source neuron not found / Вихідний нейрон не знайдено
    }

    bool NeuronLifecycleManager::removeConnection(int sourceNeuronId, int targetNeuronId) {
        // Удаление связи между нейронами
        // Remove connection between neurons
        // Видалення зв'язку між нейронами
        
        // Получение исходного нейрона
        // Get source neuron
        // Отримання вихідного нейрона
        Models::NeuronModel* sourceNeuron = getNeuron(sourceNeuronId);
        if (sourceNeuron != nullptr) {
            sourceNeuron->removeConnection(targetNeuronId);
            return true;
        }
        
        return false; // Исходный нейрон не найден / Source neuron not found / Вихідний нейрон не знайдено
    }

    bool NeuronLifecycleManager::updateConnectionWeight(int sourceNeuronId, int targetNeuronId, double weight) {
        // Обновление веса связи
        // Update connection weight
        // Оновлення ваги зв'язку
        
        // Получение исходного нейрона
        // Get source neuron
        // Отримання вихідного нейрона
        Models::NeuronModel* sourceNeuron = getNeuron(sourceNeuronId);
        if (sourceNeuron != nullptr) {
            sourceNeuron->updateConnectionWeight(targetNeuronId, weight);
            return true;
        }
        
        return false; // Исходный нейрон не найден / Source neuron not found / Вихідний нейрон не знайдено
    }

    bool NeuronLifecycleManager::addInputSignal(int neuronId, const Models::NeuronInput& input) {
        // Добавление входного сигнала нейрону
        // Add input signal to neuron
        // Додавання вхідного сигналу нейрону
        
        // Получение нейрона
        // Get neuron
        // Отримання нейрона
        Models::NeuronModel* neuron = getNeuron(neuronId);
        if (neuron != nullptr) {
            neuron->addInput(input);
            return true;
        }
        
        return false; // Нейрон не найден / Neuron not found / Нейрон не знайдено
    }

    bool NeuronLifecycleManager::shouldNeuronFire(int neuronId) {
        // Проверка, должен ли нейрон сработать
        // Check if neuron should fire
        // Перевірка, чи повинен нейрон спрацювати
        
        // Получение нейрона
        // Get neuron
        // Отримання нейрона
        Models::NeuronModel* neuron = getNeuron(neuronId);
        if (neuron != nullptr) {
            return neuron->shouldFire();
        }
        
        return false; // Нейрон не найден / Neuron not found / Нейрон не знайдено
    }

    Models::NeuronOutput NeuronLifecycleManager::getNeuronFiringOutput(int neuronId) {
        // Получение выходного сигнала при срабатывании нейрона
        // Get neuron firing output
        // Отримання вихідного сигналу при спрацюванні нейрона
        
        // Получение нейрона
        // Get neuron
        // Отримання нейрона
        Models::NeuronModel* neuron = getNeuron(neuronId);
        if (neuron != nullptr) {
            return neuron->getFiringOutput();
        }
        
        // Возвращаем пустой выходной сигнал
        // Return empty output signal
        // Повертаємо порожній вихідний сигнал
        Models::NeuronOutput emptyOutput;
        emptyOutput.targetNeuronId = -1;
        emptyOutput.signalStrength = 0.0;
        emptyOutput.timestamp = 0;
        return emptyOutput;
    }

    size_t NeuronLifecycleManager::getNeuronCount() const {
        // Получение количества нейронов
        // Get neuron count
        // Отримання кількості нейронів
        
        std::lock_guard<std::mutex> lock(neuronsMutex);
        return neurons.size();
    }

    size_t NeuronLifecycleManager::getActiveNeuronCount() const {
        // Получение количества активных нейронов
        // Get active neuron count
        // Отримання кількості активних нейронів
        
        size_t activeCount = 0;
        std::lock_guard<std::mutex> lock(neuronsMutex);
        for (const auto& pair : neurons) {
            if (pair.second->getStatus() == Models::NeuronStatus::ACTIVE) {
                activeCount++;
            }
        }
        return activeCount;
    }

} // namespace Lifecycle
} // namespace Neuron
} // namespace NeuroSync