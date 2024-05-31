#pragma once
#include <set>

class HeapSTLMultiset{
private:
    std::multiset<int> m_multiset;
public:
    void insert(int value);
    int getMin() const;
    int deleteAndGetMin();
    HeapSTLMultiset operator + (const HeapSTLMultiset& other);
    int size();
};
