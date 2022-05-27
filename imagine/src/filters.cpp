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
		    // img.getPixel(i,j).sub(128).mult(f).add(128).truncate();		
		}
	}
}


