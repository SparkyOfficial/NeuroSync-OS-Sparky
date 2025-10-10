#ifndef NEURON_UTILS_H
#define NEURON_UTILS_H

#include "../models/NeuronModel.h"
#include "../lifecycle/NeuronLifecycleManager.h"
#include <string>
#include <vector>

// NeuronUtils.h
// Утилиты для работы с нейронами в NeuroSync OS Sparky
// Utilities for working with neurons in NeuroSync OS Sparky
// Утиліти для роботи з нейронами в NeuroSync OS Sparky

namespace NeuroSync {
namespace Neuron {
namespace Utils {

    // Утилиты для работы с нейронами
    // Utilities for working with neurons
    // Утиліти для роботи з нейронами
    class NeuronUtils {
    public:
        // Создание нейронной сети заданной архитектуры
        // Create neural network with specified architecture
        // Створення нейронної мережі заданої архітектури
        static bool createNeuralNetwork(Lifecycle::NeuronLifecycleManager& manager, 
                                       const std::vector<int>& layerSizes);
        
        // Соединение нейронов в полносвязную сеть
        // Connect neurons in a fully connected network
        // З'єднання нейронів у повнозв'язну мережу
        static bool createFullyConnectedNetwork(Lifecycle::NeuronLifecycleManager& manager,
                                              const std::vector<std::vector<int>>& neuronLayers);
        
        // Создание входных нейронов
        // Create input neurons
        // Створення вхідних нейронів
        static std::vector<int> createInputNeurons(Lifecycle::NeuronLifecycleManager& manager, 
                                                  int count, const std::string& prefix = "Input");
        
        // Создание скрытых нейронов
        // Create hidden neurons
        // Створення прихованих нейронів
        static std::vector<int> createHiddenNeurons(Lifecycle::NeuronLifecycleManager& manager, 
                                                   int count, const std::string& prefix = "Hidden");
        
        // Создание выходных нейронов
        // Create output neurons
        // Створення вихідних нейронів
        static std::vector<int> createOutputNeurons(Lifecycle::NeuronLifecycleManager& manager, 
                                                   int count, const std::string& prefix = "Output");
        
        // Создание обрабатывающих нейронов
        // Create processing neurons
        // Створення обробних нейронів
        static std::vector<int> createProcessingNeurons(Lifecycle::NeuronLifecycleManager& manager, 
                                                       int count, const std::string& prefix = "Processing");
        
        // Создание нейронов памяти
        // Create memory neurons
        // Створення нейронів пам'яті
        static std::vector<int> createMemoryNeurons(Lifecycle::NeuronLifecycleManager& manager, 
                                                   int count, const std::string& prefix = "Memory");
        
        // Активация группы нейронов
        // Activate group of neurons
        // Активація групи нейронів
        static bool activateNeurons(Lifecycle::NeuronLifecycleManager& manager, 
                                   const std::vector<int>& neuronIds);
        
        // Деактивация группы нейронов
        // Deactivate group of neurons
        // Деактивація групи нейронів
        static bool deactivateNeurons(Lifecycle::NeuronLifecycleManager& manager, 
                                     const std::vector<int>& neuronIds);
        
        // Установка статуса группы нейронов
        // Set status of group of neurons
        // Встановлення статусу групи нейронів
        static bool setNeuronsStatus(Lifecycle::NeuronLifecycleManager& manager, 
                                    const std::vector<int>& neuronIds, 
                                    Models::NeuronStatus status);
        
        // Добавление входных сигналов группе нейронов
        // Add input signals to group of neurons
        // Додавання вхідних сигналів групі нейронів
        static bool addInputSignalsToNeurons(Lifecycle::NeuronLifecycleManager& manager, 
                                            const std::vector<int>& neuronIds, 
                                            const std::vector<Models::NeuronInput>& inputs);
        
        // Получение статистики нейронной сети
        // Get neural network statistics
        // Отримання статистики нейронної мережі
        static void printNetworkStatistics(const Lifecycle::NeuronLifecycleManager& manager);
        
        // Сохранение состояния нейронной сети
        // Save neural network state
        // Збереження стану нейронної мережі
        static bool saveNetworkState(const Lifecycle::NeuronLifecycleManager& manager, 
                                    const std::string& filename);
        
        // Загрузка состояния нейронной сети
        // Load neural network state
        // Завантаження стану нейронної мережі
        static bool loadNetworkState(Lifecycle::NeuronLifecycleManager& manager, 
                                    const std::string& filename);
        
    private:
        // Внутренние методы
        // Internal methods
        // Внутрішні методи
        static std::string generateNeuronName(const std::string& prefix, int index);
        static double generateRandomWeight();
    };

} // namespace Utils
} // namespace Neuron
} // namespace NeuroSync

#endif // NEURON_UTILS_H