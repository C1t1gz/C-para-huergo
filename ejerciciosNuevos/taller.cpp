
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <cmath>
#include "taller.h"


using namespace std;

bool divide(int a, int b){
	if (b % a == 0)
		return true;
	else
		return false;
}

int mayor(int a, int b){
	if (a < b)
		return b;
	else
		return a;
}

unsigned int factorialPorCopia(int n){
	int factorial = 1;
	for (int i = 1; i <= n; i++)
	{
		factorial = factorial * i;
	}
	return factorial;
}

void factorialPorTeclado(){
	cout << "ingresar numero para saber su factorial " << endl;
	int n;
	cin >> n;
	cout << "su factorial es " << factorialPorCopia(n) << endl;
}

bool esPrimo(int a){
	if (a == 0 || a == 1)
		return false;
	for (int x = 2; x < a; x++)
	{
		if (a % x == 0)
			return false;
	}
	return true;
}

bool primoGemelo(int n){
	bool bol;
	if (n == 0 || n == 1)
		bol = false;
	for (int x = 2; x < n; x++)
	{
		if (n % x == 0)
			return false;
	}
	bol = true;
	if (bol == true)
	{
		n = n + 2;
		for (int x = 2; x < n; x++)
		{
			if (n % x == 0)
				return false;
		}
		return true;
		
	}
	return false;
}

void esCapicua(string s)
{
	int l = s.length();
	int check;
	int pepe = 0;
	
	for (int i = 0; i < l; i++){
		check = isdigit(s[i]);
		if (s.at(i) != s.at(l - i - 1)){
			pepe = 1;	
		}
		if (check){
			cout << "Numero: SI, ";
			break;
		}
	}
	if (check == false) cout << "Numero: NO ";
	if (pepe == 0) 
		cout << "Palindromo: SI " << endl;
	else 
		cout << "Palindromo: NO " << endl;
	// if (s == string(s.rbegin(), s.rend())) {
    //     cout << "Palindromo: SI" << endl;
    // } else {
    //     cout << "Palindromo: NO" << endl;
    // }		
}

void numerosHasta(int n){

	for (int i = 0; i <= n; i++){
		if (i == n){
			cout << i << endl;
			break; 
		}
		cout << i <<", ";
		
	}
	
}

void escaleraSimple(int n){
	cout << "Escalera de " << n << endl;
	int i;
	for (i = 1; i <= n; i++){
		cout << 0;
		for (int x = 0; x != i; x++){
			cout << x + 1 ;
		}
		printf("\n");
	}
}

bool esPerfecto(int n){
	int c = 0;	
	
	// for(int i = 0; i < n; i++){
	// 	c = c + i;
	// 	if (c == n){
	// 		return true;  
	// 	}	
	// }
	for (int i=1; i<n; i++){
		if (n % i==0)
			c +=i;
		}

	if (n == c){
		return true;
	}
	else{
		
		return false;
	}

}

