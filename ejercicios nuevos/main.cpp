#include <string>
#include <stdio.h>
#include <iostream>
#include "taller.h"


using namespace std;

int main()
{
	if(divide(11, 2) == true)
		cout << "a es divisible por b" << endl;
	else
		cout << "a no es divisble por b" << endl;
	
	cout << "el mayor numero es "<< mayor(3,5) << endl;
	
	cout << "su factorial es "<< factorialPorCopia(8) << endl;
	
	factorialPorTeclado();
	
	cout << "ingresar numero para saber si es primo " << endl;
	int a;
	cin >> a;
	if (esPrimo(a)== false)
		cout << "El numero que ingreso no es primo" << endl;
	else 
		cout << "El numero que ingreso es primo" << endl;
}
