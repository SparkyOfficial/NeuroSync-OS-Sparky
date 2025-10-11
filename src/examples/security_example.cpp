#include "../security/SecurityModule.h"
#include <iostream>
#include <vector>

// Приклад використання модуля безпеки
// Security module usage example
// Пример использования модуля безопасности

int main() {
    std::cout << "=== Security Module Example ===" << std::endl;
    
    // Ініціалізація модуля безпеки
    // Initializing security module
    // Инициализация модуля безопасности
    NeuroSync::gSecurityModule = std::make_unique<NeuroSync::SecurityModule>();
    
    NeuroSync::SecurityConfig config;
    config.encryptionType = NeuroSync::EncryptionType::AES_256;
    config.authType = NeuroSync::AuthType::HMAC_SHA256;
    config.securityLevel = NeuroSync::SecurityLevel::HIGH;
    config.encryptionKey = NeuroSync::gSecurityModule->generateKey(NeuroSync::EncryptionType::AES_256);
    config.authKey = NeuroSync::gSecurityModule->generateKey(NeuroSync::EncryptionType::AES_128);
    config.keyRotationInterval = 3600; // 1 година
    // 1 hour
    // 1 час
    config.enableCertificateValidation = true;
    
    if (!NeuroSync::gSecurityModule->initialize(config)) {
        std::cerr << "Failed to initialize security module" << std::endl;
        return 1;
    }
    
    std::cout << "Security module initialized" << std::endl;
    
    // Запуск модуля безпеки
    // Starting security module
    // Запуск модуля безопасности
    if (!NeuroSync::gSecurityModule->start()) {
        std::cerr << "Failed to start security module" << std::endl;
        return 1;
    }
    
    std::cout << "Security module started" << std::endl;
    
    // Додавання довірених сертифікатів
    // Adding trusted certificates
    // Добавление доверенных сертификатов
    NeuroSync::gSecurityModule->addTrustedCertificate("trusted_cert_1");
    NeuroSync::gSecurityModule->addTrustedCertificate("trusted_cert_2");
    
    // Перевірка сертифікатів
    // Checking certificates
    // Проверка сертификатов
    std::cout << "\nCertificate validation:" << std::endl;
    std::cout << "  trusted_cert_1: " << (NeuroSync::gSecurityModule->validateCertificate("trusted_cert_1") ? "valid" : "invalid") << std::endl;
    std::cout << "  untrusted_cert: " << (NeuroSync::gSecurityModule->validateCertificate("untrusted_cert") ? "valid" : "invalid") << std::endl;
    
    // Генерація сесій
    // Generating sessions
    // Генерация сессий
    std::cout << "\nGenerating sessions..." << std::endl;
    std::string session1 = NeuroSync::gSecurityModule->generateSession("node_1");
    std::string session2 = NeuroSync::gSecurityModule->generateSession("node_2");
    
    std::cout << "Generated sessions:" << std::endl;
    std::cout << "  Session 1: " << session1 << std::endl;
    std::cout << "  Session 2: " << session2 << std::endl;
    
    // Перевірка сесій
    // Checking sessions
    // Проверка сессий
    std::cout << "\nSession validation:" << std::endl;
    std::cout << "  Session 1: " << (NeuroSync::gSecurityModule->validateSession(session1) ? "valid" : "invalid") << std::endl;
    std::cout << "  Session 2: " << (NeuroSync::gSecurityModule->validateSession(session2) ? "valid" : "invalid") << std::endl;
    
    // Отримання інформації про сесії
    // Getting session information
    // Получение информации о сессиях
    std::cout << "\nSession information:" << std::endl;
    auto sessionInfo1 = NeuroSync::gSecurityModule->getSessionInfo(session1);
    std::cout << "  Session 1:" << std::endl;
    std::cout << "    Node ID: " << sessionInfo1.nodeId << std::endl;
    std::cout << "    Authenticated: " << (sessionInfo1.isAuthenticated ? "yes" : "no") << std::endl;
    std::cout << "    Encrypted: " << (sessionInfo1.isEncrypted ? "yes" : "no") << std::endl;
    
    // Шифрування даних
    // Encrypting data
    // Шифрование данных
    std::cout << "\nEncrypting data..." << std::endl;
    std::vector<uint8_t> originalData = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
    std::cout << "Original data: ";
    for (const auto& byte : originalData) {
        printf("%02X ", byte);
    }
    std::cout << std::endl;
    
    std::vector<uint8_t> encryptedData = NeuroSync::gSecurityModule->encryptData(originalData);
    std::cout << "Encrypted data: ";
    for (const auto& byte : encryptedData) {
        printf("%02X ", byte);
    }
    std::cout << std::endl;
    
    // Розшифрування даних
    // Decrypting data
    // Расшифрование данных
    std::cout << "\nDecrypting data..." << std::endl;
    std::vector<uint8_t> decryptedData = NeuroSync::gSecurityModule->decryptData(encryptedData);
    std::cout << "Decrypted data: ";
    for (const auto& byte : decryptedData) {
        printf("%02X ", byte);
    }
    std::cout << std::endl;
    
    // Перевірка, що розшифровані дані співпадають з оригіналом
    // Checking that decrypted data matches original
    // Проверка, что расшифрованные данные совпадают с оригиналом
    bool dataMatch = (originalData.size() == decryptedData.size() && 
                     memcmp(originalData.data(), decryptedData.data(), originalData.size()) == 0);
    std::cout << "Data integrity: " << (dataMatch ? "maintained" : "compromised") << std::endl;
    
    // Аутентифікація даних
    // Authenticating data
    // Аутентификация данных
    std::cout << "\nAuthenticating data..." << std::endl;
    std::vector<uint8_t> signature = NeuroSync::gSecurityModule->authenticateData(originalData);
    std::cout << "Signature: ";
    for (const auto& byte : signature) {
        printf("%02X ", byte);
    }
    std::cout << std::endl;
    
    // Перевірка автентичності даних
    // Verifying data authenticity
    // Проверка подлинности данных
    std::cout << "\nVerifying data authenticity..." << std::endl;
    bool isAuthentic = NeuroSync::gSecurityModule->verifyData(originalData, signature);
    std::cout << "Data authenticity: " << (isAuthentic ? "verified" : "not verified") << std::endl;
    
    // Логування подій безпеки
    // Logging security events
    // Логирование событий безопасности
    std::cout << "\nLogging security events..." << std::endl;
    NeuroSync::gSecurityModule->logSecurityEvent("Data encryption", "Encrypted 8 bytes of data");
    NeuroSync::gSecurityModule->logSecurityEvent("Session created", "Created session for node_1");
    NeuroSync::gSecurityModule->logSecurityEvent("Authentication", "Verified data authenticity");
    
    // Отримання статистики
    // Getting statistics
    // Получение статистики
    std::cout << "\nSecurity statistics:" << std::endl;
    std::cout << "  Active sessions: " << NeuroSync::gSecurityModule->getActiveSessionCount() << std::endl;
    std::cout << "  Security status: " << static_cast<int>(NeuroSync::gSecurityModule->getStatus()) << std::endl;
    
    // Очищення прострочених сесій
    // Cleaning expired sessions
    // Очистка просроченных сессий
    std::cout << "\nCleaning expired sessions..." << std::endl;
    NeuroSync::gSecurityModule->cleanExpiredSessions();
    
    // Завершення сесій
    // Terminating sessions
    // Завершение сессий
    std::cout << "\nTerminating sessions..." << std::endl;
    NeuroSync::gSecurityModule->terminateSession(session1);
    NeuroSync::gSecurityModule->terminateSession(session2);
    
    std::cout << "Active sessions after termination: " << NeuroSync::gSecurityModule->getActiveSessionCount() << std::endl;
    
    // Зупинка модуля безпеки
    // Stopping security module
    // Остановка модуля безопасности
    std::cout << "\nStopping security module..." << std::endl;
    NeuroSync::gSecurityModule->stop();
    
    std::cout << "\nSecurity module example completed!" << std::endl;
    
    return 0;
}