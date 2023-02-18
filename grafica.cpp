#include <GL/glut.h>
#include <iostream>
#include <math.h>

using namespace std;

void inicializa();
void grafico();
void valores_x_y(double x[], double y[], double x_inicial, double x_final, int numero_lineas, int& numero_puntos);
double maximo_array(double array[], int numero_puntos);
double minimo_array(double array[], int numero_puntos);
void transformacion(double x[], double y[], int numero_puntos, double x_inicial, double x_final, double x_1, double y_1, double x_2, double y_2);


int main(int argc, char *argv[]) 
{	
	glutInitWindowSize(500, 500);
	glutInit(&argc, argv);
	glutCreateWindow("Graficacion de funciones");
	inicializa();
	glutDisplayFunc(grafico);
	glutMainLoop();
	return 0;
}

void inicializa() 
{
	glClearColor(1,1,1,0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, 500, 0, 500);
}

void grafico() 
{
	double x_inicial = 0, x_final = 0, x_1, y_1, x_2, y_2;
	double x[10000], y[10000];
	int numero_lineas, numero_puntos;
	
	cout << "Ingrese el x inicial: ";
	cin >> x_inicial;
	cout << "Ingrese el x final: ";
	cin >> x_final;
	cout << "Ingrese cuantas lineas quiere: ";
	cin >> numero_lineas;
	cout << "Ingrese x_1: ";
	cin >> x_1;
	cout << "Ingrese y_1: ";
	cin >> y_1;
	cout << "Ingrese x_2: ";
	cin >> x_2;
	cout << "Ingrese y_2: ";
	cin >> y_2;
	
	valores_x_y(x, y, x_inicial, x_final, numero_lineas, numero_puntos);
	transformacion(x, y, numero_puntos, x_inicial, x_final, x_1, y_1, x_2, y_2);
	
	
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0,0,0);
	glBegin(GL_LINES);
	for(int i = 0; i < numero_lineas; i++)
	{
		glVertex2d(x[i], y[i]);
		glVertex2d(x[i + 1], y[i + 1]);
	}	
	glEnd();
	glFlush();
}

void valores_x_y(double x[], double y[], double x_inicial, double x_final, int numero_lineas, int& numero_puntos)
{
	double incremento_x = (x_final - x_inicial) / numero_lineas;
	x[0] = x_inicial;
	
	int i = 0;
	while(x[i] <= x_final + 0.005)
	{
		y[i] =  sin(x[i]);  //funcion
		x[i + 1] = x[i] + incremento_x;
		i++;
	}
	
	numero_puntos = i;
}

double maximo_array(double array[], int numero_puntos)
{
	double maximo = array[0];
	
	for(int i = 0; i < numero_puntos; i++)
	{
		if(maximo < array[i])
			maximo = array[i];
	}
	return maximo;
}

double minimo_array(double array[], int numero_puntos)
{
	double minimo = array[0];
	
	for(int i = 0; i < numero_puntos; i++)
	{
		if(minimo > array[i])
			minimo = array[i];
	}
	return minimo;
}

void transformacion(double x[], double y[], int numero_puntos, double x_inicial, double x_final, double x_1, double y_1, double x_2, double y_2)
{
	double ymin = minimo_array(y, numero_puntos);
	double ymax = maximo_array(y, numero_puntos);
	
	for(int i = 0; i < numero_puntos; i++)
	{
		x[i] = ((x_1-y_1)/(x_inicial-x_final))*x[i] + x_1 -((x_1-y_1)/(x_inicial-x_final))*x_inicial;
	}
	for(int i = 0; i < numero_puntos; i++)
	{
		y[i] = ((x_2-y_2)/(ymin-ymax))*y[i]+ x_2 - ((x_2-y_2)/(ymin-ymax))*ymin;
	}
}
