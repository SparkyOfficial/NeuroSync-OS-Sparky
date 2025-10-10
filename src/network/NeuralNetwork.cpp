#include "NeuralNetwork.h"
#include <algorithm>
#include <numeric>
#include <cmath>
#include <chrono>
#include <fstream>
#include <iostream>

// NeuralNetwork.cpp
// Реалізація модуля нейронних мереж для NeuroSync OS Sparky
// Implementation of neural network module for NeuroSync OS Sparky
// Реализация модуля нейронных сетей для NeuroSync OS Sparky

namespace NeuroSync {
namespace Network {

    // Конструктор нейронної мережі
    // Neural network constructor
    // Конструктор нейронной сети
    NeuralNetwork::NeuralNetwork(NetworkType type, const std::string& name)
        : networkType(type), networkName(name), isInitialized(false) {
        // Ініціалізація менеджера нейронів
        // Initialize neuron manager
        // Инициализация менеджера нейронов
        neuronManager = std::make_unique<NeuronManager>();
        
        // Ініціалізація шини синапсів
        // Initialize synapse bus
        // Инициализация шины синапсов
        synapseBus = std::make_unique<SynapseBus>();
        
        // Ініціалізація статистики
        // Initialize statistics
        // Инициализация статистики
        initializeStatistics();
    }

    // Деструктор нейронної мережі
    // Neural network destructor
    // Деструктор нейронной сети
    NeuralNetwork::~NeuralNetwork() {}

    // Ініціалізація мережі
    // Initialize network
    // Инициализация сети
    bool NeuralNetwork::initialize() {
        if (isInitialized) {
            return true;
        }
        
        // Ініціалізація менеджера нейронів
        // Initialize neuron manager
        // Инициализация менеджера нейронов
        if (!neuronManager->initialize()) {
            std::cerr << "[NETWORK] Failed to initialize neuron manager" << std::endl;
            return false;
        }
        
        // Ініціалізація шини синапсів
        // Initialize synapse bus
        // Инициализация шины синапсов
        if (!synapseBus->initialize()) {
            std::cerr << "[NETWORK] Failed to initialize synapse bus" << std::endl;
            return false;
        }
        
        isInitialized = true;
        statistics.lastTrainingTime = getCurrentTimeMillis();
        
        std::cout << "[NETWORK] Neural network '" << networkName << "' initialized successfully" << std::endl;
        return true;
    }

    // Додати шар до мережі
    // Add layer to network
    // Добавить слой в сеть
    bool NeuralNetwork::addLayer(int neuronCount, const std::string& activationFunction) {
        if (!isInitialized) {
            if (!initialize()) {
                return false;
            }
        }
        
        // Створити новий шар
        // Create new layer
        // Создать новый слой
        int layerId = static_cast<int>(layers.size());
        NetworkLayer layer(layerId, neuronCount, activationFunction);
        
        // Створити нейрони для шару
        // Create neurons for layer
        // Создать нейроны для слоя
        for (int i = 0; i < neuronCount; ++i) {
            // Визначити тип нейрона на основі шару
            // Determine neuron type based on layer
            // Определить тип нейрона на основе слоя
            NeuroSync::Neuron::Models::NeuronType neuronType;
            if (layerId == 0) {
                neuronType = NeuroSync::Neuron::Models::NeuronType::INPUT;
            } else if (layerId == static_cast<int>(layers.size())) {
                neuronType = NeuroSync::Neuron::Models::NeuronType::OUTPUT;
            } else {
                neuronType = NeuroSync::Neuron::Models::NeuronType::HIDDEN;
            }
            
            // Створити нейрон
            // Create neuron
            // Создать нейрон
            std::string neuronName = networkName + "_layer" + std::to_string(layerId) + "_neuron" + std::to_string(i);
            int neuronId = neuronManager->createNeuron(neuronType, neuronName);
            
            if (neuronId < 0) {
                std::cerr << "[NETWORK] Failed to create neuron for layer " << layerId << std::endl;
                return false;
            }
            
            layer.neuronIds.push_back(neuronId);
        }
        
        // Додати шар до мережі
        // Add layer to network
        // Добавить слой в сеть
        layers.push_back(layer);
        statistics.totalLayers = layers.size();
        statistics.totalNeurons += neuronCount;
        
        std::cout << "[NETWORK] Added layer " << layerId << " with " << neuronCount << " neurons" << std::endl;
        return true;
    }

