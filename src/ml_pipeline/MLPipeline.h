#ifndef ML_PIPELINE_H
#define ML_PIPELINE_H

#include <vector>
#include <memory>
#include <string>
#include <map>
#include <thread>
#include <mutex>
#include <chrono>
#include "../network_neural/NeuralNetwork.h"
#include "../data_processing/DataProcessor.h"
#include "../model_management/ModelManager.h"

// MLPipeline.h
// Конвеєр машинного навчання для NeuroSync OS Sparky
// Machine learning pipeline for NeuroSync OS Sparky
// Конвейер машинного обучения для NeuroSync OS Sparky

namespace NeuroSync {
namespace MLPipeline {

    // Статус конвеєра
    // Pipeline status
    // Статус конвейера
    enum class PipelineStatus {
        IDLE,           // Очікування / Idle / Ожидание
        TRAINING,       // Навчання / Training / Обучение
        VALIDATING,     // Валідація / Validation / Валидация
        TESTING,        // Тестування / Testing / Тестирование
        DEPLOYING,      // Розгортання / Deployment / Развертывание
        ERROR           // Помилка / Error / Ошибка
    };

    // Конфігурація конвеєра
    // Pipeline configuration
    // Конфигурация конвейера
    struct PipelineConfig {
        int epochs;                     // Кількість епох навчання / Number of training epochs / Количество эпох обучения
        double learningRate;            // Швидкість навчання / Learning rate / Скорость обучения
        double validationSplit;         // Частка даних для валідації / Validation data split / Доля данных для валидации
        int batchSize;                  // Розмір партії / Batch size / Размер партии
        bool shuffleData;              // Перемішувати дані / Shuffle data / Перемешивать данные
        std::string modelSavePath;     // Шлях для збереження моделі / Model save path / Путь для сохранения модели
        int checkpointInterval;        // Інтервал збереження контрольних точок / Checkpoint interval / Интервал сохранения контрольных точек
        
        PipelineConfig() 
            : epochs(100), learningRate(0.01), validationSplit(0.2), 
              batchSize(32), shuffleData(true), modelSavePath(""), checkpointInterval(10) {}
    };

    // Результати конвеєра
    // Pipeline results
    // Результаты конвейера
    struct PipelineResults {
        PipelineStatus finalStatus;     // Фінальний статус / Final status / Финальный статус
        double trainingAccuracy;        // Точність навчання / Training accuracy / Точность обучения
        double validationAccuracy;      // Точність валідації / Validation accuracy / Точность валидации
        double testAccuracy;            // Точність тестування / Test accuracy / Точность тестирования
        long long trainingTime;         // Час навчання / Training time / Время обучения
        std::string errorMessage;       // Повідомлення про помилку / Error message / Сообщение об ошибке
        std::map<std::string, double> metrics; // Додаткові метрики / Additional metrics / Дополнительные метрики
        
        PipelineResults() 
            : finalStatus(PipelineStatus::IDLE), trainingAccuracy(0.0), validationAccuracy(0.0),
              testAccuracy(0.0), trainingTime(0), errorMessage("") {}
    };

    // Інтерфейс спостерігача за конвеєром
    // Pipeline observer interface
    // Интерфейс наблюдателя за конвейером
    class PipelineObserver {
    public:
        virtual ~PipelineObserver() = default;
        
        // Сповіщення про зміну статусу
        // Status change notification
        // Уведомление об изменении статуса
        virtual void onStatusChanged(PipelineStatus status) = 0;
        
        // Сповіщення про прогрес
        // Progress notification
        // Уведомление о прогрессе
        virtual void onProgressUpdate(int epoch, int totalEpochs, double loss) = 0;
        
        // Сповіщення про завершення
        // Completion notification
        // Уведомление о завершении
        virtual void onPipelineCompleted(const PipelineResults& results) = 0;
    };

    // Конвеєр машинного навчання
    // Machine learning pipeline
    // Конвейер машинного обучения
    class MachineLearningPipeline {
    public:
        MachineLearningPipeline();
        ~MachineLearningPipeline();
        
        // Ініціалізація конвеєра
        // Initialize pipeline
        // Инициализация конвейера
        bool initialize(const PipelineConfig& config);
        
        // Додати спостерігача
        // Add observer
        // Добавить наблюдателя
        void addObserver(std::shared_ptr<PipelineObserver> observer);
        
        // Видалити спостерігача
        // Remove observer
        // Удалить наблюдателя
        void removeObserver(std::shared_ptr<PipelineObserver> observer);
        
        // Запустити навчання
        // Start training
        // Запустить обучение
        bool startTraining(const std::vector<std::vector<double>>& trainingData,
                          const std::vector<std::vector<double>>& trainingLabels);
        
        // Зупинити конвеєр
        // Stop pipeline
        // Остановить конвейер
        void stopPipeline();
        
        // Отримати статус
        // Get status
        // Получить статус
        PipelineStatus getStatus() const;
        
        // Отримати результати
        // Get results
        // Получить результаты
        PipelineResults getResults() const;
        
        // Отримати конфігурацію
        // Get configuration
        // Получить конфигурацию
        PipelineConfig getConfiguration() const;
        
        // Встановити мережу
        // Set network
        // Установить сеть
        void setNeuralNetwork(std::unique_ptr<Network::NeuralNetwork> network);
        
        // Отримати мережу
        // Get network
        // Получить сеть
        Network::NeuralNetwork* getNeuralNetwork() const;
        
    private:
        PipelineConfig configuration;                           // Конфігурація / Configuration / Конфигурация
        mutable std::mutex pipelineMutex;                      // М'ютекс для потокобезпеки / Mutex for thread safety / Мьютекс для потокобезопасности
        std::unique_ptr<Network::NeuralNetwork> neuralNetwork; // Нейронна мережа / Neural network / Нейронная сеть
        std::unique_ptr<DataProcessing::DataProcessor> dataProcessor; // Процесор даних / Data processor / Процессор данных
        std::unique_ptr<ModelManagement::ModelManager> modelManager;  // Менеджер моделей / Model manager / Менеджер моделей
        std::vector<std::shared_ptr<PipelineObserver>> observers;     // Спостерігачі / Observers / Наблюдатели
        PipelineStatus currentStatus;                          // Поточний статус / Current status / Текущий статус
        PipelineResults results;                               // Результати / Results / Результаты
        std::atomic<bool> shouldStop;                         // Прапор зупинки / Stop flag / Флаг остановки
        std::thread trainingThread;                           // Потік навчання / Training thread / Поток обучения
        
        // Внутрішні методи
        // Internal methods
        // Внутренние методы
        void notifyStatusChanged(PipelineStatus status);
        void notifyProgressUpdate(int epoch, int totalEpochs, double loss);
        void notifyPipelineCompleted(const PipelineResults& results);
        void trainingLoop(const std::vector<std::vector<double>>& trainingData,
                         const std::vector<std::vector<double>>& trainingLabels);
        std::vector<std::vector<double>> preprocessData(const std::vector<std::vector<double>>& data);
        std::pair<std::vector<std::vector<double>>, std::vector<std::vector<double>>> 
            splitData(const std::vector<std::vector<double>>& data, 
                     const std::vector<std::vector<double>>& labels);
        void saveCheckpoint(int epoch);
        void updateResults(const PipelineResults& newResults);
        double calculateLoss(const std::vector<double>& predicted, const std::vector<double>& actual);

    };

} // namespace MLPipeline
} // namespace NeuroSync

#endif // ML_PIPELINE_H