#include "FileSystem.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <filesystem>
#include <cstring>

// FileSystem.cpp
// Реалізація файлової системи для NeuroSync OS Sparky
// File system implementation for NeuroSync OS Sparky
// Реализация файловой системы для NeuroSync OS Sparky

namespace NeuroSync {

    // Конструктор
    // Constructor
    // Конструктор
    FileSystem::FileSystem() : basePath(".") {
    }

    // Деструктор
    // Destructor
    // Деструктор
    FileSystem::~FileSystem() {
        clear();
    }

    // Ініціалізація файлової системи
    // Initialize file system
    // Инициализация файловой системы
    bool FileSystem::initialize(const std::string& basePath) {
        this->basePath = basePath;
        
        // Створення базової директорії, якщо вона не існує
        // Create base directory if it doesn't exist
        // Создание базовой директории, если она не существует
        if (!std::filesystem::exists(this->basePath)) {
            try {
                std::filesystem::create_directories(this->basePath);
            } catch (const std::exception& e) {
                std::cerr << "Failed to create base directory: " << e.what() << std::endl;
                return false;
            }
        }
        
        // Створення стандартних директорій
        // Create standard directories
        // Создание стандартных директорий
        std::vector<std::string> standardDirs = {
            "neurons", "synapses", "config", "logs", "plugins", "data"
        };
        
        for (const auto& dir : standardDirs) {
            std::string fullPath = this->basePath + "/" + dir;
            if (!std::filesystem::exists(fullPath)) {
                try {
                    std::filesystem::create_directory(fullPath);
                } catch (const std::exception& e) {
                    std::cerr << "Failed to create directory " << dir << ": " << e.what() << std::endl;
                }
            }
        }
        
        return true;
    }

    // Отримання базового шляху
    // Get base path
    // Получение базового пути
    std::string FileSystem::getBasePath() const {
        return basePath;
    }

    // Створення директорії
    // Create directory
    // Создание директории
    bool FileSystem::createDirectory(const std::string& path) {
        if (!validatePath(path)) {
            return false;
        }
        
        std::string fullPath = getFullPath(path);
        try {
            return std::filesystem::create_directories(fullPath);
        } catch (const std::exception& e) {
            std::cerr << "Failed to create directory " << path << ": " << e.what() << std::endl;
            return false;
        }
    }

    // Видалення директорії
    // Remove directory
    // Удаление директории
    bool FileSystem::removeDirectory(const std::string& path) {
        if (!validatePath(path)) {
            return false;
        }
        
        std::string fullPath = getFullPath(path);
        try {
            return std::filesystem::remove_all(fullPath) > 0;
        } catch (const std::exception& e) {
            std::cerr << "Failed to remove directory " << path << ": " << e.what() << std::endl;
            return false;
        }
    }

    // Перевірка існування директорії
    // Check if directory exists
    // Проверка существования директории
    bool FileSystem::directoryExists(const std::string& path) const {
        if (!validatePath(path)) {
            return false;
        }
        
        std::string fullPath = getFullPath(path);
        return std::filesystem::is_directory(fullPath);
    }

    // Створення файлу
    // Create file
    // Создание файла
    bool FileSystem::createFile(const std::string& path, FileType type) {
        if (!validatePath(path)) {
            return false;
        }
        
        std::string fullPath = getFullPath(path);
        
        // Створення директорій, якщо вони не існують
        // Create directories if they don't exist
        // Создание директорий, если они не существуют
        try {
            std::filesystem::create_directories(std::filesystem::path(fullPath).parent_path());
        } catch (const std::exception& e) {
            std::cerr << "Failed to create parent directories for " << path << ": " << e.what() << std::endl;
            return false;
        }
        
        // Створення файлу
        // Create file
        // Создание файла
        std::ofstream file(fullPath, std::ios::out | std::ios::binary);
        if (!file.is_open()) {
            std::cerr << "Failed to create file " << path << std::endl;
            return false;
        }
        
        file.close();
        
        // Оновлення метаданих
        // Update metadata
        // Обновление метаданных
        FileMetadata metadata;
        metadata.name = path;
        metadata.type = type;
        metadata.size = 0;
        metadata.created = std::chrono::system_clock::now();
        metadata.modified = metadata.created;
        
        fileMetadataMap[path] = metadata;
        
        return true;
    }

