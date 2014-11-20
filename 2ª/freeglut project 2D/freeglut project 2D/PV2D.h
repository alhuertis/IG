#ifndef PV2D_H
#define PV2D_H
#include <iostream>
#include<cmath>
using namespace std;


class PV2D{


private:
	double coordX;
	double coordY;


public: 

	PV2D::PV2D(void){
		coordX=0;
		coordY=0;
	}

	PV2D::PV2D(double x, double y){
		coordX=x;
		coordY=y;
	}

	//Geters
	const double GetX(){return coordX;}
	const double GetY(){return coordY;}

	//Seters
	void SetX(double x){coordX= x;}
	void SetY(double y){coordY= y;}
	



};
#endif
