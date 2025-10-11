// config_example.cpp
// Приклад використання менеджера конфігурації / Configuration manager usage example / Пример использования менеджера конфигурации
// NeuroSync OS Sparky

#include "../config/ConfigurationManager.h"
#include <iostream>
#include <fstream>

using namespace NeuroSync::Config;

int main() {
    std::cout << "NeuroSync OS Sparky - Configuration Manager Example" << std::endl;
    std::cout << "===================================================" << std::endl;
    
    // Створення менеджера конфігурації
    // Create configuration manager
    // Создание менеджера конфигурации
    ConfigurationManager configManager;
    
    // Ініціалізація менеджера конфігурації
    // Initialize configuration manager
    // Инициализация менеджера конфигурации
    if (!configManager.initialize()) {
        std::cerr << "Failed to initialize configuration manager" << std::endl;
        return 1;
    }
    
    std::cout << "Configuration manager initialized with " << configManager.getConfigCount() << " default values" << std::endl;
    
    // Отримання значень за замовчуванням
    // Get default values
    // Получение значений по умолчанию
    std::cout << "\nDefault configuration values:" << std::endl;
    std::cout << "System name: " << configManager.getString("system.name") << std::endl;
    std::cout << "System version: " << configManager.getString("system.version") << std::endl;
    std::cout << "Debug mode: " << (configManager.getBoolean("system.debug") ? "enabled" : "disabled") << std::endl;
    std::cout << "Log level: " << configManager.getInteger("system.log_level") << std::endl;
    std::cout << "Max threads: " << configManager.getInteger("scheduler.max_threads") << std::endl;
    
    // Встановлення нових значень
    // Set new values
    // Установка новых значений
    configManager.setConfigValue("system.name", ConfigValue(std::string("NeuroSync OS Sparky Pro")));
    configManager.setConfigValue("system.debug", ConfigValue(false));
    configManager.setConfigValue("custom.value", ConfigValue(std::string("custom_setting")));
    configManager.setConfigValue("custom.number", ConfigValue(42));

    std::cout << "\nUpdated configuration values:" << std::endl;
    std::cout << "System name: " << configManager.getString("system.name") << std::endl;
    std::cout << "Debug mode: " << (configManager.getBoolean("system.debug") ? "enabled" : "disabled") << std::endl;
    std::cout << "Custom value: " << configManager.getString("custom.value") << std::endl;
    std::cout << "Custom number: " << configManager.getInteger("custom.number") << std::endl;
    
    // Збереження конфігурації у файл
    // Save configuration to file
    // Сохранение конфигурации в файл
    std::string configFile = "example_config.txt";
    if (configManager.saveToFile(configFile)) {
        std::cout << "\nConfiguration saved to " << configFile << std::endl;
    } else {
        std::cerr << "Failed to save configuration to file" << std::endl;
    }
    
    // Створення нової конфігурації та завантаження з файлу
    // Create new configuration and load from file
    // Создание новой конфигурации и загрузка из файла
    ConfigurationManager loadedConfig;
    if (loadedConfig.loadFromFile(configFile)) {
        std::cout << "\nConfiguration loaded from " << configFile << std::endl;
        std::cout << "Loaded system name: " << loadedConfig.getString("system.name") << std::endl;
        std::cout << "Loaded custom value: " << loadedConfig.getString("custom.value") << std::endl;
        std::cout << "Loaded custom number: " << loadedConfig.getInteger("custom.number") << std::endl;
    } else {
        std::cerr << "Failed to load configuration from file" << std::endl;
    }
    
    // Створення прикладу конфігураційного файлу
    // Create example configuration file
    // Создание примера конфигурационного файла
    std::ofstream exampleFile("example_config_format.txt");
    if (exampleFile.is_open()) {
        exampleFile << "# NeuroSync OS Sparky Configuration File" << std::endl;
        exampleFile << "# This is a comment" << std::endl;
        exampleFile << "" << std::endl;
        exampleFile << "system.name = NeuroSync OS Sparky Enterprise" << std::endl;
        exampleFile << "system.version = 2.0.0" << std::endl;
        exampleFile << "system.debug = true" << std::endl;
        exampleFile << "system.log_level = 3" << std::endl;
        exampleFile << "scheduler.max_threads = 16" << std::endl;
        exampleFile << "scheduler.quantum_ms = 20" << std::endl;
        exampleFile << "memory.pool_size = 2048576" << std::endl;
        exampleFile << "neuron.max_count = 5000" << std::endl;
        exampleFile << "" << std::endl;
        exampleFile << "; This is also a comment" << std::endl;
        exampleFile << "synapse.max_connections = 50000" << std::endl;
        exampleFile.close();
        std::cout << "\nExample configuration file created: example_config_format.txt" << std::endl;
    }
    
    std::cout << "\nConfiguration manager example completed successfully!" << std::endl;
    
    return 0;
}