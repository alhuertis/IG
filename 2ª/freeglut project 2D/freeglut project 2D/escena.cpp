#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <GL/freeglut.h>
#include "lapiz.h"
#include <list>
#include "copo.h"
#include <math.h>


#include <iostream>
using namespace std;

// Freeglut parameters
// Flag telling us to keep processing events
// bool continue_in_main_loop= true; //(**)

// Viewport size
int WIDTH= 500, HEIGHT= 350;

// Scene visible area size
GLdouble xLeft= 0.0, xRight= 500.0, yBot= 0.0, yTop= 350.0;

// Scene variables
//GLdouble yTriangle= 0.1*(yTop-yBot);
//GLdouble triangleWidth= 2.0*triangleHeight/sqrt(3);
//GLdouble xTriangle= (xRight-xLeft)/2.0-triangleWidth/2.0;

GLdouble triangleHeight= 0.50*(yTop-yBot);
GLdouble centroX = (xRight-xLeft)/2;
GLdouble centroY =(yTop-yBot)/2;
double longitud= (sqrt(pow(triangleHeight,2)/3));

//creo el copo


void intitGL(){

	glClearColor(0.0,0.0,0.0,1.0);
	glColor3f(0.8,0.8,0.8); 

	glPointSize(4.0);
	glLineWidth(2.0);

	// Viewport
    glViewport(0, 0, WIDTH, HEIGHT);
    
	// Model transformation
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Scene Visible Area
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(xLeft, xRight, yBot, yTop); 
 }


void display(void){
  glClear( GL_COLOR_BUFFER_BIT );

  //obtengo en aux la lista de segmentos que forman el copo para dibujarlo desde display
  list<Segmento> aux= cop.getList();

  //recorro la lista uniendo los puntos x, y de cada vertice
  for(std::list<Segmento>::iterator it= aux.begin(); it!= aux.end(); it++){
	  
	  glBegin(GL_LINES);

	  glVertex2d(it->GetIni().GetX(), it->GetIni().GetY());
	  glColor3f(0.1,0.8,0.8); 
	  glVertex2d(it->GetFin().GetX(), it->GetFin().GetY());
	  glColor3f(0.1,0.2,0.3); 
	  glEnd();
  }

  glFlush();
  glutSwapBuffers();
}


void resize(int newWidth, int newHeight){
  //Resize Viewport
  WIDTH= newWidth;
  HEIGHT= newHeight;
  GLdouble RatioViewPort= (float)WIDTH/(float)HEIGHT;
  glViewport ( 0, 0, WIDTH, HEIGHT ) ;
  
  //Resize Scene Visible Area 
  //Se actualiza el área visible de la escena
  //para que su ratio coincida con ratioViewPort
  GLdouble SVAWidth= xRight-xLeft;
  GLdouble SVAHeight= yTop-yBot;
  GLdouble SVARatio= SVAWidth/SVAHeight;
  if (SVARatio >= RatioViewPort) {
	 // Increase SVAHeight
     GLdouble newHeight= SVAWidth/RatioViewPort;
	 GLdouble yMiddle= ( yBot+yTop )/2.0;
     yTop= yMiddle + newHeight/2.0;
     yBot= yMiddle - newHeight/2.0;
     }
  else {
     //Increase SVAWidth
     GLdouble newWidth= SVAHeight*RatioViewPort;
     GLdouble xMiddle= ( xLeft+xRight )/2.0;
	 xRight= xMiddle + newWidth/2.0;
     xLeft=  xMiddle - newWidth/2.0;
  }

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(xLeft, xRight, yBot, yTop);
}

void zoom(double factor){
	 GLdouble newHeight = 0.0;
     GLdouble newWidth = 0.0;

     GLdouble yMiddle = yBot + ((yTop - yBot) / 2.0);
     GLdouble xMiddle = xLeft + ((xRight -xLeft) / 2.0);
	
     newHeight = (yTop - yBot) * factor ;
     newWidth =  (xRight - xLeft) * factor;

     yTop = yMiddle + (newHeight / 2.0);
     yBot = yMiddle - (newHeight / 2.0);
     xRight = xMiddle + (newWidth / 2.0);
     xLeft =  xMiddle - (newWidth / 2.0);
     
     glMatrixMode(GL_PROJECTION);
     glLoadIdentity();
     gluOrtho2D(xLeft, xRight, yBot, yTop);
}

double tranformaX(double x, double escalaAncho){

	double puntoX= ( x / escalaAncho) + xLeft;
	return puntoX;

}

double tranformaY(double y, int height, double escalaAlto){

	double puntoY= (( height - y) / escalaAlto)+ yBot;
	return puntoY;

}

