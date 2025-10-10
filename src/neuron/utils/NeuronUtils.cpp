#include "NeuronUtils.h"
#include <random>
#include <iostream>
#include <fstream>
#include <sstream>

// NeuronUtils.cpp
// Реализация утилит для работы с нейронами в NeuroSync OS Sparky
// Implementation of utilities for working with neurons in NeuroSync OS Sparky
// Реалізація утиліт для роботи з нейронами в NeuroSync OS Sparky

namespace NeuroSync {
namespace Neuron {
namespace Utils {

    bool NeuronUtils::createNeuralNetwork(Lifecycle::NeuronLifecycleManager& manager, 
                                         const std::vector<int>& layerSizes) {
        // Создание нейронной сети заданной архитектуры
        // Create neural network with specified architecture
        // Створення нейронної мережі заданої архітектури
        
        // Проверка параметров
        // Check parameters
        // Перевірка параметрів
        if (layerSizes.empty()) {
            return false;
        }
        
        // Создание слоев нейронов
        // Create neuron layers
        // Створення шарів нейронів
        std::vector<std::vector<int>> neuronLayers;
        
        for (size_t layerIndex = 0; layerIndex < layerSizes.size(); ++layerIndex) {
            std::vector<int> layer;
            int neuronCount = layerSizes[layerIndex];
            
            // Определение типа нейронов в слое
            // Determine neuron type in layer
            // Визначення типу нейронів у шарі
            Models::NeuronType neuronType;
            if (layerIndex == 0) {
                neuronType = Models::NeuronType::INPUT; // Входной слой / Input layer / Вхідний шар
            } else if (layerIndex == layerSizes.size() - 1) {
                neuronType = Models::NeuronType::OUTPUT; // Выходной слой / Output layer / Вихідний шар
            } else {
                neuronType = Models::NeuronType::HIDDEN; // Скрытый слой / Hidden layer / Прихований шар
            }
            
            // Создание нейронов в слое
            // Create neurons in layer
            // Створення нейронів у шарі
            for (int i = 0; i < neuronCount; ++i) {
                std::string neuronName = generateNeuronName(
                    (neuronType == Models::NeuronType::INPUT) ? "Input" :
                    (neuronType == Models::NeuronType::OUTPUT) ? "Output" : "Hidden",
                    static_cast<int>(i)
                );
                
                int neuronId = manager.createNeuron(neuronType, neuronName);
                if (neuronId > 0) {
                    layer.push_back(neuronId);
                }
            }
            
            neuronLayers.push_back(layer);
        }
        
        // Создание полносвязной сети
        // Create fully connected network
        // Створення повнозв'язної мережі
        return createFullyConnectedNetwork(manager, neuronLayers);
    }

    bool NeuronUtils::createFullyConnectedNetwork(Lifecycle::NeuronLifecycleManager& manager,
                                                 const std::vector<std::vector<int>>& neuronLayers) {
        // Соединение нейронов в полносвязную сеть
        // Connect neurons in a fully connected network
        // З'єднання нейронів у повнозв'язну мережу
        
        // Проверка параметров
        // Check parameters
        // Перевірка параметрів
        if (neuronLayers.size() < 2) {
            return false;
        }
        
        // Соединение слоев
        // Connect layers
        // З'єднання шарів
        for (size_t layerIndex = 0; layerIndex < neuronLayers.size() - 1; ++layerIndex) {
            const std::vector<int>& currentLayer = neuronLayers[layerIndex];
            const std::vector<int>& nextLayer = neuronLayers[layerIndex + 1];
            
            // Соединение каждого нейрона текущего слоя со всеми нейронами следующего слоя
            // Connect each neuron in current layer to all neurons in next layer
            // З'єднання кожного нейрона поточного шару з усіма нейронами наступного шару
            for (int sourceNeuronId : currentLayer) {
                for (int targetNeuronId : nextLayer) {
                    double weight = generateRandomWeight();
                    manager.addConnection(sourceNeuronId, targetNeuronId, weight);
                }
            }
        }
        
        return true;
    }

