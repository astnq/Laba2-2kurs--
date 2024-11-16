#include "array.cpp"

bool hasCorrectWord(const string& word, Array& dictionary) {
    for (size_t i = 0; i < dictionary.getSize(); ++i) {
        if (dictionary.getIndex(i) == word) {
            return true; // Слово найдено в словаре
        }
    }
    return false; // Слово не найдено в словаре
}

int countWord(const string& word) {
    int count = 0;
    for (char symbol : word) { // Цикл который перебирает каждый символ в строчке 
        if (symbol >= 'A' && symbol <= 'Z') {
            count++;
        }
    }
    return count;
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
