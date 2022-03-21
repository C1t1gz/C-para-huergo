#include <string>
#include <stdio.h>
#include <iostream>
#include "taller.h"


using namespace std;

int main()
{
	
	if(divide(11, 2) == true)
		cout << "El numero a es divisible por b" << endl;
	else
		cout << "El numero a no es divisble por b" << endl;
	
	cout << "El mayor numero es "<< mayor(3,5) << endl;
	
	cout << "Su factorial es "<< factorialPorCopia(8) << endl;
	
	factorialPorTeclado();
	
	cout << "Ingresar numero para saber si es primo " << endl;
	int a;
	cin >> a;
	if (esPrimo(a)== false)
		cout << "El numero que ingreso no es primo" << endl;
	else 
		cout << "El numero que ingreso es primo" << endl;

	
	cout << "Ingresar numero para saber si existe su primo gemelo" << endl;
	int b;
	cin >> b;
	if (primoGemelo(b) == false){
		cout << "No es un numero primo o no existe su primo gemelo" << endl;
	}
	else{
		cout << "Tiene primo gemelo" << endl;
	}

	esCapicua("ep2pe");
	numerosHasta(5);
	escaleraSimple(5);
	if (esPerfecto(8))
		cout << "Es perfecto" << endl;
	else
		cout << "No es perfecto" << endl;
}
