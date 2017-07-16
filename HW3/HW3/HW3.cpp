#include "stdafx.h"
#include <iostream>

using namespace std;


class Item
{
public:
	int val;
	Item *next, *pre;
	Item()
	{
		val = 0;
		next = 0;
		pre = 0;


	}
	Item(int val)
	{
		this->val = val;
		next = 0;
		pre = 0;
	}

};


class DLinkedList
{

	int size;
	Item *front;
	Item *back;

public:

	DLinkedList();
	DLinkedList(const DLinkedList &list);

	void push_back(Item *a);
	void push_front(Item *a);

	Item * pop_front();
	Item * pop_back();

	void insert(Item *a, int t); // insert the item a after the t-th element
	void insertlist(DLinkedList *list, int t); // insert the whole list a after the t-th element
	void display(ostream &out);

	int getSize();
	Item * getfront();
	Item * getback();
	void swap(Item *p, Item *q); //swap two items pointed by p and q, you can assume that p and q are something in the list

	Item * extractmin(Item * start); // return the pointer of the min element after  "start",
									 // here you can assume user will always input a valid pointer start that points to an item in the list
	Item * extractmax(Item * start);  // return the pointer of the max element after "start"


};

DLinkedList::DLinkedList()
{
	size = 0;
	front = 0;
	back = 0;
}
DLinkedList::DLinkedList(const DLinkedList &list)
{
	Item *temp = list.front;
	while (temp->next != 0)
	{
		Item *add = new Item(temp->val);
		this->push_back(add);
		temp = temp->next;
	}
}
void DLinkedList::push_back(Item *a)
{
	if (size == 0)
	{
		front = a;
		back = a;
		a->next = 0;
		a->pre = 0;
		size++;
	}
	else
	{
		a->pre = back;
		back->next = a;
		a->next = 0;
		back = a;
		size++;
	}
}
void DLinkedList::push_front(Item *a)
{
	if (size == 0)
	{
		front = a;
		back = a;
		a->next = 0;
		a->pre = 0;
		size++;
	}
	else
	{
		front->pre = a;
		a->next = front;
		a->pre = 0;
		front = a;
		size++;
	}
}
Item * DLinkedList::pop_front()
{
	Item * temp = front;
	front = front->next;
	front->pre = 0;
	size--;
	return temp;
}
Item * DLinkedList::pop_back()
{
	Item * temp = back;
	back = back->pre;
	back->next = 0;
	size--;
	return temp;
}
void DLinkedList::insert(Item *a, int t)
{
	Item * temp = front;
	Item * temp2;
	for(int i= 0; i< t; i++)
	{
		temp = temp->next;
	}
	temp2 = temp->next;
	temp->next = a;
	a->next = temp2;
	(a->next)->pre = a;
	size++;
}
void DLinkedList::insertlist(DLinkedList *list, int t)
{
	Item * temp = front;
	Item * temp2;
	for (int i = 0; i< t; i++)
	{
		temp = temp->next;
	}
	DLinkedList copy = *list;
	temp2 = temp->next;
	temp->next = copy.front;
	(copy.front)->pre = temp;
	(copy.back)->next = temp2;
	temp2->pre = copy.back;
	size += copy.size;
}
void DLinkedList::display(ostream &out)
{
	out << "(";
	Item * temp = front;
	while (temp->next != 0)
	{
		out << temp->val<<", ";
		temp = temp->next;
	}
	out << temp->val;
	out << ")"<<endl;

}
int DLinkedList::getSize()
{
	return size;
}
Item * DLinkedList::getfront()
{
	return front;
}
Item * DLinkedList::getback()
{
	return back;
}
void DLinkedList::swap(Item *p, Item *q)
{
	Item *temp = p;
	p->val = q->val;
	q->val = temp->val;
	
}
Item * DLinkedList::extractmin(Item * start)
{
	Item *temp=start;
	Item *result = start;
	while (temp->next != 0)
	{
		if (temp->val < result->val)
		{
			result = temp;
		}
		temp = temp->next;
	}
	return result;
}
Item * DLinkedList::extractmax(Item * start)
{
	Item *temp = start;
	Item *result = start;
	while (temp->next != 0)
	{
		if (temp->val > result->val)
		{
			result = temp;
		}
		temp = temp->next;
	}
	return result;
}




class myStack
{
	DLinkedList list;
public:
	myStack();
	int getSize();
	void in(Item *a);
	Item *top();
	void out();

};
myStack::myStack()
{
}
int myStack::getSize()
{
	return list.getSize();
}
void myStack::in(Item *a)
{
	list.push_front(a);
}
Item *myStack::top()
{
	return list.getfront();
}
void myStack::out()
{
	Item * temp = list.pop_front();
}

class myQueue
{
	DLinkedList list;
public:
	myQueue();
	int getSize();
	void in(Item *a);
	Item *front();
	void out();
};
myQueue::myQueue()
{
}
int myQueue::getSize()
{
	return list.getSize();
}
void myQueue::in(Item *a)
{
	list.push_front(a);
}
Item *myQueue::front()
{
	return list.getback();
}
void myQueue::out()
{
	Item * temp = list.pop_back();
}






int main() {
	DLinkedList l1,l2;
	for (int i = 0; i < 10; i++)
	{
		Item *val = new Item(i);
		l1.push_back(val);
	}
	for (int i = 0; i <5; i++)
	{
		Item *val = new Item(i);
		l2.push_front(val);
	}
	l1.display(cout);
	l2.display(cout);
	l1.insertlist(&l2, 1);
	l1.display(cout);
	l2.display(cout);
	Item * val = new Item(11);
	l2.push_back(val);
	l2.push_back(l1.pop_front());
	l2.push_back(l1.pop_back());
	cout << l1.extractmin(l1.getfront())->val<<endl;
	cout << l2.extractmax(l2.getfront())->val<<endl;
	l1.swap(l1.getfront(), l1.getback());
	l1.display(cout);
	l2.display(cout);
	return 0;
}