    // Видалення файлу
    // Remove file
    // Удаление файла
    bool FileSystem::removeFile(const std::string& path) {
        if (!validatePath(path)) {
            return false;
        }
        
        std::string fullPath = getFullPath(path);
        try {
            bool result = std::filesystem::remove(fullPath);
            if (result) {
                // Видалення метаданих
                // Remove metadata
                // Удаление метаданных
                fileMetadataMap.erase(path);
            }
            return result;
        } catch (const std::exception& e) {
            std::cerr << "Failed to remove file " << path << ": " << e.what() << std::endl;
            return false;
        }
    }

    // Перевірка існування файлу
    // Check if file exists
    // Проверка существования файла
    bool FileSystem::fileExists(const std::string& path) const {
        if (!validatePath(path)) {
            return false;
        }
        
        std::string fullPath = getFullPath(path);
        return std::filesystem::exists(fullPath) && std::filesystem::is_regular_file(fullPath);
    }

    // Зчитування даних з файлу
    // Read data from file
    // Чтение данных из файла
    bool FileSystem::readFile(const std::string& path, std::vector<uint8_t>& data) const {
        if (!validatePath(path)) {
            return false;
        }
        
        std::string fullPath = getFullPath(path);
        std::ifstream file(fullPath, std::ios::in | std::ios::binary | std::ios::ate);
        
        if (!file.is_open()) {
            std::cerr << "Failed to open file for reading: " << path << std::endl;
            return false;
        }
        
        // Отримання розміру файлу
        // Get file size
        // Получение размера файла
        std::streamsize size = file.tellg();
        file.seekg(0, std::ios::beg);
        
        // Зчитування даних
        // Reading data
        // Чтение данных
        data.resize(size);
        if (!file.read(reinterpret_cast<char*>(data.data()), size)) {
            std::cerr << "Failed to read file: " << path << std::endl;
            return false;
        }
        
        file.close();
        return true;
    }

    // Запис даних у файл
    // Write data to file
    // Запись данных в файл
    bool FileSystem::writeFile(const std::string& path, const std::vector<uint8_t>& data) {
        if (!validatePath(path)) {
            return false;
        }
        
        std::string fullPath = getFullPath(path);
        
        // Створення директорій, якщо вони не існують
        // Create directories if they don't exist
        // Создание директорий, если они не существуют
        try {
            std::filesystem::create_directories(std::filesystem::path(fullPath).parent_path());
        } catch (const std::exception& e) {
            std::cerr << "Failed to create parent directories for " << path << ": " << e.what() << std::endl;
            return false;
        }
        
        std::ofstream file(fullPath, std::ios::out | std::ios::binary);
        if (!file.is_open()) {
            std::cerr << "Failed to open file for writing: " << path << std::endl;
            return false;
        }
        
        // Запис даних
        // Writing data
        // Запись данных
        if (!file.write(reinterpret_cast<const char*>(data.data()), data.size())) {
            std::cerr << "Failed to write to file: " << path << std::endl;
            return false;
        }
        
        file.close();
        
        // Оновлення метаданих
        // Update metadata
        // Обновление метаданных
        auto it = fileMetadataMap.find(path);
        if (it != fileMetadataMap.end()) {
            it->second.size = data.size();
            it->second.modified = std::chrono::system_clock::now();
        } else {
            FileMetadata metadata;
            metadata.name = path;
            metadata.type = detectFileType(path);
            metadata.size = data.size();
            metadata.created = std::chrono::system_clock::now();
            metadata.modified = metadata.created;
            fileMetadataMap[path] = metadata;
        }
        
        return true;
    }

    // Отримання метаданих файлу
    // Get file metadata
    // Получение метаданных файла
    bool FileSystem::getFileMetadata(const std::string& path, FileMetadata& metadata) const {
        if (!validatePath(path)) {
            return false;
        }
        
        auto it = fileMetadataMap.find(path);
        if (it != fileMetadataMap.end()) {
            metadata = it->second;
            return true;
        }
        
        // Якщо метадані не знайдено, створюємо їх з файлової системи
        // If metadata not found, create it from file system
        // Если метаданные не найдены, создаем их из файловой системы
        std::string fullPath = getFullPath(path);
        if (!std::filesystem::exists(fullPath)) {
            return false;
        }
        
        metadata.name = path;
        metadata.type = detectFileType(path);
        metadata.size = std::filesystem::file_size(fullPath);
        
        auto ftime = std::filesystem::last_write_time(fullPath);
        auto sctp = std::chrono::time_point_cast<std::chrono::system_clock::duration>(
            ftime - std::filesystem::file_time_type::clock::now() + std::chrono::system_clock::now());
        metadata.modified = sctp;
        
        // Для created використовуємо modified, оскільки std::filesystem не надає created time на всіх платформах
        // For created use modified, since std::filesystem doesn't provide created time on all platforms
        // Для created используем modified, поскольку std::filesystem не предоставляет created time на всех платформах
        metadata.created = metadata.modified;
        
        return true;
    }