void mouse(int buton, int state, int x, int y){
	if (buton==GLUT_LEFT_BUTTON && state==GLUT_DOWN) {
		double ancho, alto;

		ancho= xRight - xLeft;
		alto= yTop - yBot;

		double escalaAlto, escalaAncho;

		escalaAncho= WIDTH / ancho;
		escalaAlto= HEIGHT / alto;

		xRight= tranformaX(x, escalaAncho) + (ancho / 2);
		xLeft= tranformaX(x, escalaAncho) - (ancho / 2);
		yTop= (tranformaY(y, HEIGHT, escalaAlto) + (alto / 2));
		yBot= (tranformaY(y, HEIGHT, escalaAlto) - (alto / 2));
	

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(xLeft, xRight, yBot, yTop);

		display();
		
	}

}

void moveX(double x) {
	xLeft += x;
	xRight += x;
	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	gluOrtho2D(xLeft, xRight, yBot, yTop);
}

void moveY(double y) {  
	yTop += y;
	yBot += y;
	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	gluOrtho2D(xLeft, xRight, yBot, yTop);
}

void zoomProgresivo(GLdouble factor, int nIter){

	GLdouble fIncr = (1+factor)/nIter; 
	GLdouble centroX = (xRight + xLeft)/2.0;  //Calculamos el centro antiguo del eje de las x
	GLdouble centroY = (yTop +yBot)/2.0; //Calculamos el centro antiguo del eje de las y 
	GLdouble anchoNew, altoNew;
	GLdouble ancho = xRight -xLeft;  //Ancho antiguo
	GLdouble alto = yTop -yBot;  //Alto antiguo
	
	//Bucle progresivo
	for(int i=0; i<=nIter; i++){
		GLdouble fAux= 1 + fIncr*i;
		anchoNew= ancho/fAux; //Nuevo ancho
		altoNew = alto/fAux; //Nuevo alto

		//Nueva area visible de la escena
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(centroX-anchoNew/2.0,centroX+anchoNew/2.0,centroY-altoNew/2.0,centroY+altoNew/2.0);
		
		display();
		Sleep(50);
			
	}

	//Actualizamos xLeft,xRight,yBot,yTop
	xRight= (centroX + anchoNew/2.0);
	xLeft= (centroX - anchoNew/2.0);
	yTop= (centroY + altoNew/2.0);
	yBot= (centroY - altoNew/2.0);		
}




void key(unsigned char key, int x, int y){
 
  bool need_redisplay = true;

  switch (key) {
  case 27:  /* Escape key */
    //continue_in_main_loop = false; // (**)
	glutLeaveMainLoop (); //Freeglut's sentence for stopping glut's main loop (*)
    break;

  case '-' :
    zoom(1.1);
    break;

  case '+' :
    zoom(0.9);
    break ;

  case 'z' :
	zoomProgresivo(0.5, 15); //nos acercamos progresivamente
	break;

  case 'x':
	  zoomProgresivo(-1.5, 15); //nos alejamos progresivamente
	  break;
		

  case 'a' :
	moveX(-10.0);
	break;

  case 'd' :
	moveX(10.0);
	break;

  case 'w' :
	moveY(10.0);
	break;

  case 's' :
	moveY(-10);
	break;


  default:
    need_redisplay = false;
    break;
  }//switch

  if (need_redisplay)
    glutPostRedisplay();
    
}



int main(int argc, char *argv[]){
  cout<< "Starting console..." << endl << endl;

  cout << "Comandos:" << endl << endl;
  cout << "\t+ \t->\t Zoom positivo (nos acercamos)" << endl;
  cout << "\t- \t->\t Zoom negativo (nos alejamos)" << endl;
  cout << "\tz \t->\t Zoom progresivo positivo (nos acercamos)" << endl;
  cout << "\tx \t->\t Zoom progresivo negativo (nos alejamos)" << endl;
  cout << "\tw \t->\t Desplazamiento hacia arriba" << endl;
  cout << "\td \t->\t Desplazamiento hacia la derecha" << endl;
  cout << "\ts \t->\t Desplazamiento hacia abajo" << endl;
  cout << "\ta \t->\t Desplazamiento hacia la izquierda" << endl;
  
 
  int my_window; //my window's identifier

  //Initialization
  glutInitWindowSize(WIDTH, HEIGHT);
  glutInitWindowPosition (340, 210);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE );
  glutInit(&argc, argv);

  //Window construction
  my_window = glutCreateWindow( "Freeglut 2D-project" );
    
  //Callback registration
  glutReshapeFunc(resize);
  glutKeyboardFunc(key);
  glutDisplayFunc(display);
  glutMouseFunc(mouse);

  //OpenGL basic setting
  intitGL();


  // Freeglut's main loop can be stopped executing (**)
  //while ( continue_in_main_loop )
  //  glutMainLoopEvent();

  // Classic glut's main loop can be stopped after X-closing the window,
  // using the following freeglut's setting (*)
  glutSetOption ( GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION ) ;
    
  // Classic glut's main loop can be stopped in freeglut using (*)
  glutMainLoop(); 
  
  // We would never reach this point using classic glut
  system("PAUSE"); 
   
  return 0;
}

