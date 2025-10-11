#ifndef PLUGIN_SYSTEM_H
#define PLUGIN_SYSTEM_H

#include <string>
#include <vector>
#include <map>
#include <memory>
#include <mutex>
#include <functional>

#ifdef _WIN32
#include <windows.h>
#define PLUGIN_HANDLE HMODULE
#else
#include <dlfcn.h>
#define PLUGIN_HANDLE void*
#endif

// PluginSystem.h
// Система плагінів для NeuroSync OS Sparky
// Plugin system for NeuroSync OS Sparky
// Система плагинов для NeuroSync OS Sparky

namespace NeuroSync {
namespace Plugin {

    // Базовий інтерфейс для плагінів
    // Base interface for plugins
    // Базовый интерфейс для плагинов
    class PluginInterface {
    public:
        virtual ~PluginInterface() = default;
        
        // Ініціалізація плагіна
        // Initialize plugin
        // Инициализация плагина
        virtual bool initialize() = 0;
        
        // Деініціалізація плагіна
        // Deinitialize plugin
        // Деинициализация плагина
        virtual void deinitialize() = 0;
        
        // Отримання імені плагіна
        // Get plugin name
        // Получение имени плагина
        virtual std::string getName() const = 0;
        
        // Отримання версії плагіна
        // Get plugin version
        // Получение версии плагина
        virtual std::string getVersion() const = 0;
        
        // Отримання опису плагіна
        // Get plugin description
        // Получение описания плагина
        virtual std::string getDescription() const = 0;
    };

    // Тип функції для створення плагіна
    // Plugin creation function type
    // Тип функции для создания плагина
    typedef PluginInterface* (*CreatePluginFunc)();
    
    // Тип функції для знищення плагіна
    // Plugin destruction function type
    // Тип функции для уничтожения плагина
    typedef void (*DestroyPluginFunc)(PluginInterface*);

    // Інформація про плагін
    // Plugin information
    // Информация о плагине
    struct PluginInfo {
        std::string name;
        std::string version;
        std::string description;
        std::string filePath;
        PLUGIN_HANDLE handle;
        PluginInterface* instance;
        CreatePluginFunc createFunc;
        DestroyPluginFunc destroyFunc;
        bool loaded;
        
        PluginInfo() : handle(nullptr), instance(nullptr), createFunc(nullptr), 
                      destroyFunc(nullptr), loaded(false) {}
    };

    // Система плагінів
    // Plugin system
    // Система плагинов
    class PluginSystem {
    public:
        PluginSystem();
        ~PluginSystem();
        
        // Ініціалізація системи плагінів
        // Initialize plugin system
        // Инициализация системы плагинов
        bool initialize();
        
        // Завантаження плагіна з файлу
        // Load plugin from file
        // Загрузка плагина из файла
        bool loadPlugin(const std::string& pluginPath);
        
        // Вивантаження плагіна
        // Unload plugin
        // Выгрузка плагина
        bool unloadPlugin(const std::string& pluginName);
        
        // Отримання списку завантажених плагінів
        // Get list of loaded plugins
        // Получение списка загруженных плагинов
        std::vector<std::string> getLoadedPlugins() const;
        
        // Отримання інформації про плагін
        // Get plugin information
        // Получение информации о плагине
        PluginInfo getPluginInfo(const std::string& pluginName) const;
        
        // Перевірка чи завантажений плагін
        // Check if plugin is loaded
        // Проверка загружен ли плагин
        bool isPluginLoaded(const std::string& pluginName) const;
        
        // Отримання екземпляра плагіна
        // Get plugin instance
        // Получение экземпляра плагина
        PluginInterface* getPluginInstance(const std::string& pluginName) const;
        
        // Завантаження всіх плагінів з директорії
        // Load all plugins from directory
        // Загрузка всех плагинов из директории
        bool loadPluginsFromDirectory(const std::string& directoryPath);
        
        // Вивантаження всіх плагінів
        // Unload all plugins
        // Выгрузка всех плагинов
        void unloadAllPlugins();
        
        // Отримання кількості завантажених плагінів
        // Get loaded plugin count
        // Получение количества загруженных плагинов
        size_t getPluginCount() const;
        
    private:
        // Карта завантажених плагінів
        // Map of loaded plugins
        // Карта загруженных плагинов
        std::map<std::string, PluginInfo> plugins;
        
        // Мьютекс для потокобезпеки
        // Mutex for thread safety
        // Мьютекс для потокобезопасности
        mutable std::mutex pluginsMutex;
        
        // Внутрішні методи
        // Internal methods
        // Внутренние методы
        bool loadPluginLibrary(const std::string& pluginPath, PluginInfo& pluginInfo);
        void unloadPluginLibrary(PluginInfo& pluginInfo);
        std::string getFileNameFromPath(const std::string& path) const;
    };

} // namespace Plugin
} // namespace NeuroSync

#endif // PLUGIN_SYSTEM_H