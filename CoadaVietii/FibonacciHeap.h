#pragma once
#include <cmath>
#include <vector>


//class Vertex {
//public:
//	Vertex* ant;
//	Vertex* nxt;
//	int key;
//	Vertex* child;
//	int deg;
//	Vertex(int key) : ant(0), nxt(0), key(key), child(0), deg(0) {
//
//	}
//};
//
//void coupleClockwise(Vertex* f, Vertex* s) {
//	assert(f);
//	assert(s);
//	f->nxt = s;
//	s->ant = f;
//}
//
//class FibonacciHeap {
//public:
//	Vertex* min;
//	int sz;
//	FibonacciHeap() : min(0), sz(0) {
//
//	}
//	void insert(int key) {
//		sz++;
//		Vertex* v = new Vertex(key);
//		if (!min) {
//			min = v;
//			coupleClockwise(v, v);
//		}
//		else {
//			coupleClockwise(v, min->nxt);
//			coupleClockwise(min, v);
//			if (v->key < min->key) {
//				min = v;
//			}
//		}
//	}
//	int size() {
//		return sz;
//	}
//	int getMin() {
//		assert(min);
//		return min->key;
//	}
//};
//
//FibonacciHeap* join(FibonacciHeap* a, FibonacciHeap* b) {
//	if (!a) {
//		return b;
//	}
//	if (!b) {
//		return a;
//	}
//	coupleClockwise(a->min, b->min);
//	coupleClockwise(b->min->ant, a->min->nxt);
//	if (b->min->key < a->min->key) {
//		a->min = b->min;
//	}
//	return a;
//}






struct Node {
	int key;
	int kidsCount; 
	Node* parent;
	Node* child;
	Node* left;
	Node* right;
};

class FibonacciHeap {
private:
	Node* min;
	int sizeHeap;
public:
	FibonacciHeap() : min(0), sizeHeap(0) {}

	void insert(int key) {
		Node* newNode = new Node;
		newNode->key = key;
		newNode->kidsCount = 0;
		newNode->parent = 0;
		newNode->child = 0;

		if (min == 0){
			min = newNode;
			newNode->left = newNode;
			newNode->right = newNode;
		}
		else {
			min->right->left = newNode;
			newNode->left = min;
			newNode->right = min->right;
			min->right = newNode;

			if (key < min->key) {
				min = newNode;
			}
		}
		sizeHeap += 1;
	}

	int size() {return sizeHeap;}

	int getMin() { return min->key; }

	int deleteAndGetMin() {
		//if (min == 0) return -1e5;
		assert(min != 0);
		int minKey = min->key;

		Node* child = min->child;
		int kidsCount = min->kidsCount;

		while (kidsCount--){
			Node* nextChild = child->right;

			child->right->left = child->left;
			child->left->right = child->right;

			min->right->left = child;
			child->left = min;
			child->right = min->right;
			min->right = child;

			child->parent = 0;
			child = nextChild;
		}
		min->left->right = min->right;
		min->right->left = min->left;
		if (min == min->right){
			min = 0;
		}
		else {
			min = min->right;
			/*std::cout << "lista inainte de rebuid " << "\n";
			std::cout << "dreapta "; displyFirstListRight();
			std::cout << "stanga "; displyFirstListLeft();*/

			rebuild();
		}
		sizeHeap -= 1;
		return minKey;
	}

	int getFirstListCount() {
		if (min == 0)
			return 0;
		int nr = 1;
		Node* curent = min->right;
		while (curent != min)
		{
			nr++;
			curent = curent->right;
		}
		return nr;
	}

	void displyFirstListLeft() {
		Node* curent = min;
		if (min == 0)
		{
			std::cout << "nu mai e nimic in lista\n";
			return;
		}
		if (min == min->left)
		{
			std::cout << "lista e:";
			std::cout << min->key << "\n";
			return;
		}
		std::cout << "lista e:";
		while (curent->left != min)
		{
			std::cout << curent->key << " ";
			curent = curent->left;
		}		
		std::cout << curent->key << " ";

		std::cout << "\n";
	}

