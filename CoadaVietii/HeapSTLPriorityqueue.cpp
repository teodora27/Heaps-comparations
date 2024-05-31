#include "HeapSTLPriorityqueue.h"
#include <cassert>

void HeapSTLPriorityqueue::insert(int value) {
    m_queue.push(value);
}

int  HeapSTLPriorityqueue::getMin() const {
    assert(!m_queue.empty());
    return m_queue.top();
}

int  HeapSTLPriorityqueue::deleteAndGetMin() {
    assert(!m_queue.empty());
    int mn = m_queue.top();
    m_queue.pop();
    return mn;
}

HeapSTLPriorityqueue  HeapSTLPriorityqueue::operator + (const HeapSTLPriorityqueue& other) {
    HeapSTLPriorityqueue sum;
    sum.m_queue = m_queue;
    std::priority_queue<int, std::vector<int>, std::greater<int>> p2 = other.m_queue;
    while (!p2.empty()) {
        sum.m_queue.push(p2.top());
        p2.pop();
    }
    return sum;
};

int HeapSTLPriorityqueue::size() {
    return m_queue.size();
}
