#ifndef SECURITY_MODULE_H
#define SECURITY_MODULE_H

#include <string>
#include <vector>
#include <memory>
#include <map>
#include <chrono>
#include <atomic>
#include <mutex>

// SecurityModule.h
// Модуль безпеки для NeuroSync OS Sparky
// Security module for NeuroSync OS Sparky
// Модуль безопасности для NeuroSync OS Sparky

namespace NeuroSync {

    // Типи шифрування
    // Encryption types
    // Типы шифрования
    enum class EncryptionType {
        NONE,           // Без шифрування
        // No encryption
        // Без шифрования
        
        AES_128,        // AES-128
        AES_256,        // AES-256
        
        RSA_2048,       // RSA-2048
        RSA_4096,       // RSA-4096
        
        CHACHA20,       // ChaCha20
        CHACHA20_POLY1305  // ChaCha20-Poly1305
    };

    // Типи аутентифікації
    // Authentication types
    // Типы аутентификации
    enum class AuthType {
        NONE,           // Без аутентифікації
        // No authentication
        // Без аутентификации
        
        HMAC_SHA256,    // HMAC-SHA256
        HMAC_SHA512,    // HMAC-SHA512
        
        RSA_SIGN,       // RSA Signature
        ECDSA_SIGN,     // ECDSA Signature
        
        JWT             // JSON Web Token
    };

    // Рівні безпеки
    // Security levels
    // Уровни безопасности
    enum class SecurityLevel {
        LOW,            // Низький рівень безпеки
        // Low security level
        // Низкий уровень безопасности
        
        MEDIUM,         // Середній рівень безпеки
        // Medium security level
        // Средний уровень безопасности
        
        HIGH,           // Високий рівень безпеки
        // High security level
        // Высокий уровень безопасности
        
        VERY_HIGH       // Дуже високий рівень безпеки
        // Very high security level
        // Очень высокий уровень безопасности
    };

    // Конфігурація безпеки
    // Security configuration
    // Конфигурация безопасности
    struct SecurityConfig {
        EncryptionType encryptionType;
        AuthType authType;
        SecurityLevel securityLevel;
        std::string encryptionKey;
        std::string authKey;
        uint32_t keyRotationInterval;  // В секундах
        // In seconds
        // В секундах
        bool enableCertificateValidation;
        std::vector<std::string> trustedCertificates;
        
        SecurityConfig() : encryptionType(EncryptionType::NONE), 
                          authType(AuthType::NONE),
                          securityLevel(SecurityLevel::LOW),
                          keyRotationInterval(3600),  // 1 година
                          // 1 hour
                          // 1 час
                          enableCertificateValidation(false) {}
    };

    // Інформація про сесію
    // Session information
    // Информация о сессии
    struct SessionInfo {
        std::string sessionId;
        std::string nodeId;
        std::chrono::system_clock::time_point startTime;
        std::chrono::system_clock::time_point lastActivity;
        std::string encryptionKey;
        std::string authKey;
        bool isAuthenticated;
        bool isEncrypted;
        
        SessionInfo() : isAuthenticated(false), isEncrypted(false) {}
    };

    // Статус безпеки
    // Security status
    // Статус безопасности
    enum class SecurityStatus {
        DISABLED,       // Безпека вимкнена
        // Security disabled
        // Безопасность отключена
        
        INITIALIZING,   // Ініціалізація
        // Initializing
        // Инициализация
        
        ACTIVE,         // Активна
        // Active
        // Активна
        
        ERROR           // Помилка
        // Error
        // Ошибка
    };

    // Інтерфейс модуля безпеки
    // Security module interface
    // Интерфейс модуля безопасности
    class SecurityModule {
    public:
        // Конструктор
        // Constructor
        // Конструктор
        SecurityModule();
        
        // Деструктор
        // Destructor
        // Деструктор
        virtual ~SecurityModule();
        
        // Ініціалізація модуля безпеки
        // Initialize security module
        // Инициализация модуля безопасности
        virtual bool initialize(const SecurityConfig& config);
        
        // Запуск модуля безпеки
        // Start security module
        // Запуск модуля безопасности
        virtual bool start();
        
        // Зупинка модуля безпеки
        // Stop security module
        // Остановка модуля безопасности
        virtual void stop();
        
