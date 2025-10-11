#ifndef EXAMPLE_PLUGIN_H
#define EXAMPLE_PLUGIN_H

#include "PluginSystem.h"
#include <string>

// ExamplePlugin.h
// Приклад плагіна для NeuroSync OS Sparky
// Example plugin for NeuroSync OS Sparky
// Пример плагина для NeuroSync OS Sparky

#ifdef _WIN32
    #ifdef EXAMPLE_PLUGIN_EXPORTS
        #define EXAMPLE_PLUGIN_API __declspec(dllexport)
    #else
        #define EXAMPLE_PLUGIN_API __declspec(dllimport)
    #endif
#else
    #define EXAMPLE_PLUGIN_API
#endif

namespace NeuroSync {
namespace Plugin {

    // Приклад реалізації плагіна
    // Example plugin implementation
    // Пример реализации плагина
    class EXAMPLE_PLUGIN_API ExamplePlugin : public PluginInterface {
    public:
        ExamplePlugin();
        virtual ~ExamplePlugin();
        
        // Ініціалізація плагіна
        // Initialize plugin
        // Инициализация плагина
        virtual bool initialize() override;
        
        // Деініціалізація плагіна
        // Deinitialize plugin
        // Деинициализация плагина
        virtual void deinitialize() override;
        
        // Отримання імені плагіна
        // Get plugin name
        // Получение имени плагина
        virtual std::string getName() const override;
        
        // Отримання версії плагіна
        // Get plugin version
        // Получение версии плагина
        virtual std::string getVersion() const override;
        
        // Отримання опису плагіна
        // Get plugin description
        // Получение описания плагина
        virtual std::string getDescription() const override;
        
        // Приклад функціональності плагіна
        // Example plugin functionality
        // Пример функциональности плагина
        void doSomething();
        
    private:
        bool initialized;
    };

    // Функції для створення та знищення плагіна
    // Functions for creating and destroying plugin
    // Функции для создания и уничтожения плагина
    extern "C" {
        EXAMPLE_PLUGIN_API PluginInterface* createPlugin();
        EXAMPLE_PLUGIN_API void destroyPlugin(PluginInterface* plugin);
    }

} // namespace Plugin
} // namespace NeuroSync

#endif // EXAMPLE_PLUGIN_H