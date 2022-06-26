#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <random>
#include <chrono>
#include <math.h>
#include <sys/mman.h>  
#include <string.h>  
#include <tuple>
#include <cassert>
#include <atomic>
#include <fstream>

using namespace std;

void* share_mem(int size);
tuple<int, float, string, float> spawnChildren(int intentosNacimiento, float birthProb, float rageProb, string unitType);
void angeles(int dias, int n, float p2, atomic<float> *qtyAngeles, atomic<float> *angelesPoder);
void evitas(int dias, int m, float p1, float p3, atomic<float> *qtyEvas, atomic<float> *evitasPoder);
float Powers(string my_type);


int main(int argc, char* argv[])
{
	int max_days = atoi(argv[1]);
	int m = atoi(argv[2]); 
	int n = atoi(argv[3]); 
	float p1 = stof(argv[4]);
	float p2 = stof(argv[5]);
	float p3 = stof(argv[6]);
    float margen = stof(argv[7]);

    atomic<float> *qtyEvas = (atomic<float> *) share_mem(max_days + 1);
	atomic<float> *evitasPoder = (atomic<float> *) share_mem(max_days + 1);
	atomic<float> *angelesPoder = (atomic<float> *) share_mem(max_days + 1);
    atomic<float> *qtyAngeles = (atomic<float> *) share_mem(max_days + 1);

    cout << "El nacimiento de los angeles fue: " << endl;
    int pid = fork();
    if (pid == 0){
        
		angeles(max_days, n, p2, qtyAngeles, angelesPoder);   
		exit(0);
    }
    else{

        wait(NULL);
    
    }

    cout << "El nacimiento de los evitas fue: " << endl;
    pid = fork();
    if (pid == 0){
        
		evitas(max_days, m, p1, p3, qtyEvas, evitasPoder);
        exit(0);
    }
    else{

        wait(NULL);
    
    }

    for (int dias = 1; dias <= max_days; dias++){
        
        // Aca ya seteamos el poder
		angelesPoder[dias] = angelesPoder[dias] + angelesPoder[dias - 1];
        evitasPoder[dias] = evitasPoder[dias] + evitasPoder[dias - 1];
    
	}

    bool diaEncontrado = false;
    
	for (int dias = 1; dias <= max_days; dias++){
        if (angelesPoder[dias] - evitasPoder[dias] < margen){
            
            // Aca ya muestra el dia que sobrevivimos en el caso de hacerlo 
			
            diaEncontrado = true;
            
            cout << "Se encontro un dia que coincide con las simulaciones y el margen. El dia que sobrevivimos es el dia numero: " << dias << endl;
            
            break;
    
	    }
    }
    if (diaEncontrado == false){
        
		cout << "Nos re morimos, no hay dias donde nos salvamos" << endl;
    
	}

    // Se crea el archivo
    std::ofstream pepe("resultado.csv");
    
    // Escribo en el archivo
    pepe << max_days << " " << m << " " << n << " " << p1 << " " << p2 << " " << p3 << " " << margen << "\n";
    
	for (int dias = 0; dias <= max_days; dias++){
    
	    pepe << "Dia: " << dias << ", Evitas: " << qtyEvas[dias] << ", Angeles: " << qtyAngeles[dias] << "\n";
    
	}
    
    // Cerrio el archivo
    pepe.close();

    exit(0);

}

void angeles(int dias, int n, float p2, atomic<float> *qtyAngeles, atomic<float> *angelesPoder){

    float poderHijo = 0;
    int ppid = getpid();
    string type = "Angeles";
    float poderAdam = Powers(type);
    qtyAngeles[0] = 1;
    angelesPoder[0] = poderAdam;

    for (int diaActual = 1; diaActual <= dias; diaActual++){
        if(type == "Angeles"){
            
			tuple<int, float, string, float> simulacion = spawnChildren(n, p2, -1, type);
            
			if ("parent" == get<2>(simulacion)){
                
				type = get<2>(simulacion);
                qtyAngeles[diaActual] = qtyAngeles[diaActual] + get<0>(simulacion);
                angelesPoder[diaActual] = angelesPoder[diaActual] + get<1>(simulacion);
                
				if (ppid == getpid()){

                    cout << "Soy: " << getpid() << " tengo un poder de: " << poderAdam << " y tuve " << get<0>(simulacion) << " hijo/s" << endl;
                
				}
                else{

                    cout << "Soy: " << getpid() << " Mi papa es: " << getppid() << " tengo un poder de: " << poderHijo << " y tuve " << get<0>(simulacion) << " hijo/s" << endl;
                
				}                 
            
			}
            else{

                poderHijo = get<3>(simulacion);

                if (diaActual == dias){

                    cout << "El hijo: " << getpid() << " siendo su padre: " << getppid() << " tiene un poder de: " << poderHijo << " y engendro " << "0 hijos" << endl;
                
				}

            }
        }
    }
    if (getpid() != ppid){
        exit(0);
    }
}

