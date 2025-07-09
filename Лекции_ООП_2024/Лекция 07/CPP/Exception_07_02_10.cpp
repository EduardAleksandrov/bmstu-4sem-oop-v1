#include <iostream>
#include <stdexcept>
#include <exception>
#include <string>
#include <fstream>

// выводит пояснительную строку исключения. Если исключение вложено,
// выполняет рекурсию, чтобы распечатать объяснение удерживаемого исключения
void print_exception(const std::exception& e, int level = 0)
{
    std::cerr << std::string(level, ' ') << level << " exception: " << e.what() << std::endl;
    try
    {
        std::rethrow_if_nested(e);
    }
    catch (const std::exception& nestedException)
    {
        print_exception(nestedException, level + 1);
    }
    catch (...) {}
}

// пример функции, которая перехватывает исключение и помещает его во вложенное исключение
void open_file(const std::string& s)
{
    try
    {
        std::ifstream file(s);
        file.exceptions(std::ios_base::failbit);
    }
    catch (...)
    {
        std::throw_with_nested(std::runtime_error("Couldn't open " + s));
    }
}

// пример функции, которая перехватывает исключение и помещает его во вложенное исключение
void run()
{
    try
    {
        open_file("nonexistent.file");
    }
    catch (...)
    {
        std::throw_with_nested(std::runtime_error("run() failed"));
    }
}

// запускает приведенный выше пример функции и печатает перехваченное исключение
int main()
{
    try
    {
        run();
    }
    catch (const std::exception& e)
    {
        print_exception(e);
    }
}
