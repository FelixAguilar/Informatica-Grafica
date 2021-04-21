// Etapa_3.cpp
// Fichero principal.
////////////////////////////////////////////////////
#include <GL/freeglut.h>
#define _USE_MATH_DEFINES
#include <math.h>

GLfloat fAngulo1 = 0.0f; //Subir y Bajar el Brazo.
GLfloat fAngulo2 = 0.0f; //Subir y bajar Antebrazo.
GLfloat fAngulo3 = 0.0f; // Subir y bajar Muñeca.
GLfloat fAngulo4 = 0.0f; //Abrir y cerrar Mano.
GLfloat fAngulo5 = 45.0f; //Giro de la Mano.

// Constantes para dibujar los circulos.
const GLfloat pi = M_PI;
const GLint polygon_points = 360;
const GLdouble radius_arm = 0.05;
const GLdouble radius_hand = 0.025;

//variables para el control de giro de los ángulos.
const GLint tiempo = 10;
GLboolean sentido_horario1 = GL_FALSE;
GLboolean sentido_horario2 = GL_TRUE;
GLboolean sentido_horario3 = GL_TRUE;
GLboolean sentido_horario4 = GL_FALSE;
GLboolean sentido_horario5 = GL_FALSE;

// Constantes de la ventana.
const GLint W_WIDTH = 800;
const GLint W_HEIGHT = 800;
const GLint W_RATIO = W_WIDTH / W_HEIGHT;


// Matriz de transformación


// Función que visualiza la escena OpenGL.
GLfloat toRadians(GLfloat i)
{
	GLfloat r = i * (pi / 180);
	return r;
}

