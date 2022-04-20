#include <iostream>
#include<stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <cstring>
#include <stdio.h>
#include <malloc.h>
#include <unistd.h> 
#include <sys/types.h>
#include <sys/wait.h>


using namespace std;


int main() {
    
    string comando;
    cout << "Ingrese el comando a ejecutar" << endl;
    cin >> comando;    

    string opcion;
    cout << "Ingrese la opcion a  ejecutar" << endl;
    cin >> opcion;

    if (opcion == ""){
	    cout << "Opcion vacia" << endl;
    }

    char* cmd = strdup(comando.c_str());  
    
    
    char* argv[3];
    argv[0] = strdup(comando.c_str());
    argv[1] = strdup(opcion.c_str());
    argv[2] = NULL;

    execvp(cmd, argv);
 
}
