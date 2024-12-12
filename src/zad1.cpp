// VAR_1
#include "stack.cpp"

// Функция для определения приоритета операторов
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// Функция для преобразования инфиксного выражения в постфиксное
string infixToPostfix(const string& expression) { 
    stack<char> operators; // Стек для операторов
    stringstream result; // Поток вывода для постфиксной записи
    
    for (size_t i = 0; i < expression.size(); i++) {
        char ch = expression[i];

        
        if (isdigit(ch)) {
            // Если текущий символ - цифра, добавляем ее в результат
            result << ch;
            // Проверяем следующий символ, если это не цифра, то добавляем пробел
            if (i + 1 == expression.size() || !isdigit(expression[i + 1])) {
                result << ' ';
            }
        } else if (ch == ' ') {
            continue;  // Пропускаем пробелы
        } else if (ch == '(') {
            operators.push(ch);  // Открывающая скобка
        } else if (ch == ')') {
            // Выталкиваем операторы до открывающей скобки
            while (!operators.empty() && operators.top() != '(') {
                result << operators.top() << ' ';
                operators.pop();
            }
            operators.pop();  // Убираем открывающую скобку
        } else {
            // Для остальных операторов
            while (!operators.empty() && precedence(operators.top()) >= precedence(ch)) {
                result << operators.top() << ' ';
                operators.pop();
            }
            operators.push(ch);  // Добавляем текущий оператор
        }
    }

    // Выталкиваем все оставшиеся операторы в стек
    while (!operators.empty()) {
        result << operators.top() << ' ';
        operators.pop();
    }

    return result.str();
}

// Функция для вычисления постфиксного выражения
int calculatePostfix(const string& expression) {
    stack<int> s;
    stringstream ss(expression);
    string token;

    while (ss >> token) {
        if (isdigit(token[0])) {
            s.push(stoi(token));  // Если это число, добавляем его в стек
        } else {
            if (s.size() < 2) {
                throw runtime_error("Некорректное выражение");
            }
            
            int b = s.top(); s.pop();  // Извлекаем два числа из стека
            int a = s.top(); s.pop();
            
            // Применяем оператор к числам
            if (token == "+") {
                s.push(a + b);
            } else if (token == "-") {
                s.push(a - b);
            } else if (token == "*") {
                s.push(a * b);
            } else if (token == "/") {
                if (b == 0) {
                    throw runtime_error("Деление на ноль");
                }
                s.push(a / b);
            } else {
                throw runtime_error("Неподдерживаемая операция: " + token);
            }
        }
    }

    if (s.size() != 1) {
        throw runtime_error("Некорректное выражение");
    }

    return s.top(); // Возвращаем результат
}

int main() {
    string expression;
    cout << "Введите инфиксное выражение : ";
    getline(cin, expression);

    try {
        string postfix = infixToPostfix(expression);  // Преобразуем в постфиксную форму
        cout << "Постфиксное выражение: " << postfix << endl;
        int result = calculatePostfix(postfix);  // Вычисляем результат
        cout << "Результат: " << result << endl;
    } catch (const exception& e) {
        cout << "Ошибка: " << e.what() << endl;
    }

    return 0;
}