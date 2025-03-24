#include <iostream>

class QThread {
public:
    void start() 
    {
        // Код для создания нового потока
        run(); // Вызов метода run()
    }

protected:
    virtual void run() 
    {
        // Базовая реализация (может быть пустой)
    }
};

class MyThread : public QThread {
protected:
    void run() override 
    {
        // Ваша реализация
        std:: cout << "Mythread" << "\n";
    }
    };

class NewThread : public MyThread {
protected:
    void run() override 
    {
        // Ваша реализация
        std:: cout << "Newthread 2" << "\n";
    }
    };


int main()
{
    QThread* th = new NewThread();
    th->start();

    return 0;
}