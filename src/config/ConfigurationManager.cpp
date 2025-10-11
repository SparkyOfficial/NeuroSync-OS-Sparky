#include "ConfigurationManager.h"
#include <algorithm>
#include <cctype>
#include <iostream>

namespace NeuroSync {
namespace Config {

    ConfigurationManager::ConfigurationManager() : configFileName("") {
        // Встановлення конфігурації за замовчуванням
        // Set default configuration
        // Установка конфигурации по умолчанию
        setDefaultConfiguration();
    }

    ConfigurationManager::~ConfigurationManager() {
        // Деструктор
        // Destructor
        // Деструктор
    }

    bool ConfigurationManager::initialize(const std::string& configFile) {
        // Ініціалізація менеджера конфігурації
        // Initialize configuration manager
        // Инициализация менеджера конфигурации
        
        if (!configFile.empty()) {
            configFileName = configFile;
            return loadFromFile(configFile);
        }
        
        return true;
    }

    bool ConfigurationManager::loadFromFile(const std::string& filename) {
        // Завантаження конфігурації з файлу
        // Load configuration from file
        // Загрузка конфигурации из файла
        
        std::lock_guard<std::mutex> lock(configMutex);
        
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Failed to open configuration file: " << filename << std::endl;
            return false;
        }
        
        std::string line;
        while (std::getline(file, line)) {
            // Пропускаємо порожні рядки та коментарі
            // Skip empty lines and comments
            // Пропускаем пустые строки и комментарии
            line = trim(line);
            if (line.empty() || line[0] == '#' || line[0] == ';') {
                continue;
            }
            
            // Розбираємо рядок
            // Parse line
            // Разбираем строку
            std::string key;
            ConfigValue value;
            if (parseLine(line, key, value)) {
                configValues[key] = value;
            }
        }
        
        file.close();
        return true;
    }

    bool ConfigurationManager::saveToFile(const std::string& filename) const {
        // Збереження конфігурації у файл
        // Save configuration to file
        // Сохранение конфигурации в файл
        
        std::lock_guard<std::mutex> lock(configMutex);
        
        std::ofstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Failed to open configuration file for writing: " << filename << std::endl;
            return false;
        }
        
        // Записуємо конфігураційні значення
        // Write configuration values
        // Записываем конфигурационные значения
        for (const auto& pair : configValues) {
            file << pair.first << " = " << valueToString(pair.second) << std::endl;
        }
        
