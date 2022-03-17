
#include <iostream>
#include <math.h>
#include<stdio.h>
#include <cmath>
#include "taller.h"
using namespace std;
/* IMPORTANTE: <math.h> y <cmath> se incluyen
 * solo para que utilicen abs() y pow(),
 * si las neceistaran. */


// Ejercicio 0
// Dados enteros a y b, decide si 'a' divide a 'b'.
bool divide(int a, int b)
{
	if (a % b == 0)
		return true;
	else
		return false;

}

// Ejercicio 1
// Dados dos enteros a y b, devuelve el mayor.
 int mayor(int a, int b)
{
	if (a < b)
		return b;
	else
		return a;

}

// Ejercicio 2
// Dado un n, devuelve el factorial de n.
	unsigned int factorialPorCopia(int n)
{
	int factorial = 1;
	for(int i = 1; i <= n; i++){
		factorial = factorial * i;
	}
	return factorial;
}
void factorialPorTeclado()
{
	cout << "ingresar numero para saber su factorial " << endl;
	int n;
	cin >> n;
	cout << "su factorial es "<< factorialPorCopia(n) << endl;	
 
}
bool esPrimo(int a)
{
	if (a == 0 || a == 1 ) 
		return false;
	for (int x = 2; x < a ; x++) {
		if (a % x == 0) return false;
	}
	return true;
}
