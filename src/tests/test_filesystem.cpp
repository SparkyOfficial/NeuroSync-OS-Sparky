#include "../filesystem/FileSystem.h"
#include <iostream>
#include <cassert>
#include <vector>
#include <cstring>

// Тести для файлової системи
// File system tests
// Тесты для файловой системы

void testFileSystemInitialization() {
    std::cout << "Testing FileSystem initialization..." << std::endl;
    
    NeuroSync::FileSystem fs;
    assert(fs.initialize("./test_fs"));
    
    assert(fs.getBasePath() == "./test_fs");
    
    // Перевірка створення стандартних директорій
    // Check creation of standard directories
    // Проверка создания стандартных директорий
    assert(fs.directoryExists("neurons"));
    assert(fs.directoryExists("synapses"));
    assert(fs.directoryExists("config"));
    assert(fs.directoryExists("logs"));
    assert(fs.directoryExists("plugins"));
    assert(fs.directoryExists("data"));
    
    std::cout << "FileSystem initialization test passed!" << std::endl;
}

void testDirectoryOperations() {
    std::cout << "Testing directory operations..." << std::endl;
    
    NeuroSync::FileSystem fs;
    fs.initialize("./test_fs");
    
    // Створення директорії
    // Creating directory
    // Создание директории
    assert(fs.createDirectory("test_directory"));
    assert(fs.directoryExists("test_directory"));
    
    // Видалення директорії
    // Removing directory
    // Удаление директории
    assert(fs.removeDirectory("test_directory"));
    assert(!fs.directoryExists("test_directory"));
    
    // Створення вкладеної директорії
    // Creating nested directory
    // Создание вложенной директории
    assert(fs.createDirectory("parent/child/grandchild"));
    assert(fs.directoryExists("parent/child/grandchild"));
    
    std::cout << "Directory operations test passed!" << std::endl;
}

void testFileOperations() {
    std::cout << "Testing file operations..." << std::endl;
    
    NeuroSync::FileSystem fs;
    fs.initialize("./test_fs");
    
    // Створення файлу
    // Creating file
    // Создание файла
    assert(fs.createFile("test_file.txt"));
    assert(fs.fileExists("test_file.txt"));
    
    // Запис даних у файл
    // Writing data to file
    // Запись данных в файл
    std::vector<uint8_t> testData = {0x01, 0x02, 0x03, 0x04, 0x05};
    assert(fs.writeFile("test_file.txt", testData));
    
    // Зчитування даних з файлу
    // Reading data from file
    // Чтение данных из файла
    std::vector<uint8_t> readData;
    assert(fs.readFile("test_file.txt", readData));
    assert(readData.size() == testData.size());
    assert(memcmp(readData.data(), testData.data(), testData.size()) == 0);
    
    // Отримання розміру файлу
    // Getting file size
    // Получение размера файла
    assert(fs.getFileSize("test_file.txt") == testData.size());
    
    // Отримання метаданих файлу
    // Getting file metadata
    // Получение метаданных файла
    NeuroSync::FileMetadata metadata;
    assert(fs.getFileMetadata("test_file.txt", metadata));
    assert(metadata.name == "test_file.txt");
    assert(metadata.size == testData.size());
    assert(metadata.type == NeuroSync::FileType::CUSTOM_DATA);
    
    // Видалення файлу
    // Removing file
    // Удаление файла
    assert(fs.removeFile("test_file.txt"));
    assert(!fs.fileExists("test_file.txt"));
    
    std::cout << "File operations test passed!" << std::endl;
}

void testFileCopyAndRename() {
    std::cout << "Testing file copy and rename..." << std::endl;
    
    NeuroSync::FileSystem fs;
    fs.initialize("./test_fs");
    
    // Створення файлу
    // Creating file
    // Создание файла
    std::vector<uint8_t> testData = {0x10, 0x20, 0x30, 0x40};
    assert(fs.createFile("original.txt"));
    assert(fs.writeFile("original.txt", testData));
    
    // Копіювання файлу
    // Copying file
    // Копирование файла
    assert(fs.copyFile("original.txt", "copy.txt"));
    assert(fs.fileExists("copy.txt"));
    
    // Перевірка, що скопійовані дані співпадають
    // Checking that copied data matches
    // Проверка, что скопированные данные совпадают
    std::vector<uint8_t> copyData;
    assert(fs.readFile("copy.txt", copyData));
    assert(copyData.size() == testData.size());
    assert(memcmp(copyData.data(), testData.data(), testData.size()) == 0);
    
    // Перейменування файлу
    // Renaming file
    // Переименование файла
    assert(fs.renameFile("original.txt", "renamed.txt"));
    assert(!fs.fileExists("original.txt"));
    assert(fs.fileExists("renamed.txt"));
    
    // Перевірка даних після перейменування
    // Checking data after rename
    // Проверка данных после переименования
    std::vector<uint8_t> renamedData;
    assert(fs.readFile("renamed.txt", renamedData));
    assert(renamedData.size() == testData.size());
    assert(memcmp(renamedData.data(), testData.data(), testData.size()) == 0);
    
    std::cout << "File copy and rename test passed!" << std::endl;
}

void testListingOperations() {
    std::cout << "Testing listing operations..." << std::endl;
    
    NeuroSync::FileSystem fs;
    fs.initialize("./test_fs");
    
    // Створення тестових файлів і директорій
    // Creating test files and directories
    // Создание тестовых файлов и директорий
    fs.createFile("file1.txt");
    fs.createFile("file2.dat");
    fs.createFile("dir1/file3.txt");
    fs.createFile("dir1/file4.log");
    fs.createDirectory("dir2");
    fs.createDirectory("dir3/subdir");
    
    // Отримання списку файлів
    // Getting list of files
    // Получение списка файлов
    auto rootFiles = fs.listFiles("");
    assert(rootFiles.size() >= 2); // file1.txt, file2.dat
    
    auto dir1Files = fs.listFiles("dir1");
    assert(dir1Files.size() == 2); // file3.txt, file4.log
    
    // Отримання списку директорій
    // Getting list of directories
    // Получение списка директорий
    auto rootDirs = fs.listDirectories("");
    assert(rootDirs.size() >= 3); // dir1, dir2, dir3
    
    auto dir3Dirs = fs.listDirectories("dir3");
    assert(dir3Dirs.size() == 1); // subdir
    
    std::cout << "Listing operations test passed!" << std::endl;
}

void testIntegrityCheck() {
    std::cout << "Testing integrity check..." << std::endl;
    
    NeuroSync::FileSystem fs;
    assert(fs.initialize("./test_fs"));
    
    // Перевірка цілісності
    // Integrity check
    // Проверка целостности
    assert(fs.checkIntegrity());
    
    std::cout << "Integrity check test passed!" << std::endl;
}

int main() {
    std::cout << "=== FileSystem Tests ===" << std::endl;
    
    try {
        testFileSystemInitialization();
        testDirectoryOperations();
        testFileOperations();
        testFileCopyAndRename();
        testListingOperations();
        testIntegrityCheck();
        
        std::cout << "\nAll FileSystem tests passed!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Test failed with exception: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Test failed with unknown exception" << std::endl;
        return 1;
    }
    
    return 0;
}