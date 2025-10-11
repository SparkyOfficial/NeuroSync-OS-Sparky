#ifndef ADVANCED_NEURAL_NETWORKS_H
#define ADVANCED_NEURAL_NETWORKS_H

#include <vector>
#include <memory>
#include <string>
#include <map>
#include "../network_neural/NeuralNetwork.h"

// AdvancedNeuralNetworks.h
// Модуль розширених нейронних мереж для NeuroSync OS Sparky
// Advanced neural networks module for NeuroSync OS Sparky
// Модуль расширенных нейронных сетей для NeuroSync OS Sparky

namespace NeuroSync {
namespace AdvancedNN {

    // Типи розширених нейронних мереж
    // Types of advanced neural networks
    // Типы расширенных нейронных сетей
    enum class AdvancedNetworkType {
        CONVOLUTIONAL,      // Згорткова нейронна мережа / Convolutional neural network / Сверточная нейронная сеть
        RECURRENT,          // Рекурентна нейронна мережа / Recurrent neural network / Рекуррентная нейронная сеть
        LSTM,               // Довготривала короткотермінова пам'ять / Long short-term memory / Долговременная краткосрочная память
        GRU,                // Модуль управління затворами / Gated recurrent unit / Модуль управления затворами
        AUTOENCODER,        // Автоенкодер / Autoencoder / Автоэнкодер
        VARIATIONAL_AUTOENCODER, // Варіаційний автоенкодер / Variational autoencoder / Вариационный автоэнкодер
        GAN,                // Генеративна протиставлена мережа / Generative adversarial network / Генеративная состязательная сеть
        TRANSFORMER,        // Трансформер / Transformer / Трансформер
        ATTENTION           // Мережа з механізмом уваги / Attention network / Сеть с механизмом внимания
    };

    // Структура згорткового шару
    // Convolutional layer structure
    // Структура сверточного слоя
    struct ConvolutionalLayer {
        int layerId;                    // ID шару / Layer ID / ID слоя
        int inputChannels;              // Кількість вхідних каналів / Number of input channels / Количество входных каналов
        int outputChannels;             // Кількість вихідних каналів / Number of output channels / Количество выходных каналов
        int kernelSize;                 // Розмір ядра згортки / Kernel size / Размер ядра свертки
        int stride;                     // Крок згортки / Stride / Шаг свертки
        int padding;                    // Відступ / Padding / Отступ
        std::string activationFunction; // Функція активації / Activation function / Функция активации
        std::vector<std::vector<std::vector<std::vector<double>>>> kernels; // Ядра згортки / Convolution kernels / Ядра свертки
        std::vector<double> biases;     // Зміщення / Biases / Смещения
        
        ConvolutionalLayer(int id, int inChannels, int outChannels, int kSize, int s = 1, int p = 0, const std::string& func = "relu")
            : layerId(id), inputChannels(inChannels), outputChannels(outChannels), 
              kernelSize(kSize), stride(s), padding(p), activationFunction(func) {
            // Ініціалізація ядер та зміщень
            // Initialize kernels and biases
            // Инициализация ядер и смещений
            initializeKernels();
        }
        
    private:
        void initializeKernels();
    };

    // Структура рекурентного шару
    // Recurrent layer structure
    // Структура рекуррентного слоя
    struct RecurrentLayer {
        int layerId;                    // ID шару / Layer ID / ID слоя
        int inputSize;                  // Розмір вхідних даних / Input size / Размер входных данных
        int hiddenSize;                 // Розмір прихованого стану / Hidden state size / Размер скрытого состояния
        int outputSize;                 // Розмір вихідних даних / Output size / Размер выходных данных
        std::string layerType;          // Тип шару (RNN, LSTM, GRU) / Layer type (RNN, LSTM, GRU) / Тип слоя (RNN, LSTM, GRU)
        std::vector<std::vector<double>> weightsInput;   // Ваги вхідних зв'язків / Input weights / Веса входных связей
        std::vector<std::vector<double>> weightsHidden;  // Ваги рекурентних зв'язків / Recurrent weights / Веса рекуррентных связей
        std::vector<double> biases;     // Зміщення / Biases / Смещения
        
        RecurrentLayer(int id, int inSize, int hidSize, int outSize, const std::string& type = "RNN")
            : layerId(id), inputSize(inSize), hiddenSize(hidSize), outputSize(outSize), layerType(type) {
            // Ініціалізація ваг та зміщень
            // Initialize weights and biases
            // Инициализация весов и смещений
            initializeWeights();
        }
        
    private:
        void initializeWeights();
    };

