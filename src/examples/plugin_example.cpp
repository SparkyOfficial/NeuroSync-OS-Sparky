// plugin_example.cpp
// Приклад використання системи плагінів / Plugin system usage example / Пример использования системы плагинов
// NeuroSync OS Sparky

#include "../plugin/PluginSystem.h"
#include <iostream>
#include <thread>
#include <chrono>

using namespace NeuroSync::Plugin;

int main() {
    std::cout << "NeuroSync OS Sparky - Plugin System Example" << std::endl;
    std::cout << "===========================================" << std::endl;
    
    // Створення системи плагінів
    // Create plugin system
    // Создание системы плагинов
    PluginSystem pluginSystem;
    
    // Ініціалізація системи плагінів
    // Initialize plugin system
    // Инициализация системы плагинов
    if (!pluginSystem.initialize()) {
        std::cerr << "Failed to initialize plugin system" << std::endl;
        return 1;
    }
    
    std::cout << "Plugin system initialized successfully" << std::endl;
    
    // Отримання кількості завантажених плагінів
    // Get loaded plugin count
    // Получение количества загруженных плагинов
    std::cout << "Loaded plugins: " << pluginSystem.getPluginCount() << std::endl;
    
    // Спроба завантажити приклад плагіна (якщо він був зібраний)
    // Try to load example plugin (if it was built)
    // Попытка загрузить пример плагина (если он был собран)
#ifdef _WIN32
    std::string pluginPath = "../plugins/example_plugin.dll";
#else
    std::string pluginPath = "../plugins/libexample_plugin.so";
#endif
    
    std::cout << "\nAttempting to load plugin from: " << pluginPath << std::endl;
    
    if (pluginSystem.loadPlugin(pluginPath)) {
        std::cout << "Plugin loaded successfully!" << std::endl;
        
        // Отримання списку завантажених плагінів
        // Get list of loaded plugins
        // Получение списка загруженных плагинов
        auto loadedPlugins = pluginSystem.getLoadedPlugins();
        std::cout << "\nLoaded plugins (" << loadedPlugins.size() << "):" << std::endl;
        for (const auto& pluginName : loadedPlugins) {
            std::cout << "  - " << pluginName << std::endl;
        }
        
        // Отримання інформації про плагін
        // Get plugin information
        // Получение информации о плагине
        PluginInfo pluginInfo = pluginSystem.getPluginInfo("ExamplePlugin");
        if (pluginInfo.loaded) {
            std::cout << "\nPlugin Information:" << std::endl;
            std::cout << "  Name: " << pluginInfo.name << std::endl;
            std::cout << "  Version: " << pluginInfo.version << std::endl;
            std::cout << "  Description: " << pluginInfo.description << std::endl;
            std::cout << "  File Path: " << pluginInfo.filePath << std::endl;
        }
        
        // Отримання екземпляра плагіна та виклик функціональності
        // Get plugin instance and call functionality
        // Получение экземпляра плагина и вызов функциональности
        PluginInterface* pluginInstance = pluginSystem.getPluginInstance("ExamplePlugin");
        if (pluginInstance) {
            std::cout << "\nCalling plugin functionality through interface..." << std::endl;
            // We can only call methods defined in PluginInterface
            std::cout << "Plugin name: " << pluginInstance->getName() << std::endl;
            std::cout << "Plugin version: " << pluginInstance->getVersion() << std::endl;
            std::cout << "Plugin description: " << pluginInstance->getDescription() << std::endl;
            
            // Initialize the plugin
            if (pluginInstance->initialize()) {
                std::cout << "Plugin initialized successfully!" << std::endl;
            } else {
                std::cout << "Plugin initialization failed!" << std::endl;
            }
        }
        
        // Зачекати трохи
        // Wait a bit
        // Подождать немного
        std::this_thread::sleep_for(std::chrono::seconds(1));
        
        // Вивантаження плагіна
        // Unload plugin
        // Выгрузка плагина
        std::cout << "\nUnloading plugin..." << std::endl;
        if (pluginSystem.unloadPlugin("ExamplePlugin")) {
            std::cout << "Plugin unloaded successfully!" << std::endl;
        } else {
            std::cerr << "Failed to unload plugin!" << std::endl;
        }
    } else {
        std::cout << "Plugin not found or failed to load. This is expected if the plugin hasn't been built yet." << std::endl;
        std::cout << "To build the example plugin, copy CMakeLists.example to CMakeLists.txt in the plugins directory and build it separately." << std::endl;
    }
    
    // Отримання кількості завантажених плагінів після вивантаження
    // Get loaded plugin count after unloading
    // Получение количества загруженных плагинов после выгрузки
    std::cout << "\nLoaded plugins after unloading: " << pluginSystem.getPluginCount() << std::endl;
    
    std::cout << "\nPlugin system example completed successfully!" << std::endl;
    
    return 0;
}