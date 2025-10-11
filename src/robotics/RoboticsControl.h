#ifndef ROBOTICS_CONTROL_H
#define ROBOTICS_CONTROL_H

#include <vector>
#include <string>
#include <map>
#include <memory>
#include <chrono>
#include "../neuron/NeuronManager.h"
#include "../network_neural/NeuralNetwork.h"
#include "../event/EventSystem.h"

// RoboticsControl.h
// Модуль керування робототехнікою для NeuroSync OS Sparky
// Robotics control module for NeuroSync OS Sparky
// Модуль управления робототехникой для NeuroSync OS Sparky

namespace NeuroSync {
namespace Robotics {

    // Тип робота
    // Robot type
    // Тип робота
    enum class RobotType {
        INDUSTRIAL,     // Промисловий робот / Industrial robot / Промышленный робот
        SERVICE,        // Службовий робот / Service robot / Сервисный робот
        MOBILE,         // Мобільний робот / Mobile robot / Мобильный робот
        HUMANOID,       // Гуманоїдний робот / Humanoid robot / Гуманоидный робот
        DRONE,          // Дрон / Drone / Дрон
        AUTONOMOUS      // Автономний робот / Autonomous robot / Автономный робот
    };

    // Структура сенсорних даних
    // Sensor data structure
    // Структура сенсорных данных
    struct SensorData {
        std::map<std::string, double> sensorReadings;   // Показання сенсорів / Sensor readings / Показания сенсоров
        long long timestamp;                           // Часова мітка / Timestamp / Временная метка
        std::string sensorType;                        // Тип сенсора / Sensor type / Тип сенсора
        int sensorId;                                  // ID сенсора / Sensor ID / ID сенсора
        
        SensorData() : timestamp(0), sensorId(0) {}
    };

    // Структура команди роботу
    // Robot command structure
    // Структура команды роботу
    struct RobotCommand {
        std::string command;            // Команда / Command / Команда
        std::map<std::string, double> parameters; // Параметри команди / Command parameters / Параметры команды
        long long timestamp;           // Часова мітка / Timestamp / Временная метка
        int priority;                  // Пріоритет / Priority / Приоритет
        bool executed;                // Виконано / Executed / Выполнено
        
        RobotCommand() : timestamp(0), priority(0), executed(false) {}
        RobotCommand(const std::string& cmd) : command(cmd), timestamp(0), priority(0), executed(false) {}
    };

    // Структура стану робота
    // Robot state structure
    // Структура состояния робота
    struct RobotState {
        std::map<std::string, double> jointPositions;   // Позиції суглобів / Joint positions / Позиции суставов
        std::map<std::string, double> jointVelocities;  // Швидкості суглобів / Joint velocities / Скорости суставов
        std::map<std::string, double> sensorData;       // Дані сенсорів / Sensor data / Данные сенсоров
        std::string currentState;                       // Поточний стан / Current state / Текущее состояние
        long long timestamp;                           // Часова мітка / Timestamp / Временная метка
        double batteryLevel;                           // Рівень заряду батареї / Battery level / Уровень заряда батареи
        bool isOperational;                           // Чи працює / Is operational / Работает ли
        
        RobotState() : timestamp(0), batteryLevel(100.0), isOperational(true) {}
    };

    // Модуль керування робототехнікою
    // Robotics control module
    // Модуль управления робототехникой
    class RoboticsControl {
    public:
        // Конструктор
        // Constructor
        // Конструктор
        RoboticsControl(RobotType type, const std::string& name);
        
        // Деструктор
        // Destructor
        // Деструктор
        ~RoboticsControl();
        
        // Ініціалізація модуля
        // Initialize module
        // Инициализация модуля
        bool initialize();
        
        // Запустити робота
        // Start robot
        // Запустить робота
        bool start();
        
        // Зупинити робота
        // Stop robot
        // Остановить робота
        bool stop();
        
        // Надіслати команду роботу
        // Send command to robot
        // Отправить команду роботу
        bool sendCommand(const RobotCommand& command);
        
        // Отримати стан робота
        // Get robot state
        // Получить состояние робота
        RobotState getRobotState() const;
        
        // Оновити стан робота
        // Update robot state
        // Обновить состояние робота
        void updateRobotState(const RobotState& state);
        
