#include "src/network/NeuralNetwork.h"
#include <iostream>

int main() {
    std::cout << "Testing Neural Network module..." << std::endl;
    
    try {
        // Створити нейронну мережу
        // Create neural network
        // Создать нейронную сеть
        NeuroSync::Network::NeuralNetwork network(
            NeuroSync::Network::NetworkType::FEEDFORWARD, 
            "TestNetwork"
        );
        
        // Перевірити початкові параметри
        // Check initial parameters
        // Проверить начальные параметры
        std::cout << "Network name: " << network.getName() << std::endl;
        std::cout << "Network type: " << static_cast<int>(network.getType()) << std::endl;
        std::cout << "Layer count: " << network.getLayerCount() << std::endl;
        std::cout << "Neuron count: " << network.getNeuronCount() << std::endl;
        
        // Ініціалізувати мережу
        // Initialize network
        // Инициализировать сеть
        bool initResult = network.initialize();
        std::cout << "Initialization result: " << (initResult ? "success" : "failure") << std::endl;
        
        // Додати шар
        // Add layer
        // Добавить слой
        bool addLayerResult = network.addLayer(3, "sigmoid");
        std::cout << "Add layer result: " << (addLayerResult ? "success" : "failure") << std::endl;
        
        std::cout << "Layer count after adding: " << network.getLayerCount() << std::endl;
        std::cout << "Neuron count after adding: " << network.getNeuronCount() << std::endl;
        
        // Отримати статистику
        // Get statistics
        // Получить статистику
        auto stats = network.getStatistics();
        std::cout << "Network statistics:" << std::endl;
        std::cout << "  Total layers: " << stats.totalLayers << std::endl;
        std::cout << "  Total neurons: " << stats.totalNeurons << std::endl;
        std::cout << "  Total connections: " << stats.totalConnections << std::endl;
        
        std::cout << "Neural Network module test completed successfully!" << std::endl;
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}