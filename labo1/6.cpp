#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include <unistd.h> 
#include <sys/types.h>
#include <sys/wait.h>


using namespace std;


int main() {
	int a;
	cin >> a;
	string color ;
	cout << "Soy el Padre " << endl;
	cout << "Mi pid es: " << getpid() << endl;
	cout << "No tengo color" << endl;
	printf("\n");
	int pid;

	for (int i = 0; i < a; i++)
	{
		if (i % 2==0)
		{
			color = "Negro";
		}
		else
		{
			color = "Rojo";
		}
		
		pid = fork();

		if (pid == 0)
		{
			cout << "Soy el numero: " << i << endl;
			cout << "Mi pid es: " << getpid() << endl;
			cout << "Mi padre es: " << getppid() << endl;
			cout << "Mi color es: " << color << endl;
			printf("\n");
			exit(1);
		}
		else
		{
			wait(NULL);
		}
	}
}
