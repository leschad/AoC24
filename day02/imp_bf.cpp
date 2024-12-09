#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

bool lineCheckSimple(std::vector<int>& numbers) {
    bool ascending = false, descending = false;
    for (size_t i = 1; i < numbers.size(); i++) {
        int diff = abs(numbers[i] - numbers[i - 1]);
        if (diff < 1 || diff > 3) {
            return false;
        } else if (numbers[i] < numbers[i - 1]) {
            if (ascending) {
                return false;
            } else {
                descending = true;
            }
        } else if (numbers[i] > numbers[i - 1]) {
            if (descending) {
                return false;
            } else {
                ascending = true;
            }
        }
    }

    return true;
}

bool lineCheck(const std::string& line) {
    std::istringstream iss(line);
    std::vector<int> numbers;
    int num;

    while (iss >> num) {
        numbers.push_back(num);
    }

    for (size_t i = 0; i<numbers.size(); i++){
        std::vector<int> tmp = numbers;
        tmp.erase(tmp.begin()+i);
        if (lineCheckSimple(tmp)) {
            return true;
        }
    }

    return false;
}

int main() {
    std::ifstream inputFile("test.txt");
    std::string line;

    int result = 0;

    while (std::getline(inputFile, line)) {
        if (lineCheck(line)) {
            result++;
        }
    }
    std::cout << result << std::endl;

    return 0;
}