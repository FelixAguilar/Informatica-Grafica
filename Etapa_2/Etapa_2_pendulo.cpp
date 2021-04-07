// Etapa2.cpp
// Fichero principal 
////////////////////////////////////////////////////
#include <GL/freeglut.h>
#include <math.h>
#include <windows.h>
//#define _USE_MARH_DEFINES

const GLfloat l = 0.52f;
const GLfloat m1 = 1.0f;
const GLfloat m2 = 1.0f;
const GLfloat g = 9.8f;
const GLint polygon_points = 360;
const GLfloat radius = 0.025f;
const GLfloat pi = M_PI;
const GLint W_WIDTH = 1000; // Tamaño incial de la ventana
const GLint W_HEIGHT = 1000;
const GLint W_RATIO = W_WIDTH/W_HEIGHT;
GLint initiated = 0;
GLfloat fAngulo1 = 90.0f; // Variable que indica el ángulo de rotación de los ejes. 
GLfloat fAngulo2 = -30.0f;
GLfloat vel_ang_1_init = 0;
GLfloat vel_ang_2_init = 0;
GLfloat angleTool;//Variable para construir polígonos mediante ángulos;  
//= 2*pi/polygon_points 
GLboolean sentido_horario1 = GL_FALSE;
GLboolean sentido_horario2 = GL_TRUE;
GLint tiempo_1 = 10;

SYSTEMTIME st;
GLfloat tiempo_init;
// Función que visualiza la escena OpenGL
GLfloat toRadians(GLfloat i)
{
	GLfloat r = i*pi / 180;
	return r;
}

void angle_calculus(){

	GLfloat a_ang_1 = -sin(toRadians(fAngulo1)) * g;
	GLfloat a_ang_2 = -sin(toRadians(fAngulo2)) * g;

	GetSystemTime(&st);

	GLfloat tiempo_elapsed = tiempo_init - (st.wSecond + st.wMilliseconds/1000);
	tiempo_init = st.wSecond + st.wMilliseconds/1000;

	GLfloat vel_ang_1 = vel_ang_1_init + a_ang_1 * tiempo_elapsed;
	GLfloat vel_ang_2 = vel_ang_2_init + a_ang_2 * tiempo_elapsed;

	fAngulo1 = vel_ang_1_init * tiempo_elapsed + 0.5f * a_ang_1 * pow(tiempo_elapsed, 2.0f);
	fAngulo2 = vel_ang_2_init * tiempo_elapsed + 0.5f * a_ang_2 * pow(tiempo_elapsed, 2.0f);

	vel_ang_1_init = vel_ang_1;
	vel_ang_2_init = vel_ang_2;

}

void drawScene(){

	GLfloat angleTool = 0.0f;

	// Dibujo del péndulo 2

	// glPushMatrix();
	// glMatrixMode(GL_MODELVIEW);
	// glLoadIdentity();

	// glEnable(GL_LINE_SMOOTH);
	// glBegin(GL_LINES);
	// glLineWidth(0.05);
	// glColor3f(0.5f,0.5f,0.0f);

	// glVertex2d(0.0f, -0.52f);
	// for (GLfloat angle = 0; angle < polygon_points; i++)
    // {
    //     glVertex2d(0.0 + radius * cos(angleTool), -0.52 +radius * sin(angleTool));
    //     angleTool += 2.0f * pi / polygon_points;
    // }
	// glEnd();

	// glPopMatrix();

	// Dibujamos los ejes
	glPushMatrix();

	glEnable(GL_LINE_SMOOTH);
	glBegin(GL_LINES);
	glLineWidth(1);
	glColor3f(0.0f,0.0f,0.0f);

	glVertex2f(-1.0f, 0.0f);
	glVertex2f(1.0f, 0.0f);


	glVertex2f(0.0f, -1.0f);
	glVertex2f(0.0f, 1.0f);

	glEnd();

	glPopMatrix();

	//SEGUNDO PÉNDULO

	glPushMatrix();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(sin(toRadians(fAngulo1))*0.52, 0.52 - cos(toRadians(fAngulo1))*0.52, 0.0f);
	glRotatef(fAngulo2, 0.0f, 0.0f, 1.0f);

	glBegin(GL_POLYGON);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(-0.025f, 0.00f);
	glVertex2f(0.025f, 0.00f);
	glVertex2f(0.025f, -0.52f);
	glVertex2f(-0.025f, -0.52f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.0f, 0.0f, 0.0f);
	angleTool = 0.0f;
    for (GLint i = 0; i < polygon_points; i++)
    {
        glVertex2d(0.0 + radius * cos(angleTool), -0.52 +radius * sin(angleTool));
        angleTool += 2.0f * pi / polygon_points;
    }
    glEnd();

	glPopMatrix();

	//PRIMER PÉNDULO

    glPushMatrix();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(0.0f, 0.52f, 0.0f);
	glRotatef(fAngulo1, 0.0f, 0.0f, 1.0f);
	glTranslatef(0.0f, -0.52f, 0.0f);

	// Creamos a continuación dibujamos los poligonos
	glBegin(GL_POLYGON);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(-0.025f, 0.52f);
	glVertex2f(0.025f, 0.52f);
	glVertex2f(0.025f, 0.0f);
	glVertex2f(-0.025f, 0.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.0f, 0.0f, 0.0f);
	angleTool = 0.0f;
    for (GLint i = 0; i < polygon_points; i++)
    {
        glVertex2d(radius * cos(angleTool), radius * sin(angleTool));
        angleTool += 2.0f * pi / polygon_points;
    }
    glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.0f, 0.0f, 0.0f);
	angleTool = 0.0f;
    for (GLint i = 0; i < polygon_points; i++)
    {
        glVertex2d(0.0 + radius * cos(angleTool), 0.52 + radius * sin(angleTool));
        angleTool += 2.0f * pi / polygon_points;
    }
    glEnd();

	glPopMatrix();

}

