#include "network/NeuralNetwork.h"
#include <iostream>
#include <vector>
#include <random>

using namespace NeuroSync::Network;

// Функція для генерації навчальних даних XOR
// Function to generate XOR training data
// Функция для генерации обучающих данных XOR
void generateXORData(std::vector<std::vector<double>>& inputs, std::vector<std::vector<double>>& targets) {
    inputs = {
        {0.0, 0.0},
        {0.0, 1.0},
        {1.0, 0.0},
        {1.0, 1.0}
    };
    
    targets = {
        {0.0},
        {1.0},
        {1.0},
        {0.0}
    };
}

int main() {
    std::cout << "=== Neural Network Example for NeuroSync OS Sparky ===" << std::endl;
    
    try {
        // Створити нейронну мережу
        // Create neural network
        // Создать нейронную сеть
        NeuralNetwork network(NetworkType::FEEDFORWARD, "XOR_Network");
        
        std::cout << "Created neural network: " << network.getName() << std::endl;
        std::cout << "Network type: " << static_cast<int>(network.getType()) << std::endl;
        
        // Додати шари
        // Add layers
        // Добавить слои
        std::cout << "\nAdding network layers..." << std::endl;
        network.addLayer(2, "sigmoid");  // Вхідний шар / Input layer / Входной слой
        network.addLayer(4, "sigmoid");  // Прихований шар / Hidden layer / Скрытый слой
        network.addLayer(1, "sigmoid");  // Вихідний шар / Output layer / Выходной слой
        
        std::cout << "Added " << network.getLayerCount() << " layers" << std::endl;
        std::cout << "Total neurons: " << network.getNeuronCount() << std::endl;
        
        // Підключити шари
        // Connect layers
        // Соединить слои
        std::cout << "\nConnecting layers..." << std::endl;
        network.connectLayers(0, 1);  // Вхідний -> Прихований / Input -> Hidden / Входной -> Скрытый
        network.connectLayers(1, 2);  // Прихований -> Вихідний / Hidden -> Output / Скрытый -> Выходной
        
        auto stats = network.getStatistics();
        std::cout << "Total connections: " << stats.totalConnections << std::endl;
        
        // Генерувати навчальні дані
        // Generate training data
        // Сгенерировать обучающие данные
        std::cout << "\nGenerating training data..." << std::endl;
        std::vector<std::vector<double>> inputs, targets;
        generateXORData(inputs, targets);
        
        std::cout << "Generated " << inputs.size() << " training examples" << std::endl;
        
        // Навчити мережу
        // Train network
        // Обучить сеть
        std::cout << "\nTraining network..." << std::endl;
        bool trainingResult = network.train(inputs, targets, 1000, 0.1);
        
        if (trainingResult) {
            std::cout << "Training completed successfully!" << std::endl;
        } else {
            std::cout << "Training failed!" << std::endl;
            return 1;
        }
        
        // Перевірити результати
        // Check results
        // Проверить результаты
        std::cout << "\nTesting network..." << std::endl;
        for (size_t i = 0; i < inputs.size(); ++i) {
            auto output = network.predict(inputs[i]);
            std::cout << "Input: [" << inputs[i][0] << ", " << inputs[i][1] << "] -> ";
            std::cout << "Output: [" << output[0] << "] (Expected: " << targets[i][0] << ")" << std::endl;
        }
        
        // Отримати фінальну статистику
        // Get final statistics
        // Получить финальную статистику
        auto finalStats = network.getStatistics();
        std::cout << "\nFinal Network Statistics:" << std::endl;
        std::cout << "  Layers: " << finalStats.totalLayers << std::endl;
        std::cout << "  Neurons: " << finalStats.totalNeurons << std::endl;
        std::cout << "  Connections: " << finalStats.totalConnections << std::endl;
        std::cout << "  Training time: " << finalStats.lastTrainingTime << " ms" << std::endl;
        
        // Зберегти модель
        // Save model
        // Сохранить модель
        std::cout << "\nSaving model..." << std::endl;
        bool saveResult = network.saveModel("xor_model.txt");
        if (saveResult) {
            std::cout << "Model saved successfully!" << std::endl;
        } else {
            std::cout << "Failed to save model!" << std::endl;
        }
        
        std::cout << "\nNeural network example completed successfully!" << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}