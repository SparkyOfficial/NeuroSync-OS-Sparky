#ifndef NATURAL_LANGUAGE_PROCESSING_H
#define NATURAL_LANGUAGE_PROCESSING_H

#include <string>
#include <vector>
#include <map>
#include <memory>
#include <algorithm>
#include <regex>

// NaturalLanguageProcessing.h
// Модуль обробки природної мови для NeuroSync OS Sparky
// Natural language processing module for NeuroSync OS Sparky
// Модуль обработки естественного языка для NeuroSync OS Sparky

namespace NeuroSync {
namespace NLP {

    // Частина мови
    // Part of speech
    // Часть речи
    enum class PartOfSpeech {
        NOUN,           // Іменник / Noun / Существительное
        VERB,           // Дієслово / Verb / Глагол
        ADJECTIVE,      // Прикметник / Adjective / Прилагательное
        ADVERB,         // Прислівник / Adverb / Наречие
        PRONOUN,        // Займенник / Pronoun / Местоимение
        PREPOSITION,    // Прийменник / Preposition / Предлог
        CONJUNCTION,    // Сполучник / Conjunction / Союз
        INTERJECTION,   // Вигук / Interjection / Междометие
        ARTICLE,        // Артикль / Article / Артикль
        NUMERAL,        // Числівник / Numeral / Числительное
        UNKNOWN         // Невідомо / Unknown / Неизвестно
    };

    // Мовний токен
    // Linguistic token
    // Лингвистический токен
    struct Token {
        std::string text;               // Текст токена / Token text / Текст токена
        PartOfSpeech pos;              // Частина мови / Part of speech / Часть речи
        int position;                  // Позиція в реченні / Position in sentence / Позиция в предложении
        std::map<std::string, double> features; // Додаткові ознаки / Additional features / Дополнительные признаки
        
        Token(const std::string& t, PartOfSpeech p, int pos) 
            : text(t), pos(p), position(pos) {}
    };

    // Сентимент
    // Sentiment
    // Сентимент
    enum class Sentiment {
        VERY_NEGATIVE,  // Дуже негативний / Very negative / Очень негативный
        NEGATIVE,       // Негативний / Negative / Негативный
        NEUTRAL,        // Нейтральний / Neutral / Нейтральный
        POSITIVE,       // Позитивний / Positive / Позитивный
        VERY_POSITIVE   // Дуже позитивний / Very positive / Очень позитивный
    };

    // Результат аналізу сентименту
    // Sentiment analysis result
    // Результат анализа сентимента
    struct SentimentResult {
        Sentiment sentiment;            // Сентимент / Sentiment / Сентимент
        double confidence;             // Впевненість / Confidence / Уверенность
        std::map<Sentiment, double> scores; // Оцінки для всіх сентиментів / Scores for all sentiments / Оценки для всех сентиментов
        
        SentimentResult() : sentiment(Sentiment::NEUTRAL), confidence(0.0) {}
    };

    // Іменна сутність
    // Named entity
    // Именованная сущность
    struct NamedEntity {
        std::string text;               // Текст сутності / Entity text / Текст сущности
        std::string type;              // Тип сутності / Entity type / Тип сущности
        int startPosition;             // Початкова позиція / Start position / Начальная позиция
        int endPosition;               // Кінцева позиція / End position / Конечная позиция
        double confidence;             // Впевненість / Confidence / Уверенность
        
        NamedEntity(const std::string& t, const std::string& ty, int start, int end, double conf)
            : text(t), type(ty), startPosition(start), endPosition(end), confidence(conf) {}
    };

    // Результат виділення іменованих сутностей
    // Named entity recognition result
    // Результат выделения именованных сущностей
    struct NERResult {
        std::vector<NamedEntity> entities;  // Виділені сутності / Extracted entities / Выделенные сущности
        double confidence;                 // Загальна впевненість / Overall confidence / Общая уверенность
        
        NERResult() : confidence(0.0) {}
    };

    // Мовний профіль
    // Language profile
    // Языковой профиль
    struct LanguageProfile {
        std::string language;                   // Мова / Language / Язык
        double confidence;                     // Впевненість / Confidence / Уверенность
        std::map<std::string, int> ngrams;     // N-грами / N-grams / N-граммы
        std::vector<std::string> commonWords;  // Поширені слова / Common words / Распространенные слова
        
        LanguageProfile() : confidence(0.0) {}
    };

