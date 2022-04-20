#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include <unistd.h> 
#include <sys/types.h>
#include <sys/wait.h>


using namespace std;



int main() {
    int pid = fork();

    if (pid == 0)
    {
        int lisa = fork();
        if (lisa == 0){
            cout << "Soy lisa" << endl;
            exit;
        } 
        int bart = fork();
        if (bart == 0 && lisa != 0){
            cout << "Soy bart" << endl;
            exit;
        } 
    }
    else {
        wait(NULL);
        wait(NULL);
    }
    return 0;
}