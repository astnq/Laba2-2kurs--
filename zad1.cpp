#include "include/stack.h"
#include <vector>
int evaluateRPN(const vector<string>& tokens) {
    stack<int> stack;

    for (const string& token : tokens) {
        if (token == "+" || token == "-" || token == "*" || token == "/") {
            int b = stack.top(); stack.pop(); // Второй операнд
            int a = stack.top(); stack.pop(); // Первый операнд

            if (token == "+") stack.push(a + b);
            else if (token == "-") stack.push(a - b);
            else if (token == "*") stack.push(a * b);
            else if (token == "/") stack.push(a / b);
        } else {
            // Преобразуем строку в число и помещаем его в стек
            stack.push(stoi(token));
        }
    }

    // В конце в стеке остается одно значение - результат
    return stack.top();
}

int main() {
    string input;
    cout << "Введите выражение в постфиксной записи (разделяйте элементы пробелами): ";
    getline(cin, input);
    
    istringstream iss(input);
    vector<string> tokens;
    string token;

    // Читаем элементы из входной строки
    while (iss >> token) {
        tokens.push_back(token);
    }

    try {
        int result = evaluateRPN(tokens);
        cout << "Результат: " << result << endl;
    } catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
    }

    return 0;
}