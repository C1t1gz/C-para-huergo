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

// COMPLETAR :)
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


void contrast(ppm& img, float contrast)
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

void convolutiongeneral(ppm& img, int kernel[3][3]) {
	ppm imagenNueva (img.width-2, img.height-2);
	for(int i = 1; i < img.height-1; i++) {
		for(int j = 1; j < img.width-1; j++) {
			pixel suma;
			for(int a = -1; a <=1; a++) {
				for(int b = -1; b <=1; b++) {
					suma.addp(img.getPixel(i+i, j+a).mult(kernel[i+1][j+1])); 
				}
			}
			imagenNueva.setPixel(i-1,j-1, suma.mult((float)1/9).truncate());
		}
	}
	img = imagenNueva;
}

void zoom(ppm &img, int z) {
    ppm imagenNueva(img.width * z, img.height * z);
	for (size_t i = 0; i < img.height; i++)
	{
		for (size_t j = 0; j < img.width; j++)
		{
			pixel p = img.getPixel(i, j);

			unsigned int resultadoj = (j + (j * (z - 1)));
			unsigned int resultadoi = (i + (i * (z - 1)));
			for (size_t offset_i = 0; offset_i < z; offset_i++)
			{
				for (size_t offset_j = 0; offset_j < z; offset_j++)
				{
					imagenNueva.setPixel(resultadoi + offset_i, resultadoj + offset_j, p);
				}
			}
		}
	}
    img = imagenNueva;
};


void sharpen(ppm &img) {

	int kernel[3][3] = {
		{0,-1,0},
		{-1,5,-1},
		{0,-1,0}
	};
	convolutiongeneral(img, kernel);

}

void crop(ppm &img, int k, int t){
	ppm imagenNueva = ppm(img.width - t, img.height - k);
	for (size_t i = k; i < img.height; i++)
	{
		for (size_t j = t; j < img.width; j++)
		{
			imagenNueva.setPixel(i - k, j - t, img.getPixel(i, j));
		}
	}
	img = imagenNueva;
};