#ifndef Copo_H
#define Copo_H
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <GL/freeglut.h>
#include <list>
#include "segmento.h"
#include "lapiz.h"


#include <iostream>
using namespace std;

class Copo {

private:
	
	std::list<Segmento> lista;   //lista de segmentos
	

public:


	//Inicializa el primer triangulo
	Copo::Copo(GLdouble centroX, GLdouble centroY, double longitud, double alturaTriangulo){
		
		PV2D tr1= PV2D(centroX-longitud, centroY-(alturaTriangulo/2));  //vertice izquierdo
		PV2D tr2= PV2D(centroX, centroY+(alturaTriangulo/2));			//vertice superior
		PV2D tr3= PV2D(centroX+longitud, centroY-(alturaTriangulo/2));	//vertice derecho

		Segmento ini= Segmento(tr1,tr2,60);		//segmento izquierdo
		Segmento md= Segmento(tr2,tr3,-60);		//segmento derecho	
		Segmento fin= Segmento(tr3,tr1,180);	//segmento inferior

		//añado segmentos al final de la lista
		lista.push_back(ini);
		lista.push_back(md);
		lista.push_back(fin);
	}
	
	~Copo(){}

	//devuelvo la lista
	std::list<Segmento> Copo::getList(){return lista;}


	
	void Copo::construyeAlgoritmo(void){
		int auxListas= lista.size();

		for(int i=0; i < auxListas; i++){  //recorro la lista de segmentos y le doy forma a cada segmento llamando al procedimiento
			Segmento aux = lista.front();  //cojo el primer segmento de la lista
			lista.pop_front();			   //lo borro de la lista
			construyeP(aux);			   //contruyo el algoritmo sobre dicho segmento
		}
		
	}


	void Copo::construyeP(Segmento s){

		Lapiz x= Lapiz(&s.GetIni(), s.GetGrad());		//creo el lapiz al principio del segmento con los grados a seguir
		int longitud= s.calcularDist(s.GetIni(), s.GetFin())/3;  //longitud es la distancia de la tercera parte del segmento
		x.forward(longitud, true);  //avanzo el lapiz dicha longitud
		Segmento uno= Segmento(s.GetIni(), x.GetPos(), x.GetDir());  //creo un nuevo segmento desde el inicio hasta la posicion del lapiz
		lista.push_back(uno);  //lo añado a la lista
		x.turnTo(+60);  //cambio el angulo del lapiz para empezar con el pico
		x.forward(longitud, true);		//avanzo esa longitud
		Segmento dos= Segmento(uno.GetFin(), x.GetPos(), x.GetDir());  //creo el segmento desde donde termino uno hasta la pos del lapiz
		lista.push_back(dos);  //lo añado a la lista
		x.turnTo(-120);  //cambio el angulo del lapiz
		x.forward(longitud, true);  //avanzo
		Segmento tres= Segmento(dos.GetFin(), x.GetPos(), x.GetDir()); //creo el tercer segmento
		lista.push_back(tres);  //lo añado a la lista
		x.turnTo(60);  //cambio los grados
		x.forward(longitud, true);  //avanzo
		Segmento cuatro= Segmento(tres.GetFin(), x.GetPos(), x.GetDir());  //creo el cuarto
		lista.push_back(cuatro);  //lo añado a la lista
		

	}


} ;
#endif