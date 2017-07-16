#include"stdafx.h"
#include<iostream>
#include<string>

using namespace std;

class nDVector
{
public:
	nDVector();// default constructor
	nDVector(int c); // set the size to be as the input
	nDVector(const nDVector &b); // copy constructor
	~nDVector();//destructor

	int getSize();
	int get(int i);//get p[i]
	void set(int i, int val);// set p[i] to be val, need to check whether it is out of bound
	void remove(int i);//remove p[i] (dimension reduced)
	void append(int x); // append x to the end of the vector (need to increase the dimension)


	void operator=(const nDVector &b); // assignment operator
	nDVector operator+(const nDVector &b);// add two nDVector's if their dimensions match
	nDVector operator-(const nDVector &b);// similar as above
	int operator*(const nDVector &b);// inner product of two nDVector's if their dimensions match
	nDVector operator*(const int x); //scalar product
	friend ostream & operator<<(ostream &out, const nDVector &b);
	friend istream & operator >> (istream &in, nDVector &b);

private:
	int size;
	int *p;
	int defSize;

};

nDVector::nDVector()
{
	p = new int[10];
	size = 0;
	defSize = 10;
}

nDVector::nDVector(int c)
{
	p = new int[c];
	size = 0;
	defSize = c;
}

int nDVector::getSize()
{
	return size;
}

int nDVector::get(int i)
{
	if (i < size)
	{
		return p[i];
	}
	else
	{
		throw (string)"Index out of bounds";
	}
}

void nDVector::set(int i, int val)
{
	if (i < size)
	{
		p[i] = val;
	}
	else
	{
		throw (string)"Index out of bounds";
	}
}

void nDVector::remove(int i)
{
	if (i < size)
	{
		if (i == size - 1)
			size--;
		else
		{
			for (int j = i; i < size; i++)
			{
				p[j] = p[j + 1];
			}
			size--;
		}
	}
	else
	{
		throw (string)"Index out of bounds";
	}
}

void nDVector::append(int x)
{
	int y;
	if (size != defSize)
	{
		p[size] = x;
		size++;
		y = p[size];
	}
	else
	{
		int * temp = new int[2 * defSize];
		defSize = 2 * size;
		for (int j = 0; j < size; j++)
		{
			temp[j] = p[j];
		}
		temp[size] = x;
		delete[] p;
		p = temp;
		size++;
	}
}

nDVector::nDVector(const nDVector &b)
{
	p = new int[b.size];
	size = b.size;
	for (int i = 0; i < size; i++)
	{
		p[i] = b.p[i];
	}
	defSize = size;
}

nDVector::~nDVector()
{
	delete[] p;
}

void nDVector::operator=(const nDVector &b)
{
	size = b.size;
	defSize = b.defSize;
	delete[] p;
	p = new int[defSize];
	for (int j = 0; j < size; j++)
	{
		p[j] = b.p[j];
	}
}

nDVector nDVector::operator+(const nDVector &b)
{
	if (size = b.size)
	{
		nDVector result(size);
		for (int j = 0; j < size; j++)
		{
			result.append(p[j] + b.p[j]);
		}
		return result;
	}
	else throw (string)"Vectors do not match.";
}

nDVector nDVector::operator-(const nDVector &b)
{
	if (size = b.size)
	{
		nDVector result(size);
		for (int j = 0; j < size; j++)
		{
			result.append(p[j] - b.p[j]);
		}
		return result;
	}
	else throw (string)"Vectors do not match.";
}

int nDVector::operator*(const nDVector &b)
{
	if (size = b.size)
	{
		int result=0;
		for (int j = 0; j < size; j++)
		{
			result += p[j] * b.p[j];
		}
		return result;
	}
	else throw (string)"Vectors do not match.";
}

nDVector nDVector::operator*(const int x)
{
	nDVector result(size);
	for (int j = 0; j < size; j++)
	{
		result.append(p[j] * x);
	}
	return result;
}

ostream & operator<<(ostream &out, const nDVector &b)
{
	out << "(";
	out<< b.p[0];
	for (int j = 1; j < b.size; j++)
	{
		out<<", " << b.p[j];
	}
	out <<")"<< endl;
	return out;
}

istream & operator>>(istream &in, nDVector &b)
{
	int next;
	in >> next;
	b.append(next);
	return in;
}

int main()
{
	try
	{
		nDVector v1, v2(5);
		int i;
		for (i = 0; i < 5; i++)
		{
			v1.append(i);
		}
		for (i; i < 10; i++)
		{
			v2.append(i);
		}
		nDVector v3 = v1;
		v3.append(6);
		nDVector v4 = v1 + v2;
		cout << v1 << v2 << v3 << v4;
		v1 + v2;
		cout << v1;
		v4 = v1 * 3;
		cout << v4;
		v4.remove(2);
		cout << v4;
		cout << v1*v2;
	}
	catch (string e)
	{
		cout << e << endl;
	}

	return 0;
}