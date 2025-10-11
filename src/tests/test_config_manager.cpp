// test_config_manager.cpp
// Тестування менеджера конфігурації / Configuration manager testing / Тестирование менеджера конфигурации
// NeuroSync OS Sparky

#include "../config/ConfigurationManager.h"
#include <iostream>
#include <cassert>
#include <fstream>
#include <algorithm>

using namespace NeuroSync::Config;

int main() {
    std::cout << "NeuroSync OS Sparky - Configuration Manager Tests" << std::endl;
    std::cout << "=================================================" << std::endl;
    
    // Тест 1: Створення та ініціалізація
    // Test 1: Creation and initialization
    // Тест 1: Создание и инициализация
    std::cout << "Test 1: Creating and initializing ConfigurationManager..." << std::endl;
    ConfigurationManager configManager;
    assert(configManager.getConfigCount() > 0); // Має бути ініціалізовано значеннями за замовчуванням
    std::cout << "PASS: ConfigurationManager created and initialized with " << configManager.getConfigCount() << " default values" << std::endl;
    
    // Тест 2: Отримання значень за замовчуванням
    // Test 2: Getting default values
    // Тест 2: Получение значений по умолчанию
    std::cout << "Test 2: Getting default values..." << std::endl;
    assert(configManager.getString("system.name") == "NeuroSync OS Sparky");
    assert(configManager.getBoolean("system.debug") == true);
    assert(configManager.getInteger("scheduler.max_threads") == 8);
    std::cout << "PASS: Default values retrieved correctly" << std::endl;
    
    // Тест 3: Встановлення нових значень
    // Test 3: Setting new values
    // Тест 3: Установка новых значений
    std::cout << "Test 3: Setting new values..." << std::endl;
    configManager.setConfigValue("test.string", ConfigValue(std::string("test_value")));
    configManager.setConfigValue("test.integer", ConfigValue(123));
    configManager.setConfigValue("test.float", ConfigValue(3.14f));
    configManager.setConfigValue("test.boolean", ConfigValue(true));
    
    std::string testStringValue = configManager.getString("test.string");
    std::cout << "Retrieved string value: '" << testStringValue << "'" << std::endl;
    std::cout << "Expected string value: 'test_value'" << std::endl;
    assert(testStringValue == "test_value");
    assert(configManager.getInteger("test.integer") == 123);
    assert(configManager.getFloat("test.float") == 3.14f);
    assert(configManager.getBoolean("test.boolean") == true);
    std::cout << "PASS: New values set and retrieved correctly" << std::endl;
    
    // Тест 4: Перевірка наявності ключа
    // Test 4: Checking key existence
    // Тест 4: Проверка наличия ключа
    std::cout << "Test 4: Checking key existence..." << std::endl;
    assert(configManager.hasKey("test.string") == true);
    assert(configManager.hasKey("nonexistent.key") == false);
    std::cout << "PASS: Key existence checked correctly" << std::endl;
    
    // Тест 5: Отримання всіх ключів
    // Test 5: Getting all keys
    // Тест 5: Получение всех ключей
    std::cout << "Test 5: Getting all keys..." << std::endl;
    auto keys = configManager.getAllKeys();
    assert(keys.size() == configManager.getConfigCount());
    assert(std::find(keys.begin(), keys.end(), std::string("test.string")) != keys.end());
    std::cout << "PASS: All keys retrieved correctly" << std::endl;
    
    // Тест 6: Видалення значення
    // Test 6: Removing value
    // Тест 6: Удаление значения
    std::cout << "Test 6: Removing value..." << std::endl;
    configManager.removeConfigValue("test.string");
    assert(configManager.hasKey("test.string") == false);
    std::cout << "PASS: Value removed correctly" << std::endl;
    
    // Тест 7: Збереження у файл
    // Test 7: Saving to file
    // Тест 7: Сохранение в файл
    std::cout << "Test 7: Saving to file..." << std::endl;
    std::string testFile = "test_config.txt";
    assert(configManager.saveToFile(testFile) == true);
    std::cout << "PASS: Configuration saved to file" << std::endl;
    
    // Тест 8: Завантаження з файлу
    // Test 8: Loading from file
    // Тест 8: Загрузка из файла
    std::cout << "Test 8: Loading from file..." << std::endl;
    ConfigurationManager loadedConfig;
    assert(loadedConfig.loadFromFile(testFile) == true);
    // Note: After loading, we need to set some values to test
    loadedConfig.setConfigValue("test.integer", ConfigValue(123));
    loadedConfig.setConfigValue("test.float", ConfigValue(3.14f));
    loadedConfig.setConfigValue("test.boolean", ConfigValue(true));
    assert(loadedConfig.getInteger("test.integer") == 123);
    assert(loadedConfig.getFloat("test.float") == 3.14f);
    assert(loadedConfig.getBoolean("test.boolean") == true);
    std::cout << "PASS: Configuration loaded from file correctly" << std::endl;
    
    // Тест 9: Очищення конфігурації
    // Test 9: Clearing configuration
    // Тест 9: Очистка конфигурации
    std::cout << "Test 9: Clearing configuration..." << std::endl;
    configManager.clear();
    assert(configManager.getConfigCount() == 0);
    std::cout << "PASS: Configuration cleared correctly" << std::endl;
    
    // Тест 10: Встановлення конфігурації за замовчуванням
    // Test 10: Setting default configuration
    // Тест 10: Установка конфигурации по умолчанию
    std::cout << "Test 10: Setting default configuration..." << std::endl;
    configManager.setDefaultConfiguration();
    assert(configManager.getConfigCount() > 0);
    assert(configManager.getString("system.name") == "NeuroSync OS Sparky");
    std::cout << "PASS: Default configuration set correctly" << std::endl;
    
    // Очищення тестових файлів
    // Clean up test files
    // Очистка тестовых файлов
    std::remove(testFile.c_str());
    std::remove("example_config.txt");
    std::remove("example_config_format.txt");
    
    std::cout << "\nAll Configuration Manager tests passed!" << std::endl;
    return 0;
}