//void draw2DScene() {
//
//	GLfloat angleTool = 0.0f;
//
//	// Dibujamos los ejes.
//	glPushMatrix();
//
//	glEnable(GL_LINE_SMOOTH);
//	glBegin(GL_LINES);
//	glLineWidth(1);
//	glColor3f(0.0f, 0.0f, 0.0f);
//
//	glVertex2f(-1.0f, 0.0f);
//	glVertex2f(1.0f, 0.0f);
//
//
//	glVertex2f(0.0f, -1.0f);
//	glVertex2f(0.0f, 1.0f);
//
//	glEnd();
//
//	glPopMatrix();
//
//	// Mano superior.
//	glPushMatrix();
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//
//	glTranslatef(
//		-(0.52 - cos(toRadians(fAngulo1)) * 0.52) + (cos(toRadians(fAngulo2)) * 0.52),
//		(sin(toRadians(fAngulo1)) * 0.52) + (sin(toRadians(fAngulo2)) * 0.52),
//		0.0f);
//
//	glTranslatef(-0.8f + 0.52, -0.2f, 0.0f);
//
//	glRotatef(45.0f + fAngulo3 + fAngulo4, 0.0f, 0.0f, 1.0f);
//	glTranslatef(0.0f, 0.01f, 0.0f);
//
//	glBegin(GL_POLYGON);
//	glColor3f(1.0f, 0.0f, 0.0f);
//	glVertex2f(0.12f, -0.01f);
//	glVertex2f(0.12f, 0.01f);
//	glVertex2f(0.0f, 0.01f);
//	glVertex2f(0.0f, -0.01f);
//	glEnd();
//
//	glTranslatef(0.12f, 0.0f, 0.0f);
//	glRotatef(-90.0f, 0.0f, 0.0f, 1.0f);
//
//
//	glBegin(GL_POLYGON);
//	glColor3f(1.0f, 0.0f, 0.0f);
//	glVertex2f(0.12f, -0.01f);
//	glVertex2f(0.12f, 0.01f);
//	glVertex2f(0.0f, 0.01f);
//	glVertex2f(0.0f, -0.01f);
//	glEnd();
//
//	glBegin(GL_POLYGON);
//	glColor3f(0.0f, 0.0f, 0.0f);
//	angleTool = 0.0f;
//	for (GLint i = 0; i < polygon_points; i++)
//	{
//		glVertex2d(radius_hand * cos(angleTool), radius_hand * sin(angleTool));
//		angleTool += 2.0f * pi / polygon_points;
//	}
//	glEnd();
//
//	glBegin(GL_POLYGON);
//	glColor3f(0.0f, 0.0f, 0.0f);
//	angleTool = 0.0f;
//	for (GLint i = 0; i < polygon_points; i++)
//	{
//		glVertex2d(0.12f + radius_hand * cos(angleTool), radius_hand * sin(angleTool));
//		angleTool += 2.0f * pi / polygon_points;
//	}
//	glEnd();
//
//	glPopMatrix();
//
//	// Mano inferior.
//	glPushMatrix();
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//
//	glTranslatef(
//		-(0.52 - cos(toRadians(fAngulo1)) * 0.52) + (cos(toRadians(fAngulo2)) * 0.52),
//		(sin(toRadians(fAngulo1)) * 0.52) + (sin(toRadians(fAngulo2)) * 0.52),
//		0.0f);
//
//	glTranslatef(-0.8f + 0.52, -0.2f, 0.0f);
//
//	glRotatef(-45.0f + fAngulo3 - fAngulo4, 0.0f, 0.0f, 1.0f);
//	glTranslatef(0.0f, -0.01f, 0.0f);
//
//	glBegin(GL_POLYGON);
//	glColor3f(1.0f, 0.0f, 0.0f);
//	glVertex2f(0.12f, -0.01f);
//	glVertex2f(0.12f, 0.01f);
//	glVertex2f(0.0f, 0.01f);
//	glVertex2f(0.0f, -0.01f);
//	glEnd();
//
//	glTranslatef(0.12f, 0.0f, 0.0f);
//	glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
//
//
//	glBegin(GL_POLYGON);
//	glColor3f(1.0f, 0.0f, 0.0f);
//	glVertex2f(0.12f, -0.01f);
//	glVertex2f(0.12f, 0.01f);
//	glVertex2f(0.0f, 0.01f);
//	glVertex2f(0.0f, -0.01f);
//	glEnd();
//
//	glBegin(GL_POLYGON);
//	glColor3f(0.0f, 0.0f, 0.0f);
//	angleTool = 0.0f;
//	for (GLint i = 0; i < polygon_points; i++)
//	{
//		glVertex2d(radius_hand * cos(angleTool), radius_hand * sin(angleTool));
//		angleTool += 2.0f * pi / polygon_points;
//	}
//	glEnd();
//
//	glBegin(GL_POLYGON);
//	glColor3f(0.0f, 0.0f, 0.0f);
//	angleTool = 0.0f;
//	for (GLint i = 0; i < polygon_points; i++)
//	{
//		glVertex2d(0.12f + radius_hand * cos(angleTool), radius_hand * sin(angleTool));
//		angleTool += 2.0f * pi / polygon_points;
//	}
//	glEnd();
//
//	glPopMatrix();
//
//	// Antebrazo.
//	glPushMatrix();
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//
//	glTranslatef(-(0.52 - cos(toRadians(fAngulo1)) * 0.52), sin(toRadians(fAngulo1)) * 0.52, 0.0f);
//
//	glTranslatef(-0.8f + 0.52, -0.2f, 0.0f);
//	glRotatef(fAngulo2, 0.0f, 0.0f, 1.0f);
//
//	glBegin(GL_POLYGON);
//	glColor3f(1.0f, 0.0f, 0.0f);
//	glVertex2f(0.52f, -0.025f);
//	glVertex2f(0.52f, 0.025f);
//	glVertex2f(0.0f, 0.025f);
//	glVertex2f(0.0f, -0.025f);
//	glEnd();
//
//	glBegin(GL_POLYGON);
//	glColor3f(0.0f, 0.0f, 0.0f);
//	angleTool = 0.0f;
//	for (GLint i = 0; i < polygon_points; i++)
//	{
//		glVertex2d(0.52 + radius_arm * cos(angleTool), 0.0 + radius_arm * sin(angleTool));
//		angleTool += 2.0f * pi / polygon_points;
//	}
//	glEnd();
//
//	glPopMatrix();
//
//	// Brazo.
//
//	glPushMatrix();
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//
//	glTranslatef(-0.8f, -0.2f, 0.0f);
//	glRotatef(fAngulo1, 0.0f, 0.0f, 1.0f);
//
//	glBegin(GL_POLYGON);
//	glColor3f(1.0f, 0.0f, 0.0f);
//	glVertex2f(0.52f, -0.025f);
//	glVertex2f(0.52f, 0.025f);
//	glVertex2f(0.0f, 0.025f);
//	glVertex2f(0.0f, -0.025f);
//	glEnd();
//
//	glBegin(GL_POLYGON);
//	glColor3f(0.0f, 0.0f, 0.0f);
//	angleTool = 0.0f;
//	for (GLint i = 0; i < polygon_points; i++)
//	{
//		glVertex2d(radius_arm * cos(angleTool), radius_arm * sin(angleTool));
//		angleTool += 2.0f * pi / polygon_points;
//	}
//	glEnd();
//
//	glBegin(GL_POLYGON);
//	glColor3f(0.0f, 0.0f, 0.0f);
//	angleTool = 0.0f;
//	for (GLint i = 0; i < polygon_points; i++)
//	{
//		glVertex2d(0.52 + radius_arm * cos(angleTool), 0.0 + radius_arm * sin(angleTool));
//		angleTool += 2.0f * pi / polygon_points;
//	}
//	glEnd();
//
//	glPopMatrix();
//
//}

