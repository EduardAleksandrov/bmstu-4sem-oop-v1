#include <iostream>
#include <stack>
#include <tuple>

int Ackermann_rec(int m, int n) {
    if (m == 0) {
        return n + 1; // Условие A(0, n) = n + 1
    } else if (m > 0 && n == 0) {
        return Ackermann_rec(m - 1, 1); // Условие A(m, 0) = A(m - 1, 1)
    } else if (m > 0 && n > 0) {
        return Ackermann_rec(m - 1, Ackermann_rec(m, n - 1)); // Условие A(m, n) = A(m - 1, A(m, n - 1))
    }
    return -1; // На всякий случай, если условия не выполнены
}

int Ackermann(int m, int n) {
    std::stack<std::tuple<int, int>> s; // Стек для хранения параметров (m, n)
    s.push(std::make_tuple(m, n)); // Начальные значения

    while (!s.empty()) {
        std::tie(m, n) = s.top(); // Извлекаем верхние значения из стека
        s.pop();

        if (m == 0) {
            return n + 1; // Условие A(0, n) = n + 1
        } else if (m > 0 && n == 0) {
            s.push(std::make_tuple(m - 1, 1)); // Условие A(m, 0) = A(m - 1, 1)
        } else if (m > 0 && n > 0) {
            // Условие A(m, n) = A(m - 1, A(m, n - 1))
            s.push(std::make_tuple(m - 1, -1)); // Сохраняем m - 1 и временно ставим n как -1
            s.push(std::make_tuple(m, n - 1)); // Сохраняем A(m, n - 1)
            // После того, как мы извлечем A(m, n - 1), мы вернемся к этому состоянию
        } else {
            return -1; // На всякий случай, если условия не выполнены
        }

        // Если n было временно установлено в -1, это означает, что мы должны обработать A(m, n - 1)
        if (n == -1) {
            n = std::get<1>(s.top()); // Получаем значение n из стека
            s.pop();
            s.push(std::make_tuple(m - 1, n)); // Теперь мы можем вызвать A(m - 1, A(m, n - 1))
        }
    }

    return -1; // На всякий случай, если условия не выполнены
}

int Ackermann_iter(int m, int n) {
    std::stack<std::tuple<int, int>> s;
    s.push(std::make_tuple(m, n));

    while (!s.empty()) {
        std::tie(m, n) = s.top();
        s.pop();

        if (m == 0) {
            return n + 1; // Условие A(0, n) = n + 1
        } else if (m > 0 && n == 0) {
            s.push(std::make_tuple(m - 1, 1)); // Условие A(m, 0) = A(m - 1, 1)
        } else if (m > 0 && n > 0) {
            s.push(std::make_tuple(m - 1, -1)); // Сохраняем A(m - 1, A(m, n - 1))
            s.push(std::make_tuple(m, n - 1)); // Сохраняем A(m, n - 1)
        } else if (n == -1) {
            // Восстанавливаем значение n для A(m, n - 1)
            n = std::get<1>(s.top());
            s.pop();
            s.push(std::make_tuple(m - 1, n)); // Теперь вызываем A(m - 1, A(m, n - 1))
        }
    }

    return -1; // На всякий случай, если условия не выполнены
}

