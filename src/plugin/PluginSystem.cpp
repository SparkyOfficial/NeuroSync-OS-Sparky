#include "PluginSystem.h"
#include <iostream>
#include <algorithm>

namespace NeuroSync {
namespace Plugin {

    PluginSystem::PluginSystem() {
        // Конструктор системи плагінів
        // Plugin system constructor
        // Конструктор системы плагинов
    }

    PluginSystem::~PluginSystem() {
        // Деструктор системи плагінів
        // Plugin system destructor
        // Деструктор системы плагинов
        unloadAllPlugins();
    }

    bool PluginSystem::initialize() {
        // Ініціалізація системи плагінів
        // Initialize plugin system
        // Инициализация системы плагинов
        return true;
    }

    bool PluginSystem::loadPlugin(const std::string& pluginPath) {
        // Завантаження плагіна з файлу
        // Load plugin from file
        // Загрузка плагина из файла
        
        std::lock_guard<std::mutex> lock(pluginsMutex);
        
        // Отримуємо ім'я файлу без шляху
        // Get filename without path
        // Получаем имя файла без пути
        std::string pluginName = getFileNameFromPath(pluginPath);
        
        // Видаляємо розширення файлу
        // Remove file extension
        // Удаляем расширение файла
        size_t lastDot = pluginName.find_last_of('.');
        if (lastDot != std::string::npos) {
            pluginName = pluginName.substr(0, lastDot);
        }
        
        // Перевіряємо чи плагін вже завантажений
        // Check if plugin is already loaded
        // Проверяем загружен ли плагин уже
        if (plugins.find(pluginName) != plugins.end()) {
            std::cerr << "Plugin " << pluginName << " is already loaded" << std::endl;
            return false;
        }
        
        // Створюємо інформацію про плагін
        // Create plugin information
        // Создаем информацию о плагине
        PluginInfo pluginInfo;
        pluginInfo.name = pluginName;
        pluginInfo.filePath = pluginPath;
        
        // Завантажуємо бібліотеку плагіна
        // Load plugin library
        // Загружаем библиотеку плагина
        if (!loadPluginLibrary(pluginPath, pluginInfo)) {
            std::cerr << "Failed to load plugin library: " << pluginPath << std::endl;
            return false;
        }
        
        // Створюємо екземпляр плагіна
        // Create plugin instance
        // Создаем экземпляр плагина
        if (pluginInfo.createFunc) {
            pluginInfo.instance = pluginInfo.createFunc();
            if (pluginInfo.instance) {
                // Ініціалізуємо плагін
                // Initialize plugin
                // Инициализируем плагин
                if (!pluginInfo.instance->initialize()) {
                    std::cerr << "Failed to initialize plugin: " << pluginName << std::endl;
                    unloadPluginLibrary(pluginInfo);
                    return false;
                }
                
                // Отримуємо інформацію про плагін
                // Get plugin information
                // Получаем информацию о плагине
                pluginInfo.name = pluginInfo.instance->getName();
                pluginInfo.version = pluginInfo.instance->getVersion();
                pluginInfo.description = pluginInfo.instance->getDescription();
                pluginInfo.loaded = true;
                
                // Додаємо плагін до карти
                // Add plugin to map
                // Добавляем плагин в карту
                plugins[pluginInfo.name] = pluginInfo;
                
                std::cout << "Plugin loaded successfully: " << pluginInfo.name 
                          << " (v" << pluginInfo.version << ")" << std::endl;
                return true;
            }
        }
        
        std::cerr << "Failed to create plugin instance: " << pluginName << std::endl;
        unloadPluginLibrary(pluginInfo);
        return false;
    }

    bool PluginSystem::unloadPlugin(const std::string& pluginName) {
        // Вивантаження плагіна
        // Unload plugin
        // Выгрузка плагина
        
        std::lock_guard<std::mutex> lock(pluginsMutex);
        
        auto it = plugins.find(pluginName);
        if (it == plugins.end()) {
            std::cerr << "Plugin not found: " << pluginName << std::endl;
            return false;
        }
        
        PluginInfo& pluginInfo = it->second;
        
        // Деініціалізуємо плагін
        // Deinitialize plugin
        // Деинициализируем плагин
        if (pluginInfo.instance) {
            pluginInfo.instance->deinitialize();
            
            // Знищуємо екземпляр плагіна
            // Destroy plugin instance
            // Уничтожаем экземпляр плагина
            if (pluginInfo.destroyFunc) {
                pluginInfo.destroyFunc(pluginInfo.instance);
            }
        }
        
        // Вивантажуємо бібліотеку плагіна
        // Unload plugin library
        // Выгружаем библиотеку плагина
        unloadPluginLibrary(pluginInfo);
        
        // Видаляємо плагін з карти
        // Remove plugin from map
        // Удаляем плагин из карты
        plugins.erase(it);
        
        std::cout << "Plugin unloaded successfully: " << pluginName << std::endl;
        return true;
    }

    std::vector<std::string> PluginSystem::getLoadedPlugins() const {
        // Отримання списку завантажених плагінів
        // Get list of loaded plugins
        // Получение списка загруженных плагинов
        
        std::lock_guard<std::mutex> lock(pluginsMutex);
        
        std::vector<std::string> pluginNames;
        pluginNames.reserve(plugins.size());
        
        for (const auto& pair : plugins) {
            pluginNames.push_back(pair.first);
        }
        
        return pluginNames;
    }

    PluginInfo PluginSystem::getPluginInfo(const std::string& pluginName) const {
        // Отримання інформації про плагін
        // Get plugin information
        // Получение информации о плагине
        
        std::lock_guard<std::mutex> lock(pluginsMutex);
        
        auto it = plugins.find(pluginName);
        if (it != plugins.end()) {
            return it->second;
        }
        
        return PluginInfo();
    }

