// HW5.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include <fstream>
#include <time.h>

using namespace std;

class TNode
{
public:
	int val;
	TNode() {}
	TNode(int v) { val = v; }
	TNode * left;
	TNode * right;
	TNode * parent;
};



class minHeap // binary heap
{
	int size;
	TNode *top;
	void copy(TNode * orgRoot, TNode * newRoot);
	TNode * convertpos(int position);
	void bubbleUp(TNode * t);
	TNode * bubbleDown(TNode * t);

public:
	minHeap();
	minHeap(const minHeap &h);
	void in(const TNode &t);// you should new a new node and then add into the heap
	int removemin();
	TNode* getmin();
	void Heapify(const int n, const int *p);// p is an array of size n, representing a (full) binray tree of size n. You should not modify the array p
	int * toArray();
};

minHeap::minHeap()
{
	size = 0;
	top = 0;
}

minHeap::minHeap(const minHeap &h)
{
	top = new TNode(h.top->val);
	size++;
	copy(h.top, top);
}

void minHeap::copy(TNode * orgRoot, TNode * newRoot)
{
	if (orgRoot->left != 0)
	{
		TNode * newnode = new TNode(orgRoot->left->val);
		newRoot->left = newnode;
		newnode->parent = newRoot;
		size++;
		newnode->left = 0;
		newnode->right = 0;
		copy(orgRoot->left, newRoot->left);
	}
	if (orgRoot->right != 0)
	{
		TNode * newnode = new TNode(orgRoot->right->val);
		newRoot->right = newnode;
		newnode->parent = newRoot;
		size++;
		newnode->left = 0;
		newnode->right = 0;
		copy(orgRoot->right, newRoot->right);
	}

}

void minHeap::in(const TNode &t)
{
	TNode* newnode = new TNode(t.val);
	TNode* p = convertpos((size+1) / 2);
	if (p == 0)
	{
		top = newnode;
		newnode->parent = 0;
		size++;
	}
	else if ((size+1) % 2 == 1)
	{
		p->left = newnode;
		newnode->parent = p;
		size++;
	}
	else
	{
		p->right = newnode;
		newnode->parent = p;
		size++;
	}
	newnode -> left = 0;
	newnode->right = 0;
	bubbleUp(newnode);
}

TNode * minHeap::convertpos(int position)
{
	if (position <= 1)
	{
		return top;
	}
	TNode* temp;
	if (position & 1)
	{
		temp = (convertpos(position >> 1))->right;
	}
	else
	{
		temp = (convertpos(position >> 1))->left;
	}
	if (temp == 0) throw (string)"location does not exist";
	return temp;
}

void minHeap::bubbleUp(TNode * t)
{
	if (t->parent == 0)
	{
		return;
	}
	if ((t->val) < ((t->parent)->val))
	{
		int temp = t->val;
		(t->val) = (t->parent->val);
		(t->parent->val) = temp;
		bubbleUp(t->parent);
	}
}

int minHeap::removemin()
{
	TNode* p = bubbleDown(top);
	int temp = p->val;
	if (p == top)
	{
		top = 0;
	}
	else if (p->left == 0 && p->right == 0)
	{
		if (p->parent->left == p)
		{
			p->parent->left = 0;
		}
		else if (p->parent->right == p)
		{
			p->parent->right = 0;
		}
		delete p;
	}
	size--;
	return temp;
}

TNode* minHeap::bubbleDown(TNode * t)
{
	if (t->left == 0&&t->right==0)
	{
		return t;
	}
	else
	{
		if (t->left == 0)
		{
			int temp = t->val;
			t->val = t->right->val;
			t->right->val = temp;
			return bubbleDown(t->right);
		}
		else if (t->right == 0)
		{
			int temp = t->val;
			t->val = t->left->val;
			t->left->val = temp;
			return bubbleDown(t->left);
		}
		else if (t->right->val < t->left->val)
		{
			int temp = t->val;
			t->val = t->right->val;
			t->right->val = temp;
			return bubbleDown(t->right);
		}
		else if (t->right->val >= t->left->val)
		{
			int temp = t->val;
			t->val = t->left->val;
			t->left->val = temp;
			return bubbleDown(t->left);
		}
	}
}
TNode* minHeap::getmin()
{
	return top;
}
void minHeap::Heapify(const int n, const int *p)
{
	TNode add;
	for (int i = 0; i < n; i++)
	{
		add.val = p[i];
		in(add);
	}
}
int * minHeap::toArray()
{
	minHeap heap = *this;
	int * p = new int[size];
	for (int i = 0; i < size; i++)
	{
		p[i] = heap.removemin();
	}
	return p;
}

int * HeapSort(const int n, const int *arr)// arr is an integer array of numbers.
											//You should output a pointer to a new array which is a sorted version of arr
{
	minHeap heap;
	heap.Heapify(n, arr);
	int * p = new int[n];
	for (int i = 0; i < n; i++)
	{
		p[i] = heap.removemin();
	}
	return p;
}

void test2()
{
	int size = 60000000; //used for stress testing
	clock_t startTime = clock();
	int * arr = new int[size];
	for (int i = size; i > 0; i--)
	{
		if (i % 3)
		{
			arr[i] = i * 3;
		}
		else if (i % 3 == 1)
		{
			arr[i] = i * 2;
		}
		else
		{
			arr[i] = (i / 3) + 4;
		}
	}
	
	clock_t endTime = clock();
	clock_t elapsedTime = endTime - startTime;
	cout << "Array created" << endl;
	cout << "[" << elapsedTime << "ms]" << endl;
	startTime = clock();
	int * sarr = HeapSort(size, arr); //also tests heapify
	endTime = clock();
	elapsedTime = endTime - startTime;
	cout << "sorted" << endl;
	cout << "[" << elapsedTime << "ms]" << endl;
	startTime = clock();
	ofstream out;
	out.open("100million2.txt");
	for (int i = 0; i < size; i++)
	{
		out << arr[i] << "\t";
		out << sarr[i] << endl;
	}
	endTime = clock();
	elapsedTime = endTime - startTime;
	cout << "Printed" << endl;
	cout << "[" << elapsedTime << "ms]" << endl;
	delete[] arr;
	delete[] sarr;
	out.close();
}

void Test()
{
	minHeap heap1;
	TNode add;
	int size = 30000000; //used for stress testing
//	int size = 10;
	int * arr = new int[size];
	for (int i = 0; i < size; i++)
	{
		if (i % 3)
		{
			add.val = i * 3;
			heap1.in(add);
			arr[i] = add.val;
		}
		else if(i%3==1)
		{
			add.val = i * 2;
			heap1.in(add);
			arr[i] = add.val;
		}
		else
		{
			add.val = (i / 3)+4;
			heap1.in(add);
			arr[i] = add.val;
		}
	}
	int * sarr = HeapSort(size, arr); //also tests heapify
	ofstream out;
	out.open("30million.txt");
	for (int i = 0; i < size; i++)
	{
		out << arr[i] << "\t";
		out << sarr[i] << endl;
		cout << arr[i] << "\t";
		cout << sarr[i] << endl;
	}
	arr = heap1.toArray(); //also tests copy constructor
	for (int i = 0; i < size; i++)
	{
		cout << arr[i] << endl;
	}
	delete[] arr;
	delete[] sarr;
	out.close();
}

int main()
{
	//Test();
	test2();
    return 0;
}