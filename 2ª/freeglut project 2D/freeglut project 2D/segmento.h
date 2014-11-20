#ifndef Segmento_H
#define Segmento_H
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <GL/freeglut.h>
#include "PV2D.h"
#include <cmath>
#include <iostream>
using namespace std;

class Segmento{

private:
	
	PV2D a;
	PV2D b;
	GLdouble grado;

// Constructores para acializar las coordenadas
public:

	Segmento::Segmento ( ){};
	Segmento::Segmento ( PV2D i, PV2D f, GLdouble g ){
		this->a= i;
		this->b= f;
		this->grado= g;

	}
	
	~Segmento(){}

	//Geters

	PV2D GetIni(){return this->a;}
	PV2D GetFin(){return this->b;}
	GLdouble GetGrad(){return this->grado;}

	//Seters

	void Seta(PV2D i){this->a=i;}
	void Setb(PV2D f){this->b=f;}
	void Seta(GLdouble g){this->grado=g;}

	//Metodos

	int Segmento::calcularDist(PV2D a , PV2D b){
		return (int)sqrt(pow(b.GetX() - a.GetX(), 2) + pow( b.GetY() - a.GetY(), 2));
	}

	
} ;
#endif