    bool PluginSystem::isPluginLoaded(const std::string& pluginName) const {
        // Перевірка чи завантажений плагін
        // Check if plugin is loaded
        // Проверка загружен ли плагин
        
        std::lock_guard<std::mutex> lock(pluginsMutex);
        return plugins.find(pluginName) != plugins.end();
    }

    PluginInterface* PluginSystem::getPluginInstance(const std::string& pluginName) const {
        // Отримання екземпляра плагіна
        // Get plugin instance
        // Получение экземпляра плагина
        
        std::lock_guard<std::mutex> lock(pluginsMutex);
        
        auto it = plugins.find(pluginName);
        if (it != plugins.end()) {
            return it->second.instance;
        }
        
        return nullptr;
    }

    bool PluginSystem::loadPluginsFromDirectory(const std::string& directoryPath) {
        // Завантаження всіх плагінів з директорії
        // Load all plugins from directory
        // Загрузка всех плагинов из директории
        
        // For now, we'll just return true and print a message
        // In a full implementation, we would iterate through files in the directory
        std::cout << "Loading plugins from directory is not implemented in this simplified version" << std::endl;
        return true;
    }

    void PluginSystem::unloadAllPlugins() {
        // Вивантаження всіх плагінів
        // Unload all plugins
        // Выгрузка всех плагинов
        
        std::lock_guard<std::mutex> lock(pluginsMutex);
        
        // Створюємо копію списку плагінів для вивантаження
        // Create copy of plugin list for unloading
        // Создаем копию списка плагинов для выгрузки
        std::vector<std::string> pluginNames;
        pluginNames.reserve(plugins.size());
        
        for (const auto& pair : plugins) {
            pluginNames.push_back(pair.first);
        }
        
        // Вивантажуємо всі плагіни
        // Unload all plugins
        // Выгружаем все плагины
        for (const auto& pluginName : pluginNames) {
            unloadPlugin(pluginName);
        }
    }

    size_t PluginSystem::getPluginCount() const {
        // Отримання кількості завантажених плагінів
        // Get loaded plugin count
        // Получение количества загруженных плагинов
        
        std::lock_guard<std::mutex> lock(pluginsMutex);
        return plugins.size();
    }

    bool PluginSystem::loadPluginLibrary(const std::string& pluginPath, PluginInfo& pluginInfo) {
        // Завантаження бібліотеки плагіна
        // Load plugin library
        // Загрузка библиотеки плагина
        
#ifdef _WIN32
        // Завантажуємо DLL на Windows
        // Load DLL on Windows
        // Загружаем DLL на Windows
        pluginInfo.handle = LoadLibraryA(pluginPath.c_str());
        if (!pluginInfo.handle) {
            std::cerr << "Failed to load DLL: " << pluginPath << " (Error: " << GetLastError() << ")" << std::endl;
            return false;
        }
        
        // Отримуємо функції створення та знищення
        // Get create and destroy functions
        // Получаем функции создания и уничтожения
        pluginInfo.createFunc = reinterpret_cast<CreatePluginFunc>(GetProcAddress(pluginInfo.handle, "createPlugin"));
        pluginInfo.destroyFunc = reinterpret_cast<DestroyPluginFunc>(GetProcAddress(pluginInfo.handle, "destroyPlugin"));
#else
        // Завантажуємо shared library на Unix-подібних системах
        // Load shared library on Unix-like systems
        // Загружаем shared library на Unix-подобных системах
        pluginInfo.handle = dlopen(pluginPath.c_str(), RTLD_LAZY);
        if (!pluginInfo.handle) {
            std::cerr << "Failed to load shared library: " << pluginPath << " (" << dlerror() << ")" << std::endl;
            return false;
        }
        
        // Отримуємо функції створення та знищення
        // Get create and destroy functions
        // Получаем функции создания и уничтожения
        pluginInfo.createFunc = reinterpret_cast<CreatePluginFunc>(dlsym(pluginInfo.handle, "createPlugin"));
        pluginInfo.destroyFunc = reinterpret_cast<DestroyPluginFunc>(dlsym(pluginInfo.handle, "destroyPlugin"));
        
        // Перевіряємо на помилки
        // Check for errors
        // Проверяем на ошибки
        const char* dlsymError = dlerror();
        if (dlsymError) {
            std::cerr << "Failed to load symbols: " << dlsymError << std::endl;
            dlclose(pluginInfo.handle);
            pluginInfo.handle = nullptr;
            return false;
        }
#endif
        
        return true;
    }

    void PluginSystem::unloadPluginLibrary(PluginInfo& pluginInfo) {
        // Вивантаження бібліотеки плагіна
        // Unload plugin library
        // Выгрузка библиотеки плагина
        
        if (pluginInfo.handle) {
#ifdef _WIN32
            FreeLibrary(pluginInfo.handle);
#else
            dlclose(pluginInfo.handle);
#endif
            pluginInfo.handle = nullptr;
        }
        
        pluginInfo.createFunc = nullptr;
        pluginInfo.destroyFunc = nullptr;
        pluginInfo.instance = nullptr;
        pluginInfo.loaded = false;
    }

    std::string PluginSystem::getFileNameFromPath(const std::string& path) const {
        // Отримання імені файлу з шляху
        // Get filename from path
        // Получение имени файла из пути
        
        // Simple implementation to extract filename from path
        size_t lastSlash = path.find_last_of("/\\");
        if (lastSlash != std::string::npos) {
            return path.substr(lastSlash + 1);
        }
        return path;
    }

} // namespace Plugin
} // namespace NeuroSync