	void displyFirstListRight() {
		Node* curent = min;
		if (min == 0)
		{
			std::cout << "nu mai e nimic in lista\n";
			return;
		}
		if (min == min->right)
		{
			std::cout << "lista e:";
			std::cout << min->key << "\n";
			return;
		}
		std::cout << "lista e:";
		while (curent->right != min)
		{
			std::cout << curent->key << " ";
			curent = curent->right;
		}		
		std::cout << curent->key << " ";

		std::cout << "\n";
	}

	void rebuild() {
		int maxSize = int(log2(sizeHeap) + 1);
		std::vector<Node*> sizeRoots(maxSize, 0);
		std::set<Node*>vizitat;
		Node* curent = min;
		int nodesCount = getFirstListCount()-1;
		do {
			/*std::cout << "pozitia curenta: " << curent->key << "\n";
			std::cout << "dreapta "; displyFirstListRight();
			std::cout << "stanga ";displyFirstListLeft();
			std::cout << "vector:";
			for (int i = 0; i < sizeRoots.size(); i++)
				if (sizeRoots[i] != 0)
					std::cout <<"("<<i<<","<< sizeRoots[i]->key<<")" << " ";
			std::cout << "\n\n";*/
			if (vizitat.find(curent) != vizitat.end())
				break;
			else
				vizitat.insert(curent);
			Node* next = curent->right;
			int kidsCount = curent->kidsCount;
			if(sizeRoots[kidsCount] != 0)
			{
				while (sizeRoots[kidsCount] != 0) {
					Node* other = sizeRoots[kidsCount];
					if (curent->key > other->key)
						std::swap(curent, other);
					//std::cout << "afisre intermediara\n";
					//displyFirstList();
					//std::cout << other->key << " " << curent->key << "\n";
					merge(other, curent);
					sizeRoots[kidsCount] = 0;
					kidsCount++;
				}
				sizeRoots[kidsCount] = curent;
			}
			else {
				sizeRoots[kidsCount] = curent;
			}
			/*if (curent->key < min->key)
				min = curent;*/

			curent = next;
		} while (true);
			//(nodesCount--);
		//while (curent != min);

		/*std::cout << "-----------------\n";
		for (int i = 0; i < sizeRoots.size(); i++)
			if (sizeRoots[i] != 0)
				std::cout << "(" << i << "," << sizeRoots[i]->key << ")" << " ";
		std::cout << "\n\n";*/
		//displyFirstList();
		min=0;
		for (int i = 0; i < sizeRoots.size(); i++)
			if (sizeRoots[i] != 0)
			{
				if (min == 0)
				{
					//std::cout << "ura\n"<< sizeRoots[i]->key<<"\n";
					assert(sizeRoots[i] != 0);
					min = sizeRoots[i];
					min->left = min->right = min;
					//std::cout << "ura\n"<<min->key<<"\n";
				}

				else {
					min->right->left = sizeRoots[i];
					sizeRoots[i]->left = min;
					sizeRoots[i]->right = min->right;
					min->right = sizeRoots[i];
					if (sizeRoots[i]->key < min->key)
						min = sizeRoots[i];
				}
			}
		/*std::cout << "lista dupa rebuid " << "\n";
		std::cout << "dreapta "; displyFirstListRight();
		std::cout << "stanga "; displyFirstListLeft();*/

	}

	void merge(Node* child, Node* parent) {
		child->left->right = child->right;
		child->right->left = child->left;
		//std::cout << child->left->key << " " << child->right->key << "\n";
		//displyFirstList();
		child->parent = parent;
		if (parent->child == nullptr) {
			parent->child = child;
			child->left = child->right = child;
		}
		else {
			child->left = parent->child;
			child->right = parent->child->right;
			parent->child->right = child;
			parent->child->right->left = child;
		}
		parent->kidsCount += 1;
	}

	FibonacciHeap* unite(FibonacciHeap* other) {
		assert(min != 0 && other->min != 0);

		Node* thisMinRight = min->right;
		min->right = other->min->right;
		other->min->right->left = min;
		other->min->right = thisMinRight;
		thisMinRight->left = other->min;

		if (other->min->key < min->key) {
			min = other->min;
		}
		sizeHeap += other->sizeHeap;
		delete other;
		return this;
	}

};
