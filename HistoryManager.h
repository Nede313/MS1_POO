#ifndef HISTORYMANAGER_H
#define HISTORYMANAGER_H

#include <vector>
#include <iostream>
#include <numeric>

template <typename T>
class HistoryLog {
    std::vector<T> entries;
public:
    void addEntry(T item) { entries.push_back(item); }
    void printStatus(const std::string& label) const {
        std::cout << "[LOG " << label << "] Intrari: " << entries.size() << "\n";
    }
};

template <typename T>
T calculateSum(const std::vector<T>& values) {
    T total = 0;
    for (const auto& v : values) total += v;
    return total;
}
#endif