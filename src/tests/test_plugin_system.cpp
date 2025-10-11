// test_plugin_system.cpp
// Тестування системи плагінів / Plugin system testing / Тестирование системы плагинов
// NeuroSync OS Sparky

#include "../plugin/PluginSystem.h"
#include <iostream>
#include <cassert>

using namespace NeuroSync::Plugin;

int main() {
    std::cout << "NeuroSync OS Sparky - Plugin System Tests" << std::endl;
    std::cout << "=========================================" << std::endl;
    
    // Тест 1: Створення та ініціалізація
    // Test 1: Creation and initialization
    // Тест 1: Создание и инициализация
    std::cout << "Test 1: Creating and initializing PluginSystem..." << std::endl;
    PluginSystem pluginSystem;
    assert(pluginSystem.initialize());
    std::cout << "PASS: PluginSystem created and initialized successfully" << std::endl;
    
    // Тест 2: Початкова кількість плагінів
    // Test 2: Initial plugin count
    // Тест 2: Начальное количество плагинов
    std::cout << "Test 2: Checking initial plugin count..." << std::endl;
    assert(pluginSystem.getPluginCount() == 0);
    std::cout << "PASS: Initial plugin count is 0" << std::endl;
    
    // Тест 3: Список завантажених плагінів
    // Test 3: List of loaded plugins
    // Тест 3: Список загруженных плагинов
    std::cout << "Test 3: Getting list of loaded plugins..." << std::endl;
    auto loadedPlugins = pluginSystem.getLoadedPlugins();
    assert(loadedPlugins.empty());
    std::cout << "PASS: Loaded plugins list is empty" << std::endl;
    
    // Тест 4: Перевірка неіснуючого плагіна
    // Test 4: Checking non-existent plugin
    // Тест 4: Проверка несуществующего плагина
    std::cout << "Test 4: Checking non-existent plugin..." << std::endl;
    assert(!pluginSystem.isPluginLoaded("NonExistentPlugin"));
    assert(pluginSystem.getPluginInstance("NonExistentPlugin") == nullptr);
    std::cout << "PASS: Non-existent plugin correctly identified" << std::endl;
    
    // Тест 5: Спроба завантаження неіснуючого плагіна
    // Test 5: Attempting to load non-existent plugin
    // Тест 5: Попытка загрузки несуществующего плагина
    std::cout << "Test 5: Attempting to load non-existent plugin..." << std::endl;
    assert(!pluginSystem.loadPlugin("non_existent_plugin.dll"));
    std::cout << "PASS: Non-existent plugin correctly rejected" << std::endl;
    
    // Тест 6: Спроба вивантаження неіснуючого плагіна
    // Test 6: Attempting to unload non-existent plugin
    // Тест 6: Попытка выгрузки несуществующего плагина
    std::cout << "Test 6: Attempting to unload non-existent plugin..." << std::endl;
    assert(!pluginSystem.unloadPlugin("NonExistentPlugin"));
    std::cout << "PASS: Non-existent plugin correctly rejected for unloading" << std::endl;
    
    // Тест 7: Завантаження всіх плагінів з неіснуючої директорії
    // Test 7: Loading all plugins from non-existent directory
    // Тест 7: Загрузка всех плагинов из несуществующей директории
    std::cout << "Test 7: Loading all plugins from non-existent directory..." << std::endl;
    assert(pluginSystem.loadPluginsFromDirectory("non_existent_directory"));
    std::cout << "PASS: Non-existent directory correctly handled" << std::endl;
    
    // Тест 8: Вивантаження всіх плагінів (коли немає плагінів)
    // Test 8: Unloading all plugins (when no plugins)
    // Тест 8: Выгрузка всех плагинов (когда нет плагинов)
    std::cout << "Test 8: Unloading all plugins (when no plugins)..." << std::endl;
    pluginSystem.unloadAllPlugins();
    assert(pluginSystem.getPluginCount() == 0);
    std::cout << "PASS: Unloading all plugins when none loaded works correctly" << std::endl;
    
    // Тест 9: Отримання інформації про неіснуючий плагін
    // Test 9: Getting information about non-existent plugin
    // Тест 9: Получение информации о несуществующем плагине
    std::cout << "Test 9: Getting information about non-existent plugin..." << std::endl;
    PluginInfo pluginInfo = pluginSystem.getPluginInfo("NonExistentPlugin");
    assert(!pluginInfo.loaded);
    std::cout << "PASS: Information about non-existent plugin correctly returned" << std::endl;
    
    std::cout << "\nAll Plugin System tests passed!" << std::endl;
    return 0;
}