    // Оновлення метаданих файлу
    // Update file metadata
    // Обновление метаданных файла
    bool FileSystem::updateFileMetadata(const std::string& path, const FileMetadata& metadata) {
        if (!validatePath(path)) {
            return false;
        }
        
        fileMetadataMap[path] = metadata;
        return true;
    }

    // Перейменування файлу
    // Rename file
    // Переименование файла
    bool FileSystem::renameFile(const std::string& oldPath, const std::string& newPath) {
        if (!validatePath(oldPath) || !validatePath(newPath)) {
            return false;
        }
        
        std::string fullOldPath = getFullPath(oldPath);
        std::string fullNewPath = getFullPath(newPath);
        
        try {
            std::filesystem::rename(fullOldPath, fullNewPath);
            
            // Оновлення метаданих
            // Update metadata
            // Обновление метаданных
            auto it = fileMetadataMap.find(oldPath);
            if (it != fileMetadataMap.end()) {
                FileMetadata metadata = it->second;
                metadata.name = newPath;
                metadata.modified = std::chrono::system_clock::now();
                fileMetadataMap.erase(it);
                fileMetadataMap[newPath] = metadata;
            }
            
            return true;
        } catch (const std::exception& e) {
            std::cerr << "Failed to rename file from " << oldPath << " to " << newPath << ": " << e.what() << std::endl;
            return false;
        }
    }

    // Копіювання файлу
    // Copy file
    // Копирование файла
    bool FileSystem::copyFile(const std::string& sourcePath, const std::string& destPath) {
        if (!validatePath(sourcePath) || !validatePath(destPath)) {
            return false;
        }
        
        std::string fullSourcePath = getFullPath(sourcePath);
        std::string fullDestPath = getFullPath(destPath);
        
        try {
            // Створення директорій призначення, якщо вони не існують
            // Create destination directories if they don't exist
            // Создание директорий назначения, если они не существуют
            std::filesystem::create_directories(std::filesystem::path(fullDestPath).parent_path());
            
            std::filesystem::copy_file(fullSourcePath, fullDestPath, std::filesystem::copy_options::overwrite_existing);
            
            // Оновлення метаданих
            // Update metadata
            // Обновление метаданных
            auto it = fileMetadataMap.find(sourcePath);
            if (it != fileMetadataMap.end()) {
                FileMetadata metadata = it->second;
                metadata.name = destPath;
                metadata.modified = std::chrono::system_clock::now();
                fileMetadataMap[destPath] = metadata;
            }
            
            return true;
        } catch (const std::exception& e) {
            std::cerr << "Failed to copy file from " << sourcePath << " to " << destPath << ": " << e.what() << std::endl;
            return false;
        }
    }

    // Отримання списку файлів у директорії
    // Get list of files in directory
    // Получение списка файлов в директории
    std::vector<std::string> FileSystem::listFiles(const std::string& path) const {
        std::vector<std::string> files;
        
        if (!validatePath(path)) {
            return files;
        }
        
        std::string fullPath = getFullPath(path);
        try {
            for (const auto& entry : std::filesystem::directory_iterator(fullPath)) {
                if (entry.is_regular_file()) {
                    std::string relativePath = entry.path().lexically_relative(basePath).string();
                    // Заміна зворотних слешів на прямі (для Windows)
                    // Replace backslashes with forward slashes (for Windows)
                    // Замена обратных слешей на прямые (для Windows)
                    std::replace(relativePath.begin(), relativePath.end(), '\\', '/');
                    files.push_back(relativePath);
                }
            }
        } catch (const std::exception& e) {
            std::cerr << "Failed to list files in directory " << path << ": " << e.what() << std::endl;
        }
        
        return files;
    }

