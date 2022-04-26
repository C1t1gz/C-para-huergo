#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include <unistd.h> 
#include <sys/types.h>
#include <sys/wait.h>


using namespace std;


int main(int argc, char* argv[]) 
{
	int dias = atoi(argv[1]);
	int maximosEvitas = atoi(argv[2]);
	int maximosAngeles = atoi(argv[3]);
	int pid = fork();
	srand(time(0));
	int variablePE = atoi(argv[4]);
	int variablePA = atoi(argv[5]);
	int probabilidadE = rand() % variablePE + 1; 
	int probabilidadA = rand() % variablePA + 1;
	if (pid == 0)
	{
		int lilith = fork();
		
		
			if (lilith == 0)
			{
				
				cout << "soy Lili: "<< getpid() << endl;
				printf("\n");
				for(int i = 1; i < dias; i++) 
				{
					cout << "Estamos en el dia: " << i << endl;
					for (int a = 0; a < maximosEvitas; a++)
					{	
						if (int probabilidad2 = rand() % variablePE == probabilidadE)
						{
							int hijoE = fork();
							if (hijoE == 0)
							{
								cout << "Soy el hijo de Lili numero: " << a+1 << endl;
								cout << "Mi pid es: " << getpid() << endl;
								cout << "Mi padre es: " << getppid() << endl;
								printf("\n");
								exit(0);
							}
							// wait(NULL);				
						}
						// wait(NULL);
						// exit(1);
					}
					exit(1);
				}
				exit(0);
				wait(NULL);
			}
			wait(NULL);

			int adam = fork();	
			if (adam == 0 && main != 0)
			{
				cout << "Soy Adam: " << getpid() << endl;
				printf("\n");	
				for(int x = 1; x< dias; x++) 	
				{
					// cout << "Estamos en el dia: " << x << endl; 
					for (int c = 0; c < maximosAngeles; c++)
					{
						if(int probabilidad3 = rand() % variablePA == probabilidadA)
						{	
							int hijoA = fork();
							if (hijoA == 0)
							{
								cout << "Soy el hijo de Adam numero: " << c+1 << endl;
								cout << "Mi pid es: " << getpid() << endl;
								cout << "Mi padre es: " << getppid() << endl;
								printf("\n");
								exit(0);
							}
							wait(NULL);			
						}
					}
				}// wait(NULL);
				exit(0);
			}
		// wait(NULL);
		// exit(1);
	}
	wait(NULL);



}
