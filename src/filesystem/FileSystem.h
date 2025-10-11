#ifndef FILE_SYSTEM_H
#define FILE_SYSTEM_H

#include <string>
#include <vector>
#include <memory>
#include <map>
#include <chrono>

// FileSystem.h
// Файлова система для NeuroSync OS Sparky
// File system for NeuroSync OS Sparky
// Файловая система для NeuroSync OS Sparky

namespace NeuroSync {

    // Типи файлів
    // File types
    // Типы файлов
    enum class FileType {
        NEURON_DATA,        // Дані нейрона
        // Neuron data
        // Данные нейрона
        
        SYNAPSE_DATA,       // Дані синапса
        // Synapse data
        // Данные синапса
        
        CONFIG_DATA,        // Дані конфігурації
        // Configuration data
        // Данные конфигурации
        
        LOG_DATA,           // Дані логування
        // Log data
        // Данные логирования
        
        PLUGIN_DATA,        // Дані плагіна
        // Plugin data
        // Данные плагина
        
        CUSTOM_DATA         // Користувацькі дані
        // Custom data
        // Пользовательские данные
    };

    // Метадані файлу
    // File metadata
    // Метаданные файла
    struct FileMetadata {
        std::string name;
        FileType type;
        size_t size;
        std::chrono::system_clock::time_point created;
        std::chrono::system_clock::time_point modified;
        std::map<std::string, std::string> attributes;
        
        FileMetadata() : type(FileType::CUSTOM_DATA), size(0) {}
    };

    // Інтерфейс файлової системи
    // File system interface
    // Интерфейс файловой системы
    class FileSystem {
    public:
        // Конструктор
        // Constructor
        // Конструктор
        FileSystem();
        
        // Деструктор
        // Destructor
        // Деструктор
        virtual ~FileSystem();
        
        // Ініціалізація файлової системи
        // Initialize file system
        // Инициализация файловой системы
        virtual bool initialize(const std::string& basePath);
        
        // Отримання базового шляху
        // Get base path
        // Получение базового пути
        std::string getBasePath() const;
        
        // Створення директорії
        // Create directory
        // Создание директории
        virtual bool createDirectory(const std::string& path);
        
        // Видалення директорії
        // Remove directory
        // Удаление директории
        virtual bool removeDirectory(const std::string& path);
        
        // Перевірка існування директорії
        // Check if directory exists
        // Проверка существования директории
        virtual bool directoryExists(const std::string& path) const;
        
        // Створення файлу
        // Create file
        // Создание файла
        virtual bool createFile(const std::string& path, FileType type = FileType::CUSTOM_DATA);
        
        // Видалення файлу
        // Remove file
        // Удаление файла
        virtual bool removeFile(const std::string& path);
        
        // Перевірка існування файлу
        // Check if file exists
        // Проверка существования файла
        virtual bool fileExists(const std::string& path) const;
        
        // Зчитування даних з файлу
        // Read data from file
        // Чтение данных из файла
        virtual bool readFile(const std::string& path, std::vector<uint8_t>& data) const;
        
        // Запис даних у файл
        // Write data to file
        // Запись данных в файл
        virtual bool writeFile(const std::string& path, const std::vector<uint8_t>& data);
        
        // Отримання метаданих файлу
        // Get file metadata
        // Получение метаданных файла
        virtual bool getFileMetadata(const std::string& path, FileMetadata& metadata) const;
        
        // Оновлення метаданих файлу
        // Update file metadata
        // Обновление метаданных файла
        virtual bool updateFileMetadata(const std::string& path, const FileMetadata& metadata);
        
        // Перейменування файлу
        // Rename file
        // Переименование файла
        virtual bool renameFile(const std::string& oldPath, const std::string& newPath);
        
        // Копіювання файлу
        // Copy file
        // Копирование файла
        virtual bool copyFile(const std::string& sourcePath, const std::string& destPath);
        
        // Отримання списку файлів у директорії
        // Get list of files in directory
        // Получение списка файлов в директории
        virtual std::vector<std::string> listFiles(const std::string& path) const;
        
        // Отримання списку директорій
        // Get list of directories
        // Получение списка директорий
        virtual std::vector<std::string> listDirectories(const std::string& path) const;
        
        // Отримання розміру файлу
        // Get file size
        // Получение размера файла
        virtual size_t getFileSize(const std::string& path) const;
        
        // Очищення файлової системи
        // Clear file system
        // Очистка файловой системы
        virtual void clear();
        
        // Перевірка цілісності файлової системи
        // Check file system integrity
        // Проверка целостности файловой системы
        virtual bool checkIntegrity() const;
        
    protected:
        std::string basePath;
        std::map<std::string, FileMetadata> fileMetadataMap;
        
        // Внутрішні методи
        // Internal methods
        // Внутренние методы
        std::string getFullPath(const std::string& path) const;
        bool validatePath(const std::string& path) const;
        FileType detectFileType(const std::string& path) const;
    };

    // Глобальна файлова система
    // Global file system
    // Глобальная файловая система
    extern std::unique_ptr<FileSystem> gFileSystem;

} // namespace NeuroSync

#endif // FILE_SYSTEM_H