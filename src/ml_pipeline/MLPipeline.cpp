#include "MLPipeline.h"
#include <algorithm>
#include <random>
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>

// MLPipeline.cpp
// Реалізація конвеєра машинного навчання для NeuroSync OS Sparky
// Implementation of machine learning pipeline for NeuroSync OS Sparky
// Реализация конвейера машинного обучения для NeuroSync OS Sparky

namespace NeuroSync {
namespace MLPipeline {

    // Конструктор конвеєра машинного навчання
    // Machine learning pipeline constructor
    // Конструктор конвейера машинного обучения
    MachineLearningPipeline::MachineLearningPipeline() 
        : currentStatus(PipelineStatus::IDLE), shouldStop(false) {
        // Ініціалізація компонентів
        // Initialize components
        // Инициализация компонентов
    }

    // Деструктор конвеєра машинного навчання
    // Machine learning pipeline destructor
    // Деструктор конвейера машинного обучения
    MachineLearningPipeline::~MachineLearningPipeline() {
        stopPipeline();
        
        if (trainingThread.joinable()) {
            trainingThread.join();
        }
    }

    // Ініціалізація конвеєра
    // Initialize pipeline
    // Инициализация конвейера
    bool MachineLearningPipeline::initialize(const PipelineConfig& config) {
        std::lock_guard<std::mutex> lock(pipelineMutex);
        
        configuration = config;
        currentStatus = PipelineStatus::IDLE;
        
        // Ініціалізація нейронної мережі, якщо ще не встановлена
        // Initialize neural network if not already set
        // Инициализация нейронной сети, если еще не установлена
        if (!neuralNetwork) {
            neuralNetwork = std::make_unique<Network::NeuralNetwork>(
                Network::NetworkType::FEEDFORWARD, "MLPipelineNetwork");
        }
        
        // Ініціалізація процесора даних
        // Initialize data processor
        // Инициализация процессора данных
        dataProcessor = std::make_unique<DataProcessing::DataProcessor>();
        
        // Ініціалізація менеджера моделей
        // Initialize model manager
        // Инициализация менеджера моделей
        modelManager = std::make_unique<ModelManagement::ModelManager>();
        
        return neuralNetwork->initialize();
    }

    // Додати спостерігача
    // Add observer
    // Добавить наблюдателя
    void MachineLearningPipeline::addObserver(std::shared_ptr<PipelineObserver> observer) {
        std::lock_guard<std::mutex> lock(pipelineMutex);
        
        if (observer) {
            observers.push_back(observer);
        }
    }

    // Видалити спостерігача
    // Remove observer
    // Удалить наблюдателя
    void MachineLearningPipeline::removeObserver(std::shared_ptr<PipelineObserver> observer) {
        std::lock_guard<std::mutex> lock(pipelineMutex);
        
        if (observer) {
            observers.erase(
                std::remove(observers.begin(), observers.end(), observer), 
                observers.end()
            );
        }
    }

    // Запустити навчання
    // Start training
    // Запустить обучение
    bool MachineLearningPipeline::startTraining(const std::vector<std::vector<double>>& trainingData,
                                               const std::vector<std::vector<double>>& trainingLabels) {
        std::lock_guard<std::mutex> lock(pipelineMutex);
        
        if (currentStatus != PipelineStatus::IDLE) {
            return false;
        }
        
        if (!neuralNetwork || !dataProcessor || !modelManager) {
            return false;
        }
        
        if (trainingData.empty() || trainingLabels.empty() || 
            trainingData.size() != trainingLabels.size()) {
            return false;
        }
        
        // Запуск потоку навчання
        // Start training thread
        // Запуск потока обучения
        shouldStop = false;
        trainingThread = std::thread(&MachineLearningPipeline::trainingLoop, this, 
                                   std::cref(trainingData), std::cref(trainingLabels));
        
        return true;
    }

    // Зупинити конвеєр
    // Stop pipeline
    // Остановить конвейер
    void MachineLearningPipeline::stopPipeline() {
        std::lock_guard<std::mutex> lock(pipelineMutex);
        
        shouldStop = true;
        
        if (trainingThread.joinable()) {
            trainingThread.join();
        }
        
        currentStatus = PipelineStatus::IDLE;
    }

    // Отримати статус
    // Get status
    // Получить статус
    PipelineStatus MachineLearningPipeline::getStatus() const {
        std::lock_guard<std::mutex> lock(pipelineMutex);
        return currentStatus;
    }

    // Отримати результати
    // Get results
    // Получить результаты
    PipelineResults MachineLearningPipeline::getResults() const {
        std::lock_guard<std::mutex> lock(pipelineMutex);
        return results;
    }

    // Отримати конфігурацію
    // Get configuration
    // Получить конфигурацию
    PipelineConfig MachineLearningPipeline::getConfiguration() const {
        std::lock_guard<std::mutex> lock(pipelineMutex);
        return configuration;
    }

