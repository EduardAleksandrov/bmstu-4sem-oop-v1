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
class One
{
private:
    int a;
protected:
    int b;
public:
    One(): a{5}, b{6} {}
    int f()
    {
        return a;
    }
};

class Two: private One
{
    private:    
        int c;
    protected:
        int t;
    public:
    Two(): c{7}, t{8} {}
    int g()
    {
        return b;
    }
};

int main()
{
    Two t;
    std::cout << t.g() << "\n";

    QThread* th = new MyThread();
    th->start();

    return 0;
}