    // Структура шару трансформера
    // Transformer layer structure
    // Структура слоя трансформера
    struct TransformerLayer {
        int layerId;                    // ID шару / Layer ID / ID слоя
        int modelDimension;             // Розмірність моделі / Model dimension / Размерность модели
        int numHeads;                   // Кількість голов уваги / Number of attention heads / Количество голов внимания
        int feedForwardDimension;       // Розмірність прямого поширення / Feed forward dimension / Размерность прямого распространения
        double dropoutRate;             // Коефіцієнт випадання / Dropout rate / Коэффициент выпадения
        std::vector<std::vector<std::vector<double>>> attentionWeights; // Ваги уваги / Attention weights / Веса внимания
        std::vector<std::vector<double>> feedForwardWeights1; // Ваги першого шару прямого поширення / First feed forward layer weights
        std::vector<std::vector<double>> feedForwardWeights2; // Ваги другого шару прямого поширення / Second feed forward layer weights
        
        TransformerLayer(int id, int modelDim, int heads, int ffDim, double dropout = 0.1)
            : layerId(id), modelDimension(modelDim), numHeads(heads), 
              feedForwardDimension(ffDim), dropoutRate(dropout) {
            // Ініціалізація ваг
            // Initialize weights
            // Инициализация весов
            initializeWeights();
        }
        
    private:
        void initializeWeights();
    };

    // Розширена нейронна мережа
    // Advanced neural network
    // Расширенная нейронная сеть
    class AdvancedNeuralNetwork {
    public:
        AdvancedNeuralNetwork(AdvancedNetworkType type, const std::string& name);
        ~AdvancedNeuralNetwork();
        
        // Ініціалізація мережі
        // Initialize network
        // Инициализация сети
        bool initialize();
        
        // Додати згортковий шар
        // Add convolutional layer
        // Добавить сверточный слой
        bool addConvolutionalLayer(int inputChannels, int outputChannels, int kernelSize, 
                                 int stride = 1, int padding = 0, const std::string& activationFunction = "relu");
        
        // Додати рекурентний шар
        // Add recurrent layer
        // Добавить рекуррентный слой
        bool addRecurrentLayer(int inputSize, int hiddenSize, int outputSize, const std::string& layerType = "RNN");
        
        // Додати шар трансформера
        // Add transformer layer
        // Добавить слой трансформера
        bool addTransformerLayer(int modelDimension, int numHeads, int feedForwardDimension, double dropoutRate = 0.1);
        
        // Додати повністю зв'язаний шар
        // Add fully connected layer
        // Добавить полностью связанный слой
        bool addFullyConnectedLayer(int inputSize, int outputSize, const std::string& activationFunction = "sigmoid");
        
        // Навчити мережу
        // Train network
        // Обучить сеть
        bool train(const std::vector<std::vector<std::vector<double>>>& inputs, 
                  const std::vector<std::vector<std::vector<double>>>& targets,
                  int epochs, double learningRate);
        
        // Передбачити результат
        // Predict result
        // Предсказать результат
        std::vector<std::vector<double>> predict(const std::vector<std::vector<double>>& input);
        
        // Отримати вихідні дані
        // Get output data
        // Получить выходные данные
        std::vector<std::vector<double>> getOutput();
        
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
        AdvancedNetworkType getType() const;
        
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
        AdvancedNetworkType networkType;                    // Тип мережі / Network type / Тип сети
        std::string networkName;                            // Ім'я мережі / Network name / Имя сети
        std::vector<ConvolutionalLayer> convLayers;         // Згорткові шари / Convolutional layers / Сверточные слои
        std::vector<RecurrentLayer> recurrentLayers;        // Рекурентні шари / Recurrent layers / Рекуррентные слои
        std::vector<TransformerLayer> transformerLayers;    // Шари трансформера / Transformer layers / Слои трансформера
        std::vector<Network::NetworkLayer> fullyConnectedLayers; // Повністю зв'язані шари / Fully connected layers / Полностью связанные слои
        std::unique_ptr<Network::NeuralNetwork> baseNetwork; // Базова мережа / Base network / Базовая сеть
        NetworkStatistics statistics;                       // Статистика мережі / Network statistics / Статистика сети
        bool isInitialized;                                 // Прапор ініціалізації / Initialization flag / Флаг инициализации
        std::map<int, std::vector<std::vector<double>>> layerOutputs; // Вихідні дані шарів / Layer outputs / Выходные данные слоев
        
        // Внутрішні методи
        // Internal methods
        // Внутренние методы
        void initializeStatistics();
        double calculateLoss(const std::vector<std::vector<double>>& predicted, const std::vector<std::vector<double>>& actual);
        void backpropagate(const std::vector<std::vector<double>>& input, const std::vector<std::vector<double>>& target, double learningRate);
        std::vector<std::vector<double>> forwardPass(const std::vector<std::vector<double>>& input);
        double sigmoid(double x) const;
        double sigmoidDerivative(double x) const;
        double relu(double x) const;
        double reluDerivative(double x) const;
        std::vector<std::vector<double>> softmax(const std::vector<double>& input) const;
        long long getCurrentTimeMillis() const;
    };

} // namespace AdvancedNN
} // namespace NeuroSync

#endif // ADVANCED_NEURAL_NETWORKS_H