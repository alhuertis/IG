#ifndef Lapiz_H
#define Lapiz_H
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <GL/freeglut.h>
#include "Segmento.h"
#include "PV2D.h"
#include <math.h>

#include <iostream>
using namespace std;

#define PI 3.14159265358979323846
class Lapiz{

private:

    PV2D *pos;  // Posicion actual 
	GLdouble dir;  // Direccion actual


public:
   
	//constructor y destructor
    Lapiz::Lapiz(){
		this->pos= new PV2D(0,0);
		this->dir=0;
	}
	Lapiz::Lapiz(PV2D* p,GLdouble direction){
		this->pos= p;
		this->dir= direction;
	}
	
	Lapiz::~Lapiz(){};

	//Geters
	PV2D GetPos(){return *pos;}
	GLdouble GetDir(){return this->dir;}

	//Seters
	void setPos(PV2D *p){ this->pos=p;}
	void setDir(GLdouble d){this->dir= d;}


	void Lapiz::moveTo(PV2D* p){
		this->pos=p;	
	}

	void Lapiz::turnTo(GLdouble a){
		this->dir+=a;
	}

	void Lapiz::forward(GLdouble dist, bool draw){
		double xPrima= dist*cos(dir*(PI/180));
		double yPrima= dist*sin(dir*(PI/180));
		PV2D nuevoPunto(pos->GetX() + xPrima, pos->GetY() + yPrima);
		*pos = nuevoPunto;
	}

	

};

#endif