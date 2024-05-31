#include "HeapSTLMultiset.h"
#include <cassert>

void HeapSTLMultiset::insert(int value) {
    m_multiset.insert(value);
}

int  HeapSTLMultiset::getMin() const {
    assert(!m_multiset.empty());
    return *m_multiset.begin();
}

int  HeapSTLMultiset::deleteAndGetMin() {
    assert(!m_multiset.empty());
    auto it = m_multiset.begin();
    int mn = *it;
    m_multiset.erase(it);
    return mn;
}

HeapSTLMultiset  HeapSTLMultiset::operator + (const HeapSTLMultiset& other) {
    HeapSTLMultiset sum;
    sum.m_multiset = m_multiset;
    for (auto& value : other.m_multiset) {
        sum.insert(value);
    }
    return sum;
};

int HeapSTLMultiset::size() {
    return m_multiset.size();
}