        // Обробити сенсорні дані
        // Process sensor data
        // Обработать сенсорные данные
        void processSensorData(const SensorData& data);
        
        // Виконати навчання
        // Perform training
        // Выполнить обучение
        bool train(const std::vector<SensorData>& trainingData, 
                  const std::vector<RobotCommand>& trainingCommands,
                  int epochs, double learningRate);
        
        // Навігація
        // Navigation
        // Навигация
        bool navigateTo(const std::map<std::string, double>& targetPosition);
        
        // Уникнення перешкод
        // Obstacle avoidance
        // Избегание препятствий
        bool avoidObstacles(const std::vector<SensorData>& sensorData);
        
        // Маніпуляція об'єктами
        // Object manipulation
        // Манипуляция объектами
        bool manipulateObject(const std::string& objectName, const std::string& action);
        
        // Розпізнавання об'єктів
        // Object recognition
        // Распознавание объектов
        std::map<std::string, double> recognizeObjects(const std::vector<SensorData>& imageData);
        
        // Планування шляху
        // Path planning
        // Планирование пути
        std::vector<std::map<std::string, double>> planPath(const std::map<std::string, double>& startPosition,
                                                           const std::map<std::string, double>& targetPosition);
        
        // Синхронізація з іншими роботами
        // Synchronize with other robots
        // Синхронизация с другими роботами
        bool synchronizeWithRobots(const std::vector<int>& robotIds);
        
        // Екстрена зупинка
        // Emergency stop
        // Аварийная остановка
        bool emergencyStop();
        
        // Самодіагностика
        // Self-diagnostics
        // Самодиагностика
        std::map<std::string, std::string> runDiagnostics();
        
        // Отримати статистику
        // Get statistics
        // Получить статистику
        struct RoboticsStatistics {
            size_t totalCommandsExecuted;
            size_t totalSensorReadingsProcessed;
            double averageResponseTime;
            size_t totalTrainingSessions;
            long long lastCommandTime;
            double operationalEfficiency;
        };
        
        RoboticsStatistics getStatistics() const;
        
        // Отримати версію модуля
        // Get module version
        // Получить версию модуля
        std::string getVersion() const;
        
    private:
        RobotType robotType;                            // Тип робота / Robot type / Тип робота
        std::string robotName;                          // Ім'я робота / Robot name / Имя робота
        std::unique_ptr<Network::NeuralNetwork> controlModel; // Модель керування / Control model / Модель управления
        std::unique_ptr<Network::NeuralNetwork> navigationModel; // Модель навігації / Navigation model / Модель навигации
        std::unique_ptr<NeuronManager> neuronManager;   // Менеджер нейронів / Neuron manager / Менеджер нейронов
        std::unique_ptr<Event::EventSystem> eventSystem; // Система подій / Event system / Система событий
        RoboticsStatistics statistics;                  // Статистика / Statistics / Статистика
        RobotState currentState;                        // Поточний стан / Current state / Текущее состояние
        bool isInitialized;                            // Прапор ініціалізації / Initialization flag / Флаг инициализации
        bool isRunning;                                // Прапор запуску / Running flag / Флаг запуска
        std::string version;                           // Версія модуля / Module version / Версия модуля
        std::queue<RobotCommand> commandQueue;         // Черга команд / Command queue / Очередь команд
        
        // Внутрішні методи
        // Internal methods
        // Внутренние методы
        void initializeModels();
        long long getCurrentTimeMillis() const;
        std::vector<double> normalizeSensorData(const std::map<std::string, double>& sensorData);
        std::map<std::string, double> denormalizeSensorData(const std::vector<double>& normalizedData);
        double calculateDistance(const std::map<std::string, double>& pos1, const std::map<std::string, double>& pos2);
        std::map<std::string, double> calculateTrajectory(const std::map<std::string, double>& currentPosition,
                                                         const std::map<std::string, double>& targetPosition);
        bool executeCommand(const RobotCommand& command);
        void updateStatistics(bool success, long long responseTime);
        std::string generateReport(const RoboticsStatistics& stats);
    };

} // namespace Robotics
} // namespace NeuroSync

#endif // ROBOTICS_CONTROL_H