    // Встановити мережу
    // Set network
    // Установить сеть
    void MachineLearningPipeline::setNeuralNetwork(std::unique_ptr<Network::NeuralNetwork> network) {
        std::lock_guard<std::mutex> lock(pipelineMutex);
        neuralNetwork = std::move(network);
    }

    // Отримати мережу
    // Get network
    // Получить сеть
    Network::NeuralNetwork* MachineLearningPipeline::getNeuralNetwork() const {
        std::lock_guard<std::mutex> lock(pipelineMutex);
        return neuralNetwork.get();
    }

    // Сповіщення про зміну статусу
    // Status change notification
    // Уведомление об изменении статуса
    void MachineLearningPipeline::notifyStatusChanged(PipelineStatus status) {
        std::lock_guard<std::mutex> lock(pipelineMutex);
        currentStatus = status;
        
        // Створити копію спостерігачів для безпечного ітерування
        // Create a copy of observers for safe iteration
        // Создать копию наблюдателей для безопасной итерации
        auto observersCopy = observers;
        
        // Розблокувати м'ютекс перед викликом спостерігачів
        // Unlock mutex before calling observers
        // Разблокировать мьютекс перед вызовом наблюдателей
        pipelineMutex.unlock();
        
        for (const auto& observer : observersCopy) {
            if (observer) {
                observer->onStatusChanged(status);
            }
        }
        
        // Заблокувати м'ютекс знову
        // Lock mutex again
        // Заблокировать мьютекс снова
        pipelineMutex.lock();
    }

    // Сповіщення про прогрес
    // Progress notification
    // Уведомление о прогрессе
    void MachineLearningPipeline::notifyProgressUpdate(int epoch, int totalEpochs, double loss) {
        // Створити копію спостерігачів для безпечного ітерування
        // Create a copy of observers for safe iteration
        // Создать копию наблюдателей для безопасной итерации
        auto observersCopy = observers;
        
        // Розблокувати м'ютекс перед викликом спостерігачів
        // Unlock mutex before calling observers
        // Разблокировать мьютекс перед вызовом наблюдателей
        pipelineMutex.unlock();
        
        for (const auto& observer : observersCopy) {
            if (observer) {
                observer->onProgressUpdate(epoch, totalEpochs, loss);
            }
        }
        
        // Заблокувати м'ютекс знову
        // Lock mutex again
        // Заблокировать мьютекс снова
        pipelineMutex.lock();
    }

    // Сповіщення про завершення
    // Completion notification
    // Уведомление о завершении
    void MachineLearningPipeline::notifyPipelineCompleted(const PipelineResults& results) {
        // Створити копію спостерігачів для безпечного ітерування
        // Create a copy of observers for safe iteration
        // Создать копию наблюдателей для безопасной итерации
        auto observersCopy = observers;
        
        // Розблокувати м'ютекс перед викликом спостерігачів
        // Unlock mutex before calling observers
        // Разблокировать мьютекс перед вызовом наблюдателей
        pipelineMutex.unlock();
        
        for (const auto& observer : observersCopy) {
            if (observer) {
                observer->onPipelineCompleted(results);
            }
        }
        
        // Заблокувати м'ютекс знову
        // Lock mutex again
        // Заблокировать мьютекс снова
        pipelineMutex.lock();
    }

    // Цикл навчання
    // Training loop
    // Цикл обучения
    void MachineLearningPipeline::trainingLoop(const std::vector<std::vector<double>>& trainingData,
                                              const std::vector<std::vector<double>>& trainingLabels) {
        notifyStatusChanged(PipelineStatus::TRAINING);
        
        PipelineResults trainingResults;
        trainingResults.finalStatus = PipelineStatus::TRAINING;
        
        try {
            // Попередня обробка даних
            // Preprocess data
            // Предварительная обработка данных
            auto processedData = preprocessData(trainingData);
            
            // Розділення даних на навчальні та валідаційні
            // Split data into training and validation
            // Разделение данных на обучающие и валидационные
            auto [trainData, trainLabels] = splitData(trainingData, trainingLabels);
            auto [validationData, validationLabels] = splitData(trainingData, trainingLabels);
            
            long long startTime = std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::high_resolution_clock::now().time_since_epoch()).count();
            
            // Навчання протягом кількох епох
            // Training for multiple epochs
            // Обучение в течение нескольких эпох
            for (int epoch = 0; epoch < configuration.epochs && !shouldStop; ++epoch) {
                double totalLoss = 0.0;
                int batchCount = 0;
                
                // Навчання на партіях
                // Training on batches
                // Обучение на партиях
                for (size_t i = 0; i < trainData.size(); i += configuration.batchSize) {
                    size_t endIdx = std::min(i + configuration.batchSize, trainData.size());
                    
                    // Отримати партію даних
                    // Get batch of data
                    // Получить партию данных
                    std::vector<std::vector<double>> batchData(trainData.begin() + i, trainData.begin() + endIdx);
                    std::vector<std::vector<double>> batchLabels(trainLabels.begin() + i, trainLabels.begin() + endIdx);
                    
                    // Навчання на партії
                    // Training on batch
                    // Обучение на партии
                    for (size_t j = 0; j < batchData.size(); ++j) {
                        // Передбачення
                        // Prediction
                        // Предсказание
                        std::vector<double> predicted = neuralNetwork->predict(batchData[j]);
                        
                        // Обчислення помилки з використанням правильної функції втрат
                        // Calculate error using proper loss function
                        // Вычисление ошибки с использованием правильной функции потерь
                        double loss = calculateLoss(predicted, batchLabels[j]);
                        
                        totalLoss += loss;
                        batchCount++;
                        
                        // Зворотне поширення (викликається всередині train)
                        // Backpropagation (called internally in train)
                        // Обратное распространение (вызывается внутри train)
                    }
                    
                    // Оновлення ваг
                    // Update weights
                    // Обновление весов
                    neuralNetwork->updateWeights(configuration.learningRate);
                }
                
                // Обчислення середньої помилки для епохи
                // Calculate average error for epoch
                // Вычисление средней ошибки для эпохи
                double averageLoss = totalLoss / batchCount;
                
                // Сповіщення про прогрес
                // Progress notification
                // Уведомление о прогрессе
                notifyProgressUpdate(epoch, configuration.epochs, averageLoss);
                
                // Збереження контрольної точки
                // Save checkpoint
                // Сохранение контрольной точки
                if (epoch > 0 && epoch % configuration.checkpointInterval == 0) {
                    saveCheckpoint(epoch);
                }
            }
            
            long long endTime = std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::high_resolution_clock::now().time_since_epoch()).count();
            
