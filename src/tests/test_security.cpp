#include "../security/SecurityModule.h"
#include <iostream>
#include <cassert>
#include <vector>

// Тести для модуля безпеки
// Security module tests
// Тесты для модуля безопасности

void testSecurityInitialization() {
    std::cout << "Testing SecurityModule initialization..." << std::endl;
    
    NeuroSync::SecurityModule securityModule;
    
    NeuroSync::SecurityConfig config;
    config.encryptionType = NeuroSync::EncryptionType::AES_128;
    config.authType = NeuroSync::AuthType::HMAC_SHA256;
    
    assert(securityModule.initialize(config));
    
    assert(securityModule.getStatus() == NeuroSync::SecurityStatus::INITIALIZING);
    assert(securityModule.getConfiguration().encryptionType == NeuroSync::EncryptionType::AES_128);
    assert(securityModule.getConfiguration().authType == NeuroSync::AuthType::HMAC_SHA256);
    
    std::cout << "SecurityModule initialization test passed!" << std::endl;
}

void testSecurityStartStop() {
    std::cout << "Testing SecurityModule start/stop..." << std::endl;
    
    NeuroSync::SecurityModule securityModule;
    
    NeuroSync::SecurityConfig config;
    securityModule.initialize(config);
    
    // Запуск модуля безпеки
    // Starting security module
    // Запуск модуля безопасности
    assert(securityModule.start());
    assert(securityModule.getStatus() == NeuroSync::SecurityStatus::ACTIVE);
    
    // Зупинка модуля безпеки
    // Stopping security module
    // Остановка модуля безопасности
    securityModule.stop();
    assert(securityModule.getStatus() == NeuroSync::SecurityStatus::DISABLED);
    
    std::cout << "SecurityModule start/stop test passed!" << std::endl;
}

void testKeyGeneration() {
    std::cout << "Testing key generation..." << std::endl;
    
    NeuroSync::SecurityModule securityModule;
    
    // Генерація ключів різних типів
    // Generating keys of different types
    // Генерация ключей разных типов
    std::string aes128Key = securityModule.generateKey(NeuroSync::EncryptionType::AES_128);
    std::string aes256Key = securityModule.generateKey(NeuroSync::EncryptionType::AES_256);
    std::string rsa2048Key = securityModule.generateKey(NeuroSync::EncryptionType::RSA_2048);
    
    assert(!aes128Key.empty());
    assert(!aes256Key.empty());
    assert(!rsa2048Key.empty());
    
    // Перевірка довжини ключів
    // Checking key lengths
    // Проверка длины ключей
    assert(aes128Key.length() >= 32); // 16 байтів * 2 символи на байт (hex)
    // 16 bytes * 2 characters per byte (hex)
    // 16 байт * 2 символа на байт (hex)
    assert(aes256Key.length() >= 64); // 32 байти * 2 символи на байт (hex)
    // 32 bytes * 2 characters per byte (hex)
    // 32 байта * 2 символа на байт (hex)
    assert(rsa2048Key.length() >= 512); // 256 байтів * 2 символи на байт (hex)
    // 256 bytes * 2 characters per byte (hex)
    // 256 байт * 2 символа на байт (hex)
    
    std::cout << "Key generation test passed!" << std::endl;
}

void testSessionManagement() {
    std::cout << "Testing session management..." << std::endl;
    
    NeuroSync::SecurityModule securityModule;
    
    NeuroSync::SecurityConfig config;
    securityModule.initialize(config);
    securityModule.start();
    
    // Генерація сесій
    // Generating sessions
    // Генерация сессий
    std::string session1 = securityModule.generateSession("node_1");
    std::string session2 = securityModule.generateSession("node_2");
    
    assert(!session1.empty());
    assert(!session2.empty());
    assert(session1 != session2);
    
    // Перевірка кількості активних сесій
    // Checking active session count
    // Проверка количества активных сессий
    assert(securityModule.getActiveSessionCount() == 2);
    
    // Перевірка сесій
    // Checking sessions
    // Проверка сессий
    assert(securityModule.validateSession(session1));
    assert(securityModule.validateSession(session2));
    
    // Отримання інформації про сесії
    // Getting session information
    // Получение информации о сессиях
    NeuroSync::SessionInfo info1 = securityModule.getSessionInfo(session1);
    NeuroSync::SessionInfo info2 = securityModule.getSessionInfo(session2);
    
    assert(info1.sessionId == session1);
    assert(info1.nodeId == "node_1");
    assert(info2.sessionId == session2);
    assert(info2.nodeId == "node_2");
    
    // Завершення сесій
    // Terminating sessions
    // Завершение сессий
    securityModule.terminateSession(session1);
    assert(securityModule.getActiveSessionCount() == 1);
    
    securityModule.terminateSession(session2);
    assert(securityModule.getActiveSessionCount() == 0);
    
    std::cout << "Session management test passed!" << std::endl;
}

