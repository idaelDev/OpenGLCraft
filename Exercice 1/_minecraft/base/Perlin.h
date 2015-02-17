#include <stdlib.h>
#include <math.h>
#include <time.h>

#pragma once
class Perlin
{
public:
	Perlin();
	~Perlin();

	void initBruit1D(int longueur, int pas, int octaves);
	double bruit_coherent1D(double x, double persistance);
	void destroyBruit1D();

	void initBruit2D(int longueur, int hauteur, int pas, int octaves);
	double bruit_coherent2D(double x, double y, double persistance);
	void destroyBruit2D();


};