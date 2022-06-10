#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>
#include <time.h>
#include "filters.h"
#include <thread>
#include <unistd.h>
#include <fstream>      // std::ofstream
#define ONE_OVER_BILLION 1E-9


using namespace std;

// El siguiente es un template basico que pueden usar como base
		
int main(int argc , char* argv[]){
	
	// Asumimos que los filtros sin p1 se escriben primero (por lo tanto, el primer p1 es no nulo)
	// Asumimos que Zoom no se puede encadenar

	if(string(argv[1]) == "-help"){
		cout << "Uso: ./main <filtro> <nthreads> <[p1]> <img1> <imagen Modificada> <[p2]>" << endl;
		cout << "otros comandos -filters" << endl;
		return 0; 
	}

	if(string(argv[1]) == "-filters"){
		cout << "blackWhite, brightness, contrast, zoom, sharpen, crop" << endl;
		return 0;
	}
	string filter = string(argv[1]);
	unsigned int n = atoi(argv[2]);
	float p1 = atof(argv[3]);
	string img1(argv[4]);
	string out = string(argv[5]);
	float p2 = atof(argv[6]);
	
	ppm img(img1);
	
	cout << "Aplicando filtros"<< endl;
	struct timespec start, stop;    	
	clock_gettime(CLOCK_REALTIME, &start);


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

	else 
		cout << "haha filters go brrr" << endl;	
	
   	clock_gettime(CLOCK_REALTIME, &stop);

	double accum;
	accum = ( stop.tv_sec - start.tv_sec ) + ( stop.tv_nsec - start.tv_nsec ) * ONE_OVER_BILLION;
	printf("%lf s\n", accum);

	cout << "Escribiendo imagen" << endl;
	img.write(out);	
	    
	cout << "Listo" << endl;
	return 0;
}