void testEncryptionDecryption() {
    std::cout << "Testing encryption/decryption..." << std::endl;
    
    NeuroSync::SecurityModule securityModule;
    
    NeuroSync::SecurityConfig config;
    config.encryptionType = NeuroSync::EncryptionType::AES_128;
    config.encryptionKey = securityModule.generateKey(NeuroSync::EncryptionType::AES_128);
    securityModule.initialize(config);
    securityModule.start();
    
    // Шифрування даних
    // Encrypting data
    // Шифрование данных
    std::vector<uint8_t> originalData = {0x01, 0x02, 0x03, 0x04, 0x05};
    std::vector<uint8_t> encryptedData = securityModule.encryptData(originalData);
    
    assert(!encryptedData.empty());
    assert(encryptedData.size() == originalData.size());
    
    // Розшифрування даних
    // Decrypting data
    // Расшифрование данных
    std::vector<uint8_t> decryptedData = securityModule.decryptData(encryptedData);
    
    assert(!decryptedData.empty());
    assert(decryptedData.size() == originalData.size());
    
    // Перевірка, що розшифровані дані співпадають з оригіналом
    // Checking that decrypted data matches original
    // Проверка, что расшифрованные данные совпадают с оригиналом
    assert(memcmp(originalData.data(), decryptedData.data(), originalData.size()) == 0);
    
    std::cout << "Encryption/decryption test passed!" << std::endl;
}

void testAuthentication() {
    std::cout << "Testing authentication..." << std::endl;
    
    NeuroSync::SecurityModule securityModule;
    
    NeuroSync::SecurityConfig config;
    config.authType = NeuroSync::AuthType::HMAC_SHA256;
    config.authKey = securityModule.generateKey(NeuroSync::EncryptionType::AES_128);
    securityModule.initialize(config);
    securityModule.start();
    
    // Аутентифікація даних
    // Authenticating data
    // Аутентификация данных
    std::vector<uint8_t> data = {0x10, 0x20, 0x30, 0x40, 0x50};
    std::vector<uint8_t> signature = securityModule.authenticateData(data);
    
    assert(!signature.empty());
    
    // Перевірка автентичності даних
    // Verifying data authenticity
    // Проверка подлинности данных
    assert(securityModule.verifyData(data, signature));
    
    // Перевірка з невірною сигнатурою
    // Checking with incorrect signature
    // Проверка с неверной сигнатурой
    std::vector<uint8_t> wrongSignature = {0xFF, 0xFF, 0xFF};
    assert(!securityModule.verifyData(data, wrongSignature));
    
    std::cout << "Authentication test passed!" << std::endl;
}

void testCertificateManagement() {
    std::cout << "Testing certificate management..." << std::endl;
    
    NeuroSync::SecurityModule securityModule;
    
    NeuroSync::SecurityConfig config;
    config.enableCertificateValidation = true;
    securityModule.initialize(config);
    
    // Додавання довірених сертифікатів
    // Adding trusted certificates
    // Добавление доверенных сертификатов
    securityModule.addTrustedCertificate("cert_1");
    securityModule.addTrustedCertificate("cert_2");
    
    // Перевірка сертифікатів
    // Checking certificates
    // Проверка сертификатов
    assert(securityModule.validateCertificate("cert_1"));
    assert(securityModule.validateCertificate("cert_2"));
    assert(!securityModule.validateCertificate("cert_3"));
    
    // Видалення довіреного сертифіката
    // Removing trusted certificate
    // Удаление доверенного сертификата
    securityModule.removeTrustedCertificate("cert_1");
    assert(!securityModule.validateCertificate("cert_1"));
    assert(securityModule.validateCertificate("cert_2"));
    
    std::cout << "Certificate management test passed!" << std::endl;
}

void testSecurityEvents() {
    std::cout << "Testing security events..." << std::endl;
    
    NeuroSync::SecurityModule securityModule;
    
    NeuroSync::SecurityConfig config;
    securityModule.initialize(config);
    securityModule.start();
    
    // Логування подій безпеки
    // Logging security events
    // Логирование событий безопасности
    securityModule.logSecurityEvent("Test event 1");
    securityModule.logSecurityEvent("Test event 2", "With details");
    
    // Примітка: немає прямого способу перевірити журнали, тому просто перевіряємо, що методи не викликають помилок
    // Note: there's no direct way to check logs, so we just verify that methods don't cause errors
    // Примечание: нет прямого способа проверить журналы, поэтому мы просто проверяем, что методы не вызывают ошибок
    
    std::cout << "Security events test passed!" << std::endl;
}

int main() {
    std::cout << "=== Security Module Tests ===" << std::endl;
    
    try {
        testSecurityInitialization();
        testSecurityStartStop();
        testKeyGeneration();
        testSessionManagement();
        testEncryptionDecryption();
        testAuthentication();
        testCertificateManagement();
        testSecurityEvents();
        
        std::cout << "\nAll Security Module tests passed!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Test failed with exception: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Test failed with unknown exception" << std::endl;
        return 1;
    }
    
    return 0;
}