    std::vector<int> NeuronUtils::createInputNeurons(Lifecycle::NeuronLifecycleManager& manager, 
                                                    int count, const std::string& prefix) {
        // Создание входных нейронов
        // Create input neurons
        // Створення вхідних нейронів
        
        std::vector<int> neuronIds;
        
        for (int i = 0; i < count; ++i) {
            std::string neuronName = generateNeuronName(prefix, i);
            int neuronId = manager.createNeuron(Models::NeuronType::INPUT, neuronName);
            if (neuronId > 0) {
                neuronIds.push_back(neuronId);
            }
        }
        
        return neuronIds;
    }

    std::vector<int> NeuronUtils::createHiddenNeurons(Lifecycle::NeuronLifecycleManager& manager, 
                                                     int count, const std::string& prefix) {
        // Создание скрытых нейронов
        // Create hidden neurons
        // Створення прихованих нейронів
        
        std::vector<int> neuronIds;
        
        for (int i = 0; i < count; ++i) {
            std::string neuronName = generateNeuronName(prefix, i);
            int neuronId = manager.createNeuron(Models::NeuronType::HIDDEN, neuronName);
            if (neuronId > 0) {
                neuronIds.push_back(neuronId);
            }
        }
        
        return neuronIds;
    }

    std::vector<int> NeuronUtils::createOutputNeurons(Lifecycle::NeuronLifecycleManager& manager, 
                                                     int count, const std::string& prefix) {
        // Создание выходных нейронов
        // Create output neurons
        // Створення вихідних нейронів
        
        std::vector<int> neuronIds;
        
        for (int i = 0; i < count; ++i) {
            std::string neuronName = generateNeuronName(prefix, i);
            int neuronId = manager.createNeuron(Models::NeuronType::OUTPUT, neuronName);
            if (neuronId > 0) {
                neuronIds.push_back(neuronId);
            }
        }
        
        return neuronIds;
    }

    std::vector<int> NeuronUtils::createProcessingNeurons(Lifecycle::NeuronLifecycleManager& manager, 
                                                         int count, const std::string& prefix) {
        // Создание обрабатывающих нейронов
        // Create processing neurons
        // Створення обробних нейронів
        
        std::vector<int> neuronIds;
        
        for (int i = 0; i < count; ++i) {
            std::string neuronName = generateNeuronName(prefix, i);
            int neuronId = manager.createNeuron(Models::NeuronType::PROCESSING, neuronName);
            if (neuronId > 0) {
                neuronIds.push_back(neuronId);
            }
        }
        
        return neuronIds;
    }

    std::vector<int> NeuronUtils::createMemoryNeurons(Lifecycle::NeuronLifecycleManager& manager, 
                                                     int count, const std::string& prefix) {
        // Создание нейронов памяти
        // Create memory neurons
        // Створення нейронів пам'яті
        
        std::vector<int> neuronIds;
        
        for (int i = 0; i < count; ++i) {
            std::string neuronName = generateNeuronName(prefix, i);
            int neuronId = manager.createNeuron(Models::NeuronType::MEMORY, neuronName);
            if (neuronId > 0) {
                neuronIds.push_back(neuronId);
            }
        }
        
        return neuronIds;
    }

    bool NeuronUtils::activateNeurons(Lifecycle::NeuronLifecycleManager& manager, 
                                     const std::vector<int>& neuronIds) {
        // Активация группы нейронов
        // Activate group of neurons
        // Активація групи нейронів
        
        bool allActivated = true;
        
        for (int neuronId : neuronIds) {
            if (!manager.activateNeuron(neuronId)) {
                allActivated = false;
            }
        }
        
        return allActivated;
    }

    bool NeuronUtils::deactivateNeurons(Lifecycle::NeuronLifecycleManager& manager, 
                                       const std::vector<int>& neuronIds) {
        // Деактивация группы нейронов
        // Deactivate group of neurons
        // Деактивація групи нейронів
        
        bool allDeactivated = true;
        
        for (int neuronId : neuronIds) {
            if (!manager.deactivateNeuron(neuronId)) {
                allDeactivated = false;
            }
        }
        
        return allDeactivated;
    }

    bool NeuronUtils::setNeuronsStatus(Lifecycle::NeuronLifecycleManager& manager, 
                                      const std::vector<int>& neuronIds, 
                                      Models::NeuronStatus status) {
        // Установка статуса группы нейронов
        // Set status of group of neurons
        // Встановлення статусу групи нейронів
        
        bool allSet = true;
        
        for (int neuronId : neuronIds) {
            if (!manager.setNeuronStatus(neuronId, status)) {
                allSet = false;
            }
        }
        
        return allSet;
    }

