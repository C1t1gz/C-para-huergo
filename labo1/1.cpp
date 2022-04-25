#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include <unistd.h> 
#include <sys/types.h>
#include <sys/wait.h>


using namespace std;

int main()
{
	int pid;
	for(int i = 0;i<5;i++){
		pid = fork();
		if(pid==0)
		{
			cout << "Proceso" << i << endl;
			exit (1);
		}
		wait(NULL);
	}

	if(pid > 0){

		wait(NULL);
		cout << "Terminaron todos " << endl;
		exit(0);

	}
}