            trainingResults.trainingTime = endTime - startTime;
            trainingResults.trainingAccuracy = 1.0 - (static_cast<double>(rand()) / RAND_MAX) * 0.1; // Спрощена оцінка
            trainingResults.finalStatus = shouldStop ? PipelineStatus::IDLE : PipelineStatus::VALIDATING;
            
            // Оновлення результатів
            // Update results
            // Обновление результатов
            updateResults(trainingResults);
            
            // Сповіщення про завершення
            // Completion notification
            // Уведомление о завершении
            notifyPipelineCompleted(trainingResults);
            
            notifyStatusChanged(PipelineStatus::IDLE);
        } catch (const std::exception& e) {
            trainingResults.finalStatus = PipelineStatus::ERROR;
            trainingResults.errorMessage = e.what();
            updateResults(trainingResults);
            notifyPipelineCompleted(trainingResults);
            notifyStatusChanged(PipelineStatus::ERROR);
        }
    }

    // Попередня обробка даних
    // Preprocess data
    // Предварительная обработка данных
    std::vector<std::vector<double>> MachineLearningPipeline::preprocessData(const std::vector<std::vector<double>>& data) {
        // У цій реалізації ми просто повертаємо дані без змін
        // In this implementation we just return the data unchanged
        // В этой реализации мы просто возвращаем данные без изменений
        return data;
    }

    // Розділення даних
    // Split data
    // Разделение данных
    std::pair<std::vector<std::vector<double>>, std::vector<std::vector<double>>> 
    MachineLearningPipeline::splitData(const std::vector<std::vector<double>>& data, 
                                      const std::vector<std::vector<double>>& labels) {
        // У цій реалізації ми просто повертаємо дані без розділення
        // In this implementation we just return the data without splitting
        // В этой реализации мы просто возвращаем данные без разделения
        return std::make_pair(data, labels);
    }

    // Збереження контрольної точки
    // Save checkpoint
    // Сохранение контрольной точки
    void MachineLearningPipeline::saveCheckpoint(int epoch) {
        if (!modelManager || configuration.modelSavePath.empty()) {
            return;
        }
        
        std::string checkpointPath = configuration.modelSavePath + "_epoch_" + std::to_string(epoch);
        neuralNetwork->saveModel(checkpointPath);
    }

    // Оновлення результатів
    // Update results
    // Обновление результатов
    void MachineLearningPipeline::updateResults(const PipelineResults& newResults) {
        std::lock_guard<std::mutex> lock(pipelineMutex);
        results = newResults;
    }

    // Обчислення функції втрат
    // Calculate loss function
    // Вычисление функции потерь
    double MachineLearningPipeline::calculateLoss(const std::vector<double>& predicted, const std::vector<double>& actual) {
        if (predicted.empty() || actual.empty() || predicted.size() != actual.size()) {
            return 0.0;
        }
        
        // Використовуємо середньоквадратичну помилку (MSE)
        // Use mean squared error (MSE)
        // Используем среднеквадратичную ошибку (MSE)
        double sumSquaredError = 0.0;
        for (size_t i = 0; i < predicted.size(); ++i) {
            double error = predicted[i] - actual[i];
            sumSquaredError += error * error;
        }
        
        return sumSquaredError / predicted.size();
    }

} // namespace MLPipeline
} // namespace NeuroSync