    // Налаштування NLP
    // NLP configuration
    // Настройки NLP
    struct NLPConfig {
        bool enableStemming;           // Увімкнути стемінг / Enable stemming / Включить стемминг
        bool enableLemmatization;      // Увімкнути лематизацію / Enable lemmatization / Включить лемматизацию
        bool enablePOS;               // Увімкнути частини мови / Enable part of speech / Включить части речи
        bool enableNER;               // Увімкнути виділення сутностей / Enable named entity recognition / Включить выделение сущностей
        bool enableSentiment;         // Увімкнути аналіз сентименту / Enable sentiment analysis / Включить анализ сентимента
        std::string defaultLanguage;  // Мова за замовчуванням / Default language / Язык по умолчанию
        size_t maxTokens;             // Максимальна кількість токенів / Maximum token count / Максимальное количество токенов
        
        NLPConfig() 
            : enableStemming(true), enableLemmatization(true), enablePOS(true), 
              enableNER(true), enableSentiment(true), defaultLanguage("en"), maxTokens(10000) {}
    };

    // Модуль обробки природної мови
    // Natural language processing module
    // Модуль обработки естественного языка
    class NaturalLanguageProcessor {
    public:
        NaturalLanguageProcessor();
        ~NaturalLanguageProcessor();
        
        // Ініціалізація процесора
        // Initialize processor
        // Инициализация процессора
        bool initialize(const NLPConfig& config = NLPConfig());
        
        // Токенізація тексту
        // Tokenize text
        // Токенизация текста
        std::vector<Token> tokenize(const std::string& text);
        
        // Лематизація тексту
        // Lemmatize text
        // Лемматизация текста
        std::string lemmatize(const std::string& word);
        
        // Стемінг тексту
        // Stem text
        // Стемминг текста
        std::string stem(const std::string& word);
        
        // Визначення частин мови
        // Part of speech tagging
        // Определение частей речи
        std::vector<Token> posTag(const std::vector<Token>& tokens);
        
        // Аналіз сентименту
        // Sentiment analysis
        // Анализ сентимента
        SentimentResult analyzeSentiment(const std::string& text);
        
        // Виділення іменованих сутностей
        // Named entity recognition
        // Выделение именованных сущностей
        NERResult recognizeEntities(const std::string& text);
        
        // Визначення мови
        // Language detection
        // Определение языка
        LanguageProfile detectLanguage(const std::string& text);
        
        // Переклад тексту
        // Translate text
        // Перевод текста
        std::string translate(const std::string& text, const std::string& targetLanguage);
        
        // Виділення ключових слів
        // Extract keywords
        // Выделение ключевых слов
        std::vector<std::string> extractKeywords(const std::string& text);
        
        // Підсумовування тексту
        // Summarize text
        // Резюмирование текста
        std::string summarize(const std::string& text, size_t sentenceCount = 3);
        
        // Аналіз читабельності
        // Readability analysis
        // Анализ читаемости
        double analyzeReadability(const std::string& text);
        
        // Отримання конфігурації
        // Get configuration
        // Получение конфигурации
        NLPConfig getConfiguration() const;
        
        // Оновлення конфігурації
        // Update configuration
        // Обновление конфигурации
        void updateConfiguration(const NLPConfig& config);
        
    private:
        NLPConfig configuration;                    // Конфігурація / Configuration / Конфигурация
        std::map<std::string, std::string> dictionary; // Словник для лематизації / Dictionary for lemmatization / Словарь для лемматизации
        std::map<std::string, std::string> stemRules;  // Правила стемінгу / Stemming rules / Правила стемминга
        std::map<std::string, Sentiment> sentimentLexicon; // Лексикон сентименту / Sentiment lexicon / Лексикон сентимента
        std::map<std::string, std::string> translationModel; // Модель перекладу / Translation model / Модель перевода
        std::map<std::string, std::vector<std::string>> languageProfiles; // Профілі мов / Language profiles / Профили языков
        
        // Внутрішні методи
        // Internal methods
        // Внутренние методы
        std::vector<std::string> splitSentences(const std::string& text);
        std::vector<std::string> splitWords(const std::string& sentence);
        bool isStopWord(const std::string& word);
        double calculateTFIDF(const std::string& word, const std::vector<std::string>& documents);
        std::string preprocessText(const std::string& text);
        PartOfSpeech getPartOfSpeech(const std::string& word);
        std::vector<std::pair<std::string, double>> rankSentences(const std::vector<std::string>& sentences);
    };

} // namespace NLP
} // namespace NeuroSync

#endif // NATURAL_LANGUAGE_PROCESSING_H