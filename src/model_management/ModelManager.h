#ifndef MODEL_MANAGER_H
#define MODEL_MANAGER_H

#include <string>
#include <vector>
#include <map>
#include <memory>
#include <chrono>
#include "../network_neural/NeuralNetwork.h"

// ModelManager.h
// Менеджер моделей для NeuroSync OS Sparky
// Model manager for NeuroSync OS Sparky
// Менеджер моделей для NeuroSync OS Sparky

namespace NeuroSync {
namespace ModelManagement {

    // Статус моделі
    // Model status
    // Статус модели
    enum class ModelStatus {
        UNTRAINED,      // Ненавчена / Untrained / Необученная
        TRAINING,       // Навчання / Training / Обучение
        TRAINED,        // Навчена / Trained / Обученная
        DEPLOYED,       // Розгорнута / Deployed / Развернутая
        ARCHIVED        // Архівована / Archived / Архивированная
    };

    // Інформація про модель
    // Model information
    // Информация о модели
    struct ModelInfo {
        std::string modelId;                    // ID моделі / Model ID / ID модели
        std::string modelName;                  // Ім'я моделі / Model name / Имя модели
        std::string version;                    // Версія моделі / Model version / Версия модели
        std::string description;                // Опис моделі / Model description / Описание модели
        std::string creationDate;              // Дата створення / Creation date / Дата создания
        std::string lastModified;              // Дата останньої зміни / Last modified date / Дата последнего изменения
        ModelStatus status;                    // Статус моделі / Model status / Статус модели
        std::string filePath;                  // Шлях до файлу моделі / Model file path / Путь к файлу модели
        size_t fileSize;                       // Розмір файлу моделі / Model file size / Размер файла модели
        std::map<std::string, double> metrics; // Метрики моделі / Model metrics / Метрики модели
        
        ModelInfo() : status(ModelStatus::UNTRAINED), fileSize(0) {}
    };

    // Конфігурація менеджера моделей
    // Model manager configuration
    // Конфигурация менеджера моделей
    struct ModelManagerConfig {
        std::string modelStoragePath;          // Шлях до сховища моделей / Model storage path / Путь к хранилищу моделей
        bool autoVersioning;                   // Автоматичне версіювання / Auto versioning / Автоматическое версионирование
        size_t maxModelsToKeep;               // Максимальна кількість моделей для збереження / Max models to keep / Максимальное количество моделей для сохранения
        bool compressModels;                   // Стиснення моделей / Compress models / Сжатие моделей
        
        ModelManagerConfig() 
            : modelStoragePath("./models"), autoVersioning(true), maxModelsToKeep(10), compressModels(true) {}
    };

    // Менеджер моделей
    // Model manager
    // Менеджер моделей
    class ModelManager {
    public:
        ModelManager();
        ~ModelManager();
        
        // Ініціалізація менеджера моделей
        // Initialize model manager
        // Инициализация менеджера моделей
        bool initialize(const ModelManagerConfig& config = ModelManagerConfig());
        
        // Зберегти модель
        // Save model
        // Сохранить модель
        bool saveModel(Network::NeuralNetwork* model, const std::string& modelName, 
                      const std::string& description = "");
        
        // Завантажити модель
        // Load model
        // Загрузить модель
        std::unique_ptr<Network::NeuralNetwork> loadModel(const std::string& modelId);
        
        // Видалити модель
        // Delete model
        // Удалить модель
        bool deleteModel(const std::string& modelId);
        
        // Отримати інформацію про модель
        // Get model information
        // Получить информацию о модели
        ModelInfo getModelInfo(const std::string& modelId) const;
        
        // Отримати список всіх моделей
        // Get list of all models
        // Получить список всех моделей
        std::vector<ModelInfo> getAllModels() const;
        
        // Оновити статус моделі
        // Update model status
        // Обновить статус модели
        bool updateModelStatus(const std::string& modelId, ModelStatus status);
        
        // Оновити метрики моделі
        // Update model metrics
        // Обновить метрики модели
        bool updateModelMetrics(const std::string& modelId, const std::map<std::string, double>& metrics);
        
        // Архівувати старі моделі
        // Archive old models
        // Архивировать старые модели
        void archiveOldModels();
        
        // Отримати конфігурацію
        // Get configuration
        // Получить конфигурацию
        ModelManagerConfig getConfiguration() const;
        
        // Експортувати модель
        // Export model
        // Экспортировать модель
        bool exportModel(const std::string& modelId, const std::string& exportPath);
        
        // Імпортувати модель
        // Import model
        // Импортировать модель
        bool importModel(const std::string& importPath, const std::string& modelName = "");
        
    private:
        ModelManagerConfig configuration;              // Конфігурація / Configuration / Конфигурация
        std::map<std::string, ModelInfo> modelRegistry; // Реєстр моделей / Model registry / Реестр моделей
        mutable std::mutex registryMutex;             // М'ютекс для потокобезпеки / Mutex for thread safety / Мьютекс для потокобезопасности
        
        // Внутрішні методи
        // Internal methods
        // Внутренние методы
        std::string generateModelId();
        std::string getCurrentTimestamp() const;
        std::string getVersionFromModelName(const std::string& modelName) const;
        std::string incrementVersion(const std::string& version) const;
        bool saveModelToFile(Network::NeuralNetwork* model, const std::string& filePath);
        std::unique_ptr<Network::NeuralNetwork> loadModelFromFile(const std::string& filePath);
        bool deleteModelFile(const std::string& filePath);
        std::vector<std::string> listModelFiles() const;
    };

} // namespace ModelManagement
} // namespace NeuroSync

#endif // MODEL_MANAGER_H