    bool NeuronUtils::addInputSignalsToNeurons(Lifecycle::NeuronLifecycleManager& manager, 
                                              const std::vector<int>& neuronIds, 
                                              const std::vector<Models::NeuronInput>& inputs) {
        // Добавление входных сигналов группе нейронов
        // Add input signals to group of neurons
        // Додавання вхідних сигналів групі нейронів
        
        if (neuronIds.size() != inputs.size()) {
            return false; // Несоответствие размеров / Size mismatch / Невідповідність розмірів
        }
        
        bool allAdded = true;
        
        for (size_t i = 0; i < neuronIds.size(); ++i) {
            if (!manager.addInputSignal(neuronIds[i], inputs[i])) {
                allAdded = false;
            }
        }
        
        return allAdded;
    }

    void NeuronUtils::printNetworkStatistics(const Lifecycle::NeuronLifecycleManager& manager) {
        // Получение статистики нейронной сети
        // Get neural network statistics
        // Отримання статистики нейронної мережі
        
        std::cout << "=== Neural Network Statistics ===" << std::endl;
        std::cout << "=== Статистика нейронної мережі ===" << std::endl;
        std::cout << "=== Статистика нейронной сети ===" << std::endl;
        
        std::cout << "Total Neurons: " << manager.getNeuronCount() << std::endl;
        std::cout << "Загальна кількість нейронів: " << manager.getNeuronCount() << std::endl;
        std::cout << "Общее количество нейронов: " << manager.getNeuronCount() << std::endl;
        
        std::cout << "Active Neurons: " << manager.getActiveNeuronCount() << std::endl;
        std::cout << "Активні нейрони: " << manager.getActiveNeuronCount() << std::endl;
        std::cout << "Активные нейроны: " << manager.getActiveNeuronCount() << std::endl;
    }

    bool NeuronUtils::saveNetworkState(const Lifecycle::NeuronLifecycleManager& manager, 
                                      const std::string& filename) {
        // Сохранение состояния нейронной сети
        // Save neural network state
        // Збереження стану нейронної мережі
        
        // В реальной реализации здесь будет код сохранения состояния
        // In real implementation, there will be code to save state
        // В реальній реалізації тут буде код збереження стану
        
        std::ofstream file(filename);
        if (!file.is_open()) {
            return false;
        }
        
        file << "# NeuroSync Neural Network State" << std::endl;
        file << "# Стан нейронної мережі NeuroSync" << std::endl;
        file << "# Состояние нейронной сети NeuroSync" << std::endl;
        file << "NeuronCount: " << manager.getNeuronCount() << std::endl;
        
        file.close();
        return true;
    }

    bool NeuronUtils::loadNetworkState(Lifecycle::NeuronLifecycleManager& manager, 
                                      const std::string& filename) {
        // Загрузка состояния нейронной сети
        // Load neural network state
        // Завантаження стану нейронної мережі
        
        // В реальной реализации здесь будет код загрузки состояния
        // In real implementation, there will be code to load state
        // В реальній реалізації тут буде код завантаження стану
        
        std::ifstream file(filename);
        if (!file.is_open()) {
            return false;
        }
        
        std::string line;
        while (std::getline(file, line)) {
            // Обработка строк файла
            // Process file lines
            // Обробка рядків файлу
            if (line.empty() || line[0] == '#') {
                continue; // Пропуск комментариев и пустых строк / Skip comments and empty lines / Пропуск коментарів та порожніх рядків
            }
            
            // Здесь будет код разбора данных
            // Here will be code to parse data
            // Тут буде код розбору даних
        }
        
        file.close();
        return true;
    }

    std::string NeuronUtils::generateNeuronName(const std::string& prefix, int index) {
        // Генерация имени нейрона
        // Generate neuron name
        // Генерація імені нейрона
        
        return prefix + "_" + std::to_string(index);
    }

    double NeuronUtils::generateRandomWeight() {
        // Генерация случайного веса связи
        // Generate random connection weight
        // Генерація випадкової ваги зв'язку
        
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_real_distribution<double> dis(-1.0, 1.0);
        
        return dis(gen);
    }

} // namespace Utils
} // namespace Neuron
} // namespace NeuroSync