int Ackermann_iters(int m, int n) {
    std::stack<std::tuple<int, int>> s;
    s.push(std::make_tuple(m, n));

    while (!s.empty()) {
        std::tie(m, n) = s.top();
        s.pop();

        if (m == 0) {
            n += 1; // Условие A(0, n) = n + 1
            if (s.empty()) {
                return n; // Если стек пуст, возвращаем результат
            }
            // Если стек не пуст, продолжаем
            std::tie(m, n) = s.top();
            s.pop();
            s.push(std::make_tuple(m - 1, n)); // Переходим к A(m - 1, n)
        } else if (m == 1) {
            n += 2; // Условие A(1, n) = n + 2
            if (s.empty()) {
                return n; // Если стек пуст, возвращаем результат
            }
            std::tie(m, n) = s.top();
            s.pop();
            s.push(std::make_tuple(m - 1, n)); // Переходим к A(m - 1, n)
        } else if (m == 2) {
            n = 2 * n + 3; // Условие A(2, n) = 2n + 3
            if (s.empty()) {
                return n; // Если стек пуст, возвращаем результат
            }
            std::tie(m, n) = s.top();
            s.pop();
            s.push(std::make_tuple(m - 1, n)); // Переходим к A(m - 1, n)
        } else if (m > 2) {
            s.push(std::make_tuple(m - 1, -1)); // Сохраняем A(m - 1, A(m, n - 1))
            s.push(std::make_tuple(m, n - 1)); // Сохраняем A(m, n - 1)
        }
    }

    return -1; // На всякий случай, если условия не выполнены
}
// work before 4
int Ackermannss(int m, int n) {
    std::stack<std::tuple<int, int>> stack;
    stack.push(std::make_tuple(m, n));

    while (!stack.empty()) {
        std::tie(m, n) = stack.top();
        stack.pop();

        if (m == 0) {
            return n + 1;
        } else if (m == 1) {
            return n + 2;
        } else if (m == 2) {
            return 2 * n + 3;
        } else if (m == 3) {
            return (1 << (n + 3)) - 3; // 2^(n+3) - 3
        } else {
            // Для m > 3, используем стек для хранения промежуточных значений
            stack.push(std::make_tuple(m - 1, 1));
            if (n > 0) {
                stack.push(std::make_tuple(m, n - 1));
            }
            //stack.push(std::make_tuple(m, n - 1));
        }


    }

    return -1; // На случай, если функция не завершится
}
int Ackermannt(int m, int n) {
    std::stack<std::tuple<int, int>> stack;
    stack.push(std::make_tuple(m, n));

    while (!stack.empty()) {
        std::tie(m, n) = stack.top();
        stack.pop();

        if (m == 0 && n!=-1) {
            return n + 1; // Условие 1
        } else if (n == 0 && m>0) {
            // Условие 2: A(m, 0) = A(m - 1, 1)
            stack.push(std::make_tuple(m - 1, 1));
        } else if(n>0 && m>0){
            // Условие 3: A(m, n) = A(m - 1, A(m, n - 1))
            // Сначала добавляем A(m, n - 1) в стек
            stack.push(std::make_tuple(m, n - 1));
            // Затем добавляем A(m - 1, результат A(m, n - 1)
            stack.push(std::make_tuple(m - 1, -1)); // Используем -1 как маркер
        }

        // Обработка результата
        if (n == -1) {
            // Это означает, что мы только что вернулись из A(m, n - 1)
            // Теперь мы можем обработать результат
            n = std::get<1>(stack.top()); // Получаем n из стека
            stack.pop(); // Убираем его из стека
            stack.push(std::make_tuple(m - 1, n)); // Теперь добавляем A(m - 1, результат)
        }
    }

    return -1; // На случай, если функция не завершится
}

int Ackermannr(int m, int n) {
    std::stack<std::tuple<int, int>> stack;
    stack.push(std::make_tuple(m, n));

    while (!stack.empty()) {
        std::tie(m, n) = stack.top();
        stack.pop();

        if (m == 0) {
            return n + 1; // Condition 1: A(0, n) = n + 1
        } else if (m == 1) {
            return n + 2; // Condition 1: A(1, n) = n + 2
        } else if (m == 2) {
            return 2 * n + 3; // Condition 1: A(2, n) = 2n + 3
        } else if (m == 3) {
            return (1 << (n + 3)) - 3; // Condition 1: A(3, n) = 2^(n + 3) - 3
        } else {
            // For m > 3, we need to handle the cases
            if (n == 0) {
                // Condition 2: A(m, 0) = A(m - 1, 1)
                stack.push(std::make_tuple(m - 1, 1));
            } else {
                // Condition 3: A(m, n) = A(m - 1, A(m, n - 1))
                // First, we need to push (m, n - 1) to compute A(m, n - 1)
                stack.push(std::make_tuple(m, n - 1));
                // Then, we push (m - 1, result of A(m, n - 1)) as a placeholder
                stack.push(std::make_tuple(m - 1, -1)); // -1 as a marker
            }
        }

        // Handle the case when we return from A(m, n - 1)
        if (n == -1) {
            // We need to get the last value of n from the stack
            n = std::get<1>(stack.top()); // Get the n value from the top of the stack
            stack.pop(); // Remove it from the stack
            stack.push(std::make_tuple(m - 1, n)); // Now we can push (m - 1, result)
        }
    }

    return -1; // In case the function does not terminate
}

int ackermanni(int m, int n) {
    std::stack<int> s;
    s.push(m);
    while(!s.empty()) {
        m = s.top();
        s.pop();
        if(m == 0) {
            n++;
        }
        else if(n == 0) {
            s.push(--m);
            n = 1;
        }
        else {
            s.push(m-1);
            s.push(m);
            n--;
        }
    }
    return n;
}


int main() {
    int m, n;
    std::cout << "Введите m и n: ";
    std::cin >> m >> n;

    std::cout << "A_rec(" << m << ", " << n << ") = " << Ackermann_rec(m, n) << std::endl;
    std::cout << "A(" << m << ", " << n << ") = " << ackermanni(m, n) << std::endl;


    return 0;
}