#pragma once

#include <vector>
#include <cassert>
#include <limits>

class BinomialTree {
public:
	int value;
	int deg;
	std::vector<BinomialTree*> kids;
	
	void build(int newValue) {
		value = newValue;
		deg = 0;
		kids.clear();
	}
};

BinomialTree* merge(BinomialTree* a, BinomialTree* b) {
	if (!a) {
		return b;
	}
	if (!b) {
		return a;
	}
	if (a->value > b->value) {
		std::swap(a, b);
	}
	a->kids.push_back(b);
	a->deg++;
	return a;
}

class InnerBinomialHeap {
public:
	std::vector<BinomialTree*> trees;
	void shrink() {
		while (!trees.empty() && trees.back() == 0) {
			trees.pop_back();
		}
	}
	int size() {
		int sol = 0;
		for (auto& tree : trees) {
			if (tree) {
				sol += (1 << tree->deg);
			}
		}
		return sol;
	}
	void build(int x) {
		BinomialTree* tree = new BinomialTree;
		tree->build(x);
		trees.clear();
		trees.push_back(tree);
	}
	BinomialTree* getMin() {
		BinomialTree* sol = 0;
		for (auto& t : trees) {
			if (t) {
				if (!sol) {
					sol = t;
				}
				else {
					if (t->value < sol->value) {
						sol = t;
					}
				}
			}
		}
		return sol;
	}
};

InnerBinomialHeap* eraseMin(BinomialTree* a) {
	InnerBinomialHeap* heap = new InnerBinomialHeap;
	for (int i = 0; i < a->deg; i++) {
		heap->trees.push_back(a->kids[i]);
	}
	return heap;
}

InnerBinomialHeap* merge(InnerBinomialHeap* a, InnerBinomialHeap* b) {
	if (!a) {
		return b;
	}
	if (!b) {
		return a;
	}
	InnerBinomialHeap* heap = new InnerBinomialHeap;
	int dim = std::max((int)a->trees.size(), (int)b->trees.size()) + 1;
	heap->trees.resize(dim, 0);
	std::vector<BinomialTree*> have;
	for (int i = 0; i < dim; i++) {
		if (i < (int)a->trees.size() && a->trees[i]) {
			have.push_back(a->trees[i]);
		}
		if (i < (int)b->trees.size() && b->trees[i]) {
			have.push_back(b->trees[i]);
		}
		int dim = (int)have.size();
		if (dim == 0) {
			have = {};
			continue;
		}
		if (dim == 1) {
			heap->trees[i] = have[0];
			have = {};
			continue;
		}
		if (dim == 2) {
			have = { merge(have[0], have[1]) };
			continue;
		}
		if (dim == 3) {
			heap->trees[i] = have[2];
			have = { merge(have[0], have[1]) };
			continue;
		}
	}
	heap->shrink();
	return heap;
}

InnerBinomialHeap* eraseMin(InnerBinomialHeap* heap) {
	BinomialTree* tree = heap->getMin();
	for (auto& t : heap->trees) {
		if (t == tree) {
			t = 0;
		}
	}
	InnerBinomialHeap* b = eraseMin(tree);
	return merge(b, heap);
}

class BinomialHeap {
private:
	InnerBinomialHeap* a;
public:
	BinomialHeap() : a(0) {

	}
	void insert(int value) {
		InnerBinomialHeap* b = new InnerBinomialHeap;
		b->build(value);
		a = merge(a, b);
	}
	int getMin() {
		return a->getMin()->value;
	}
	int deleteAndGetMin() {
		int val = getMin();
		a = eraseMin(a);
		return val;
	}
	int size() {
		return a->size();
	}
};