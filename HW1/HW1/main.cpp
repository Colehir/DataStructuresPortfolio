#include<iostream>
#include<string>
#include<vector>
using namespace std;

void dec2bin(int n)
{
	//vector<int> p;
	int * p = new int[32];
	int i=0;

	cout << n << " (Base 10) = ";

	while (n > 0)
	{
		//p.push_back(n % 2);
		p[i] = n % 2;
		n /= 2;
		i++;
	}
	
	for (int y = i-1; y >= 0; y--)
	{
		cout << p[y];
	}
	cout << " (Base 2)";

	cout << "\n";

}

void bin2dec(int *p, int n)
{
	int x = 1;
	int res=0;
	for (int i = n - 1; i >= 0; i--)
	{
		if (p[i]) res += x;
		x *= 2;
		cout << p[n-1-i];
	}

	cout << " (Base 2) = "  << res << " (Base 10)" << endl;
	
}

int main()
{
	dec2bin(1024);
	dec2bin(48);
	dec2bin(60019);
	int bin[] = { 1,0,1,0 };
	bin2dec(bin, 4);
	int bin1[] = { 1,1,1,1,0 };
	bin2dec(bin1, 5);
	int bin2[] = { 1,0,0,0,0,0,1 };
	bin2dec(bin2, 7);
}