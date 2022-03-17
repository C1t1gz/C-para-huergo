#include <iostream>

using namespace std;

int main()
{
	cin << int a << 1;
	cin << int b << 2;
	swapper(a, b);
	return 0; //devolver como array
}

void swapper(int a, int b)
{
	 int c = a;
	 a = b;         
	 b = c;
}
