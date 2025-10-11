#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <vector>
#include <queue>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>
#include <stdexcept>
#include <atomic>

// ThreadPool.h
// Пул потоків для NeuroSync OS Sparky
// Thread pool for NeuroSync OS Sparky
// Пул потоков для NeuroSync OS Sparky

namespace NeuroSync {

    class ThreadPool {
    public:
        // Конструктор
        // Constructor
        // Конструктор
        explicit ThreadPool(size_t threads);

        // Деструктор
        // Destructor
        // Деструктор
        ~ThreadPool();

        // Видалення конструктора копіювання та оператора присвоєння
        // Delete copy constructor and assignment operator
        // Удаление конструктора копирования и оператора присваивания
        ThreadPool(const ThreadPool&) = delete;
        ThreadPool& operator=(const ThreadPool&) = delete;

        // Додавання завдання до пулу
        // Add task to pool
        // Добавление задачи в пул
        template<class F, class... Args>
        auto enqueue(F&& f, Args&&... args) 
            -> std::future<typename std::result_of<F(Args...)>::type>;

        // Отримання кількості потоків
        // Get thread count
        // Получение количества потоков
        size_t getThreadCount() const;

        // Отримання кількості завдань у черзі
        // Get queue size
        // Получение количества задач в очереди
        size_t getQueueSize();

        // Зупинка пулу потоків
        // Stop thread pool
        // Остановка пула потоков
        void stop();

        // Перезапуск пулу потоків
        // Restart thread pool
        // Перезапуск пула потоков
        void restart();

    private:
        // Вектор робочих потоків
        // Vector of worker threads
        // Вектор рабочих потоков
        std::vector<std::thread> workers;

        // Черга завдань
        // Task queue
        // Очередь задач
        std::queue<std::function<void()>> tasks;

        // Мутекс для синхронізації доступу до черги
        // Mutex for synchronizing access to queue
        // Мьютекс для синхронизации доступа к очереди
        std::mutex queueMutex;

        // Змінна умови для сповіщення потоків про нові завдання
        // Condition variable to notify threads about new tasks
        // Переменная условия для оповещения потоков о новых задачах
        std::condition_variable condition;

        // Атомарний прапорець зупинки
        // Atomic stop flag
        // Атомарный флаг остановки
        std::atomic<bool> stopFlag;

        // Атомарний лічильник активних потоків
        // Atomic counter of active threads
        // Атомарный счетчик активных потоков
        std::atomic<size_t> activeThreads;
    };

    // Реалізація шаблонної функції enqueue
    // Implementation of enqueue template function
    // Реализация шаблонной функции enqueue
    template<class F, class... Args>
    auto ThreadPool::enqueue(F&& f, Args&&... args) 
        -> std::future<typename std::result_of<F(Args...)>::type> {
        using returnType = typename std::result_of<F(Args...)>::type;

        auto task = std::make_shared<std::packaged_task<returnType()>>(
            std::bind(std::forward<F>(f), std::forward<Args>(args)...)
        );

        std::future<returnType> res = task->get_future();
        {
            std::unique_lock<std::mutex> lock(queueMutex);

            // Не додаємо завдання, якщо пул зупинено
            // Don't add task if pool is stopped
            // Не добавляем задачу, если пул остановлен
            if (stopFlag.load()) {
                throw std::runtime_error("enqueue on stopped ThreadPool");
            }

            tasks.emplace([task]() { (*task)(); });
        }
        condition.notify_one();
        return res;
    }

} // namespace NeuroSync

#endif // THREAD_POOL_H