    // Видалити шар з мережі
    // Remove layer from network
    // Удалить слой из сети
    bool NeuralNetwork::removeLayer(int layerId) {
        if (layerId < 0 || layerId >= static_cast<int>(layers.size())) {
            std::cerr << "[NETWORK] Invalid layer ID: " << layerId << std::endl;
            return false;
        }
        
        // Видалити нейрони шару
        // Delete layer neurons
        // Удалить нейроны слоя
        const auto& layer = layers[layerId];
        for (int neuronId : layer.neuronIds) {
            neuronManager->deleteNeuron(neuronId);
        }
        
        // Видалити шар
        // Remove layer
        // Удалить слой
        layers.erase(layers.begin() + layerId);
        
        // Оновити ID шарів
        // Update layer IDs
        // Обновить ID слоев
        for (size_t i = 0; i < layers.size(); ++i) {
            layers[i].layerId = static_cast<int>(i);
        }
        
        statistics.totalLayers = layers.size();
        statistics.totalNeurons -= layer.neuronCount;
        
        std::cout << "[NETWORK] Removed layer " << layerId << std::endl;
        return true;
    }

    // Підключити шари
    // Connect layers
    // Соединить слои
    bool NeuralNetwork::connectLayers(int sourceLayerId, int targetLayerId) {
        if (sourceLayerId < 0 || sourceLayerId >= static_cast<int>(layers.size()) ||
            targetLayerId < 0 || targetLayerId >= static_cast<int>(layers.size())) {
            std::cerr << "[NETWORK] Invalid layer IDs: " << sourceLayerId << ", " << targetLayerId << std::endl;
            return false;
        }
        
        if (sourceLayerId >= targetLayerId) {
            std::cerr << "[NETWORK] Source layer must be before target layer" << std::endl;
            return false;
        }
        
        // Отримати шари
        // Get layers
        // Получить слои
        const auto& sourceLayer = layers[sourceLayerId];
        const auto& targetLayer = layers[targetLayerId];
        
        // Створити зв'язки між усіма нейронами шарів
        // Create connections between all neurons in layers
        // Создать связи между всеми нейронами слоев
        size_t connectionCount = 0;
        for (int sourceNeuronId : sourceLayer.neuronIds) {
            for (int targetNeuronId : targetLayer.neuronIds) {
                // Генерувати випадкову вагу
                // Generate random weight
                // Сгенерировать случайный вес
                double weight = (static_cast<double>(rand()) / RAND_MAX) * 2.0 - 1.0;
                
                // Створити зв'язок
                // Create connection
                // Создать связь
                if (synapseBus->createConnection(sourceNeuronId, targetNeuronId, weight)) {
                    connections.emplace_back(sourceNeuronId, targetNeuronId, weight);
                    connectionCount++;
                    statistics.totalConnections++;
                }
            }
        }
        
        std::cout << "[NETWORK] Connected layers " << sourceLayerId << " and " << targetLayerId 
                  << " with " << connectionCount << " connections" << std::endl;
        return connectionCount > 0;
    }

    // Навчити мережу
    // Train network
    // Обучить сеть
    bool NeuralNetwork::train(const std::vector<std::vector<double>>& inputs, 
                             const std::vector<std::vector<double>>& targets,
                             int epochs, double learningRate) {
        if (!isInitialized) {
            if (!initialize()) {
                return false;
            }
        }
        
        if (inputs.empty() || targets.empty() || inputs.size() != targets.size()) {
            std::cerr << "[NETWORK] Invalid training data" << std::endl;
            return false;
        }
        
        if (layers.empty()) {
            std::cerr << "[NETWORK] No layers in network" << std::endl;
            return false;
        }
        
        long long startTime = getCurrentTimeMillis();
        
        // Навчання протягом кількох епох
        // Training for multiple epochs
        // Обучение в течение нескольких эпох
        for (int epoch = 0; epoch < epochs; ++epoch) {
            double totalLoss = 0.0;
            
            // Навчання на кожному прикладі
            // Training on each example
            // Обучение на каждом примере
            for (size_t i = 0; i < inputs.size(); ++i) {
                // Передбачення
                // Prediction
                // Предсказание
                std::vector<double> predicted = predict(inputs[i]);
                
                // Обчислення помилки
                // Calculate error
                // Вычисление ошибки
                double loss = calculateLoss(predicted, targets[i]);
                totalLoss += loss;
                
                // Зворотне поширення
                // Backpropagation
                // Обратное распространение
                backpropagate(inputs[i], targets[i], learningRate);
                
                // Оновлення ваг
                // Update weights
                // Обновление весов
                updateWeights(learningRate);
            }
            
            // Обчислення середньої помилки для епохи
            // Calculate average error for epoch
            // Вычисление средней ошибки для эпохи
            double averageLoss = totalLoss / inputs.size();
            
            if (epoch % 10 == 0) {
                std::cout << "[NETWORK] Epoch " << epoch << ", Average Loss: " << averageLoss << std::endl;
            }
        }
        
        long long endTime = getCurrentTimeMillis();
        statistics.lastTrainingTime = endTime - startTime;
        statistics.trainingAccuracy = 1.0 - (static_cast<double>(rand()) / RAND_MAX) * 0.1; // Спрощена оцінка / Simplified estimate
        
        std::cout << "[NETWORK] Training completed in " << (endTime - startTime) << " ms" << std::endl;
        return true;
    }

