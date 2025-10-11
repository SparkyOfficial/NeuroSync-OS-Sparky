/*
 * ml_pipeline_example.cpp
 * Приклад використання конвеєра машинного навчання
 * Example of using machine learning pipeline
 * Пример использования конвейера машинного обучения
 */

#include "../ml_pipeline/MLPipeline.h"
#include "../data_processing/DataProcessor.h"
#include "../model_management/ModelManager.h"
#include "../network_neural/NeuralNetwork.h"
#include <iostream>
#include <vector>
#include <random>
#include <thread>
#include <chrono>

using namespace NeuroSync::MLPipeline;
using namespace NeuroSync::DataProcessing;
using namespace NeuroSync::ModelManagement;
using namespace NeuroSync::Network;

// Реалізація спостерігача для відображення прогресу
// Observer implementation for displaying progress
// Реализация наблюдателя для отображения прогресса
class ProgressObserver : public PipelineObserver {
public:
    void onStatusChanged(PipelineStatus status) override {
        std::cout << "[PROGRESS] Status changed to: ";
        switch (status) {
            case PipelineStatus::IDLE:
                std::cout << "IDLE";
                break;
            case PipelineStatus::TRAINING:
                std::cout << "TRAINING";
                break;
            case PipelineStatus::VALIDATING:
                std::cout << "VALIDATING";
                break;
            case PipelineStatus::TESTING:
                std::cout << "TESTING";
                break;
            case PipelineStatus::DEPLOYING:
                std::cout << "DEPLOYING";
                break;
            case PipelineStatus::ERROR:
                std::cout << "ERROR";
                break;
        }
        std::cout << std::endl;
    }
    
    void onProgressUpdate(int epoch, int totalEpochs, double loss) override {
        int progress = static_cast<int>((static_cast<double>(epoch) / totalEpochs) * 100);
        std::cout << "[PROGRESS] Epoch " << epoch << "/" << totalEpochs 
                  << " (" << progress << "%) - Loss: " << loss << std::endl;
    }
    
    void onPipelineCompleted(const PipelineResults& results) override {
        std::cout << "[PROGRESS] Pipeline completed!" << std::endl;
        std::cout << "  Final Status: " << static_cast<int>(results.finalStatus) << std::endl;
        std::cout << "  Training Accuracy: " << results.trainingAccuracy << std::endl;
        std::cout << "  Training Time: " << results.trainingTime << " ms" << std::endl;
        if (!results.errorMessage.empty()) {
            std::cout << "  Error: " << results.errorMessage << std::endl;
        }
    }
};

