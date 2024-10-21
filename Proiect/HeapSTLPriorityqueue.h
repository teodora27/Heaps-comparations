#pragma once
#include <queue>
#include <vector>

class HeapSTLPriorityqueue {
private:
    std::priority_queue<int, std::vector<int>, std::greater<int>> m_queue;
public:
    void insert(int value);
    int getMin() const;
    int deleteAndGetMin();
    HeapSTLPriorityqueue operator + (const HeapSTLPriorityqueue& other);
    int size();
};