        // Шифрування даних
        // Encrypt data
        // Шифрование данных
        virtual std::vector<uint8_t> encryptData(const std::vector<uint8_t>& data, 
                                                const std::string& key = "");
        
        // Розшифрування даних
        // Decrypt data
        // Расшифрование данных
        virtual std::vector<uint8_t> decryptData(const std::vector<uint8_t>& encryptedData, 
                                                const std::string& key = "");
        
        // Аутентифікація даних
        // Authenticate data
        // Аутентификация данных
        virtual std::vector<uint8_t> authenticateData(const std::vector<uint8_t>& data, 
                                                     const std::string& key = "");
        
        // Перевірка автентичності даних
        // Verify data authenticity
        // Проверка подлинности данных
        virtual bool verifyData(const std::vector<uint8_t>& data, 
                               const std::vector<uint8_t>& signature,
                               const std::string& key = "");
        
        // Генерація ключа
        // Generate key
        // Генерация ключа
        virtual std::string generateKey(EncryptionType type = EncryptionType::AES_128);
        
        // Генерація сесії
        // Generate session
        // Генерация сессии
        virtual std::string generateSession(const std::string& nodeId);
        
        // Завершення сесії
        // Terminate session
        // Завершение сессии
        virtual void terminateSession(const std::string& sessionId);
        
        // Отримання інформації про сесію
        // Get session information
        // Получение информации о сессии
        virtual SessionInfo getSessionInfo(const std::string& sessionId) const;
        
        // Перевірка сесії
        // Validate session
        // Проверка сессии
        virtual bool validateSession(const std::string& sessionId) const;
        
        // Отримання статусу безпеки
        // Get security status
        // Получение статуса безопасности
        SecurityStatus getStatus() const;
        
        // Отримання конфігурації безпеки
        // Get security configuration
        // Получение конфигурации безопасности
        SecurityConfig getConfiguration() const;
        
        // Встановлення конфігурації безпеки
        // Set security configuration
        // Установка конфигурации безопасности
        void setConfiguration(const SecurityConfig& config);
        
        // Отримання кількості активних сесій
        // Get active session count
        // Получение количества активных сессий
        size_t getActiveSessionCount() const;
        
        // Очищення прострочених сесій
        // Clean expired sessions
        // Очистка просроченных сессий
        void cleanExpiredSessions();
        
        // Додавання довіреного сертифіката
        // Add trusted certificate
        // Добавление доверенного сертификата
        void addTrustedCertificate(const std::string& cert);
        
        // Видалення довіреного сертифіката
        // Remove trusted certificate
        // Удаление доверенного сертификата
        void removeTrustedCertificate(const std::string& cert);
        
        // Перевірка сертифіката
        // Validate certificate
        // Проверка сертификата
        bool validateCertificate(const std::string& cert) const;
        
        // Логування подій безпеки
        // Log security events
        // Логирование событий безопасности
        virtual void logSecurityEvent(const std::string& event, 
                                     const std::string& details = "");
        
    protected:
        SecurityConfig config;
        SecurityStatus status;
        std::map<std::string, SessionInfo> sessions;
        mutable std::mutex securityMutex;
        std::atomic<uint64_t> securityEventCount;
        std::chrono::system_clock::time_point lastKeyRotation;
        
        // Внутрішні методи
        // Internal methods
        // Внутренние методы
        virtual std::vector<uint8_t> aesEncrypt(const std::vector<uint8_t>& data, 
                                               const std::string& key);
        virtual std::vector<uint8_t> aesDecrypt(const std::vector<uint8_t>& encryptedData, 
                                               const std::string& key);
        virtual std::vector<uint8_t> hmacSign(const std::vector<uint8_t>& data, 
                                             const std::string& key);
        virtual bool hmacVerify(const std::vector<uint8_t>& data, 
                               const std::vector<uint8_t>& signature,
                               const std::string& key);
        virtual std::string generateRandomString(size_t length);
        virtual std::vector<uint8_t> generateRandomBytes(size_t length);
        virtual std::string hashData(const std::vector<uint8_t>& data);
        virtual bool rotateKeys();
        virtual void sessionCleanup();
    };

    // Глобальний модуль безпеки
    // Global security module
    // Глобальный модуль безопасности
    extern std::unique_ptr<SecurityModule> gSecurityModule;

} // namespace NeuroSync

#endif // SECURITY_MODULE_H