void evitas(int dias, int m, float p1, float p3, atomic<float> *qtyEvas, atomic<float> *evitasPoder){

	// recibe dias, y la probabilidad de hacer evitas los intenteos y el poder generado de este
    qtyEvas[0] = 1;
    float poderHijo = 0;
    int ppid = getpid();
    string type = "Evitas";
    float poderlilith = Powers(type);
    evitasPoder[0] = poderlilith;

    for (int diaActual = 1; diaActual <= dias; diaActual++){
        if(type == "Evitas"){
           
		    tuple<int, float, string, float> simulacion = spawnChildren(m, p1, p3, type);

            if ("parent" == get<2>(simulacion)){

                type = get<2>(simulacion);
                qtyEvas[diaActual] = qtyEvas[diaActual] + get<0>(simulacion);
                evitasPoder[diaActual] = evitasPoder[diaActual] + get<1>(simulacion);

                if (ppid == getpid()){
                   
				    cout << "Soy: " << getpid() << " tiene un poder de: " << poderlilith << " y dio nacimiento a " << get<0>(simulacion) << " hijo/s" << endl;
                
				}
                else{
                
				    cout << "Soy: " << getpid() << " Mi padre es:  " << getppid() << " tiene un poder de: " << poderHijo << " y dio nacimiento a " << get<0>(simulacion) << " hijo/s" << endl;
                
				}                 
            }
            else{

                poderHijo = get<3>(simulacion);

                if (diaActual == dias || get<2>(simulacion) == "invalid"){

                    type = get<2>(simulacion);
                    cout << "Soy: " << getpid() << " Mi padre es: " << getppid() << " tiene un poder de: " << poderHijo << " y dio nacimiento a " << "0 hijo/s" << endl;
                
				}

            }
        }
    }
    if (getpid() != ppid){
        
		exit(0);
    
	}
}

tuple<int, float, string, float> spawnChildren(int intentosNacimiento, float birthProb, float rageProb, string unitType){	

	// toma el maximo intento de hijos, las probabilidades de nacimiento y la raza y hace la prueba de nacumiento 
    int pid = -1;
    int children = 0;
    atomic<float> *poder = (atomic<float> *) share_mem(1);
    float unitPower = 0;

    srand(time(NULL));

    for (int i = 0; i < intentosNacimiento; i++){
        if (pid != 0){
            if (((float)rand()) / ((float)RAND_MAX) * (0 - 100) + 100 < birthProb){
                
                children += 1;
                pid = fork();
            
            }
        }
        if (pid == 0){

            unitPower = Powers(unitType);

            if (((float)rand()) / ((float)RAND_MAX) * (0 - 100) + 100 < rageProb){
                
                unitPower *= 2;
                poder[0] = poder[0] + unitPower;
                unitType = "invalid";
                children = 0;
            
            }
            else{
             
                poder[0] = poder[0] + unitPower;
            
            }

            break;
        }
    }

    float poderTotal = poder[0];

    if (pid != 0){
        for (int i = 0; i < children; i++){
            
            wait(NULL);
        
        }
        
        unitType = "parent";
    
    }

    return make_tuple(children, poderTotal, unitType, unitPower);
}

void* share_mem(int size)
{
	// Vamos a pedir size * sizeof(int) para reservar suficiendte memoria 
	// para un vector sizeof nos dice el tamaño del tipo atomic int.
    void * mem;
    if( MAP_FAILED == (mem = (atomic<float>*)mmap(NULL, sizeof(atomic<float>)*size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, -1, 0) ) )
    {
        perror( "mmap failed" );
        exit( EXIT_FAILURE );
    }
    return mem;
}

float Powers(string my_type){
	// Seteamos los valores de la distribución según cada especie
	float u = (my_type == "Evitas") ? 20 : 25;
	float std = (my_type == "Evitas") ? 5 : 10;

	// Inicializamos un generador con distribucion uniforme en el intervalo (0,1)
	// La semilla es aleatoria, pero puede ser util fijarla para facilitar las pruebas	
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    //semilla aca
	default_random_engine generator (seed);  
 	uniform_real_distribution<double> distribution(0.0,1.0);

 	// Inicializamos un generador con distribucion normal
 	normal_distribution<double> ap_distribution(u,std);

    float poder = ap_distribution(generator);

    if (poder < 0){

        poder = 0;
 
    }

    return poder;
}

