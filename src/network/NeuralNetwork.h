#ifndef NEURAL_NETWORK_H
#define NEURAL_NETWORK_H

#include <vector>
#include <memory>
#include <string>
#include <map>
#include "../neuron/NeuronManager.h"
#include "../synapse/SynapseBus.h"

// NeuralNetwork.h
// Модуль нейронних мереж для NeuroSync OS Sparky
// Neural network module for NeuroSync OS Sparky
// Модуль нейронных сетей для NeuroSync OS Sparky

namespace NeuroSync {
namespace Network {

    // Тип нейронної мережі
    // Neural network type
    // Тип нейронной сети
    enum class NetworkType {
        FEEDFORWARD,    // Передаюча нейронна мережа / Feedforward neural network / Прямая нейронная сеть
        RECURRENT,      // Рекурентна нейронна мережа / Recurrent neural network / Рекуррентная нейронная сеть
        CONVOLUTIONAL,  // Згорткова нейронна мережа / Convolutional neural network / Сверточная нейронная сеть
        AUTOENCODER,    // Автоенкодер / Autoencoder / Автоэнкодер
        GAN             // Генеративна протиставлена мережа / Generative adversarial network / Генеративная состязательная сеть
    };

    // Структура шару нейронної мережі
    // Neural network layer structure
    // Структура слоя нейронной сети
    struct NetworkLayer {
        int layerId;                    // ID шару / Layer ID / ID слоя
        int neuronCount;                // Кількість нейронів у шарі / Number of neurons in layer / Количество нейронов в слое
        std::string activationFunction; // Функція активації / Activation function / Функция активации
        std::vector<int> neuronIds;     // ID нейронів у шарі / Neuron IDs in layer / ID нейронов в слое
        
        NetworkLayer(int id, int count, const std::string& func)
            : layerId(id), neuronCount(count), activationFunction(func) {}
    };

    // Структура для зберігання ваг зв'язків
    // Structure for storing connection weights
    // Структура для хранения весов связей
    struct ConnectionWeight {
        int sourceNeuronId;     // ID вихідного нейрона / Source neuron ID / ID исходного нейрона
        int targetNeuronId;     // ID цільового нейрона / Target neuron ID / ID целевого нейрона
        double weight;          // Вага зв'язку / Connection weight / Вес связи
        double gradient;        // Градієнт для навчання / Gradient for learning / Градиент для обучения
        
        ConnectionWeight(int source, int target, double w)
            : sourceNeuronId(source), targetNeuronId(target), weight(w), gradient(0.0) {}
    };

    // Нейронна мережа
    // Neural network
    // Нейронная сеть
    class NeuralNetwork {
    public:
        NeuralNetwork(NetworkType type, const std::string& name);
        ~NeuralNetwork();
        
        // Ініціалізація мережі
        // Initialize network
        // Инициализация сети
        bool initialize();
        
        // Додати шар до мережі
        // Add layer to network
        // Добавить слой в сеть
        bool addLayer(int neuronCount, const std::string& activationFunction);
        
        // Видалити шар з мережі
        // Remove layer from network
        // Удалить слой из сети
        bool removeLayer(int layerId);
        
        // Підключити шари
        // Connect layers
        // Соединить слои
        bool connectLayers(int sourceLayerId, int targetLayerId);
        
        // Навчити мережу
        // Train network
        // Обучить сеть
        bool train(const std::vector<std::vector<double>>& inputs, 
                  const std::vector<std::vector<double>>& targets,
                  int epochs, double learningRate);
        
        // Передбачити результат
        // Predict result
        // Предсказать результат
        std::vector<double> predict(const std::vector<double>& input);
        
        // Отримати вихідні дані
        // Get output data
        // Получить выходные данные
        std::vector<double> getOutput();
        
        // Оновити ваги
        // Update weights
        // Обновить веса
        void updateWeights(double learningRate);
        
        // Зберегти модель
        // Save model
        // Сохранить модель
        bool saveModel(const std::string& filename);
        
        // Завантажити модель
        // Load model
        // Загрузить модель
        bool loadModel(const std::string& filename);
        
        // Отримати ім'я мережі
        // Get network name
        // Получить имя сети
        const std::string& getName() const;
        
        // Отримати тип мережі
        // Get network type
        // Получить тип сети
        NetworkType getType() const;
        
        // Отримати кількість шарів
        // Get layer count
        // Получить количество слоев
        size_t getLayerCount() const;
        
        // Отримати кількість нейронів
        // Get neuron count
        // Получить количество нейронов
        size_t getNeuronCount() const;
        
        // Отримати статистику мережі
        // Get network statistics
        // Получить статистику сети
        struct NetworkStatistics {
            size_t totalLayers;
            size_t totalNeurons;
            size_t totalConnections;
            double trainingAccuracy;
            double validationAccuracy;
            long long lastTrainingTime;
        };
        
        NetworkStatistics getStatistics() const;
        
    private:
        NetworkType networkType;                    // Тип мережі / Network type / Тип сети
        std::string networkName;                    // Ім'я мережі / Network name / Имя сети
        std::vector<NetworkLayer> layers;           // Шари мережі / Network layers / Слои сети
        std::vector<ConnectionWeight> connections;   // Зв'язки між нейронами / Connections between neurons / Связи между нейронами
        std::unique_ptr<NeuronManager> neuronManager; // Менеджер нейронів / Neuron manager / Менеджер нейронов
        std::unique_ptr<SynapseBus> synapseBus;     // Шина синапсів / Synapse bus / Шина синапсов
        NetworkStatistics statistics;               // Статистика мережі / Network statistics / Статистика сети
        bool isInitialized;                         // Прапор ініціалізації / Initialization flag / Флаг инициализации
        
        // Внутрішні методи
        // Internal methods
        // Внутренние методы
        void initializeStatistics();
        double calculateLoss(const std::vector<double>& predicted, const std::vector<double>& actual);
        void backpropagate(const std::vector<double>& input, const std::vector<double>& target, double learningRate);
        double sigmoid(double x) const;
        double sigmoidDerivative(double x) const;
        long long getCurrentTimeMillis() const;
    };

} // namespace Network
} // namespace NeuroSync

#endif // NEURAL_NETWORK_H