// Генерація синтетичних даних для навчання
// Generate synthetic data for training
// Генерация синтетических данных для обучения
std::pair<std::vector<std::vector<double>>, std::vector<std::vector<double>>> 
generateSyntheticData(int samples, int inputFeatures, int outputFeatures) {
    std::vector<std::vector<double>> data;
    std::vector<std::vector<double>> labels;
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(-1.0, 1.0);
    
    data.reserve(samples);
    labels.reserve(samples);
    
    for (int i = 0; i < samples; ++i) {
        // Генерація вхідних даних
        // Generate input data
        // Генерация входных данных
        std::vector<double> inputData;
        inputData.reserve(inputFeatures);
        for (int j = 0; j < inputFeatures; ++j) {
            inputData.push_back(dis(gen));
        }
        data.push_back(inputData);
        
        // Генерація міток (спрощена логіка)
        // Generate labels (simplified logic)
        // Генерация меток (упрощенная логика)
        std::vector<double> labelData;
        labelData.reserve(outputFeatures);
        for (int j = 0; j < outputFeatures; ++j) {
            // Проста функція для генерації міток
            // Simple function to generate labels
            // Простая функция для генерации меток
            double sum = 0;
            for (int k = 0; k < inputFeatures; ++k) {
                sum += data[i][k] * (k + 1);
            }
            labelData.push_back(std::tanh(sum / inputFeatures));
        }
        labels.push_back(labelData);
    }
    
    return std::make_pair(data, labels);
}

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "  NeuroSync ML Pipeline Example" << std::endl;
    std::cout << "========================================" << std::endl;
    
    try {
        // 1. Створення компонентів конвеєра
        // 1. Creating pipeline components
        // 1. Создание компонентов конвейера
        std::cout << "\n1. Initializing ML Pipeline components..." << std::endl;
        
        MachineLearningPipeline pipeline;
        DataProcessor dataProcessor;
        ModelManager modelManager;
        
        // 2. Налаштування конфігурації
        // 2. Setting up configuration
        // 2. Настройка конфигурации
        std::cout << "\n2. Setting up configuration..." << std::endl;
        
        PipelineConfig pipelineConfig;
        pipelineConfig.epochs = 50;
        pipelineConfig.learningRate = 0.01;
        pipelineConfig.batchSize = 32;
        pipelineConfig.shuffleData = true;
        pipelineConfig.modelSavePath = "./models/pipeline_model";
        pipelineConfig.checkpointInterval = 10;
        
        DataProcessorConfig dataConfig;
        dataConfig.shuffleData = true;
        dataConfig.trainValidationSplit = 0.8;
        dataConfig.removeDuplicates = true;
        
        ModelManagerConfig modelConfig;
        modelConfig.modelStoragePath = "./models";
        modelConfig.autoVersioning = true;
        modelConfig.maxModelsToKeep = 5;
        
        // 3. Ініціалізація компонентів
        // 3. Initializing components
        // 3. Инициализация компонентов
        std::cout << "\n3. Initializing components..." << std::endl;
        
        if (!pipeline.initialize(pipelineConfig)) {
            std::cerr << "Failed to initialize ML Pipeline" << std::endl;
            return 1;
        }
        
        if (!dataProcessor.initialize(dataConfig)) {
            std::cerr << "Failed to initialize Data Processor" << std::endl;
            return 1;
        }
        
        if (!modelManager.initialize(modelConfig)) {
            std::cerr << "Failed to initialize Model Manager" << std::endl;
            return 1;
        }
        
        std::cout << "Components initialized successfully!" << std::endl;
        
        // 4. Створення нейронної мережі
        // 4. Creating neural network
        // 4. Создание нейронной сети
        std::cout << "\n4. Creating neural network..." << std::endl;
        
        auto neuralNetwork = std::make_unique<NeuralNetwork>(
            NetworkType::FEEDFORWARD, "ExampleNetwork");
        
        if (!neuralNetwork->initialize()) {
            std::cerr << "Failed to initialize neural network" << std::endl;
            return 1;
        }
        
        // Додавання шарів до мережі
        // Adding layers to the network
        // Добавление слоев в сеть
        neuralNetwork->addLayer(10, "sigmoid");  // Вхідний шар / Input layer / Входной слой
        neuralNetwork->addLayer(20, "sigmoid");  // Прихований шар / Hidden layer / Скрытый слой
        neuralNetwork->addLayer(5, "sigmoid");   // Вихідний шар / Output layer / Выходной слой
        
        // З'єднання шарів
        // Connecting layers
        // Соединение слоев
        neuralNetwork->connectLayers(0, 1);  // Вхідний до прихованого / Input to hidden / Входной к скрытому
        neuralNetwork->connectLayers(1, 2);  // Прихований до вихідного / Hidden to output / Скрытый к выходному
        
        // Встановлення мережі в конвеєр
        // Setting network in pipeline
        // Установка сети в конвейер
        pipeline.setNeuralNetwork(std::move(neuralNetwork));
        
        std::cout << "Neural network created successfully!" << std::endl;
        
        // 5. Генерація синтетичних даних
        // 5. Generating synthetic data
        // 5. Генерация синтетических данных
        std::cout << "\n5. Generating synthetic training data..." << std::endl;
        
        auto [trainingData, trainingLabels] = generateSyntheticData(1000, 10, 5);
        std::cout << "Generated " << trainingData.size() << " training samples" << std::endl;
        
        // 6. Додавання спостерігача
        // 6. Adding observer
        // 6. Добавление наблюдателя
        std::cout << "\n6. Adding progress observer..." << std::endl;
        
        auto observer = std::make_shared<ProgressObserver>();
        pipeline.addObserver(observer);
        
        std::cout << "Progress observer added!" << std::endl;
        
        // 7. Запуск навчання
        // 7. Starting training
        // 7. Запуск обучения
        std::cout << "\n7. Starting training pipeline..." << std::endl;
        
        if (!pipeline.startTraining(trainingData, trainingLabels)) {
            std::cerr << "Failed to start training" << std::endl;
            return 1;
        }
        
        std::cout << "Training started! Monitoring progress..." << std::endl;
        
        // 8. Очікування завершення навчання
        // 8. Waiting for training completion
        // 8. Ожидание завершения обучения
        std::cout << "\n8. Waiting for training to complete..." << std::endl;
        
        // Очікування завершення (в реальному випадку це було б автоматично)
        // Waiting for completion (in real case this would be automatic)
        // Ожидание завершения (в реальном случае это было бы автоматически)
        std::this_thread::sleep_for(std::chrono::seconds(5));
        
        // 9. Отримання результатів
        // 9. Getting results
        // 9. Получение результатов
        std::cout << "\n9. Getting training results..." << std::endl;
        
        PipelineResults results = pipeline.getResults();
        std::cout << "Training Results:" << std::endl;
        std::cout << "  Status: " << static_cast<int>(results.finalStatus) << std::endl;
        std::cout << "  Training Accuracy: " << results.trainingAccuracy << std::endl;
        std::cout << "  Training Time: " << results.trainingTime << " ms" << std::endl;
        
        // 10. Збереження моделі
        // 10. Saving model
        // 10. Сохранение модели
        std::cout << "\n10. Saving trained model..." << std::endl;
        
        auto network = pipeline.getNeuralNetwork();
        if (network) {
            if (modelManager.saveModel(network, "ExampleModel", "Example model from ML Pipeline")) {
                std::cout << "Model saved successfully!" << std::endl;
            } else {
                std::cout << "Failed to save model" << std::endl;
            }
        }
        
        // 11. Відображення інформації про моделі
        // 11. Displaying model information
        // 11. Отображение информации о моделях
        std::cout << "\n11. Displaying model information..." << std::endl;
        
        auto models = modelManager.getAllModels();
        std::cout << "Available models:" << std::endl;
        for (const auto& modelInfo : models) {
            std::cout << "  ID: " << modelInfo.modelId << std::endl;
            std::cout << "  Name: " << modelInfo.modelName << std::endl;
            std::cout << "  Version: " << modelInfo.version << std::endl;
            std::cout << "  Status: " << static_cast<int>(modelInfo.status) << std::endl;
            std::cout << "  File Size: " << modelInfo.fileSize << " bytes" << std::endl;
            std::cout << std::endl;
        }
        
        std::cout << "\n========================================" << std::endl;
        std::cout << "  ML Pipeline Example Completed!" << std::endl;
        std::cout << "========================================" << std::endl;
        
        return 0;
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}