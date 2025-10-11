/*
 * test_ml_pipeline.cpp
 * Тест для конвеєра машинного навчання
 * Test for machine learning pipeline
 * Тест для конвейера машинного обучения
 */

#include "../ml_pipeline/MLPipeline.h"
#include "../data_processing/DataProcessor.h"
#include "../model_management/ModelManager.h"
#include <iostream>
#include <vector>
#include <cassert>
#include <thread>
#include <chrono>

using namespace NeuroSync::MLPipeline;
using namespace NeuroSync::DataProcessing;
using namespace NeuroSync::ModelManagement;

// Тестова реалізація спостерігача
// Test observer implementation
// Тестовая реализация наблюдателя
class TestObserver : public PipelineObserver {
public:
    int statusChanges = 0;
    int progressUpdates = 0;
    int completions = 0;
    
    void onStatusChanged(PipelineStatus status) override {
        statusChanges++;
        std::cout << "Status changed to: " << static_cast<int>(status) << std::endl;
    }
    
    void onProgressUpdate(int epoch, int totalEpochs, double loss) override {
        progressUpdates++;
        std::cout << "Progress: epoch " << epoch << "/" << totalEpochs << ", loss: " << loss << std::endl;
    }
    
    void onPipelineCompleted(const PipelineResults& results) override {
        completions++;
        std::cout << "Pipeline completed with status: " << static_cast<int>(results.finalStatus) << std::endl;
    }
};

int main() {
    std::cout << "=== Running ML Pipeline Tests ===" << std::endl;
    
    try {
        // Тест 1: Створення та ініціалізація конвеєра
        // Test 1: Creating and initializing pipeline
        // Тест 1: Создание и инициализация конвейера
        std::cout << "\nTest 1: Creating and initializing pipeline..." << std::endl;
        
        MachineLearningPipeline pipeline;
        
        PipelineConfig config;
        config.epochs = 5;
        config.learningRate = 0.01;
        config.batchSize = 10;
        
        bool initSuccess = pipeline.initialize(config);
        assert(initSuccess);
        std::cout << "Pipeline initialized successfully" << std::endl;
        
        // Тест 2: Додавання спостерігача
        // Test 2: Adding observer
        // Тест 2: Добавление наблюдателя
        std::cout << "\nTest 2: Adding observer..." << std::endl;
        
        auto observer = std::make_shared<TestObserver>();
        pipeline.addObserver(observer);
        std::cout << "Observer added successfully" << std::endl;
        
        // Тест 3: Підготовка тестових даних
        // Test 3: Preparing test data
        // Тест 3: Подготовка тестовых данных
        std::cout << "\nTest 3: Preparing test data..." << std::endl;
        
        // Створення простих тестових даних
        // Creating simple test data
        // Создание простых тестовых данных
        std::vector<std::vector<double>> trainingData = {
            {0.1, 0.2, 0.3},
            {0.4, 0.5, 0.6},
            {0.7, 0.8, 0.9},
            {0.2, 0.3, 0.4},
            {0.5, 0.6, 0.7}
        };
        
        std::vector<std::vector<double>> trainingLabels = {
            {0.3},
            {0.6},
            {0.9},
            {0.4},
            {0.7}
        };
        
        std::cout << "Test data prepared successfully" << std::endl;
        
        // Тест 4: Запуск навчання
        // Test 4: Starting training
        // Тест 4: Запуск обучения
        std::cout << "\nTest 4: Starting training..." << std::endl;
        
        bool trainingStarted = pipeline.startTraining(trainingData, trainingLabels);
        assert(trainingStarted);
        std::cout << "Training started successfully" << std::endl;
        
        // Очікування завершення навчання
        // Waiting for training completion
        // Ожидание завершения обучения
        std::this_thread::sleep_for(std::chrono::seconds(2));
        
        // Тест 5: Перевірка результатів
        // Test 5: Checking results
        // Тест 5: Проверка результатов
        std::cout << "\nTest 5: Checking results..." << std::endl;
        
        PipelineResults results = pipeline.getResults();
        std::cout << "Final status: " << static_cast<int>(results.finalStatus) << std::endl;
        std::cout << "Training time: " << results.trainingTime << " ms" << std::endl;
        
        // Тест 6: Перевірка спостерігача
        // Test 6: Checking observer
        // Тест 6: Проверка наблюдателя
        std::cout << "\nTest 6: Checking observer..." << std::endl;
        
        std::cout << "Status changes: " << observer->statusChanges << std::endl;
        std::cout << "Progress updates: " << observer->progressUpdates << std::endl;
        std::cout << "Completions: " << observer->completions << std::endl;
        
        // Тест 7: Тестування процесора даних
        // Test 7: Testing data processor
        // Тест 7: Тестирование процессора данных
        std::cout << "\nTest 7: Testing data processor..." << std::endl;
        
        DataProcessor dataProcessor;
        DataProcessorConfig dataConfig;
        dataConfig.shuffleData = true;
        dataConfig.removeDuplicates = true;
        
        bool dataProcessorInit = dataProcessor.initialize(dataConfig);
        assert(dataProcessorInit);
        std::cout << "Data processor initialized successfully" << std::endl;
        
        // Тест 8: Нормалізація даних
        // Test 8: Data normalization
        // Тест 8: Нормализация данных
        std::cout << "\nTest 8: Data normalization..." << std::endl;
        
        auto normalizedData = dataProcessor.normalizeData(trainingData);
        assert(!normalizedData.empty());
        std::cout << "Data normalization completed successfully" << std::endl;
        
        // Тест 9: Тестування менеджера моделей
        // Test 9: Testing model manager
        // Тест 9: Тестирование менеджера моделей
        std::cout << "\nTest 9: Testing model manager..." << std::endl;
        
        ModelManager modelManager;
        ModelManagerConfig modelConfig;
        modelConfig.modelStoragePath = "./test_models";
        
        bool modelManagerInit = modelManager.initialize(modelConfig);
        assert(modelManagerInit);
        std::cout << "Model manager initialized successfully" << std::endl;
        
        // Тест 10: Отримання конфігурації
        // Test 10: Getting configuration
        // Тест 10: Получение конфигурации
        std::cout << "\nTest 10: Getting configuration..." << std::endl;
        
        auto pipelineConfig = pipeline.getConfiguration();
        assert(pipelineConfig.epochs == 5);
        std::cout << "Pipeline configuration retrieved successfully" << std::endl;
        
        auto dataProcessorConfig = dataProcessor.getConfiguration();
        assert(dataProcessorConfig.shuffleData == true);
        std::cout << "Data processor configuration retrieved successfully" << std::endl;
        
        auto modelManagerConfig = modelManager.getConfiguration();
        assert(modelManagerConfig.modelStoragePath == "./test_models");
        std::cout << "Model manager configuration retrieved successfully" << std::endl;
        
        std::cout << "\n=== All ML Pipeline Tests Passed! ===" << std::endl;
        return 0;
        
    } catch (const std::exception& e) {
        std::cerr << "Test failed with exception: " << e.what() << std::endl;
        return 1;
    }
}