#ifndef SECURITY_MANAGER_H
#define SECURITY_MANAGER_H

#include <string>
#include <vector>
#include <memory>

namespace NeuroSync {
namespace Security {

    // Менеджер безпеки
    // Security manager
    // Менеджер безопасности
    class SecurityManager {
    public:
        // Конструктор
        // Constructor
        // Конструктор
        SecurityManager();
        
        // Деструктор
        // Destructor
        // Деструктор
        virtual ~SecurityManager();
        
        // Ініціалізація менеджера безпеки
        // Initialize security manager
        // Инициализация менеджера безопасности
        bool initialize();
        
        // Шифрування даних
        // Encrypt data
        // Шифрование данных
        bool encrypt(const std::vector<uint8_t>& data, std::vector<uint8_t>& encryptedData);
        
        // Розшифрування даних
        // Decrypt data
        // Расшифровка данных
        bool decrypt(const std::vector<uint8_t>& encryptedData, std::vector<uint8_t>& data);
        
        // Хешування даних
        // Hash data
        // Хеширование данных
        std::string hash(const std::string& data);
        
        // Генерація ключа
        // Generate key
        // Генерация ключа
        std::string generateKey();
        
        // Встановлення ключа
        // Set key
        // Установка ключа
        void setKey(const std::string& key);
        
        // Отримання ключа
        // Get key
        // Получение ключа
        std::string getKey() const;
        
    private:
        std::string encryptionKey;
        bool initialized;
    };

} // namespace Security
} // namespace NeuroSync

#endif // SECURITY_MANAGER_H