#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include <unistd.h> 
#include <sys/types.h>
#include <sys/wait.h>


using namespace std;



int main() {
	
	int nivel;
	cout << "Ingresar Nivel: ";
	cin >> nivel;
	int hijos = 0;
	int proceso;
	cout << "Soy el proceso Padre: " << getpid() << endl;
	printf("\n");

	while (nivel > 0 && hijos < 2)
	{			   
		proceso = fork();    
       		switch(proceso)
		{
			case -1:
				cout << "Proceso incorrecto";
			case 0:
				cout << "Soy el proceso:  " << getpid() << " y mi padre es: " << getppid() << endl;
				printf("\n");
				nivel--;
				hijos = 0;                                                                
				break;
			default:
				wait(NULL);
				hijos++;
		}			
	}
}
