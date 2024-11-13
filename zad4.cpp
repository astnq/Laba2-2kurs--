//var 1
#include "include/array.h"
#include <vector>
void printSubsets(const vector<char>& arr) {
    int n = arr.size();
    set<vector<char>> subsets; // Используем set для хранения уникальных подмассивов

    // Генерация подмножеств с помощью битовых масок
    for (int i = 0; i < (1 << n); ++i) {
        vector<char> subset;
        for (int j = 0; j < n; ++j) {
            // Проверяем, установлен ли j-ый бит в i
            if (i & (1 << j)) {
                subset.push_back(arr[j]);
            }
        }
        subsets.insert(subset); // Добавляем подмассив в множество уникальных подмассивов
    }

    // Выводим уникальные подмассивы
    for (const auto& subset : subsets) {
        cout << "{ ";
        for (const auto& elem : subset) {
            cout << elem << " ";
        }
        cout << "}" << endl;
    }
}

int main() {
    std::vector<char> S = {'x', 'y', 'z'};
    
    std::cout << "All unique subsets:" << endl;
    printSubsets(S);
    
    return 0;
}
