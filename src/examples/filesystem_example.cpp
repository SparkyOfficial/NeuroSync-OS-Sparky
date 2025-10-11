#include "../filesystem/FileSystem.h"
#include <iostream>
#include <vector>
#include <cstring>

// Приклад використання файлової системи
// File system usage example
// Пример использования файловой системы

int main() {
    std::cout << "=== FileSystem Example ===" << std::endl;
    
    // Ініціалізація файлової системи
    // Initializing file system
    // Инициализация файловой системы
    NeuroSync::gFileSystem = std::make_unique<NeuroSync::FileSystem>();
    if (!NeuroSync::gFileSystem->initialize("./neurosync_data")) {
        std::cerr << "Failed to initialize file system" << std::endl;
        return 1;
    }
    
    std::cout << "File system initialized with base path: " << NeuroSync::gFileSystem->getBasePath() << std::endl;
    
    // Створення директорій
    // Creating directories
    // Создание директорий
    std::cout << "\nCreating directories..." << std::endl;
    if (NeuroSync::gFileSystem->createDirectory("test_dir")) {
        std::cout << "Created directory: test_dir" << std::endl;
    }
    
    if (NeuroSync::gFileSystem->createDirectory("nested/dir/example")) {
        std::cout << "Created nested directory: nested/dir/example" << std::endl;
    }
    
    // Створення файлів
    // Creating files
    // Создание файлов
    std::cout << "\nCreating files..." << std::endl;
    
    // Створення файлу даних нейрона
    // Creating neuron data file
    // Создание файла данных нейрона
    std::vector<uint8_t> neuronData = {0x01, 0x02, 0x03, 0x04, 0x05};
    if (NeuroSync::gFileSystem->createFile("neurons/neuron_001.dat", NeuroSync::FileType::NEURON_DATA)) {
        std::cout << "Created neuron data file: neurons/neuron_001.dat" << std::endl;
        
        // Запис даних у файл
        // Writing data to file
        // Запись данных в файл
        if (NeuroSync::gFileSystem->writeFile("neurons/neuron_001.dat", neuronData)) {
            std::cout << "Wrote data to neuron file" << std::endl;
        }
    }
    
    // Створення файлу даних синапса
    // Creating synapse data file
    // Создание файла данных синапса
    std::vector<uint8_t> synapseData = {0x10, 0x20, 0x30, 0x40, 0x50, 0x60};
    if (NeuroSync::gFileSystem->createFile("synapses/synapse_001.dat", NeuroSync::FileType::SYNAPSE_DATA)) {
        std::cout << "Created synapse data file: synapses/synapse_001.dat" << std::endl;
        
        // Запис даних у файл
        // Writing data to file
        // Запись данных в файл
        if (NeuroSync::gFileSystem->writeFile("synapses/synapse_001.dat", synapseData)) {
            std::cout << "Wrote data to synapse file" << std::endl;
        }
    }
    
    // Створення конфігураційного файлу
    // Creating configuration file
    // Создание конфигурационного файла
    std::string configContent = "neuron_count=100\nsynapse_count=500\nlearning_rate=0.01";
    std::vector<uint8_t> configData(configContent.begin(), configContent.end());
    if (NeuroSync::gFileSystem->createFile("config/system.cfg", NeuroSync::FileType::CONFIG_DATA)) {
        std::cout << "Created config file: config/system.cfg" << std::endl;
        
        // Запис даних у файл
        // Writing data to file
        // Запись данных в файл
        if (NeuroSync::gFileSystem->writeFile("config/system.cfg", configData)) {
            std::cout << "Wrote data to config file" << std::endl;
        }
    }
    
    // Зчитування даних з файлів
    // Reading data from files
    // Чтение данных из файлов
    std::cout << "\nReading files..." << std::endl;
    
    std::vector<uint8_t> readNeuronData;
    if (NeuroSync::gFileSystem->readFile("neurons/neuron_001.dat", readNeuronData)) {
        std::cout << "Read neuron data: ";
        for (const auto& byte : readNeuronData) {
            printf("%02X ", byte);
        }
        std::cout << std::endl;
    }
    
    std::vector<uint8_t> readSynapseData;
    if (NeuroSync::gFileSystem->readFile("synapses/synapse_001.dat", readSynapseData)) {
        std::cout << "Read synapse data: ";
        for (const auto& byte : readSynapseData) {
            printf("%02X ", byte);
        }
        std::cout << std::endl;
    }
    
    std::vector<uint8_t> readConfigData;
    if (NeuroSync::gFileSystem->readFile("config/system.cfg", readConfigData)) {
        std::cout << "Read config data: " << std::string(readConfigData.begin(), readConfigData.end()) << std::endl;
    }
    
    // Отримання метаданих файлів
    // Getting file metadata
    // Получение метаданных файлов
    std::cout << "\nFile metadata:" << std::endl;
    
    NeuroSync::FileMetadata metadata;
    if (NeuroSync::gFileSystem->getFileMetadata("neurons/neuron_001.dat", metadata)) {
        std::cout << "Neuron file metadata:" << std::endl;
        std::cout << "  Name: " << metadata.name << std::endl;
        std::cout << "  Size: " << metadata.size << " bytes" << std::endl;
        std::cout << "  Type: NEURON_DATA" << std::endl;
    }
    
    if (NeuroSync::gFileSystem->getFileMetadata("synapses/synapse_001.dat", metadata)) {
        std::cout << "Synapse file metadata:" << std::endl;
        std::cout << "  Name: " << metadata.name << std::endl;
        std::cout << "  Size: " << metadata.size << " bytes" << std::endl;
        std::cout << "  Type: SYNAPSE_DATA" << std::endl;
    }
    
    // Список файлів у директоріях
    // Listing files in directories
    // Список файлов в директориях
    std::cout << "\nDirectory listings:" << std::endl;
    
    auto neuronFiles = NeuroSync::gFileSystem->listFiles("neurons");
    std::cout << "Files in neurons/: ";
    for (const auto& file : neuronFiles) {
        std::cout << file << " ";
    }
    std::cout << std::endl;
    
    auto synapseFiles = NeuroSync::gFileSystem->listFiles("synapses");
    std::cout << "Files in synapses/: ";
    for (const auto& file : synapseFiles) {
        std::cout << file << " ";
    }
    std::cout << std::endl;
    
    auto configFiles = NeuroSync::gFileSystem->listFiles("config");
    std::cout << "Files in config/: ";
    for (const auto& file : configFiles) {
        std::cout << file << " ";
    }
    std::cout << std::endl;
    
    // Список директорій
    // Listing directories
    // Список директорий
    auto directories = NeuroSync::gFileSystem->listDirectories("");
    std::cout << "Directories in root: ";
    for (const auto& dir : directories) {
        std::cout << dir << " ";
    }
    std::cout << std::endl;
    
    // Копіювання файлу
    // Copying file
    // Копирование файла
    std::cout << "\nCopying file..." << std::endl;
    if (NeuroSync::gFileSystem->copyFile("neurons/neuron_001.dat", "neurons/neuron_001_backup.dat")) {
        std::cout << "Copied neuron_001.dat to neuron_001_backup.dat" << std::endl;
    }
    
    // Перейменування файлу
    // Renaming file
    // Переименование файла
    std::cout << "Renaming file..." << std::endl;
    if (NeuroSync::gFileSystem->renameFile("config/system.cfg", "config/system_backup.cfg")) {
        std::cout << "Renamed system.cfg to system_backup.cfg" << std::endl;
    }
    
    // Перевірка цілісності файлової системи
    // Checking file system integrity
    // Проверка целостности файловой системы
    std::cout << "\nChecking file system integrity..." << std::endl;
    if (NeuroSync::gFileSystem->checkIntegrity()) {
        std::cout << "File system integrity check passed!" << std::endl;
    } else {
        std::cout << "File system integrity check failed!" << std::endl;
    }
    
    std::cout << "\nFileSystem example completed!" << std::endl;
    
    return 0;
}