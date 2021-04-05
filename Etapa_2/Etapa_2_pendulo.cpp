// Etapa2.cpp
// Fichero principal 
////////////////////////////////////////////////////
#include <GL/freeglut.h>
#include <math.h>
//#define _USE_MARH_DEFINES

const GLfloat pi = M_PI;
const GLint W_WIDTH = 1500; // Tamaño incial de la ventana
const GLint W_HEIGHT = 1500;
const GLint W_RATIO = W_WIDTH/W_HEIGHT;
GLint initiated = 0;
GLfloat fAngulo = 120.0f; // Variable que indica el ángulo de rotación de los ejes. 
GLfloat anglePrevi = 0.0f;
GLfloat fAngulo2 = 0.0;
GLfloat angleTool;//Variable para construir polígonos mediante ángulos;  
//= 2*pi/polygon_points 
GLboolean sentido_horario1 = GL_FALSE;
GLboolean sentido_horario2 = GL_TRUE;
GLint tiempo_1 = 10;
GLint tiempo_2 = 10;
GLfloat xp, yp;
// Función que visualiza la escena OpenGL
GLfloat toRadians(GLfloat i)
{
	GLfloat r = i*pi / 180;
	return r;
}

void drawScene(){

	GLint polygon_points = 360;
	GLfloat radius = 0.025f;
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

	//SEGUNDO PÉNDULO

	glPushMatrix();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(sin(toRadians(fAngulo))*0.52, 0.52 - cos(toRadians(fAngulo))*0.52, 0.0f);
	glRotatef(fAngulo2, 0.0f, 0.0f, 1.0f);

	xp = cos(toRadians(fAngulo))*-0.025f - sin(toRadians(fAngulo))*0.52f;
	yp = cos(toRadians(fAngulo))*0.52f + sin(toRadians(fAngulo))*-0.025f;

	glBegin(GL_POLYGON);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(-0.025f, 0.00f);
	glVertex2f(0.025f, 0.00f);
	glVertex2f(0.025f, -0.52f);
	glVertex2f(-0.025f, -0.52f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.0f, 0.0f, 0.0f);
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
	glRotatef(fAngulo, 0.0f, 0.0f, 1.0f);
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
	glColor3f(0.0f, 0.0f, 1.0f);
    for (GLint i = 0; i < polygon_points; i++)
    {
        glVertex2d(radius * cos(angleTool), radius * sin(angleTool));
        angleTool += 2.0f * pi / polygon_points;
    }
    glEnd();

	angleTool = 0.0f;

	glBegin(GL_POLYGON);
	glColor3f(0.0f, 0.0f, 0.0f);
    for (GLint i = 0; i < polygon_points; i++)
    {
        glVertex2d(0.0 + radius * cos(angleTool), 0.52 +radius * sin(angleTool));
        angleTool += 2.0f * pi / polygon_points;
    }
    glEnd();

	glPopMatrix();

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
	// Control Angulo1
	if (fAngulo <= -120)
		sentido_horario1 = GL_TRUE;
	if (fAngulo >= 120)
		sentido_horario1 = GL_FALSE;
	if (sentido_horario1) {
		fAngulo += 3.0f;
	}
	else {
		fAngulo -= 3.0f;
	}

	// Control Angulo2
	if (fAngulo2 <= -120)
		sentido_horario2 = GL_TRUE;
	if (fAngulo2 >= 120)
		sentido_horario2 = GL_FALSE;
	if (sentido_horario2) {
		fAngulo2 += 6.0f;
	}
	else {
		fAngulo2 -= 6.0f;
	}

	// Indicamos que es necesario repintar la pantalla
	glutPostRedisplay();
	glutTimerFunc(tiempo_1, Timer, 0);
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
	glutDisplayFunc(Display);
	glutTimerFunc(tiempo_1, Timer, 0);

	//Ajuste de proporciones
	glutReshapeFunc(MyReshape);

	// El color de fondo será el negro (RGBA, RGB + Alpha channel)
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glOrtho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);

	// Comienza la ejecución del core de GLUT
	glutMainLoop();
	return 0;
}