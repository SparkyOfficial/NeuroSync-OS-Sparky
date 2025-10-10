#ifndef NEURON_LIFECYCLE_MANAGER_H
#define NEURON_LIFECYCLE_MANAGER_H

#include "../models/NeuronModel.h"
#include <memory>
#include <map>
#include <vector>
#include <mutex>

// NeuronLifecycleManager.h
// Менеджер жизненного цикла нейронов для NeuroSync OS Sparky
// Neuron lifecycle manager for NeuroSync OS Sparky
// Менеджер життєвого циклу нейронів для NeuroSync OS Sparky

namespace NeuroSync {
namespace Neuron {
namespace Lifecycle {

    // Менеджер жизненного цикла нейронов
    // Neuron lifecycle manager
    // Менеджер життєвого циклу нейронів
    class NeuronLifecycleManager {
    public:
        NeuronLifecycleManager();
        ~NeuronLifecycleManager();
        
        // Инициализация менеджера
        // Initialize manager
        // Ініціалізація менеджера
        bool initialize();
        
        // Создание нового нейрона
        // Create a new neuron
        // Створення нового нейрона
        int createNeuron(Models::NeuronType type, const std::string& name);
        
        // Удаление нейрона
        // Delete a neuron
        // Видалення нейрона
        bool deleteNeuron(int neuronId);
        
        // Получение нейрона по ID
        // Get neuron by ID
        // Отримання нейрона за ID
        Models::NeuronModel* getNeuron(int neuronId);
        
        // Активация нейрона
        // Activate a neuron
        // Активація нейрона
        bool activateNeuron(int neuronId);
        
        // Деактивация нейрона
        // Deactivate a neuron
        // Деактивація нейрона
        bool deactivateNeuron(int neuronId);
        
        // Установка статуса нейрона
        // Set neuron status
        // Встановлення статусу нейрона
        bool setNeuronStatus(int neuronId, Models::NeuronStatus status);
        
        // Получение статуса нейрона
        // Get neuron status
        // Отримання статусу нейрона
        Models::NeuronStatus getNeuronStatus(int neuronId);
        
        // Добавление связи между нейронами
        // Add connection between neurons
        // Додавання зв'язку між нейронами
        bool addConnection(int sourceNeuronId, int targetNeuronId, double weight);
        
        // Удаление связи между нейронами
        // Remove connection between neurons
        // Видалення зв'язку між нейронами
        bool removeConnection(int sourceNeuronId, int targetNeuronId);
        
        // Обновление веса связи
        // Update connection weight
        // Оновлення ваги зв'язку
        bool updateConnectionWeight(int sourceNeuronId, int targetNeuronId, double weight);
        
        // Добавление входного сигнала нейрону
        // Add input signal to neuron
        // Додавання вхідного сигналу нейрону
        bool addInputSignal(int neuronId, const Models::NeuronInput& input);
        
        // Проверка, должен ли нейрон сработать
        // Check if neuron should fire
        // Перевірка, чи повинен нейрон спрацювати
        bool shouldNeuronFire(int neuronId);
        
        // Получение выходного сигнала при срабатывании нейрона
        // Get neuron firing output
        // Отримання вихідного сигналу при спрацюванні нейрона
        Models::NeuronOutput getNeuronFiringOutput(int neuronId);
        
        // Получение количества нейронов
        // Get neuron count
        // Отримання кількості нейронів
        size_t getNeuronCount() const;
        
        // Получение количества активных нейронов
        // Get active neuron count
        // Отримання кількості активних нейронів
        size_t getActiveNeuronCount() const;
        
    private:
        // Карта нейронов
        // Map of neurons
        // Карта нейронів
        std::map<int, Models::NeuronModel*> neurons;
        
        // Мьютекс для синхронизации
        // Mutex for synchronization
        // М'ютекс для синхронізації
        mutable std::mutex neuronsMutex;
        
        // Счетчик ID нейронов
        // Neuron ID counter
        // Лічильник ID нейронів
        int neuronIdCounter;
        
        // Флаг инициализации
        // Initialization flag
        // Прапор ініціалізації
        bool initialized;
    };

} // namespace Lifecycle
} // namespace Neuron
} // namespace NeuroSync

#endif // NEURON_LIFECYCLE_MANAGER_H