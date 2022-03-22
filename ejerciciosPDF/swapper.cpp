#include <iostream>
#include <vector>

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
void reverse(){
	vector<int> vector = {2,3,5};
	vector<int> vectorDos = {};

	for (int i = 0;i < vector.size(); i++){
		vectorDos.insert(vectorDos.begin(), vector[i])
	}
	for (int x = 0; x < vectorDos.size(); x++){
		vector[x] = vectorDos[x];
		cout << vector[x];
	}
 


}
