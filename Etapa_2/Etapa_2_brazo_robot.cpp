// Etapa_2_brazo_robot.cpp
// Félix Aguilar y Antonio Pujol
////////////////////////////////////////////////////
#include <GL/freeglut.h>
#define _USE_MATH_DEFINES
#include <math.h>

GLfloat fAngulo1 = 0.0f; //Subir y Bajar el Brazo.
GLfloat fAngulo2 = 0.0f; //Subir y bajar Antebrazo.
GLfloat fAngulo3 = 0.0f; // Subir y bajar Muñeca.
GLfloat fAngulo4 = 0.0f; //Abrir y cerrar Mano.

// Constantes para dibujar los circulos.
const GLfloat pi = M_PI;
const GLint polygon_points = 360;
const GLfloat radius_arm= 0.025f;
const GLfloat radius_hand = 0.01f;

//variables para el control de giro de los ángulos.
const GLint tiempo = 10;
GLboolean sentido_horario1 = GL_FALSE;
GLboolean sentido_horario2 = GL_TRUE;
GLboolean sentido_horario3 = GL_TRUE;
GLboolean sentido_horario4 = GL_FALSE;

// Constantes de la ventana.
const GLint W_WIDTH = 800;
const GLint W_HEIGHT = 800;
const GLint W_RATIO = W_WIDTH / W_HEIGHT;
GLfloat aux = 1.0f;
GLdouble new_ratio = 1.0;


// Función que visualiza la escena OpenGL.
GLfloat toRadians(GLfloat i)
{
	GLfloat r = i * (pi / 180);
	return r;
}

void drawScene() {

	GLfloat angleTool = 0.0f;

	// Dibujamos los ejes.
	glPushMatrix();

	glEnable(GL_LINE_SMOOTH);
	glBegin(GL_LINES);
	glLineWidth(1);
	glColor3f(0.0f, 0.0f, 0.0f);

	glVertex2f(-1.0f, 0.0f);
	glVertex2f(1.0f, 0.0f);


	glVertex2f(0.0f, -1.0f);
	glVertex2f(0.0f, 1.0f);

	glEnd();

	glPopMatrix();

	// Mano superior.
	glPushMatrix();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(
		-(0.52 - cos(toRadians(fAngulo1)) * 0.52) + (cos(toRadians(fAngulo2)) * 0.52), 
		(sin(toRadians(fAngulo1)) * 0.52) + (sin(toRadians(fAngulo2)) * 0.52), 
		0.0f);

	glTranslatef(-0.8f + 0.52, -0.2f, 0.0f);	

	glRotatef(45.0f + fAngulo3 + fAngulo4, 0.0f, 0.0f, 1.0f);
	glTranslatef(0.0f, 0.01f, 0.0f);

	glBegin(GL_POLYGON);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(0.12f, -0.01f);
	glVertex2f(0.12f, 0.01f);
	glVertex2f(0.0f, 0.01f);
	glVertex2f(0.0f, -0.01f);
	glEnd();

	glTranslatef(0.12f, 0.0f, 0.0f);
	glRotatef(-90.0f, 0.0f, 0.0f, 1.0f);


	glBegin(GL_POLYGON);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(0.12f, -0.01f);
	glVertex2f(0.12f, 0.01f);
	glVertex2f(0.0f, 0.01f);
	glVertex2f(0.0f, -0.01f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.0f, 0.0f, 0.0f);
	angleTool = 0.0f;
	for (GLint i = 0; i < polygon_points; i++)
	{
		glVertex2d(radius_hand * cos(angleTool), radius_hand * sin(angleTool));
		angleTool += 2.0f * pi / polygon_points;
	}
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.0f, 0.0f, 0.0f);
	angleTool = 0.0f;
	for (GLint i = 0; i < polygon_points; i++)
	{
		glVertex2d(0.12f + radius_hand * cos(angleTool), radius_hand * sin(angleTool));
		angleTool += 2.0f * pi / polygon_points;
	}
	glEnd();

	glPopMatrix();

	// Mano inferior.
	glPushMatrix();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(
		-(0.52 - cos(toRadians(fAngulo1)) * 0.52) + (cos(toRadians(fAngulo2)) * 0.52), 
		(sin(toRadians(fAngulo1)) * 0.52) + (sin(toRadians(fAngulo2)) * 0.52), 
		0.0f);
	
	glTranslatef(-0.8f + 0.52, -0.2f, 0.0f);

	glRotatef(-45.0f + fAngulo3 - fAngulo4, 0.0f, 0.0f, 1.0f);
	glTranslatef(0.0f, -0.01f, 0.0f);

	glBegin(GL_POLYGON);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(0.12f, -0.01f);
	glVertex2f(0.12f, 0.01f);
	glVertex2f(0.0f, 0.01f);
	glVertex2f(0.0f, -0.01f);
	glEnd();

	glTranslatef(0.12f, 0.0f, 0.0f);
	glRotatef(90.0f, 0.0f, 0.0f, 1.0f);


	glBegin(GL_POLYGON);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(0.12f, -0.01f);
	glVertex2f(0.12f, 0.01f);
	glVertex2f(0.0f, 0.01f);
	glVertex2f(0.0f, -0.01f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.0f, 0.0f, 0.0f);
	angleTool = 0.0f;
	for (GLint i = 0; i < polygon_points; i++)
	{
		glVertex2d(radius_hand * cos(angleTool), radius_hand * sin(angleTool));
		angleTool += 2.0f * pi / polygon_points;
	}
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.0f, 0.0f, 0.0f);
	angleTool = 0.0f;
	for (GLint i = 0; i < polygon_points; i++)
	{
		glVertex2d(0.12f + radius_hand * cos(angleTool), radius_hand * sin(angleTool));
		angleTool += 2.0f * pi / polygon_points;
	}
	glEnd();

	glPopMatrix();

	// Antebrazo.
	glPushMatrix();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(-(0.52 - cos(toRadians(fAngulo1)) * 0.52), sin(toRadians(fAngulo1)) * 0.52, 0.0f);
	
	glTranslatef(-0.8f + 0.52, -0.2f, 0.0f);
	glRotatef(fAngulo2, 0.0f, 0.0f, 1.0f);

	glBegin(GL_POLYGON);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(0.52f, -0.025f);
	glVertex2f(0.52f, 0.025f);
	glVertex2f(0.0f, 0.025f);
	glVertex2f(0.0f, -0.025f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.0f, 0.0f, 0.0f);
	angleTool = 0.0f;
	for (GLint i = 0; i < polygon_points; i++)
	{
		glVertex2d(0.52 + radius_arm * cos(angleTool), 0.0 + radius_arm * sin(angleTool));
		angleTool += 2.0f * pi / polygon_points;
	}
	glEnd();

	glPopMatrix();

	// Brazo.

	glPushMatrix();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(-0.8f, -0.2f, 0.0f);
	glRotatef(fAngulo1, 0.0f, 0.0f, 1.0f);
	
	glBegin(GL_POLYGON);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(0.52f, -0.025f);
	glVertex2f(0.52f, 0.025f);
	glVertex2f(0.0f, 0.025f);
	glVertex2f(0.0f,-0.025f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.0f, 0.0f, 0.0f);
	angleTool = 0.0f;
	for (GLint i = 0; i < polygon_points; i++)
	{
		glVertex2d(radius_arm * cos(angleTool), radius_arm * sin(angleTool));
		angleTool += 2.0f * pi / polygon_points;
	}
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.0f, 0.0f, 0.0f);
	angleTool = 0.0f;
	for (GLint i = 0; i < polygon_points; i++)
	{
		glVertex2d(0.52 + radius_arm * cos(angleTool), 0.0 + radius_arm * sin(angleTool));
		angleTool += 2.0f * pi / polygon_points;
	}
	glEnd();

	glPopMatrix();

}

