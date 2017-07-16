#include"stdafx.h"
#include <iostream>

using namespace std;

void clear2dArray(int ** arr, int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int y = 0; y < size; y++) arr[i][y] = 0;
	}
}
void clear1dArray(int * arr, int size)
{
	for (int i = 0; i < size; i++)arr[i] = 0;
}

class Graph
{
	int n;
	int **adjmatrix;

	void DFSRec(int i, int * visited);
	bool ECRec(int i, int * visited);

public:
	Graph();
	Graph(int n,int **m);
	bool adj(int i, int j); // return true if i --> j
	int outdegree(int i);// return the outdegree of the node i
	int indegree(int i);// return the outdegree of the node i


						// the following funcitons are bonus (can be used to replace the final)
	void BFS(int z); // print the nodes according to the Breadth-first search
	void DFS(int z); // print the nodes according to the Depth-first search //z=starting node
	bool isConnected(); // return true iff the graph is connected
	bool exist_cycle(); // return true iff the graph has a cycle


};

Graph::Graph(int n,int **m)
{
	(*this).n = n;
	adjmatrix = new int*[n];
	for (int i = 0; i < n; i++)
	{
		adjmatrix[i] = new int[n];
		for (int y = 0; y < n; y++)
		{
			adjmatrix[i][y] = m[i][y];
		}
	}
}
Graph::Graph()
{
	n = 0;
	adjmatrix = 0;
}

bool Graph::adj(int i, int j)
{
	if (i >= n||j >= n) throw "Entrance point out of bound.";
	if (i < n&&j < n)
	{
		if (adjmatrix[i][j] > 0)
		{
			return true;
		}
	
	}
	return false;
}

int Graph::outdegree(int i)
{
	if (i >= n) throw "Entrance point out of bound.";
	int res=0;
	for (int y = 0; y < n; y++)
	{
		if (adj(i, y))
		{
			res++;
		}
	}
	return res;
}

int Graph::indegree(int i)
{
	if (i >= n) throw "Entrance point out of bound.";
	int res=0;
	for (int y = 0; y < n; y++)
	{
		if (adj(y, i))
		{
			res++;
		}
	}
	return res;
}

void Graph::BFS(int z)
{
	if (z >= n) throw "Entrance point out of bound.";
	int * arr = new int[n];
	int * temp = new int[n];
	int * visited = new int[n];

	clear1dArray(arr, n);
	clear1dArray(temp, n);
	clear1dArray(visited, n);

	int arrCount = 1, tempCount = 0;

	visited[z] = 1;
	arr[0] = z;
	
	cout << z << " ";

	while (arrCount != 0)
	{
		for (int i = 0; i < arrCount; i++)
		{
			for (int y = 0; y < n; y++)
			{
				if (adj(arr[i], y)&&visited[y]!=1)
				{
					temp[tempCount] = y;
					cout << y << " ";
					visited[y] = 1;
					tempCount++;
				}
			}
		}
		delete[] arr;
		arr = temp;
		arrCount = tempCount;
		temp = new int[n];
		tempCount = 0;
	}
	cout << endl;
}

void Graph::DFS(int z)
{
	if (z >= n) throw "Entrance point out of bound.";
	int* visited = new int[n];
	clear1dArray(visited, n);
	visited[z] = 1;
	DFSRec(z, visited);
	cout << z<< " ";
	cout << endl;
}

void Graph::DFSRec(int i, int * visited)
{
	for(int y =0; y<n;y++)
	{ 
		if(adj(i, y) && visited[y] != 1)
		{
			visited[y] = 1;
			DFSRec(y, visited);
			cout << y << " ";
		}
	}
	
}

bool Graph::isConnected()
{
	if (n == 0) throw "Empty graph";
	int * arr = new int[n];
	int * temp = new int[n];
	int * visited = new int[n];

	clear1dArray(arr, n);
	clear1dArray(temp, n);
	clear1dArray(visited, n);

	int arrCount = 1, tempCount = 0, visCount = 0;

	visited[0] = 1;
	arr[0] = 0;

	while (arrCount != 0)
	{
		for (int i = 0; i < arrCount; i++)
		{
			for (int y = 0; y < n; y++)
			{
				if (adj(arr[i], y) && visited[y] != 1)
				{
					temp[tempCount] = y;
					visited[y] = 1;
					tempCount++;
				}
			}
			visCount++;
		}
		delete[] arr;
		arr = temp;
		arrCount = tempCount;
		temp = new int[n];
		tempCount = 0;
	}
	if (visCount == n)
	{
		return true;
	}
	return false;
}

bool Graph::exist_cycle()
{
	if (n == 0) throw "Empty graph";
	int* visited = new int[n];
	clear1dArray(visited, n);
	visited[0] = 1;
	return ECRec(0, visited);


	//the following code will determine a cycle using BFS
	//The current code using DFS is more efficient
	/*int * arr = new int[n];
	int * temp = new int[n];
	int * visited = new int[n];

	clear1dArray(arr, n);
	clear1dArray(temp, n);
	clear1dArray(visited, n);

	int arrCount = 1, tempCount = 0;

	visited[0] = 1;
	arr[0] = 0;

	while (arrCount != 0)
	{
		for (int i = 0; i < arrCount; i++)
		{
			for (int y = 0; y < n; y++)
			{
				if (adj(arr[i], y) && visited[y] != 1)
				{
					temp[tempCount] = y;
					visited[y] = 1;
					tempCount++;
				}
				else if (adj(arr[i], y) && visited[y] == 1)
				{
					return true;
				}
			}
		}
		delete[] arr;
		arr = temp;
		arrCount = tempCount;
		temp = new int[n];
		tempCount = 0;
	}
	return false;*/
}

bool Graph::ECRec(int i, int * visited)
{
	for (int y = 0; y<n; y++)
	{
		if (adj(i, y) && visited[y] != 1)
		{
			visited[y] = 1;
			if (ECRec(y, visited)) // do not return if false
			{
				return true;
			}
		}
		else if (adj(i, y) && visited[y] == 1)
		{
			return true;
		}

	}
	return false;
}


int main() 
{
	try
	{
		int size = 5;
		int ** graph = new int*[size];
		for (int i = 0; i < size; i++) graph[i] = new int[size];
		clear2dArray(graph, size);
		graph[0][1] = 1;
		graph[0][2] = 1;
		graph[2][3] = 1;
		graph[3][1] = 1;
		graph[1][0] = 1;
		graph[2][4] = 1;
		graph[3][2] = 1;

		Graph g1(size,graph);
		g1.BFS(0);
		g1.DFS(0);
		cout << g1.isConnected() << endl;
		cout << g1.exist_cycle() << endl;
		cout << g1.indegree(1) << endl;
		cout << g1.outdegree(0) << endl;
	}
	catch (char*s)
	{
		cout << "Error: "<< s<<endl;
	}



	return 0;
}

