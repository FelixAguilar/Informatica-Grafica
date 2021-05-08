// Etapa_3.cpp
// Fichero principal.
////////////////////////////////////////////////////
#include <GL/freeglut.h>
#define _USE_MATH_DEFINES
#include <math.h>

GLfloat fAngulo1 = 0.0f; //Subir y Bajar el Brazo.
GLfloat fAngulo2 = 0.0f; //Subir y bajar Antebrazo.
GLfloat fAngulo3 = 0.0f; // Subir y bajar Mu�eca.
GLfloat fAngulo4 = 0.0f; //Abrir y cerrar Mano.
GLfloat fAngulo5 = 45.0f; //Giro de la Mano.

GLdouble new_ratio;

// Constantes para dibujar los circulos.
const GLfloat pi = M_PI;
const GLint polygon_points = 360;
const GLdouble radius_arm = 0.05;
const GLdouble radius_hand = 0.025;

//variables para el control de giro de los �ngulos.
const GLint tiempo = 10;
GLboolean sentido_horario1 = GL_FALSE;
GLboolean sentido_horario2 = GL_TRUE;
GLboolean sentido_horario3 = GL_TRUE;
GLboolean sentido_horario4 = GL_FALSE;
GLboolean sentido_horario5 = GL_FALSE;

// Constantes de la ventana.
const GLint W_WIDTH = 600;
const GLint W_HEIGHT = 600;
const GLint W_RATIO = W_WIDTH / W_HEIGHT;

// UP vector for camera.
GLdouble eye_vector[3] = {0.0,0.0,1.0};

GLfloat toRadians(GLfloat i)
{
	GLfloat r = i * (pi / 180);
	return r;
}

