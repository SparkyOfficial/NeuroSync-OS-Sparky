#include "../advanced_nn/AdvancedNeuralNetworks.h"
#include <iostream>
#include <cassert>
#include <cmath>

using namespace NeuroSync::AdvancedNN;

// Тест для розширених нейронних мереж
// Test for advanced neural networks
// Тест для расширенных нейронных сетей

int main() {
    try {
        std::cout << "========================================\n";
        std::cout << "  Advanced Neural Networks Test\n";
        std::cout << "  NeuroSync OS Sparky\n";
        std::cout << "========================================\n\n";
        
        // Тест 1: Створення мережі
        // Test 1: Network creation
        // Тест 1: Создание сети
        std::cout << "Test 1: Creating advanced neural network...\n";
        auto advancedNN = std::make_unique<AdvancedNeuralNetwork>(
            AdvancedNetworkType::CONVOLUTIONAL, "TestCNN");
        
        assert(advancedNN != nullptr);
        assert(advancedNN->getName() == "TestCNN");
        assert(advancedNN->getType() == AdvancedNetworkType::CONVOLUTIONAL);
        assert(advancedNN->getLayerCount() == 0);
        std::cout << "✓ Network creation test passed\n\n";
        
        // Тест 2: Ініціалізація мережі
        // Test 2: Network initialization
        // Тест 2: Инициализация сети
        std::cout << "Test 2: Initializing network...\n";
        bool initSuccess = advancedNN->initialize();
        assert(initSuccess);
        std::cout << "✓ Network initialization test passed\n\n";
        
        // Тест 3: Додавання згорткового шару
        // Test 3: Adding convolutional layer
        // Тест 3: Добавление сверточного слоя
        std::cout << "Test 3: Adding convolutional layer...\n";
        bool convSuccess = advancedNN->addConvolutionalLayer(3, 16, 3, 1, 1, "relu");
        assert(convSuccess);
        assert(advancedNN->getLayerCount() == 1);
        std::cout << "✓ Convolutional layer addition test passed\n\n";
        
        // Тест 4: Додавання рекурентного шару
        // Test 4: Adding recurrent layer
        // Тест 4: Добавление рекуррентного слоя
        std::cout << "Test 4: Adding recurrent layer...\n";
        bool recurrentSuccess = advancedNN->addRecurrentLayer(10, 20, 15, "LSTM");
        assert(recurrentSuccess);
        assert(advancedNN->getLayerCount() == 2);
        std::cout << "✓ Recurrent layer addition test passed\n\n";
        
        // Тест 5: Додавання шару трансформера
        // Test 5: Adding transformer layer
        // Тест 5: Добавление слоя трансформера
        std::cout << "Test 5: Adding transformer layer...\n";
        bool transformerSuccess = advancedNN->addTransformerLayer(128, 8, 512, 0.1);
        assert(transformerSuccess);
        assert(advancedNN->getLayerCount() == 3);
        std::cout << "✓ Transformer layer addition test passed\n\n";
        
        // Тест 6: Додавання повністю зв'язаного шару
        // Test 6: Adding fully connected layer
        // Тест 6: Добавление полностью связанного слоя
        std::cout << "Test 6: Adding fully connected layer...\n";
        bool fcSuccess = advancedNN->addFullyConnectedLayer(128, 10, "softmax");
        assert(fcSuccess);
        assert(advancedNN->getLayerCount() == 4);
        std::cout << "✓ Fully connected layer addition test passed\n\n";
        
        // Тест 7: Статистика мережі
        // Test 7: Network statistics
        // Тест 7: Статистика сети
        std::cout << "Test 7: Checking network statistics...\n";
        auto stats = advancedNN->getStatistics();
        assert(stats.totalLayers == 4);
        std::cout << "✓ Network statistics test passed\n\n";
        
        // Тест 8: Збереження моделі
        // Test 8: Model saving
        // Тест 8: Сохранение модели
        std::cout << "Test 8: Saving model...\n";
        bool saveSuccess = advancedNN->saveModel("test_model.dat");
        assert(saveSuccess);
        std::cout << "✓ Model saving test passed\n\n";
        
        // Тест 9: Завантаження моделі
        // Test 9: Model loading
        // Тест 9: Загрузка модели
        std::cout << "Test 9: Loading model...\n";
        bool loadSuccess = advancedNN->loadModel("test_model.dat");
        assert(loadSuccess);
        std::cout << "✓ Model loading test passed\n\n";
        
        // Тест 10: Функції активації
        // Test 10: Activation functions
        // Тест 10: Функции активации
        std::cout << "Test 10: Testing activation functions...\n";
        double sigmoidResult = advancedNN->sigmoid(0.0);
        assert(std::abs(sigmoidResult - 0.5) < 0.0001);
        
        double reluResult = advancedNN->relu(-1.0);
        assert(reluResult == 0.0);
        
        reluResult = advancedNN->relu(1.0);
        assert(reluResult == 1.0);
        std::cout << "✓ Activation functions test passed\n\n";
        
        std::cout << "========================================\n";
        std::cout << "  All Advanced Neural Networks Tests Passed!\n";
        std::cout << "  Total Tests: 10\n";
        std::cout << "========================================\n";
        
    } catch (const std::exception& e) {
        std::cerr << "Test failed with error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}