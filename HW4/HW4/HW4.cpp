#include"stdafx.h"
#include<iostream>
#include<string>

using namespace std;

bool isValidBT(const int *p, const int n);
// input is given an array that denotes a tree of n nodes.
// the array is pointed by p and has size n+1, where p[0] is used to store the empty symbol.
//Determine whether the array forms a valid BT.

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



class BTree
{

public:
	
	//constructors and destructor
	BTree();
	BTree(TNode *r);// initialize BTree with the root r. r is the only node.
	BTree(const BTree & t); // copy constructor
	BTree(const int *p, const int n);// similar to the copy constructor, but your input is of the array form.
									 // input is given an array that denotes a tree of n nodes.
									 // the array is pointed by p and has size n+1, where p[0] is used to store the empty symbol.
									 //the function converts the array representation into a linked-list representation, i.e. BTree



	//~BTree();

	TNode * convertpos(int position);// find the pointer where the position points to

	void add2left(TNode *newnode, TNode *p);
	void add2right(TNode *newnode, TNode *p);

	void add2left(TNode *newnode, int position);
	void add2right(TNode *newnode, int position);


	void add2left(BTree &newsubtree, int position);
	void add2right(BTree &newsubtree, int position);

	void addNode(TNode *newnode);


	void removeleaf(int position);
	void removeleaf(TNode *p);

	void swapnodes(TNode *n1, TNode *n2);//swap-the-values is fine

	int * Toarray(int &n);// convert the BT into the array form. Write the size to n, and new an array of size n+1. Retrun the array

	void print_pre_order();// print the node as you traverse according to the order.
	void print_in_order();
	void print_post_order();

private:
	int size;
	TNode *root;
	void copy(TNode * orgRoot, TNode * newRoot);
	void pInOrder(TNode * root);
	void pPreOrder(TNode * root);
	void pPostOrder(TNode * root);

};


