//var 4
#include "include/hastable.h"
#include <vector>

string intToRoman(int num) {
    // Массив римских символов и их соответствующих значений
    vector<pair<int, string>> valueMap = {
        {1000, "M"},
        {900, "CM"},
        {500, "D"},
        {400, "CD"},
        {100, "C"},
        {90, "XC"},
        {50, "L"},
        {40, "XL"},
        {10, "X"},
        {9, "IX"},
        {5, "V"},
        {4, "IV"},
        {1, "I"}
    };

    string result;

    // Перебираем значения от большего к меньшему
    for (auto& pair : valueMap) {
        while (num >= pair.first) {
            result += pair.second; // Добавляем римский символ
            num -= pair.first;     // Уменьшаем число
        }
    }

    return result;
}

int main() {
    int number;
    cout << "Введите число: ";
    cin >> number;

    string roman = intToRoman(number);
    cout << "Римская цифра: " << roman << endl;

    return 0;
}
