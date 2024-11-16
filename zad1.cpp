#include "include/stack.h"
// VAR_3
#include "stack.cpp"

int priority(char arif) { //Функия для определения приоритета оператора
    if (arif == '+' || arif == '-') return 1;
    if (arif == '*' || arif == '/') return 2;
    return 0;
}

string infixToPostfix(const string& infix) { //Функция для преобразования инфиксного в постфиксное выражение
    Stack stack;
    string output;

    for(char operand : infix) {
        if((operand >= '0' && operand <= '9') || (operand >= 'a' && operand <= 'z') || (operand >= 'A' && operand <= 'Z')) { //Проверяем если операнд цифра или буква, то добавляем его в строку
            output += operand;
        } else if (operand == '('){ // Если операнд открывающая скобка, помещаем ее в стек
            stack.push(string(1, operand));
        } else if(operand == ')') { // Если операнд закрывающая скобка, извлекаем из стека до открывающей скобки
            while(!stack.isEmpty() && stack.peek() != "(") {
                output +=stack.pop();
            }
            stack.pop(); // Удаляем '(' из стека
        } else { // Если токен — оператор
            while(!stack.isEmpty() && priority(stack.peek()[0]) >= priority(operand)) {
                output += stack.pop();
            }
            stack.push(string(1, operand));
        } 
    }

    while(!stack.isEmpty()) { // Извлекаем оставшиеся операторы из стека
        output += stack.pop();
    }
    return output;

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
