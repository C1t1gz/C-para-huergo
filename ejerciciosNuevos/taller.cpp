
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <cmath>
#include "taller.h"
using namespace std;

bool divide(int a, int b)
{
	if (a % b == 0)
		return true;
	else
		return false;
}

int mayor(int a, int b)
{
	if (a < b)
		return b;
	else
		return a;
}

unsigned int factorialPorCopia(int n)
{
	int factorial = 1;
	for (int i = 1; i <= n; i++)
	{
		factorial = factorial * i;
	}
	return factorial;
}

void factorialPorTeclado()
{
	cout << "ingresar numero para saber su factorial " << endl;
	int n;
	cin >> n;
	cout << "su factorial es " << factorialPorCopia(n) << endl;
}

bool esPrimo(int a)
{
	if (a == 0 || a == 1)
		return false;
	for (int x = 2; x < a; x++)
	{
		if (a % x == 0)
			return false;
	}
	return true;
}

bool primoGemelo(int n)
{
	bool bol;
	if (n == 0 || n == 1)
		bol = false;
	for (int x = 2; x < n; x++)
	{
		if (n % x == 0)
			return false;
	}
	bol = true;
	if (bol = true)
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

// Ejercicio 6
// Dado un sting, detemina si es un palindromo.
// Por ejemplo: la entrada "hola mundo", deberia dar por resultado:
// "Numero: NO, Palindromo: NO". Mientras que "severlasalreves" deberia dar 
// "Numero: NO, Palindromo: SI"
// Hint: Ver las funciones at() y isdigit() del tipo string.

void esCapicua(string s)
{
	int l = s.length();
	int check;
	
	for (int i = 0; i < l; i++){
		check = isdigit(s[i]);	
	}
	if (check)
		cout << "Numero: SI";
	else
		cout << "Numero: NO";
	
	
}