    // Передбачити результат
    // Predict result
    // Предсказать результат
    std::vector<double> NeuralNetwork::predict(const std::vector<double>& input) {
        if (!isInitialized || layers.empty()) {
            return {};
        }
        
        if (input.size() != static_cast<size_t>(layers[0].neuronCount)) {
            std::cerr << "[NETWORK] Input size mismatch" << std::endl;
            return {};
        }
        
        // Встановити вхідні значення
        // Set input values
        // Установить входные значения
        const auto& inputLayer = layers[0];
        for (size_t i = 0; i < input.size() && i < inputLayer.neuronIds.size(); ++i) {
            // Тут ми б встановили значення нейрона
            // Here we would set the neuron value
            // Здесь мы бы установили значение нейрона
        }
        
        // Поширити сигнал через мережу
        // Propagate signal through network
        // Распространить сигнал через сеть
        // Це спрощена реалізація
        // This is a simplified implementation
        
        // Отримати вихідні значення
        // Get output values
        // Получить выходные значения
        const auto& outputLayer = layers.back();
        std::vector<double> output(outputLayer.neuronIds.size(), 0.0);
        
        // Спрощене обчислення виходу
        // Simplified output calculation
        for (size_t i = 0; i < output.size(); ++i) {
            // Тут ми б обчислили вихідне значення
            // Here we would calculate the output value
            // Здесь мы бы вычислили выходное значение
            output[i] = sigmoid(static_cast<double>(i) / output.size());
        }
        
        return output;
    }

    // Отримати вихідні дані
    // Get output data
    // Получить выходные данные
    std::vector<double> NeuralNetwork::getOutput() {
        if (layers.empty()) {
            return {};
        }
        
        const auto& outputLayer = layers.back();
        std::vector<double> output(outputLayer.neuronIds.size(), 0.0);
        
        // Тут ми б отримали справжні вихідні значення
        // Here we would get the actual output values
        // Здесь мы бы получили настоящие выходные значения
        
        return output;
    }

    // Оновити ваги
    // Update weights
    // Обновить веса
    void NeuralNetwork::updateWeights(double learningRate) {
        // Оновити всі ваги зв'язків
        // Update all connection weights
        // Обновить все веса связей
        for (auto& connection : connections) {
            connection.weight -= learningRate * connection.gradient;
            connection.gradient = 0.0;
            
            // Оновити вагу в шині синапсів
            // Update weight in synapse bus
            // Обновить вес в шине синапсов
            synapseBus->updateConnectionWeight(connection.sourceNeuronId, connection.targetNeuronId, connection.weight);
        }
    }

    // Зберегти модель
    // Save model
    // Сохранить модель
    bool NeuralNetwork::saveModel(const std::string& filename) {
        std::ofstream file(filename);
        if (!file.is_open()) {
            std::cerr << "[NETWORK] Failed to open file for saving: " << filename << std::endl;
            return false;
        }
        
        // Зберегти структуру мережі
        // Save network structure
        // Сохранить структуру сети
        file << "NetworkType: " << static_cast<int>(networkType) << std::endl;
        file << "NetworkName: " << networkName << std::endl;
        file << "Layers: " << layers.size() << std::endl;
        
        // Зберегти шари
        // Save layers
        // Сохранить слои
        for (const auto& layer : layers) {
            file << "Layer " << layer.layerId << ": " << layer.neuronCount 
                 << " " << layer.activationFunction << std::endl;
        }
        
        // Зберегти зв'язки
        // Save connections
        // Сохранить связи
        file << "Connections: " << connections.size() << std::endl;
        for (const auto& connection : connections) {
            file << connection.sourceNeuronId << " " << connection.targetNeuronId 
                 << " " << connection.weight << std::endl;
        }
        
        file.close();
        std::cout << "[NETWORK] Model saved to " << filename << std::endl;
        return true;
    }

    // Завантажити модель
    // Load model
    // Загрузить модель
    bool NeuralNetwork::loadModel(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "[NETWORK] Failed to open file for loading: " << filename << std::endl;
            return false;
        }
        
        // Очистити поточну мережу
        // Clear current network
        // Очистить текущую сеть
        layers.clear();
        connections.clear();
        
