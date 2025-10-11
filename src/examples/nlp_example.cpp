#include "../nlp/NaturalLanguageProcessing.h"
#include <iostream>
#include <string>

using namespace NeuroSync::NLP;

int main() {
    std::cout << "========================================\n";
    std::cout << "  NeuroSync Natural Language Processing Example\n";
    std::cout << "========================================\n\n";
    
    // Створення процесора обробки природної мови
    // Create natural language processor
    // Создание процессора обработки естественного языка
    NaturalLanguageProcessor nlpProcessor;
    
    // Ініціалізація процесора
    // Initialize processor
    // Инициализация процессора
    NLPConfig config;
    config.enableStemming = true;
    config.enableLemmatization = true;
    config.enablePOS = true;
    config.enableNER = true;
    config.enableSentiment = true;
    config.defaultLanguage = "en";
    
    if (!nlpProcessor.initialize(config)) {
        std::cerr << "Failed to initialize NLP processor" << std::endl;
        return 1;
    }
    
    std::cout << "NLP processor initialized successfully\n\n";
    
    // Приклад тексту для аналізу
    // Example text for analysis
    // Пример текста для анализа
    std::string sampleText = "Natural language processing is a fascinating field of artificial intelligence. "
                           "It combines computational linguistics with machine learning to enable computers "
                           "to understand, interpret, and generate human language. This technology has "
                           "revolutionary applications in various domains including chatbots, translation "
                           "services, and sentiment analysis. The development of advanced neural networks "
                           "has significantly improved the accuracy and capabilities of NLP systems.";
    
    std::cout << "Sample text: " << sampleText << "\n\n";
    
    // Токенізація
    // Tokenization
    // Токенизация
    std::cout << "1. Tokenization:\n";
    std::vector<Token> tokens = nlpProcessor.tokenize(sampleText);
    std::cout << "   Found " << tokens.size() << " tokens\n";
    for (size_t i = 0; i < std::min(size_t(10), tokens.size()); ++i) {
        std::cout << "   - " << tokens[i].text << " (POS: " << static_cast<int>(tokens[i].pos) << ")\n";
    }
    if (tokens.size() > 10) {
        std::cout << "   ... and " << (tokens.size() - 10) << " more tokens\n";
    }
    std::cout << "\n";
    
    // Лематизація
    // Lemmatization
    // Лемматизация
    std::cout << "2. Lemmatization:\n";
    std::vector<std::string> testWords = {"running", "better", "walking", "worse"};
    for (const auto& word : testWords) {
        std::string lemma = nlpProcessor.lemmatize(word);
        std::cout << "   " << word << " -> " << lemma << "\n";
    }
    std::cout << "\n";
    
    // Стемінг
    // Stemming
    // Стемминг
    std::cout << "3. Stemming:\n";
    for (const auto& word : testWords) {
        std::string stem = nlpProcessor.stem(word);
        std::cout << "   " << word << " -> " << stem << "\n";
    }
    std::cout << "\n";
    
    // Аналіз частин мови
    // Part of speech tagging
    // Анализ частей речи
    std::cout << "4. Part of Speech Tagging:\n";
    std::vector<Token> posTokens = nlpProcessor.posTag(tokens);
    for (size_t i = 0; i < std::min(size_t(10), posTokens.size()); ++i) {
        std::cout << "   " << posTokens[i].text << " -> POS: " << static_cast<int>(posTokens[i].pos) << "\n";
    }
    std::cout << "\n";
    
    // Аналіз сентименту
    // Sentiment analysis
    // Анализ сентимента
    std::cout << "5. Sentiment Analysis:\n";
    SentimentResult sentiment = nlpProcessor.analyzeSentiment(sampleText);
    std::cout << "   Overall sentiment: " << static_cast<int>(sentiment.sentiment) << "\n";
    std::cout << "   Confidence: " << sentiment.confidence << "\n\n";
    
    // Виділення іменованих сутностей
    // Named entity recognition
    // Выделение именованных сущностей
    std::cout << "6. Named Entity Recognition:\n";
    NERResult nerResult = nlpProcessor.recognizeEntities(sampleText);
    std::cout << "   Found " << nerResult.entities.size() << " entities\n";
    for (const auto& entity : nerResult.entities) {
        std::cout << "   - " << entity.text << " (" << entity.type << ")\n";
    }
    std::cout << "\n";
    
    // Визначення мови
    // Language detection
    // Определение языка
    std::cout << "7. Language Detection:\n";
    LanguageProfile languageProfile = nlpProcessor.detectLanguage(sampleText);
    std::cout << "   Detected language: " << languageProfile.language << "\n";
    std::cout << "   Confidence: " << languageProfile.confidence << "\n\n";
    
    // Виділення ключових слів
    // Keyword extraction
    // Выделение ключевых слов
    std::cout << "8. Keyword Extraction:\n";
    std::vector<std::string> keywords = nlpProcessor.extractKeywords(sampleText);
    std::cout << "   Found " << keywords.size() << " keywords:\n";
    for (const auto& keyword : keywords) {
        std::cout << "   - " << keyword << "\n";
    }
    std::cout << "\n";
    
    // Підсумовування
    // Summarization
    // Резюмирование
    std::cout << "9. Text Summarization:\n";
    std::string summary = nlpProcessor.summarize(sampleText, 2);
    std::cout << "   Summary: " << summary << "\n\n";
    
    // Аналіз читабельності
    // Readability analysis
    // Анализ читаемости
    std::cout << "10. Readability Analysis:\n";
    double readability = nlpProcessor.analyzeReadability(sampleText);
    std::cout << "   Readability score: " << readability << "/100\n\n";
    
    std::cout << "========================================\n";
    std::cout << "  NLP Example Completed Successfully!\n";
    std::cout << "========================================\n";
    
    return 0;
}