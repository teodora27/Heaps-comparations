#pragma once
#include <vector>
#include <random>
#include <chrono>
#include <functional>

class Operation {
public:
    enum OperationType { INSERT, GET_MIN, DELETE_AND_GET_MIN, GET_SIZE };
    Operation(OperationType type, int value = 0) : m_opType(type), m_value(value) {}
    OperationType m_opType;
    int m_value;
};

std::vector<Operation> generateTestRandom(int numberOfElementsAtStart, int numberOfOperations, int maxValue) {
    std::vector<Operation> operations;
    std::mt19937 rng(228);
    std::uniform_int_distribution<int> dist(1, maxValue);
    for (int i = 0; i < numberOfElementsAtStart; i++) {
        operations.push_back({ Operation::INSERT, dist(rng) });
    }
    for (int i = 0; i < numberOfOperations; i++) {
        int type = rng() % 4;
        if (type == 0) {
            operations.push_back({ Operation::INSERT, dist(rng) });
        }
        if (type == 1) {
            operations.push_back({ Operation::GET_MIN });
        }
        if (type == 2) {
            operations.push_back({Operation::DELETE_AND_GET_MIN});
        }
        if (type == 3) {
            operations.push_back({ Operation::GET_SIZE });
        }
    }
    return operations;
}

std::vector<Operation> testInsertIncreasingInsertHeavy(int nrElementsAtStart) {
    std::vector<Operation> operations;
    for (int i = 1; i <= nrElementsAtStart; i++) {
        operations.push_back({ Operation::INSERT, (i + 1) });
    }
    return operations;
}

std::vector<Operation> testInsertDecreasingInsertHeavy(int nrElementsAtStart) {
    std::vector<Operation> operations;
    for (int i = 1; i <= nrElementsAtStart; i++) {
        operations.push_back({ Operation::INSERT, -(i + 1) });
    }
    return operations;
}

std::vector<Operation> generateTestMixedProbabilityTendancyTowardsIncreasing(int numberOfElementsAtStart, int numberOfOperations, int maxValue, double probabilityOfRandom) {
    std::vector<Operation> operations;
    std::mt19937 rng(228);
    std::uniform_int_distribution<int> dist(1, maxValue);
    std::uniform_real_distribution<double> distrib01(0.0, 1.0);
    for (int i = 0; i < numberOfElementsAtStart; i++) {
        operations.push_back({ Operation::INSERT, (distrib01(rng) < probabilityOfRandom) ? operations.back().m_value : (i + 1) });
    }
    for (int i = 0; i < numberOfOperations; i++) {
        int type = rng() % 4;
        if (type == 0) {
            operations.push_back({ Operation::INSERT, (distrib01(rng) < probabilityOfRandom) ? operations.back().m_value : (numberOfElementsAtStart + i + 1) });
        }
        if (type == 1) {
            operations.push_back({ Operation::GET_MIN });
        }
        if (type == 2) {
            operations.push_back({ Operation::DELETE_AND_GET_MIN });
        }
        if (type == 3) {
            operations.push_back({ Operation::GET_SIZE });
        }
    }
    return operations;
}

std::vector<Operation> generateTestMixedProbabilityTendancyTowardsDecreasing(int numberOfElementsAtStart, int numberOfOperations, int maxValue, double probabilityOfRandom) {
    std::vector<Operation> operations;
    std::mt19937 rng(228);
    std::uniform_int_distribution<int> dist(1, maxValue);
    std::uniform_real_distribution<double> distrib01(0.0, 1.0);
    for (int i = 0; i < numberOfElementsAtStart; i++) {
        operations.push_back({ Operation::INSERT, (distrib01(rng) < probabilityOfRandom) ? operations.back().m_value : -(i + 1) });
    }
    for (int i = 0; i < numberOfOperations; i++) {
        int type = rng() % 4;
        if (type == 0) {
            operations.push_back({ Operation::INSERT, (distrib01(rng) < probabilityOfRandom) ? operations.back().m_value : -(numberOfElementsAtStart + i + 1) });
        }
        if (type == 1) {
            operations.push_back({ Operation::GET_MIN });
        }
        if (type == 2) {
            operations.push_back({Operation::DELETE_AND_GET_MIN});
        }
        if (type == 3) {
            operations.push_back({ Operation::GET_SIZE });
        }
    }
    return operations;
}

template<typename Func, typename... Args>
std::pair<std::vector<int>, double> evaluateAndTimeFunction(Func func, Args... args) {
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<int> result = func(args...);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    return { result, duration.count() };
}

template<typename BinomialHeap> 
std::vector<int> evaluateOperations(BinomialHeap* heap, std::vector<Operation> operations) {
    std::vector<int> results;
    for (const auto& op : operations) {
        if (op.m_opType == Operation::INSERT) {
            heap->insert(op.m_value);
        }
        if (op.m_opType == Operation::GET_MIN && heap->size() > 0) {
            results.push_back(heap->getMin());
        }
        if (op.m_opType == Operation::DELETE_AND_GET_MIN && heap->size() > 0) {
            results.push_back(heap->deleteAndGetMin());
        }
        if (op.m_opType == Operation::GET_SIZE) {
            results.push_back(heap->size());
        }
    }
    return results;
}

std::vector<int> evaluateOperations(FibonacciHeap* heap, std::vector<Operation> operations) {
    std::vector<int> results;
    for (const auto& op : operations) {
        if (op.m_opType == Operation::INSERT) {
            heap->insert(op.m_value);
        }
        if (op.m_opType == Operation::GET_MIN && heap->size() > 0) {
            results.push_back(heap->getMin());
        }
        if (op.m_opType == Operation::DELETE_AND_GET_MIN && heap->size() > 0) {
            results.push_back(heap->deleteAndGetMin());
        }
        if (op.m_opType == Operation::GET_SIZE) {
            results.push_back(heap->size());
        }
    }
    return results;
}