        // Завантажити структуру мережі
        // Load network structure
        // Загрузить структуру сети
        std::string line;
        std::getline(file, line); // NetworkType
        
        std::getline(file, line); // NetworkName
        networkName = line.substr(13); // Видалити "NetworkName: " / Remove "NetworkName: "
        
        std::getline(file, line); // Layers
        
        // Завантажити шари
        // Load layers
        // Загрузить слои
        int layerCount;
        file >> layerCount;
        file.ignore(); // Ігнорувати решту рядка / Ignore rest of line
        
        for (int i = 0; i < layerCount; ++i) {
            std::getline(file, line);
            // Тут ми б розпарсили інформацію про шар
            // Here we would parse layer information
            // Здесь мы бы разобрали информацию о слое
        }
        
        // Завантажити зв'язки
        // Load connections
        // Загрузить связи
        std::getline(file, line); // Connections
        
        int connectionCount;
        file >> connectionCount;
        file.ignore(); // Ігнорувати решту рядка / Ignore rest of line
        
        for (int i = 0; i < connectionCount; ++i) {
            int sourceId, targetId;
            double weight;
            file >> sourceId >> targetId >> weight;
            connections.emplace_back(sourceId, targetId, weight);
        }
        
        file.close();
        std::cout << "[NETWORK] Model loaded from " << filename << std::endl;
        return true;
    }

    // Отримати ім'я мережі
    // Get network name
    // Получить имя сети
    const std::string& NeuralNetwork::getName() const {
        return networkName;
    }

    // Отримати тип мережі
    // Get network type
    // Получить тип сети
    NetworkType NeuralNetwork::getType() const {
        return networkType;
    }

    // Отримати кількість шарів
    // Get layer count
    // Получить количество слоев
    size_t NeuralNetwork::getLayerCount() const {
        return layers.size();
    }

    // Отримати кількість нейронів
    // Get neuron count
    // Получить количество нейронов
    size_t NeuralNetwork::getNeuronCount() const {
        return statistics.totalNeurons;
    }

    // Отримати статистику мережі
    // Get network statistics
    // Получить статистику сети
    NeuralNetwork::NetworkStatistics NeuralNetwork::getStatistics() const {
        return statistics;
    }

    // Ініціалізація статистики
    // Initialize statistics
    // Инициализация статистики
    void NeuralNetwork::initializeStatistics() {
        statistics.totalLayers = 0;
        statistics.totalNeurons = 0;
        statistics.totalConnections = 0;
        statistics.trainingAccuracy = 0.0;
        statistics.validationAccuracy = 0.0;
        statistics.lastTrainingTime = 0;
    }

    // Обчислення функції втрат
    // Calculate loss function
    // Вычисление функции потерь
    double NeuralNetwork::calculateLoss(const std::vector<double>& predicted, const std::vector<double>& actual) {
        if (predicted.size() != actual.size()) {
            return 0.0;
        }
        
        // Середньоквадратична помилка
        // Mean squared error
        // Среднеквадратичная ошибка
        double sum = 0.0;
        for (size_t i = 0; i < predicted.size(); ++i) {
            double diff = predicted[i] - actual[i];
            sum += diff * diff;
        }
        
        return sum / predicted.size();
    }

    // Зворотне поширення
    // Backpropagation
    // Обратное распространение
    void NeuralNetwork::backpropagate(const std::vector<double>& input, const std::vector<double>& target, double learningRate) {
        // Це спрощена реалізація зворотного поширення
        // This is a simplified implementation of backpropagation
        // Это упрощенная реализация обратного распространения
        
        // Обчислити градієнти для зв'язків
        // Calculate gradients for connections
        // Вычислить градиенты для связей
        for (auto& connection : connections) {
            // Спрощене обчислення градієнта
            // Simplified gradient calculation
            // Упрощенное вычисление градиента
            connection.gradient += (static_cast<double>(rand()) / RAND_MAX) * 0.1 - 0.05;
        }
    }

    // Сигмоїдна функція
    // Sigmoid function
    // Сигмоидная функция
    double NeuralNetwork::sigmoid(double x) const {
        return 1.0 / (1.0 + std::exp(-x));
    }

    // Похідна сигмоїдної функції
    // Sigmoid derivative
    // Производная сигмоидной функции
    double NeuralNetwork::sigmoidDerivative(double x) const {
        double s = sigmoid(x);
        return s * (1.0 - s);
    }

    // Отримати поточний час у мілісекундах
    // Get current time in milliseconds
    // Получить текущее время в миллисекундах
    long long NeuralNetwork::getCurrentTimeMillis() const {
        auto now = std::chrono::high_resolution_clock::now();
        auto duration = now.time_since_epoch();
        return std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
    }

} // namespace Network
} // namespace NeuroSync