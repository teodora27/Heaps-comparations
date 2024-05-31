#include <iostream>
#include <vector>
#include <cmath>
#include <list>
#include <map>
#include <algorithm>
#include <cassert>
#include "HeapSTLMultiset.h"
#include "HeapSTLPriorityqueue.h"
#include "BinomialHeap.h"
#include "FibonacciHeap.h"
#include "Tests.h"
#include <iomanip>

std::vector<int> exampleFunction(int n) {
	int sum = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			sum += i * (j + 1);
		}
	}
	std::vector<int> sol;
	sol.push_back(sum);
	return sol;
}

void print(std::vector<int> v) {
	std::cout << " ---> ";
	for (auto& x : v) {
		std::cout << x << " ";
	}
	std::cout << "\n";
}

void step(std::map<std::string, int>& mp_cnt, std::map<std::string, double>& mp_sum, std::vector<Operation> operations) {
	std::vector<std::vector<int>> results;
	{
		typedef HeapSTLMultiset HeapType;
		const std::string name = "HeapSTLMultiset";
		HeapType* heap = new HeapType;
		std::pair<std::vector<int>, double> result = evaluateAndTimeFunction(evaluateOperations<HeapType>, heap, operations);
		results.push_back(result.first);
		mp_cnt[name]++;
		mp_sum[name] += result.second;
	}
	{
		typedef HeapSTLPriorityqueue HeapType;
		const std::string name = "HeapSTLPriorityqueue";
		HeapType* heap = new HeapType;
		std::pair<std::vector<int>, double> result = evaluateAndTimeFunction(evaluateOperations<HeapType>, heap, operations);
		results.push_back(result.first);
		mp_cnt[name]++;
		mp_sum[name] += result.second;
	}
	{
		typedef BinomialHeap HeapType;
		const std::string name = "BinomialHeap";
		HeapType* heap = new HeapType;
		std::pair<std::vector<int>, double> result = evaluateAndTimeFunction(evaluateOperations<HeapType>, heap, operations);
		results.push_back(result.first);
		mp_cnt[name]++;
		mp_sum[name] += result.second;
	}
	/*{
		typedef FibonacciHeap HeapType;
		const std::string name = "FiboHeap";
		HeapType* heap = new HeapType;
		std::pair<std::vector<int>, double> result = evaluateAndTimeFunction(evaluateOperations<HeapType>, heap, operations);
		results.push_back(result.first);
		mp_cnt[name]++;
		mp_sum[name] += result.second;
	}*/
	
	
	for (int i = 1; i < (int)results.size(); i++) {
		assert(results[i] == results[i - 1]);
	}
}

void print(std::map<std::string, int>& mp_cnt, std::map<std::string, double>& mp_sum, int doneTests) {
	std::cout << "tests done = " << doneTests << "\n";
	for (auto& it : mp_cnt) {
		std::string name = it.first;
		assert(mp_cnt[name] >= 1);
		std::cout << "name = " << name << ", mean = " << std::fixed << std::setprecision(6) << mp_sum[name] / mp_cnt[name] << "\n";
	}
	std::cout << "--------------------------------------------------------------------------------------------------\n";
}


int main() {
	if (0) {
		FibonacciHeap* heap = new FibonacciHeap;
		heap->insert(5);
		heap->insert(-2);
		heap->insert(-15);
		heap->insert(17);
		heap->insert(1);
		std::cout << heap->size() << "\n";
		std::cout << heap->getFirstListCount() << "\n";
		std::cout << heap->deleteAndGetMin() << "\n";
		std::cout << heap->size() << "\n";
		//heap->displyFirstListLeft();
		//heap->displyFirstListRight();
		std::cout << heap->deleteAndGetMin() << "\n";
		heap->insert(55);
		std::cout << heap->size() << "\n";
		std::cout << heap->deleteAndGetMin() << "\n";
		std::cout << heap->size() << "\n";
		std::cout << heap->getMin() << "\n";

		exit(0);
		//std::cout << heap->getFirstListCount() << "\n";
		//heap->displyFirstListRight();
		//heap->displyFirstListLeft();

		//std::cout << heap->getSize()<<"\n";

	}
	if (0) {
		/*FibonacciHeap* heap = new FibonacciHeap;
		heap->insert(5);
		heap->insert(-2);
		heap->insert(7);
		FibonacciHeap* heap2 = new FibonacciHeap;
		heap2->insert(5);
		heap2->insert(2);
		heap2->insert(100);
		std::cout << heap->size() << "\n";
		std::cout << heap->getMin() << "\n";
		exit(0);*/
	}
	if (0) {
		// ai grija sa eliberezi memoria cu delete!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		BinomialHeap* heap = new BinomialHeap;
		heap->insert(5);
		heap->insert(3);
		heap->insert(-1);
		heap->insert(7);
		std::cout << heap->getMin() << "\n";
		exit(0);
	}
	/*
	std::vector<Operation> generateTestRandom(int numberOfElementsAtStart, int numberOfOperations, int maxValue)
	std::vector<Operation> testInsertIncreasingInsertHeavy(int nrElementsAtStart)
	std::vector<Operation> testInsertDecreasingInsertHeavy(int nrElementsAtStart)
	std::vector<Operation> generateTestMixedProbabilityTendancyTowardsIncreasing(int numberOfElementsAtStart, int numberOfOperations, int maxValue, double probabilityOfRandom)
	std::vector<Operation> generateTestMixedProbabilityTendancyTowardsDecreasing(int numberOfElementsAtStart, int numberOfOperations, int maxValue, double probabilityOfRandom)
	*/
	// HeapSTLMultiset.h


	{
		// random Tests with 1e5 elements
		std::map<std::string, int> mp_cnt;
		std::map<std::string, double> mp_sum;

		for (int testId = 1; 1; testId++) {
			step(mp_cnt, mp_sum, generateTestRandom((int)1e2, (int)1e2, (int)1e2));

			print(mp_cnt, mp_sum, testId);
		}
	}
	return 0;
}