void draw3DScene() {

	glMatrixMode(GL_PROJECTION); // Selecciona la matriz del dibujado
	glLoadIdentity();

	// Cambio de aspect ratio.
	gluPerspective(55.0, new_ratio, 0.2, 150.0);
	gluLookAt(eye_vector[0], eye_vector[1], eye_vector[2], 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	glMatrixMode(GL_MODELVIEW);

	// Dibujamos los ejes.
	glPushMatrix();

	glTranslatef(-0.4f, -0.2f, -1.5f);

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

	glTranslatef(-0.4f, -0.2f, -1.5f);
	glRotatef(fAngulo5, 0.0f, 1.f, 0.f);

	glTranslatef(cos(toRadians(fAngulo1)) * 0.4 + cos(toRadians(fAngulo2)) * 0.4, sin(toRadians(fAngulo1)) * 0.4 + sin(toRadians(fAngulo2)) * 0.4, 0);

	glColor3f(0.0f, 0.0f, 0.0f);
	glutSolidSphere(radius_arm, 50, 50);

	glRotatef(45 + fAngulo3 + fAngulo4, 0.0f, 0.0f, 1.0f);
	glTranslatef(0.0f, 0.013f, 0.0f);
	glRotatef(90, 0.0f, 1.0f, 0.0f);
	glColor3f(1.0f, 0.0f, 0.0f);
	glutSolidCylinder(radius_hand, 0.2f, 50, 50);

	glTranslatef(0.0f, 0.0f, 0.2f);

	glColor3f(0.0f, 0.0f, 0.0f);
	glutSolidSphere(radius_hand, 50, 50);

	glRotatef(90, 1.0f, 0.0f, 0.0f);
	glColor3f(1.0f, 0.0f, 0.0f);
	glutSolidCylinder(radius_hand, 0.2f, 50, 50);

	glTranslatef(0.0f, 0.0f, 0.2f);

	glColor3f(0.0f, 0.0f, 0.0f);
	glutSolidSphere(radius_hand, 50, 50);


	glPopMatrix();

	// Mano inferior.

	glPushMatrix();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(-0.4f, -0.2f, -1.5f);
	glRotatef(fAngulo5, 0.0f, 1.f, 0.f);

	glTranslatef(cos(toRadians(fAngulo1)) * 0.4 + cos(toRadians(fAngulo2)) * 0.4, sin(toRadians(fAngulo1)) * 0.4 + sin(toRadians(fAngulo2)) * 0.4, 0);


	glRotatef(-45 + fAngulo3 - fAngulo4, 0.0f, 0.0f, 1.0f);
	glTranslatef(0.0f, -0.013f, 0.0f);
	glRotatef(90, 0.0f, 1.0f, 0.0f);
	glColor3f(1.0f, 0.0f, 0.0f);
	glutSolidCylinder(radius_hand, 0.2f, 50, 50);

	glTranslatef(0.0f, 0.0f, 0.2f);

	glColor3f(0.0f, 0.0f, 0.0f);
	glutSolidSphere(radius_hand, 50, 50);

	glRotatef(-90, 1.0f, 0.0f, 0.0f);
	glColor3f(1.0f, 0.0f, 0.0f);
	glutSolidCylinder(radius_hand, 0.2f, 50, 50);

	glTranslatef(0.0f, 0.0f, 0.2f);

	glColor3f(0.0f, 0.0f, 0.0f);
	glutSolidSphere(radius_hand, 50, 50);

	glPopMatrix();

	// Antebrazo
	glPushMatrix();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(-0.4f, -0.2f, -1.5f);
	glRotatef(fAngulo5, 0.0f, 1.f, 0.f);

	glTranslatef(cos(toRadians(fAngulo1)) * 0.4, sin(toRadians(fAngulo1)) * 0.4, 0);
	glRotatef(fAngulo2, 0.0f, 0.0f, 1.0f);
	glRotatef(90, 0.0f, 1.0f, 0.0f);

	glColor3f(1.0f, 0.0f, 0.0f);
	glutSolidCylinder(radius_arm, 0.4f, 50, 50);

	glColor3f(0.0f, 0.0f, 0.0f);
	glutSolidSphere(radius_arm, 50, 50);

	glPopMatrix();

	// Brazo
	glPushMatrix();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(-0.4f, -0.2f, -1.5f);
	glRotatef(fAngulo5, 0.0f, 1.f, 0.f);

	glRotatef(fAngulo1, 0.0f, 0.0f, 1.0f);
	glRotatef(90, 0.0f, 1.0f, 0.0f);


	glColor3f(1.0f, 0.0f, 0.0f);
	glutSolidCylinder(radius_arm, 0.4f, 50, 50);

	glColor3f(0.0f, 0.0f, 0.0f);
	glutSolidSphere(radius_arm, 50, 50);

	glPopMatrix();

}

void Display(void)
{
	//Activamos buffer de profundidad
	glEnable(GL_DEPTH_TEST);
	// Borramos la escena
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	draw3DScene();

	// glPushMatrix();
	// glMatrixMode(GL_MODELVIEW);
	// glLoadIdentity();
	// gluLookAt(0.0d,0.0d,0.0d, 0.0d,0.0d,0.0d, up_vector[0], up_vector[1], up_vector[2]);
	// glPopMatrix();

	glFlush();
	glutSwapBuffers();
}

void MyReshape(GLint width, GLint height)
{
	if (height != 0) {
		new_ratio = (GLdouble)width / (GLdouble)height;
	}
	else {
		new_ratio = width;
	}
	glViewport(0, 0, width, height);
}

 void camera_set(){
     if ((GetKeyState(0x26) & 0x8000) != 0) {
         eye_vector[2] += -0.01;
     } else if ((GetKeyState(0x28) & 0x8000) != 0){
         eye_vector[2] += 0.01;
     } else if ((GetKeyState(0x27) & 0x8000) != 0){
         eye_vector[0] += 0.01;
     } else if ((GetKeyState(0x25) & 0x8000) != 0){
         eye_vector[0] += -0.01;
     }
 }

void Timer(GLint t) {
	camera_set();

	// Control Angulo1 teclas Q - A
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

	// Control Angulo2 teclas W - S
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

	// Control Angulo3 teclas E - D
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

	// Control Angulo4 teclas R - F
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

	// Control Angulo5 teclas T - G
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

// Funci�n principal
int main(int argc, char** argv)
{
	// Inicializamos la librer�a GLUT
	glutInit(&argc, argv);

	// Indicamos como ha de ser la nueva ventana
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(W_WIDTH, W_HEIGHT);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);

	// Creamos la nueva ventana
	glutCreateWindow("Etapa_4");

	// Indicamos cuales son las funciones de redibujado e idle
	glutDisplayFunc(Display);
	glutTimerFunc(tiempo, Timer, 0.0f);

	// funci�n de direccionamiento d c�mara
	//glutSpecialFunc(camera_set);

	//Ajuste de proporciones
	glutReshapeFunc(MyReshape);

	// El color de fondo ser� el negro (RGBA, RGB + Alpha channel)
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	//glOrtho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);

	// Comienza la ejecuci�n del core de GLUT
	glutMainLoop();
	return 0;
}