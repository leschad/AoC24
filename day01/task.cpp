#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>
#include <algorithm>

void parseFile(const std::string& filename, std::vector<int>& column1, std::vector<int>& column2) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Unable to open file: " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        int num1, num2;
        if (iss >> num1 >> num2) {
            column1.push_back(num1);
            column2.push_back(num2);
        }
    }

    file.close();
}

void sortVec(std::vector<int>& vec) {
    std::sort(vec.begin(), vec.end());
}

size_t distanceVec(const std::vector<int>& column1, const std::vector<int>& column2){
    int len = column1.size();
    size_t dist = 0;

    for (int i = 0; i<len; i++){
        dist += abs(column1[i] - column2[i]);
    }

    return dist;
}

void histogramVector(std::vector<int>& vec, std::map<int,int>& histogram) {
    
    for (auto it = vec.begin(); it != vec.end(); it++) {
        auto loc = histogram.find(*it);
        if (loc != histogram.end()) {
            loc->second++;
        } else {
            histogram.insert(std::pair<int,int>{*it, 1});
        }
    }
}

size_t similarityScore(const std::vector<int>& vec, const std::map<int,int>& histogram) {
    size_t result = 0;

    for (auto it = vec.begin(); it != vec.end(); it++) {
        auto loc = histogram.find(*it);
        int multiplier = 0;

        if (loc != histogram.end()) {
            multiplier = loc->second;
        } else {
            multiplier = 0;
        }

        result += *it * multiplier;
    }

    return result;
}

int main() {
    std::vector<int> column1, column2;
    std::map<int,int> histogram;
    parseFile("input2.txt", column1, column2);

    histogramVector(column2, histogram);

    size_t result = similarityScore(column1, histogram);

    std::cout << result << std::endl;

    return 0;
}