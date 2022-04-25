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
	
	if (pid == 0)
	{
		int lilith = fork();
		if (lilith == 0)
		{
			cout << "soy Lilith: "<< getpid() << endl;
			printf("\n");
			for (int a = 0; a < maximosEvitas; a++)
			{
				int hijoE = fork();
				if (hijoE == 0)
				{
					cout << "Soy el hijo de Lilith numero: " << a+1 << endl;
					cout << "Mi pid es: " << getpid() << endl;
					cout << "Mi padre es: " << getppid() << endl;
					printf("\n");
					exit(1);

				}
				wait(NULL);
			}
		}
		wait(NULL);
		int adam = fork();	
		if (adam == 0 && main != 0)
		{
			cout << "Soy Adam: " << getpid() << endl;
			printf("\n");
			for (int c = 0; c < maximosAngeles; c++)
			{
				int hijoA = fork();
				if (hijoA == 0)
				{
					cout << "Soy el hijo de Adam numero: " << c+1 << endl;
					cout << "Mi pid es: " << getpid() << endl;
					cout << "Mi padre es: " << getppid() << endl;
					printf("\n");
					exit(1);

				}
				wait(NULL);
			}
		}
		wait(NULL);
	}
	wait(NULL);



}