void draw3DScene() {

	// Dibujamos los ejes.
	glPushMatrix();

	glEnable(GL_LINE_SMOOTH);
	glBegin(GL_LINES);
	glLineWidth(1);
	glColor3f(0.0f, 0.0f, 0.0f);

	glVertex3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(1.0f, 0.0f, 0.0f);


	glVertex3f(0.0f, -1.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);

	glVertex3f(0.0f, 0.0f, -1.0f);
	glVertex3f(0.0f, 0.0f, 1.0f);

	glEnd();

	// Mano Superior
	glPushMatrix();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(-0.8f, -0.2f, 0.0f);
	glRotatef(fAngulo5, 0.0f, 1.f, 0.f);

	glTranslatef(cos(toRadians(fAngulo1)) * 0.4 + cos(toRadians(fAngulo2)) * 0.4, sin(toRadians(fAngulo1)) * 0.4 + sin(toRadians(fAngulo2)) * 0.4, 0);

	glColor3f(0.0f, 0.0f, 0.0f);
	glutWireSphere(radius_arm, 50, 50);

	glRotatef(45 + fAngulo3 + fAngulo4, 0.0f, 0.0f, 1.0f);
	glTranslatef(0.0f, 0.013f, 0.0f);
	glRotatef(90, 0.0f, 1.0f, 0.0f);
	glColor3f(1.0f, 0.0f, 0.0f);
	glutWireCylinder(radius_hand, 0.2f, 50, 50);

	glTranslatef(0.0f, 0.0f, 0.2f);

	glColor3f(0.0f, 0.0f, 0.0f);
	glutWireSphere(radius_hand, 50, 50);

	glRotatef(90, 1.0f, 0.0f, 0.0f);
	glColor3f(1.0f, 0.0f, 0.0f);
	glutWireCylinder(radius_hand, 0.2f, 50, 50);

	glTranslatef(0.0f, 0.0f, 0.2f);

	glColor3f(0.0f, 0.0f, 0.0f);
	glutWireSphere(radius_hand, 50, 50);


	glPopMatrix();

	// Mano inferior.

	glPushMatrix();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(-0.8f, -0.2f, 0.0f);
	glRotatef(fAngulo5, 0.0f, 1.f, 0.f);

	glTranslatef(cos(toRadians(fAngulo1)) * 0.4 + cos(toRadians(fAngulo2)) * 0.4, sin(toRadians(fAngulo1)) * 0.4 + sin(toRadians(fAngulo2)) * 0.4, 0);


	glRotatef(-45 + fAngulo3 - fAngulo4, 0.0f, 0.0f, 1.0f);
	glTranslatef(0.0f, -0.013f, 0.0f);
	glRotatef(90, 0.0f, 1.0f, 0.0f);
	glColor3f(1.0f, 0.0f, 0.0f);
	glutWireCylinder(radius_hand, 0.2f, 50, 50);

	glTranslatef(0.0f, 0.0f, 0.2f);

	glColor3f(0.0f, 0.0f, 0.0f);
	glutWireSphere(radius_hand, 50, 50);

	glRotatef(-90, 1.0f, 0.0f, 0.0f);
	glColor3f(1.0f, 0.0f, 0.0f);
	glutWireCylinder(radius_hand, 0.2f, 50, 50);

	glTranslatef(0.0f, 0.0f, 0.2f);

	glColor3f(0.0f, 0.0f, 0.0f);
	glutWireSphere(radius_hand, 50, 50);

	glPopMatrix();

	// Antebrazo
	glPushMatrix();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(-0.8f, -0.2f, 0.0f);
	glRotatef(fAngulo5, 0.0f, 1.f, 0.f);

	glTranslatef(cos(toRadians(fAngulo1)) * 0.4, sin(toRadians(fAngulo1)) * 0.4, 0);
	glRotatef(fAngulo2, 0.0f, 0.0f, 1.0f);
	glRotatef(90, 0.0f, 1.0f, 0.0f);

	glColor3f(1.0f, 0.0f, 0.0f);
	glutWireCylinder(radius_arm, 0.4f, 50, 50);

	glColor3f(0.0f, 0.0f, 0.0f);
	glutWireSphere(radius_arm, 50, 50);

	glPopMatrix();

	// Brazo
	glPushMatrix();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(-0.8f, -0.2f, 0.0f);
	glRotatef(fAngulo5, 0.0f, 1.f, 0.f);

	glRotatef(fAngulo1, 0.0f, 0.0f, 1.0f);
	glRotatef(90, 0.0f, 1.0f, 0.0f);


	glColor3f(1.0f, 0.0f, 0.0f);
	glutWireCylinder(radius_arm, 0.4f, 50, 50);

	glColor3f(0.0f, 0.0f, 0.0f);
	glutWireSphere(radius_arm, 50, 50);

	glPopMatrix();

}