        file.close();
        return true;
    }

    void ConfigurationManager::setConfigValue(const std::string& key, const ConfigValue& value) {
        // Встановлення конфігураційного значення
        // Set configuration value
        // Установка конфигурационного значения
        
        std::lock_guard<std::mutex> lock(configMutex);
        configValues[key] = value;
    }

    ConfigValue ConfigurationManager::getConfigValue(const std::string& key) const {
        // Отримання конфігураційного значення
        // Get configuration value
        // Получение конфигурационного значения
        
        std::lock_guard<std::mutex> lock(configMutex);
        
        auto it = configValues.find(key);
        if (it != configValues.end()) {
            return it->second;
        }
        
        // Повертаємо порожнє значення, якщо ключ не знайдено
        // Return empty value if key not found
        // Возвращаем пустое значение, если ключ не найден
        return ConfigValue("");
    }

    std::string ConfigurationManager::getString(const std::string& key, const std::string& defaultValue) const {
        // Отримання строкового значення
        // Get string value
        // Получение строкового значения
        
        std::lock_guard<std::mutex> lock(configMutex);
        
        auto it = configValues.find(key);
        if (it != configValues.end() && it->second.type == ConfigValueType::STRING) {
            return it->second.stringValue;
        }
        
        return defaultValue;
    }

    int ConfigurationManager::getInteger(const std::string& key, int defaultValue) const {
        // Отримання цілого значення
        // Get integer value
        // Получение целого значения
        
        std::lock_guard<std::mutex> lock(configMutex);
        
        auto it = configValues.find(key);
        if (it != configValues.end() && it->second.type == ConfigValueType::INTEGER) {
            return it->second.intValue;
        }
        
        return defaultValue;
    }

    float ConfigurationManager::getFloat(const std::string& key, float defaultValue) const {
        // Отримання числа з плаваючою точкою
        // Get float value
        // Получение числа с плавающей точкой
        
        std::lock_guard<std::mutex> lock(configMutex);
        
        auto it = configValues.find(key);
        if (it != configValues.end() && it->second.type == ConfigValueType::FLOAT) {
            return it->second.floatValue;
        }
        
        return defaultValue;
    }

    bool ConfigurationManager::getBoolean(const std::string& key, bool defaultValue) const {
        // Отримання булевого значення
        // Get boolean value
        // Получение булевого значения
        
        std::lock_guard<std::mutex> lock(configMutex);
        
        auto it = configValues.find(key);
        if (it != configValues.end() && it->second.type == ConfigValueType::BOOLEAN) {
            return it->second.boolValue;
        }
        
        return defaultValue;
    }

    bool ConfigurationManager::hasKey(const std::string& key) const {
        // Перевірка наявності ключа
        // Check if key exists
        // Проверка наличия ключа
        
        std::lock_guard<std::mutex> lock(configMutex);
        return configValues.find(key) != configValues.end();
    }

    void ConfigurationManager::removeConfigValue(const std::string& key) {
        // Видалення конфігураційного значення
        // Remove configuration value
        // Удаление конфигурационного значения
        
        std::lock_guard<std::mutex> lock(configMutex);
        configValues.erase(key);
    }

    std::vector<std::string> ConfigurationManager::getAllKeys() const {
        // Отримання всіх ключів
        // Get all keys
        // Получение всех ключей
        
        std::lock_guard<std::mutex> lock(configMutex);
        
        std::vector<std::string> keys;
        keys.reserve(configValues.size());
        
        for (const auto& pair : configValues) {
            keys.push_back(pair.first);
        }
        
        return keys;
    }

    void ConfigurationManager::clear() {
        // Очищення всіх конфігураційних значень
        // Clear all configuration values
        // Очистка всех конфигурационных значений
        
        std::lock_guard<std::mutex> lock(configMutex);
        configValues.clear();
    }

    size_t ConfigurationManager::getConfigCount() const {
        // Отримання кількості конфігураційних значень
        // Get configuration count
        // Получение количества конфигурационных значений
        
        std::lock_guard<std::mutex> lock(configMutex);
        return configValues.size();
    }

    void ConfigurationManager::setDefaultConfiguration() {
        // Встановлення конфігурації за замовчуванням
        // Set default configuration
        // Установка конфигурации по умолчанию
        
        std::lock_guard<std::mutex> lock(configMutex);
        
        // Базова конфігурація за замовчуванням
        // Default base configuration
        // Базовая конфигурация по умолчанию
        configValues["system.name"] = ConfigValue(std::string("NeuroSync OS Sparky"));
        configValues["system.version"] = ConfigValue(std::string("1.0.0"));
        configValues["system.debug"] = ConfigValue(true);
        configValues["system.log_level"] = ConfigValue(2); // 0=ERROR, 1=WARNING, 2=INFO, 3=DEBUG
        configValues["scheduler.max_threads"] = ConfigValue(8);
        configValues["scheduler.quantum_ms"] = ConfigValue(10);
        configValues["memory.pool_size"] = ConfigValue(1024 * 1024); // 1MB
        configValues["neuron.max_count"] = ConfigValue(1000);
        configValues["synapse.max_connections"] = ConfigValue(10000);
        configValues["event.queue_size"] = ConfigValue(1000);
    }

    std::string ConfigurationManager::trim(const std::string& str) const {
        // Обрізка пробілів
        // Trim whitespace
        // Обрезка пробелов
        
        size_t first = str.find_first_not_of(' ');
        if (first == std::string::npos) {
            return "";
        }
        
        size_t last = str.find_last_not_of(' ');
        return str.substr(first, (last - first + 1));
    }

    bool ConfigurationManager::parseLine(const std::string& line, std::string& key, ConfigValue& value) const {
        // Розбір рядка конфігурації
        // Parse configuration line
        // Разбор строки конфигурации
        
        size_t equalPos = line.find('=');
        if (equalPos == std::string::npos) {
            return false;
        }
        
        key = trim(line.substr(0, equalPos));
        std::string valueStr = trim(line.substr(equalPos + 1));
        
        // Conservative approach: only parse explicit boolean values
        // For everything else, treat as string
        // This avoids the issue where "NeuroSync OS Sparky" gets parsed as boolean "true"
        if (valueStr == "true") {
            value = ConfigValue(true);
        } else if (valueStr == "false") {
            value = ConfigValue(false);
        } else {
            // Try to parse as number, but fall back to string
            if (valueStr.find('.') != std::string::npos) {
                try {
                    value = ConfigValue(std::stof(valueStr));
                } catch (...) {
                    value = ConfigValue(valueStr);
                }
            } else {
                try {
                    value = ConfigValue(std::stoi(valueStr));
                } catch (...) {
                    value = ConfigValue(valueStr);
                }
            }
        }
        
        return true;
    }

    std::string ConfigurationManager::valueToString(const ConfigValue& value) const {
        // Перетворення значення в строку
        // Convert value to string
        // Преобразование значения в строку
        
        switch (value.type) {
            case ConfigValueType::STRING:
                return value.stringValue;
            case ConfigValueType::INTEGER:
                return std::to_string(value.intValue);
            case ConfigValueType::FLOAT:
                return std::to_string(value.floatValue);
            case ConfigValueType::BOOLEAN:
                return value.boolValue ? "true" : "false";
            default:
                return "";
        }
    }

    ConfigValue ConfigurationManager::stringToValue(const std::string& str, ConfigValueType type) const {
        // Перетворення строки в значення
        // Convert string to value
        // Преобразование строки в значение
        
        switch (type) {
            case ConfigValueType::STRING:
                return ConfigValue(str);
            case ConfigValueType::INTEGER:
                try {
                    return ConfigValue(std::stoi(str));
                } catch (...) {
                    return ConfigValue(0);
                }
            case ConfigValueType::FLOAT:
                try {
                    return ConfigValue(std::stof(str));
                } catch (...) {
                    return ConfigValue(0.0f);
                }
            case ConfigValueType::BOOLEAN:
                return ConfigValue(str == "true");
            default:
                return ConfigValue("");
        }
    }

} // namespace Config
} // namespace NeuroSync