void Display(void)
{
	// Borramos la escena
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
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
	drawScene();

	glFlush();
	glutSwapBuffers();
}

void MyReshape(GLint width, GLint height)
{
	if (height != 0)
	{
		new_ratio = (GLdouble)width / (GLdouble)height;
	}
	else
	{
		new_ratio = width;
	}

	glViewport(0, 0, width, height);
}

void Timer(GLint t) {

	// Control Angulo1
	 if (fAngulo1 <= -45)
	 	sentido_horario1 = GL_TRUE;
	 if (fAngulo1 >= 100)
		sentido_horario1 = GL_FALSE;
	 if (sentido_horario1) {
	 	fAngulo1 += 0.5f;
	 }
	 else {
	 	fAngulo1 -= 0.5f;
	 }

	// Control Angulo2
	 if (fAngulo2 <= -30)
	 	sentido_horario2 = GL_TRUE;
	 if (fAngulo2 >= 60)
	 	sentido_horario2 = GL_FALSE;
	 if (sentido_horario2) {
	 	fAngulo2 += 1.0f;
	 }
	 else {
	 	fAngulo2 -= 1.0f;
	 }

	 // Control Angulo3
	 if (fAngulo3 <= -45)
	 	sentido_horario3 = GL_TRUE;
	 if (fAngulo3 >= 45)
	 	sentido_horario3 = GL_FALSE;
	 if (sentido_horario3) {
	 	fAngulo3 += 0.5f;
	 }
	 else {
	 	fAngulo3 -= 0.5f;
	 }

	 // Control Angulo4
	 if (fAngulo4 <= 0)
	 	sentido_horario4 = GL_TRUE;
	 if (fAngulo4 >= 45)
	 	sentido_horario4 = GL_FALSE;
	 if (sentido_horario4) {
	 	fAngulo4 += 2.0f;
	 }
	 else {
	 	fAngulo4 -= 2.0f;
	 }

	glutPostRedisplay();
	glutTimerFunc(tiempo, Timer, 0.0f);
}

// Función principal
int main(int argc, char** argv)
{
	// Inicializamos la librería GLUT
	glutInit(&argc, argv);

	// Indicamos como ha de ser la nueva ventana
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(W_WIDTH, W_HEIGHT);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);

	// Creamos la nueva ventana
	glutCreateWindow("Etapa_2_brazo_robot");

	// Indicamos cuales son las funciones de redibujado e idle
	glutDisplayFunc(Display);
	glutTimerFunc(tiempo, Timer, 0.0f);

	//Ajuste de proporciones
	glutReshapeFunc(MyReshape);

	// El color de fondo será el negro (RGBA, RGB + Alpha channel)
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glOrtho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);

	// Comienza la ejecución del core de GLUT
	glutMainLoop();
	return 0;
}