void Display(void)
{
	// Borramos la escena
	glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

	drawScene();

	glFlush();
	glutSwapBuffers();
}

void Timer(GLint t)
{


	// GLfloat a_ang_1 = -sin(toRadians(fAngulo1)) * g;
	// GLfloat a_ang_2 = -sin(toRadians(fAngulo2)) * g;

	// GetSystemTime(&st);

	// GLfloat tiempo_elapsed = tiempo_init - (st.wSecond + st.wMilliseconds/1000);
	// tiempo_init = st.wSecond + st.wMilliseconds/1000;

	// GLfloat vel_ang_1 = vel_ang_1_init + a_ang_1 * tiempo_elapsed;
	// GLfloat vel_ang_2 = vel_ang_2_init + a_ang_2 * tiempo_elapsed;

	// fAngulo1 = vel_ang_1_init * tiempo_elapsed + 0.5f * a_ang_1 * pow(tiempo_elapsed, 2.0f);
	// fAngulo2 = vel_ang_2_init * tiempo_elapsed + 0.5f * a_ang_2 * pow(tiempo_elapsed, 2.0f);

	// vel_ang_1_init = vel_ang_1;
	// vel_ang_2_init = vel_ang_2;
	
	// Control Angulo1
	// if (fAngulo1 <= -120)
	// 	sentido_horario1 = GL_TRUE;
	// if (fAngulo1 >= 120)
	// 	sentido_horario1 = GL_FALSE;
	// if (sentido_horario1) {
	// 	fAngulo1 += 3.0f;
	// }
	// else {
	// 	fAngulo1 -= 3.0f;
	// }

	// // Control Angulo2
	// if (fAngulo2 <= -120)
	// 	sentido_horario2 = GL_TRUE;
	// if (fAngulo2 >= 120)
	// 	sentido_horario2 = GL_FALSE;
	// if (sentido_horario2) {
	// 	fAngulo2 += 6.0f;
	// }
	// else {
	// 	fAngulo2 -= 6.0f;
	// }

	// Indicamos que es necesario repintar la pantalla
	angle_calculus();
	glutPostRedisplay();
	glutTimerFunc(tiempo_1, Timer, tiempo_init);
}


void MyReshape(GLint width, GLint height)
{
	GLfloat new_ratio;
	if (height != 0) {
		 new_ratio = (GLfloat)width / (GLfloat)height;
	}
	else {
		new_ratio = width;
	}

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION); // Selecciona la matriz del dibujado
	glLoadIdentity();

	// Cambio de aspect ratio.
	if (new_ratio >= W_RATIO) {
		glOrtho(-1.0 * new_ratio, 1.0 * new_ratio, -1.0, 1.0, 1.0, -1.0);
	}
	else {
		GLfloat aux = 1 / new_ratio;
		glOrtho(-1.0, 1.0, -1.0 * aux, 1.0 * aux, 1.0, -1.0);
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void idle(){
	angle_calculus();
	glutPostRedisplay();
}

// Función principal
int main(int argc, char **argv)
{
	// Inicializamos la librería GLUT
	glutInit(&argc, argv);

	// Indicamos como ha de ser la nueva ventana
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(W_WIDTH, W_HEIGHT);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);

	// Creamos la nueva ventana
	glutCreateWindow("Mi primera Ventana");

	// Indicamos cuales son las funciones de redibujado e idle
	GetSystemTime(&st);
	tiempo_init = st.wSecond + st.wMilliseconds/1000;
	glutDisplayFunc(Display);
	//glutIdleFunc(idle);
	glutTimerFunc(tiempo_1, Timer, 0.0f);

	//Ajuste de proporciones
	glutReshapeFunc(MyReshape);

	// El color de fondo será el negro (RGBA, RGB + Alpha channel)
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glOrtho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);

	// Comienza la ejecución del core de GLUT
	glutMainLoop();
	return 0;
}