BTree::BTree()
{
	root = 0;
	size = 0;
}
BTree::BTree(TNode *r)
{
	root = r;
	r->parent = 0;
	r->left = 0;
	r->right = 0;
	size = 1;
}
BTree::BTree(const BTree &t)
{
	root = new TNode(t.root->val);
	copy(t.root, root);
}
BTree::BTree(const int *p, const int n)
{
	if (isValidBT(p, n))
	{
		for (int i = 1; i < n + 1; i++)	
		{
			if (p[i] != p[0])
			{
				if ((size + 1) % 2 != 0) add2right(new TNode(p[i]), i);
				else add2left(new TNode(p[i]), i);
			}
		}
	}
}
TNode * BTree::convertpos(int position)
{
	if (position <= 1)
	{
		return root;
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

void BTree::add2left(TNode *newnode, TNode *p)
{
	if (p == 0)
	{
		root = newnode;
		newnode->parent = p;
		size++;
	}
	else if (p->left == 0)
	{
		p->left = newnode;
		newnode->parent = p;
		size++;
	}
	else throw (string)"Location already full.";
}
void BTree::add2right(TNode *newnode, TNode *p)
{
	if (p == 0)
	{
		root = newnode;
		newnode->parent = p;
		size++;
	}
	else if (p->right == 0)
	{
		p->right = newnode;
		newnode->parent = p;
		size++;
	}
	else throw (string)"Location already full.";
}
void BTree::add2left(TNode *newnode, int position)
{
	add2left(newnode, convertpos((position/2)));
}
void BTree::add2right(TNode *newnode, int position)
{
	add2right(newnode, convertpos((position/2)));
}
void BTree::add2left(BTree &newsubtree, int position)
{
	BTree temp = newsubtree;
	add2left(temp.root, position);
	size += (temp.size) - 1;
}
void BTree::add2right(BTree &newsubtree, int position)
{
	BTree temp = newsubtree;
	add2right(temp.root, position);
	size += (temp.size) - 1;
}


void BTree::copy(TNode * orgRoot, TNode * newRoot)
{
	if (orgRoot->left != 0)
	{
		add2left(new TNode(orgRoot->left->val), newRoot);
		copy(orgRoot->left, newRoot->left);
	}
	if (orgRoot->right != 0)
	{
		add2right(new TNode(orgRoot->right->val), newRoot);
		copy(orgRoot->right, newRoot->right);
	}

}
void BTree::print_in_order()
{
	pInOrder(root);
	cout << endl;
}
void BTree::pInOrder(TNode * root)
{
	if (root->left != 0)
	{
		pInOrder(root->left);
	}
	cout << root->val<< " ";
	if (root->right != 0)
	{
		pInOrder(root->right);
	}
}
void BTree::addNode(TNode *newnode)
{
	if ((size+1) % 2 != 0) add2right(newnode, size+1);
	else add2left(newnode, size+1);
}
void BTree::print_pre_order()
{
	pPreOrder(root);
	cout << endl;
}
void BTree::pPreOrder(TNode * root)
{
	cout << root->val << " ";
	if (root->left != 0)
	{
		pPreOrder(root->left);
	}
	if (root->right != 0)
	{
		pPreOrder(root->right);
	}
}
void BTree::print_post_order()
{
	pPostOrder(root);
	cout << endl;
}
void BTree::pPostOrder(TNode * root)
{
	if (root->left != 0)
	{
		pPostOrder(root->left);
	}
	if (root->right != 0)
	{
		pPostOrder(root->right);
	}
	cout << root->val << " ";
}
void BTree::removeleaf(int position)
{
	removeleaf(convertpos(position));
}
void BTree::removeleaf(TNode *p)
{
	if (p->left == 0 && p->right == 0)
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
}
void BTree::swapnodes(TNode *n1, TNode *n2)
{
	int temp = n1->val;
	n1->val = n2->val;
	n2->val = temp;
}
int * BTree::Toarray(int &n)
{
	n = 1;
	int i = 1, j = 1;
	while(i<size)
	{
		try
		{
			convertpos(i)->val;
			i++;
		}
		catch (...){}
		j++;
	}
	int * p = new int[j];
	for (int x = 1; x <= j; x++)
	{
		try
		{
			p[x] = convertpos(x)->val;
		}
		catch (...)
		{
			p[x] = -1;
		}
		n++;
	}
	p[0] = -1;
	return p;
}






bool isValidBT(const int *p, const int n)
{
	for (int i = 2; i < n + 1; i++)
	{
		if (p[i] != p[0] && p[i/2]==p[0])
		{
			return false;
		}
	}
	return true;
}

int main()
{
	try {
		BTree T1;
		BTree T2;

		for (int i = 1; i <= 5; i++)
		{
			TNode* temp = new TNode(i);
			T1.addNode(temp);
		}
		for (int i = 6; i <= 10; i++)
		{
			TNode* temp = new TNode(i);
			T2.addNode(temp);
		}
		T1.print_in_order();
		T2.print_in_order();
		T1.add2left(T2, 6);
		T1.print_in_order();
		T2.print_in_order();
		T2.removeleaf(4);
		T1.removeleaf(12);
		T1.print_post_order();
		T2.print_post_order();
		T1.print_pre_order();
		T2.print_pre_order();
		int * ar = new int[10];
		ar[0] = -1; ar[1] = 1; ar[2] = 2; ar[3] = -1; ar[4] = 4; ar[5] = 5; ar[6] = -1; ar[7] = -1;
		cout << isValidBT(ar, 6)<<endl;
		BTree T3(ar, 6);
		T3.print_in_order();
		ar[6] = 6;
		cout << isValidBT(ar, 6) << endl;
		int size;
		int * p = T2.Toarray(size);
		for (int i = 0; i < size; i++)
		{
			cout << p[i] << " ";
		}
	}
	catch (string s)
	{
		cout << s << endl;
	}

	return 0;
}


