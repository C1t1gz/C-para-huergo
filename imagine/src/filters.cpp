#include <iostream>
#include <string>
#include <stdlib.h>
#include <math.h>       /* sqrt */
#include <vector>
#include "filters.h"
#include <thread>  
#include <atomic>  

#define BLACK 0

using namespace std;

// COMPLETAr:)
unsigned char truncate_pixel(float color)
{ 
    return (color > 255) ? 255 : ((color < 0) ? 0: (unsigned char)color); 
}


// Filtro plano como ejemplo

void plain(ppm& img, unsigned char c)
{

	for(int i = 0; i < img.height; i++)
		for(int j = 0; j < img.width; j++)			
			img.setPixel(i, j, pixel(c,c,c));

}

void blackWhite(ppm& img)
{
	int g = 0;
	for(int i = 0; i < img.height; i++)
	{
		for(int j = 0; j < img.width; j++)			
		{
			g = (int)((img.getPixel(i, j).r + img.getPixel(i, j).g + img.getPixel(i, j).b)/3);
			img.setPixel(i,j,pixel(g,g,g).truncate());
		}
	}			
}
void brightness(ppm& img, float b)
{
	for(int i = 0; i < img.height; i++)
	{
		for(int j = 0; j < img.width; j++)			
		{
			int r = img.getPixel(i, j).r;
			int g = img.getPixel(i, j).g;
			int bl = img.getPixel(i, j).b;
			r = r + 255 * b;
			g = g + 255 * b;
			bl = bl + 255 * b; 	
			img.setPixel(i,j,pixel(r,g,bl).truncate());
		}
	}
}


void contraste(ppm& img, float contrast)
{
	for(int i = 0; i < img.height; i++)
	{
		for(int j = 0; j < img.width; j++)			
		{
			int r = img.getPixel(i, j).r;
			int g = img.getPixel(i, j).g;
			int bl = img.getPixel(i, j).b;
			float f = (259*(contrast+255)) / (255*(259-contrast));

			float newr = (f*(r-128)) + 128;
			float newg = (f*(g-128)) + 128;
			float newbl = (f*(bl-128)) +128;
		
			img.setPixel(i,j,pixel(newr,newg,newbl).truncate());		
		}
	}
}



void zoom(ppm &img, int z) {
    ppm imagenNueva(img.width * z, img.height * z);
	for (int i = 0; i < img.height; i++)
	{
		for (int j = 0; j < img.width; j++)
		{
			pixel p = img.getPixel(i, j);

			unsigned int resultadoj = (j + (j * (z - 1)));
			unsigned int resultadoi = (i + (i * (z - 1)));
			for (int offset_i = 0; offset_i < z; offset_i++)
			{
				for (int offset_j = 0; offset_j < z; offset_j++)
				{
					imagenNueva.setPixel(resultadoi + offset_i, resultadoj + offset_j, p);
				}
			}
		}
	}
    img = imagenNueva;
};


void convolutiongeneral(ppm& img, short int ker[]){

    short int r;
    short int g;
    short int b;

	ppm imagenNueva (img.width-2, img.height-2);

    for(int h = 1; h < img.height - 1; h++){
        for(int w = 1; w < img.width - 1; w++){
            r = 0; 
            g = 0;
            b = 0;
            for(int kh = 0; kh < 3; kh++){

                for(int kw = 0; kw < 3; kw++){

                    r = r + img.getPixel(h + kh - 1, w + kw - 1).r * ker[kh * 3 + kw];
                    g = g + img.getPixel(h + kh - 1, w + kw - 1).g * ker[kh * 3 + kw];
                    b = b + img.getPixel(h + kh - 1, w + kw - 1).b * ker[kh * 3 + kw];
                }
            }
            imagenNueva.setPixel(h - 1,w - 1, pixel(r, g, b).truncate());
        }
    }
	img = imagenNueva;
	    
	
}


void sharpen(ppm &img) {

	short int kernel[9] = {
		0,-1,0,
		-1,5,-1,
		0,-1,0
	};
	convolutiongeneral(img, kernel);
}

void crop(ppm &img, int k, int t){
	ppm imagenNueva = ppm(img.width - t, img.height - k);
	for (int i = k; i < img.height; i++)
	{
		for (int j = t; j < img.width; j++)
		{
			imagenNueva.setPixel(i - k, j - t, img.getPixel(i, j));
		}
	}
	img = imagenNueva;
}


// multithread


void blackWhiteWithThreads(ppm& img, int i0, int i1)
{
	int g = 0;
	for(i0; i0 < i1; i0++)
	{
		for(int j = 0; j < img.width; j++)
		{
			g = (int)((img.getPixel(i0, j).r + img.getPixel(i0, j).g + img.getPixel(i0, j).b)/3);
			img.setPixel(i0,j,pixel(g,g,g).truncate());

		}	
	}	
}

