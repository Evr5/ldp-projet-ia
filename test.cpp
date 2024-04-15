#include <iostream>
#include <string>
#include <map>
#include <vector>

int main() {
    std::vector<int> numbers;
    for (int i = 0; i < 100; i++) {
        numbers.push_back(5);
        numbers.push_back(i);
    }

    std::map<int, int> numberCount;
    for (const float num : numbers) {
        numberCount[num]++;
    }

    // Afficher les résultats
    for (const auto& pair : numberCount) {
        std::cout << "Nombre " << pair.first << " : " << pair.second << " occurrences\n";
    }

    return 0;
}