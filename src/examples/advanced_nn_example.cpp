#include "../advanced_nn/AdvancedNeuralNetworks.h"
#include <iostream>
#include <vector>
#include <random>

using namespace NeuroSync::AdvancedNN;

// Приклад використання розширених нейронних мереж
// Example of using advanced neural networks
// Пример использования расширенных нейронных сетей

int main() {
    try {
        std::cout << "========================================\n";
        std::cout << "  Advanced Neural Networks Example\n";
        std::cout << "  NeuroSync OS Sparky\n";
        std::cout << "========================================\n\n";
        
        // Створення розширеної нейронної мережі
        // Create advanced neural network
        // Создание расширенной нейронной сети
        std::cout << "Creating advanced neural network...\n";
        auto advancedNN = std::make_unique<AdvancedNeuralNetwork>(
            AdvancedNetworkType::CONVOLUTIONAL, "AdvancedCNN");
        
        // Ініціалізація мережі
        // Initialize network
        // Инициализация сети
        if (!advancedNN->initialize()) {
            std::cerr << "Failed to initialize advanced neural network\n";
            return 1;
        }
        
        std::cout << "Advanced neural network initialized successfully\n\n";
        
        // Додавання згорткових шарів
        // Add convolutional layers
        // Добавление сверточных слоев
        std::cout << "Adding convolutional layers...\n";
        advancedNN->addConvolutionalLayer(3, 32, 3, 1, 1, "relu");  // 32 фільтри 3x3
        advancedNN->addConvolutionalLayer(32, 64, 3, 1, 1, "relu"); // 64 фільтри 3x3
        advancedNN->addConvolutionalLayer(64, 128, 3, 1, 1, "relu"); // 128 фільтрів 3x3
        
        // Додавання повністю зв'язаних шарів
        // Add fully connected layers
        // Добавление полностью связанных слоев
        std::cout << "Adding fully connected layers...\n";
        advancedNN->addFullyConnectedLayer(128, 256, "relu");
        advancedNN->addFullyConnectedLayer(256, 10, "softmax"); // 10 класів для класифікації
        
        std::cout << "Network architecture created with " << advancedNN->getLayerCount() << " layers\n\n";
        
        // Генерація навчальних даних
        // Generate training data
        // Генерация обучающих данных
        std::cout << "Generating training data...\n";
        std::random_device rd;
        std::mt19937 gen(rd());
        std::normal_distribution<double> dis(0.0, 1.0);
        
        // Створення прикладів зображень 28x28x3 (RGB)
        // Create example images 28x28x3 (RGB)
        // Создание примеров изображений 28x28x3 (RGB)
        std::vector<std::vector<std::vector<double>>> trainingData(100);
        std::vector<std::vector<std::vector<double>>> trainingLabels(100);
        
        for (int i = 0; i < 100; ++i) {
            // Генерація випадкового зображення
            // Generate random image
            // Генерация случайного изображения
            trainingData[i].resize(28, std::vector<double>(28 * 3));
            for (int row = 0; row < 28; ++row) {
                for (int col = 0; col < 28 * 3; ++col) {
                    trainingData[i][row][col] = dis(gen);
                }
            }
            
            // Генерація випадкових міток (one-hot кодування для 10 класів)
            // Generate random labels (one-hot encoding for 10 classes)
            // Генерация случайных меток (one-hot кодирование для 10 классов)
            trainingLabels[i].resize(1, std::vector<double>(10, 0.0));
            int classIndex = i % 10;
            trainingLabels[i][0][classIndex] = 1.0;
        }
        
        std::cout << "Generated " << trainingData.size() << " training samples\n\n";
        
        // Навчання мережі
        // Train network
        // Обучение сети
        std::cout << "Training network...\n";
        bool success = advancedNN->train(trainingData, trainingLabels, 50, 0.01);
        
        if (success) {
            std::cout << "Training completed successfully\n\n";
            
            // Отримання статистики
            // Get statistics
            // Получение статистики
            auto stats = advancedNN->getStatistics();
            std::cout << "Network Statistics:\n";
            std::cout << "  Total Layers: " << advancedNN->getLayerCount() << "\n";
            std::cout << "  Total Neurons: " << advancedNN->getNeuronCount() << "\n";
            std::cout << "  Training Accuracy: " << stats.trainingAccuracy << "\n";
            std::cout << "  Training Time: " << stats.lastTrainingTime << " ms\n\n";
            
            // Тестування передбачення
            // Test prediction
            // Тестирование предсказания
            std::cout << "Testing prediction...\n";
            std::vector<std::vector<double>> testImage(28, std::vector<double>(28 * 3));
            for (int row = 0; row < 28; ++row) {
                for (int col = 0; col < 28 * 3; ++col) {
                    testImage[row][col] = dis(gen);
                }
            }
            
            auto prediction = advancedNN->predict(testImage);
            std::cout << "Prediction made for test image\n";
            if (!prediction.empty() && !prediction[0].empty()) {
                std::cout << "Output vector size: " << prediction[0].size() << "\n";
                std::cout << "First 5 output values: ";
                for (int i = 0; i < 5 && i < static_cast<int>(prediction[0].size()); ++i) {
                    std::cout << prediction[0][i] << " ";
                }
                std::cout << "\n\n";
            }
        } else {
            std::cerr << "Training failed\n\n";
        }
        
        // Збереження моделі
        // Save model
        // Сохранение модели
        std::cout << "Saving model...\n";
        if (advancedNN->saveModel("advanced_model.dat")) {
            std::cout << "Model saved successfully\n\n";
        } else {
            std::cerr << "Failed to save model\n\n";
        }
        
        std::cout << "Advanced Neural Networks Example completed!\n";
        std::cout << "========================================\n";
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}