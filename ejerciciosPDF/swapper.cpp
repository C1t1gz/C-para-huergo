#include <iostream>

using namespace std;


void swapper(int& a, int& b){
	int c = a;
	a = b;
	b = c;
}

int main()
{
	int a = 1;
	int b = 2;
	swapper(a, b);
	int matriz[2] = {a, b};
	for(int i = 0; i < 2; i++){
		cout << matriz[i] << endl;
	}
	return 0; //devolver como array
}