void blackWhiteThreaded(ppm& img, int n){

	if (n == 1)
	{
		blackWhite(img);
		return;	
	}
	int limites = int(img.height / n);
	vector<thread> threads;
	for (int i = 0; i < n; i++)
	{
		int inicio = i * limites;
		int fin = (i + 1) * limites;
		threads.push_back(thread(blackWhiteWithThreads, ref(img), inicio, fin));
	}
	for (int i = 0; i < n; i++){
		threads[i].join();
	}
}

void brightnessWithThreads(ppm& img, float b, int i0, int i1)
{
	for(i0; i0 < i1; i0++)
	{
		for(int j = 0; j < img.width; j++)			
		{
			int r = img.getPixel(i0, j).r;
			int g = img.getPixel(i0, j).g;
			int bl = img.getPixel(i0, j).b;
			r = r + 255 * b;
			g = g + 255 * b;
			bl = bl + 255 * b; 	
			img.setPixel(i0,j,pixel(r,g,bl).truncate());
		}
	}
}

void brightnessThreaded(ppm& img, float b, int n){
	if (n==1)
	{
		brightness(img, b);
		return;
	}
	int limites = int(img.height / n);
	vector<thread> threads;
	for (int i = 0; i < n; i++)
	{
		int inicio = i * limites;
		int fin = (i + 1) * limites;
		threads.push_back(thread(brightnessWithThreads, ref(img), b, inicio, fin));
	}
	for (int i = 0; i < n; i++){
		threads[i].join();
	}
}



void contrastWithThreads(ppm& img, float contrast, int i0, int i1)
{
	int f = ((259*(contrast+255))/(255*(259-contrast)));

	for(i0; i0 < i1; i0++)
	{
		for(int j = 0; j < img.width; j++)
		{
			int r = img.getPixel(i0, j).r;
			int g = img.getPixel(i0, j).g;
			int bl = img.getPixel(i0, j).b;
			float f = (259*(contrast+255)) / (255*(259-contrast));

			float newr = (f*(r-128)) + 128;
			float newg = (f*(g-128)) + 128;
			float newbl = (f*(bl-128)) +128;
		
			img.setPixel(i0,j,pixel(newr,newg,newbl).truncate());


		}
	}
}


void constrastThreaded(ppm& img, float contrast, int n){
	if (n==1)
		contraste(img, contrast);

	int limites = int(img.height / n);
	vector<thread> threads;
	for (int i = 0; i < n; i++)
	{
		int inicio = i * limites;
		int fin = (i + 1) * limites;
		threads.push_back(thread(contrastWithThreads, ref(img), contrast, inicio, fin));
	}
	for (int i = 0; i < n; i++){
		threads[i].join();
	}
}



void sharpenwithThreads(ppm& img, ppm img2, int start, int end){

	vector<int> c1 = {0, -1, 0};
	vector<int> c2 = {-1, 5, -1};
	vector<int> c3 = {0, -1, 0};
	vector<vector<int>> matriz = {c1, c2, c3};	

	for(int i = 0; i < img.height; i++){

		if (i == 0 || i == img.height - 1)
			continue;

		for(int j = 0; j < img.width; j++){

			if(j == 0 || j == img.width - 1)
				continue;

			int red = 0;
			int green = 0;
			int blue = 0;

			int r = 0;
			int g = 0;
			int b = 0;

			int x = 0;
			int y = 0;

			for (int height = -1; height <= 1; height++){

				for (int width = -1; width <= 1; width++){
					r = img2.getPixel(i + height, j + width).r;
					g =	img2.getPixel(i + height, j + width).g;
					b = img2.getPixel(i + height, j + width).b;

					red += r * matriz[x][y];
					green += g * matriz[x][y];
					blue += b * matriz[x][y];

					x++;
				}
				x = 0;
				y++;
			}
			img.setPixel(i, j, pixel(red, green, blue).truncate());
		}
	}
}

void threadedsharpen(ppm& img, int n){
	
	if (n==1)
	{
		sharpen(img);
		return;
	}
	ppm imagenNueva = img;

	int limites = int(img.height / n);
	vector<thread> threads;
	for (int i = 0; i < n; i++)
	{
		int inicio = i * limites;
		int fin = (i + 1) * limites;
		threads.push_back(thread(sharpenwithThreads, ref(img), imagenNueva, inicio, fin));
	}
	for (int i = 0; i < n; i++){
		threads[i].join();
	}
}


