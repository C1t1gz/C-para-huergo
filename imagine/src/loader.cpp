#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>
#include <time.h>
#include <thread>
#include <unistd.h>
#include <fstream> 
#include <filesystem>
#include <dirent.h>
#include "filters.h"
#define ONE_OVER_BILLION 1E-9
// Liberia de filesystem para la lectura de carpetas
namespace fs = std::filesystem;

using namespace std;



int main(int argc , char* argv[]){
	

	if(string(argv[1]) == "-help"){
		cout << "Uso: ./loader <filtro> <nthreads> <[p1]> <carpeta de origen> <carpeta de destino> <[p2]>" << endl;
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
	string root = string(argv[4]);
	string out = string(argv[5]);
    float p2 = atof(argv[6]);
    
	cout << "Aplicando filtros"<< endl;
	struct timespec start, stop;    	
	clock_gettime(CLOCK_REALTIME, &start);
     
	DIR *dir; struct dirent *diread;
    vector<string> archivos;
    if ((dir = opendir(root.c_str())) != nullptr) {
        while ((diread = readdir(dir)) != nullptr) {
            archivos.push_back(diread->d_name);
        }
        closedir (dir);
    }
    
    for(auto archivo : archivos){
        string tipo; 
        if (archivo.size() > 4){
            tipo = archivo.substr(archivo.size() - 4, 4);
        } 
        if (tipo == ".ppm"){   
            ppm img(root + archivo);
            
            if (filter == "plain")
                plain(img, (unsigned char)p1);
            else if (filter == "blackWhite")
            {
                blackWhiteThreaded(img, n);
            }
            else if (filter == "contrast")
            {
                constrastThreaded(img,p1,n);
            }
            else if (filter == "brightness")
            {
                brightnessThreaded(img,p1,n);
            }
            else if (filter == "zoom")
            {
                zoom(img, p1);
            }
            else if (filter == "sharpen")
            {
                threadedsharpen(img,n);
            }
            else if (filter == "crop")
            {
                crop(img, p1, p2);
            }
            string outFinal = out + archivo;
            cout << "Escribiendo imagen: " << archivo << endl;
            img.write(outFinal);	    
            cout << "Listo" << endl;
        }
    }
    

   	clock_gettime(CLOCK_REALTIME, &stop);

	double accum;
	accum = ( stop.tv_sec - start.tv_sec ) + ( stop.tv_nsec - start.tv_nsec ) * ONE_OVER_BILLION;
    cout << accum;
	
	return 0;
}