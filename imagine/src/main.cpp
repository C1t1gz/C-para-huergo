#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>
#include <time.h>
#include "filters.h"
#include <thread>
#include <unistd.h>
#include <fstream>      // std::ofstream
#include <sstream>
#include <math.h>       /* sqrt */  
#include <atomic>  

#define ONE_OVER_BILLION 1E-9


using namespace std;

vector<string> separacion(string str, char separador) {
    
    int inicio = 0;
    int final = 0;
    string separado;
    vector<string> resultado;
    
    while(final >= 0){
        final = str.find(separador, inicio);
        separado = str.substr(inicio, final - inicio);
        inicio = final + 1;
        resultado.push_back(separado);
    }
    
    return resultado;
}



void filters(string filter, unsigned int n,float p1,ppm& img, float p2 )
{
	if (filter == "plain")
		plain(img, p1);
	else if (filter == "blackWhite")
		blackWhiteThreaded(img, n);
	else if (filter == "brightness")
		brightnessThreaded(img,p1,n);
	else if (filter == "contrast")
		constrastThreaded(img,p1,n);
	else if (filter == "zoom")
		zoom(img, p1);	
	else if (filter == "sharpen")
		threadedsharpen(img,n);
	else if (filter == "crop")
		crop(img, p1, p2);	
}

// El siguiente es un template basico que pueden usar como base
		
int main(int argc , char* argv[]){
	
	// Asumimos que los filtros sin p1 se escriben primero (por lo tanto, el primer p1 es no nulo)
	// Asumimos que Zoom no se puede encadenar

	if(string(argv[1]) == "-help"){
		cout << "Uso: ./main <'filtro1 filtro2 filtro 3'> <nthreads> <'p1 p12 p13'> <img1> <imagen Modificada> <[p2]>" << endl;
		cout << "otros comandos -filters" << endl;
		return 0; 
	}

	if(string(argv[1]) == "-filters"){
		cout << "blackWhite, brightness, contrast, zoom, sharpen, crop" << endl;
		return 0;
	}
	string filter = string(argv[1]);
	unsigned int n = atoi(argv[2]);
	string p1 = string(argv[3]);
	string img1(argv[4]);
	string out = string(argv[5]);
	float p2 = atof(argv[6]);
	vector<string> filtros =separacion(filter, ' ');
	vector<string> lP1 = separacion(p1,' ');
	
	vector<float> p1V;
		for (int i = 0; i < lP1.size(); i++){
			p1V.push_back(stof(lP1[i]));
		}
	
	
	ppm img(img1);
	
	cout << "Aplicando filtros"<< endl;    	
	struct timespec start, stop;    	
		clock_gettime(CLOCK_REALTIME, &start);

	for(int i = 0; i < filtros.size(); i++){

			filter = filtros[i];
			float p1 = p1V[i];

			filters(filter, n, p1, img, p2);
		}

		clock_gettime(CLOCK_REALTIME, &stop);

		double accum;
		accum = ( stop.tv_sec - start.tv_sec ) + ( stop.tv_nsec - start.tv_nsec ) * ONE_OVER_BILLION;
		printf("%lf s\n", accum);

	cout << "Escribiendo imagen" << endl;
	img.write(out);	
	    
	cout << "Listo" << endl;

	ofstream file;
	file.open("../pruebas/resultados.csv", ios::app);
	string outPrueba = "Ancho: " + to_string(img.width)+ " Alto: " +to_string(img.height) + " Tiempo Tardado: " + to_string(accum) + " Numero de hilos: " + to_string(n) + "\n";
	file << outPrueba;
	file.close();
	return 0;
}