    // Отримання списку директорій
    // Get list of directories
    // Получение списка директорий
    std::vector<std::string> FileSystem::listDirectories(const std::string& path) const {
        std::vector<std::string> directories;
        
        if (!validatePath(path)) {
            return directories;
        }
        
        std::string fullPath = getFullPath(path);
        try {
            for (const auto& entry : std::filesystem::directory_iterator(fullPath)) {
                if (entry.is_directory()) {
                    std::string relativePath = entry.path().lexically_relative(basePath).string();
                    // Заміна зворотних слешів на прямі (для Windows)
                    // Replace backslashes with forward slashes (for Windows)
                    // Замена обратных слешей на прямые (для Windows)
                    std::replace(relativePath.begin(), relativePath.end(), '\\', '/');
                    directories.push_back(relativePath);
                }
            }
        } catch (const std::exception& e) {
            std::cerr << "Failed to list directories in " << path << ": " << e.what() << std::endl;
        }
        
        return directories;
    }

    // Отримання розміру файлу
    // Get file size
    // Получение размера файла
    size_t FileSystem::getFileSize(const std::string& path) const {
        if (!validatePath(path)) {
            return 0;
        }
        
        std::string fullPath = getFullPath(path);
        try {
            return std::filesystem::file_size(fullPath);
        } catch (const std::exception& e) {
            std::cerr << "Failed to get file size for " << path << ": " << e.what() << std::endl;
            return 0;
        }
    }

    // Очищення файлової системи
    // Clear file system
    // Очистка файловой системы
    void FileSystem::clear() {
        fileMetadataMap.clear();
    }

    // Перевірка цілісності файлової системи
    // Check file system integrity
    // Проверка целостности файловой системы
    bool FileSystem::checkIntegrity() const {
        // Перевірка базової директорії
        // Check base directory
        // Проверка базовой директории
        if (!std::filesystem::exists(basePath)) {
            std::cerr << "Base directory does not exist: " << basePath << std::endl;
            return false;
        }
        
        if (!std::filesystem::is_directory(basePath)) {
            std::cerr << "Base path is not a directory: " << basePath << std::endl;
            return false;
        }
        
        // Перевірка стандартних директорій
        // Check standard directories
        // Проверка стандартных директорий
        std::vector<std::string> standardDirs = {
            "neurons", "synapses", "config", "logs", "plugins", "data"
        };
        
        for (const auto& dir : standardDirs) {
            std::string fullPath = basePath + "/" + dir;
            if (!std::filesystem::exists(fullPath) || !std::filesystem::is_directory(fullPath)) {
                std::cerr << "Standard directory missing or invalid: " << dir << std::endl;
                return false;
            }
        }
        
        return true;
    }

    // Внутрішні методи
    // Internal methods
    // Внутренние методы
    
    // Отримання повного шляху
    // Get full path
    // Получение полного пути
    std::string FileSystem::getFullPath(const std::string& path) const {
        return basePath + "/" + path;
    }

    // Перевірка валідності шляху
    // Validate path
    // Проверка валидности пути
    bool FileSystem::validatePath(const std::string& path) const {
        // Перевірка на порожній шлях
        // Check for empty path
        // Проверка на пустой путь
        if (path.empty()) {
            return false;
        }
        
        // Перевірка на відносні шляхи, що виходять за межі базової директорії
        // Check for relative paths that go outside base directory
        // Проверка на относительные пути, выходящие за пределы базовой директории
        if (path.find("..") != std::string::npos) {
            return false;
        }
        
        return true;
    }

    // Визначення типу файлу за шляхом
    // Detect file type by path
    // Определение типа файла по пути
    FileType FileSystem::detectFileType(const std::string& path) const {
        std::string lowerPath = path;
        std::transform(lowerPath.begin(), lowerPath.end(), lowerPath.begin(), ::tolower);
        
        if (lowerPath.find("neuron") != std::string::npos) {
            return FileType::NEURON_DATA;
        } else if (lowerPath.find("synapse") != std::string::npos) {
            return FileType::SYNAPSE_DATA;
        } else if (lowerPath.find("config") != std::string::npos) {
            return FileType::CONFIG_DATA;
        } else if (lowerPath.find("log") != std::string::npos) {
            return FileType::LOG_DATA;
        } else if (lowerPath.find("plugin") != std::string::npos) {
            return FileType::PLUGIN_DATA;
        } else {
            return FileType::CUSTOM_DATA;
        }
    }

    // Глобальна файлова система
    // Global file system
    // Глобальная файловая система
    std::unique_ptr<FileSystem> gFileSystem = nullptr;

} // namespace NeuroSync