void Display(void)
{
	//Activamos buffer de profundidad
	glEnable(GL_DEPTH_TEST);
	// Borramos la escena
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	//draw2DScene();
	draw3DScene();

	glPushMatrix();
	glMatrixMode(GL_PROJECTION);
	glFrustum(-1.0d, 1.0d, -1.0d, 1.0d, 0.5d, 500.0d);
	glPopMatrix();

	glFlush();
	glutSwapBuffers();
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

void Timer(GLint t) {

	//// Control Angulo1
	//if (fAngulo1 <= -45)
	//	sentido_horario1 = GL_TRUE;
	//if (fAngulo1 >= 100)
	//	sentido_horario1 = GL_FALSE;
	//if (sentido_horario1) {
	//	fAngulo1 += 0.5f;
	//}
	//else {
	//	fAngulo1 -= 0.5f;
	//}

	//// Control Angulo2
	//if (fAngulo2 <= -30)
	//	sentido_horario2 = GL_TRUE;
	//if (fAngulo2 >= 60)
	//	sentido_horario2 = GL_FALSE;
	//if (sentido_horario2) {
	//	fAngulo2 += 1.0f;
	//}
	//else {
	//	fAngulo2 -= 1.0f;
	//}

	//// Control Angulo3
	//if (fAngulo3 <= -45)
	//	sentido_horario3 = GL_TRUE;
	//if (fAngulo3 >= 45)
	//	sentido_horario3 = GL_FALSE;
	//if (sentido_horario3) {
	//	fAngulo3 += 0.5f;
	//}
	//else {
	//	fAngulo3 -= 0.5f;
	//}

	//// Control Angulo4
	//if ((GetKeyState(VK_LBUTTON) & 0x8000) != 0) {
	//	if (fAngulo4 < 45)
	//	{
	//		fAngulo4 += 1.0f;
	//	}
	//}
	//else {
	//	if (fAngulo4 > 0)
	//	{
	//		fAngulo4 -= 1.0f;
	//	}
	//}

	//// Control Angulo5
	//if (fAngulo5 <= -90)
	//	sentido_horario5 = GL_TRUE;
	//if (fAngulo5 >= 90)
	//	sentido_horario5 = GL_FALSE;
	//if (sentido_horario5) {
	//	fAngulo5 += 0.5f;
	//}
	//else {
	//	fAngulo5 -= 0.5f;
	//}

	// Control Angulo1 Q - A
	if ((GetKeyState(0x51) & 0x8000) != 0) {
		if (fAngulo1 < 100)
		{
			fAngulo1 += 1.0f;
		}
	}
	if ((GetKeyState(0x41) & 0x8000) != 0) {
		if (fAngulo1 > -45)
		{
			fAngulo1 -= 1.0f;
		}
	}

	// Control Angulo2 W - S
	if ((GetKeyState(0x57) & 0x8000) != 0) {
		if (fAngulo2 < 45)
		{
			fAngulo2 += 1.0f;
		}
	}
	if ((GetKeyState(0x53) & 0x8000) != 0) {
		if (fAngulo2 > -50)
		{
			fAngulo2 -= 1.0f;
		}
	}

	// Control Angulo3 E - D
	if ((GetKeyState(0x45) & 0x8000) != 0) {
		if (fAngulo3 < 30)
		{
			fAngulo3 += 1.0f;
		}
	}
	if ((GetKeyState(0x44) & 0x8000) != 0) {
		if (fAngulo3 > -30)
		{
			fAngulo3 -= 1.0f;
		}
	}

	// Control Angulo4 R - F
	if ((GetKeyState(0x52) & 0x8000) != 0) {
		if (fAngulo4 < 45)
		{
			fAngulo4 += 1.0f;
		}
	}
	if ((GetKeyState(0x46) & 0x8000) != 0) {
		if (fAngulo4 > 0)
		{
			fAngulo4 -= 1.0f;
		}
	}

	// Control Angulo5 T - G
	if ((GetKeyState(0x54) & 0x8000) != 0) {
		if (fAngulo5 < 100)
		{
			fAngulo5 += 1.0f;
		}
	}
	if ((GetKeyState(0x47) & 0x8000) != 0) {
		if (fAngulo5 > -100)
		{
			fAngulo5 -= 1.0f;
		}
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
	glutCreateWindow("Mi primera Ventana");

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