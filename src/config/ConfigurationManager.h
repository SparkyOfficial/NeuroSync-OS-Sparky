#ifndef CONFIGURATION_MANAGER_H
#define CONFIGURATION_MANAGER_H

#include <string>
#include <map>
#include <vector>
#include <memory>
#include <mutex>
#include <fstream>
#include <sstream>

// ConfigurationManager.h
// Менеджер конфігурації для NeuroSync OS Sparky
// Configuration manager for NeuroSync OS Sparky
// Менеджер конфигурации для NeuroSync OS Sparky

namespace NeuroSync {
namespace Config {

    // Типи конфігураційних значень
    // Configuration value types
    // Типы конфигурационных значений
    enum class ConfigValueType {
        STRING,
        INTEGER,
        FLOAT,
        BOOLEAN
    };

    // Конфігураційне значення
    // Configuration value
    // Конфигурационное значение
    struct ConfigValue {
        ConfigValueType type;
        std::string stringValue;
        int intValue;
        float floatValue;
        bool boolValue;
        
        // Конструктори для різних типів
        // Constructors for different types
        // Конструкторы для разных типов
        ConfigValue() : type(ConfigValueType::STRING), stringValue(""), intValue(0), floatValue(0.0f), boolValue(false) {} // Default constructor
        ConfigValue(const std::string& value) : type(ConfigValueType::STRING), stringValue(value), intValue(0), floatValue(0.0f), boolValue(false) {}
        ConfigValue(int value) : type(ConfigValueType::INTEGER), stringValue(""), intValue(value), floatValue(0.0f), boolValue(false) {}
        ConfigValue(float value) : type(ConfigValueType::FLOAT), stringValue(""), intValue(0), floatValue(value), boolValue(false) {}
        ConfigValue(bool value) : type(ConfigValueType::BOOLEAN), stringValue(""), intValue(0), floatValue(0.0f), boolValue(value) {}
    };

    // Менеджер конфігурації
    // Configuration manager
    // Менеджер конфигурации
    class ConfigurationManager {
    public:
        ConfigurationManager();
        ~ConfigurationManager();
        
        // Ініціалізація менеджера конфігурації
        // Initialize configuration manager
        // Инициализация менеджера конфигурации
        bool initialize(const std::string& configFile = "");
        
        // Завантаження конфігурації з файлу
        // Load configuration from file
        // Загрузка конфигурации из файла
        bool loadFromFile(const std::string& filename);
        
        // Збереження конфігурації у файл
        // Save configuration to file
        // Сохранение конфигурации в файл
        bool saveToFile(const std::string& filename) const;
        
        // Встановлення конфігураційного значення
        // Set configuration value
        // Установка конфигурационного значения
        void setConfigValue(const std::string& key, const ConfigValue& value);
        
        // Отримання конфігураційного значення
        // Get configuration value
        // Получение конфигурационного значения
        ConfigValue getConfigValue(const std::string& key) const;
        
        // Отримання конфігураційного значення з типом
        // Get configuration value with type
        // Получение конфигурационного значения с типом
        std::string getString(const std::string& key, const std::string& defaultValue = "") const;
        int getInteger(const std::string& key, int defaultValue = 0) const;
        float getFloat(const std::string& key, float defaultValue = 0.0f) const;
        bool getBoolean(const std::string& key, bool defaultValue = false) const;
        
        // Перевірка наявності ключа
        // Check if key exists
        // Проверка наличия ключа
        bool hasKey(const std::string& key) const;
        
        // Видалення конфігураційного значення
        // Remove configuration value
        // Удаление конфигурационного значения
        void removeConfigValue(const std::string& key);
        
        // Отримання всіх ключів
        // Get all keys
        // Получение всех ключей
        std::vector<std::string> getAllKeys() const;
        
        // Очищення всіх конфігураційних значень
        // Clear all configuration values
        // Очистка всех конфигурационных значений
        void clear();
        
        // Отримання кількості конфігураційних значень
        // Get configuration count
        // Получение количества конфигурационных значений
        size_t getConfigCount() const;
        
        // Встановлення конфігурації за замовчуванням
        // Set default configuration
        // Установка конфигурации по умолчанию
        void setDefaultConfiguration();
        
    private:
        // Конфігураційні значення
        // Configuration values
        // Конфигурационные значения
        std::map<std::string, ConfigValue> configValues;
        
        // Мьютекс для потокобезпеки
        // Mutex for thread safety
        // Мьютекс для потокобезопасности
        mutable std::mutex configMutex;
        
        // Ім'я файлу конфігурації
        // Configuration file name
        // Имя файла конфигурации
        std::string configFileName;
        
        // Внутрішні методи
        // Internal methods
        // Внутренние методы
        std::string trim(const std::string& str) const;
        bool parseLine(const std::string& line, std::string& key, ConfigValue& value) const;
        std::string valueToString(const ConfigValue& value) const;
        ConfigValue stringToValue(const std::string& str, ConfigValueType type) const;
    };

} // namespace Config
} // namespace NeuroSync

#endif // CONFIGURATION_MANAGER_H