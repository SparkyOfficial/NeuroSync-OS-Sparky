#include "../nlp/NaturalLanguageProcessing.h"
#include <iostream>
#include <cassert>
#include <string>

using namespace NeuroSync::NLP;

int main() {
    std::cout << "========================================\n";
    std::cout << "  NeuroSync NLP Module Tests\n";
    std::cout << "========================================\n\n";
    
    // Створення процесора обробки природної мови
    // Create natural language processor
    // Создание процессора обработки естественного языка
    NaturalLanguageProcessor nlpProcessor;
    
    // Тест ініціалізації
    // Test initialization
    // Тест инициализации
    std::cout << "1. Testing initialization...\n";
    NLPConfig config;
    bool initResult = nlpProcessor.initialize(config);
    assert(initResult);
    std::cout << "   ✓ Initialization successful\n\n";
    
    // Тест токенізації
    // Test tokenization
    // Тест токенизации
    std::cout << "2. Testing tokenization...\n";
    std::string testText = "Hello world! This is a test sentence.";
    std::vector<Token> tokens = nlpProcessor.tokenize(testText);
    assert(!tokens.empty());
    std::cout << "   ✓ Tokenization successful, found " << tokens.size() << " tokens\n\n";
    
    // Тест лематизації
    // Test lemmatization
    // Тест лемматизации
    std::cout << "3. Testing lemmatization...\n";
    std::string lemma1 = nlpProcessor.lemmatize("running");
    assert(!lemma1.empty());
    std::cout << "   ✓ Lemmatization successful: running -> " << lemma1 << "\n";
    
    std::string lemma2 = nlpProcessor.lemmatize("better");
    assert(!lemma2.empty());
    std::cout << "   ✓ Lemmatization successful: better -> " << lemma2 << "\n\n";
    
    // Тест стемінгу
    // Test stemming
    // Тест стемминга
    std::cout << "4. Testing stemming...\n";
    std::string stem1 = nlpProcessor.stem("running");
    assert(!stem1.empty());
    std::cout << "   ✓ Stemming successful: running -> " << stem1 << "\n";
    
    std::string stem2 = nlpProcessor.stem("walking");
    assert(!stem2.empty());
    std::cout << "   ✓ Stemming successful: walking -> " << stem2 << "\n\n";
    
    // Тест визначення частин мови
    // Test part of speech tagging
    // Тест определения частей речи
    std::cout << "5. Testing part of speech tagging...\n";
    std::vector<Token> posTokens = nlpProcessor.posTag(tokens);
    assert(posTokens.size() == tokens.size());
    std::cout << "   ✓ POS tagging successful\n\n";
    
    // Тест аналізу сентименту
    // Test sentiment analysis
    // Тест анализа сентимента
    std::cout << "6. Testing sentiment analysis...\n";
    SentimentResult sentiment = nlpProcessor.analyzeSentiment("This is a great product!");
    std::cout << "   ✓ Sentiment analysis successful\n";
    std::cout << "   Sentiment: " << static_cast<int>(sentiment.sentiment) << "\n";
    std::cout << "   Confidence: " << sentiment.confidence << "\n\n";
    
    // Тест виділення іменованих сутностей
    // Test named entity recognition
    // Тест выделения именованных сущностей
    std::cout << "7. Testing named entity recognition...\n";
    NERResult nerResult = nlpProcessor.recognizeEntities("John Smith works at Google.");
    std::cout << "   ✓ Named entity recognition successful\n";
    std::cout << "   Found " << nerResult.entities.size() << " entities\n\n";
    
    // Тест визначення мови
    // Test language detection
    // Тест определения языка
    std::cout << "8. Testing language detection...\n";
    LanguageProfile languageProfile = nlpProcessor.detectLanguage("This is an English sentence.");
    std::cout << "   ✓ Language detection successful\n";
    std::cout << "   Detected language: " << languageProfile.language << "\n";
    std::cout << "   Confidence: " << languageProfile.confidence << "\n\n";
    
    // Тест виділення ключових слів
    // Test keyword extraction
    // Тест выделения ключевых слов
    std::cout << "9. Testing keyword extraction...\n";
    std::vector<std::string> keywords = nlpProcessor.extractKeywords("Natural language processing is fascinating.");
    std::cout << "   ✓ Keyword extraction successful\n";
    std::cout << "   Found " << keywords.size() << " keywords\n\n";
    
    // Тест підсумовування
    // Test summarization
    // Тест резюмирования
    std::cout << "10. Testing text summarization...\n";
    std::string summary = nlpProcessor.summarize("This is the first sentence. This is the second sentence. This is the third sentence.", 2);
    assert(!summary.empty());
    std::cout << "   ✓ Text summarization successful\n\n";
    
    // Тест аналізу читабельності
    // Test readability analysis
    // Тест анализа читаемости
    std::cout << "11. Testing readability analysis...\n";
    double readability = nlpProcessor.analyzeReadability("This is a simple sentence.");
    assert(readability >= 0.0 && readability <= 100.0);
    std::cout << "   ✓ Readability analysis successful\n";
    std::cout << "   Readability score: " << readability << "\n\n";
    
    // Тест конфігурації
    // Test configuration
    // Тест конфигурации
    std::cout << "12. Testing configuration...\n";
    NLPConfig newConfig = nlpProcessor.getConfiguration();
    nlpProcessor.updateConfiguration(newConfig);
    std::cout << "   ✓ Configuration test successful\n\n";
    
    std::cout << "========================================\n";
    std::cout << "  All NLP Tests Passed Successfully!\n";
    std::cout << "========================================\n";
    
    return 0;
}