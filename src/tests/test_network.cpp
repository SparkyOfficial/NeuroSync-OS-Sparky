#include "network/NeuralNetwork.h"
#include <cassert>
#include <iostream>
#include <vector>

using namespace NeuroSync::Network;

void testNetworkCreation() {
    std::cout << "Testing neural network creation..." << std::endl;
    
    NeuralNetwork network(NetworkType::FEEDFORWARD, "TestNetwork");
    
    // Перевірити початкові параметри
    // Check initial parameters
    // Проверить начальные параметры
    assert(network.getName() == "TestNetwork");
    assert(network.getType() == NetworkType::FEEDFORWARD);
    assert(network.getLayerCount() == 0);
    assert(network.getNeuronCount() == 0);
    
    // Перевірити ініціалізацію
    // Check initialization
    // Проверить инициализацию
    bool initResult = network.initialize();
    assert(initResult);
    
    std::cout << "Network creation test passed!" << std::endl;
}

void testLayerManagement() {
    std::cout << "Testing layer management..." << std::endl;
    
    NeuralNetwork network(NetworkType::FEEDFORWARD, "LayerTestNetwork");
    
    // Додати шари
    // Add layers
    // Добавить слои
    bool addResult1 = network.addLayer(3, "sigmoid");
    assert(addResult1);
    assert(network.getLayerCount() == 1);
    assert(network.getNeuronCount() == 3);
    
    bool addResult2 = network.addLayer(2, "relu");
    assert(addResult2);
    assert(network.getLayerCount() == 2);
    assert(network.getNeuronCount() == 5);
    
    // Видалити шар
    // Remove layer
    // Удалить слой
    bool removeResult = network.removeLayer(1);
    assert(removeResult);
    assert(network.getLayerCount() == 1);
    assert(network.getNeuronCount() == 3);
    
    std::cout << "Layer management test passed!" << std::endl;
}

void testNetworkConnections() {
    std::cout << "Testing network connections..." << std::endl;
    
    NeuralNetwork network(NetworkType::FEEDFORWARD, "ConnectionTestNetwork");
    
    // Додати шари
    // Add layers
    // Добавить слои
    network.addLayer(2, "sigmoid");
    network.addLayer(3, "sigmoid");
    network.addLayer(1, "sigmoid");
    
    // Підключити шари
    // Connect layers
    // Соединить слои
    bool connectResult1 = network.connectLayers(0, 1);
    assert(connectResult1);
    
    bool connectResult2 = network.connectLayers(1, 2);
    assert(connectResult2);
    
    // Отримати статистику
    // Get statistics
    // Получить статистику
    auto stats = network.getStatistics();
    assert(stats.totalLayers == 3);
    assert(stats.totalNeurons == 6);
    assert(stats.totalConnections > 0);
    
    std::cout << "Network connections test passed!" << std::endl;
}

void testNetworkPrediction() {
    std::cout << "Testing network prediction..." << std::endl;
    
    NeuralNetwork network(NetworkType::FEEDFORWARD, "PredictionTestNetwork");
    
    // Додати шари
    // Add layers
    // Добавить слои
    network.addLayer(2, "sigmoid");
    network.addLayer(3, "sigmoid");
    network.addLayer(1, "sigmoid");
    
    // Підключити шари
    // Connect layers
    // Соединить слои
    network.connectLayers(0, 1);
    network.connectLayers(1, 2);
    
    // Зробити передбачення
    // Make prediction
    // Сделать предсказание
    std::vector<double> input = {0.5, 0.3};
    std::vector<double> output = network.predict(input);
    
    // Перевірити розмір виходу
    // Check output size
    // Проверить размер выхода
    assert(output.size() == 1);
    
    std::cout << "Network prediction test passed!" << std::endl;
}

void testModelSaveLoad() {
    std::cout << "Testing model save/load..." << std::endl;
    
    NeuralNetwork network(NetworkType::FEEDFORWARD, "SaveLoadTestNetwork");
    
    // Додати шари
    // Add layers
    // Добавить слои
    network.addLayer(2, "sigmoid");
    network.addLayer(3, "sigmoid");
    network.addLayer(1, "sigmoid");
    
    // Підключити шари
    // Connect layers
    // Соединить слои
    network.connectLayers(0, 1);
    network.connectLayers(1, 2);
    
    // Зберегти модель
    // Save model
    // Сохранить модель
    bool saveResult = network.saveModel("test_model.txt");
    assert(saveResult);
    
    // Створити нову мережу та завантажити модель
    // Create new network and load model
    // Создать новую сеть и загрузить модель
    NeuralNetwork loadedNetwork(NetworkType::FEEDFORWARD, "LoadedNetwork");
    bool loadResult = loadedNetwork.loadModel("test_model.txt");
    assert(loadResult);
    
    // Перевірити параметри завантаженої мережі
    // Check loaded network parameters
    // Проверить параметры загруженной сети
    assert(loadedNetwork.getLayerCount() == 3);
    assert(loadedNetwork.getNeuronCount() == 6);
    
    std::cout << "Model save/load test passed!" << std::endl;
}

int main() {
    std::cout << "=== Running Neural Network Tests ===" << std::endl;
    
    try {
        testNetworkCreation();
        testLayerManagement();
        testNetworkConnections();
        testNetworkPrediction();
        testModelSaveLoad();
        
        std::cout << "\n=== All Neural Network Tests Passed! ===" << std::endl;
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Test failed with error: " << e.what() << std::endl;
        return 1;
    }
}