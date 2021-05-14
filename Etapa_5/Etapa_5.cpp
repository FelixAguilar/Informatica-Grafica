// Etapa_5.cpp
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

// aspect ratio
GLdouble new_ratio;

//variables para el control de giro de los ángulos.
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

// Vector for camera.
GLdouble angulo_y = 0;
GLdouble angulo_x = 0;
GLdouble radio = 2;
GLdouble x = 0;
GLdouble y = 0;
GLdouble eye_vector[3] = {0.0,0.0,1.0};
GLdouble up_vector[3] = {0.0,1.0,0.0};
GLdouble center_vector[3] = {0.0,0.0,0.0};

// Light params values
const GLfloat param_AMB[4] = {0.0f, 0.0f, 0.0f, 1.0f};
const GLfloat param_DIFF[4] = {1.0f, 1.0f, 1.0f, 1.0f};
const GLfloat param_SPEC[4] = {1.0f, 1.0f, 1.0f, 1.0f};
const GLfloat param_POSIT[4] = {2.0f, 2.0f, 2.0f, 0.0f};
const GLfloat param_SPOT_DIR[3] = {0.0f, 0.0f, -1.0f};
const GLfloat param_SPOT_EXP[3] = {90.0f, 90.0f, 90.0f};
const GLfloat param_SPOT_CUT[3] = {45.0f, 45.0f, 45.0f};
const GLfloat param_CONST_ATT[3] = {1.0f, 0.0f, 0.0f};
const GLfloat param_LIN_ATT[3] = {1.0f, 0.0f, 0.0f};
const GLfloat param_QUAD_ATT[3] = {1.0f, 0.0f, 0.0f};
GLboolean smooth_shade = true;
GLboolean light_up = true;
const GLfloat param_SHINE[4] = {120.0f, 120.0f, 120.0f, 120.0f};

GLfloat toRadians(GLfloat i)
{
	GLfloat r = i * (pi / 180);
	return r;
}

void draw3DScene() 
{

	// Dibujamos los ejes.
	glPushMatrix();

	//glTranslatef(-0.4f, -0.2f, -1.5f);

	glEnable(GL_LINE_SMOOTH);
	glBegin(GL_LINES);
	glLineWidth(1);
	
	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex3f(-2.0f, 0.0f, 0.0f);
	glVertex3f(2.0f, 0.0f, 0.0f);

	glColor3f(0.0f, 0.6f, 0.0f);
	glVertex3f(0.0f, -0.9f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);

	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, -2.0f);
	glVertex3f(0.0f, 0.0f, 2.0f);

	glEnd();

	// Mano Superior
	glPushMatrix();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//glTranslatef(-0.4f, -0.2f, -1.5f);
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

	//glTranslatef(-0.4f, -0.2f, -1.5f);
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

	//glTranslatef(-0.4f, -0.2f, -1.5f);
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

	//glTranslatef(-0.4f, -0.2f, -1.5f);
	glRotatef(fAngulo5, 0.0f, 1.f, 0.f);

	glRotatef(fAngulo1, 0.0f, 0.0f, 1.0f);
	glRotatef(90, 0.0f, 1.0f, 0.0f);


	glColor3f(1.0f, 0.0f, 0.0f);
	glutSolidCylinder(radius_arm, 0.4f, 50, 50);

	glColor3f(0.0f, 0.0f, 0.0f);
	glutSolidSphere(radius_arm, 50, 50);

	glPopMatrix();

	// Plano
	glPushMatrix();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(0.0f, -1.0f, 0.0f);

	//borde del plano
	glEnable(GL_LINE_SMOOTH);
	glBegin(GL_LINES);
	glLineWidth(2);
	glColor3f(0.0f, 0.0f, 0.0f);

	glVertex3f(-2.0f, 0.0f, -2.0f);
	glVertex3f(2.0f, 0.0f, -2.0f);


	glVertex3f(2.0f, 0.0f, -2.0f);
	glVertex3f(2.0f, 0.0f, 2.0f);

	glVertex3f(2.0f, 0.0f, 2.0f);
	glVertex3f(-2.0f, 0.0f, 2.0f);

	glVertex3f(-2.0f, 0.0f, 2.0f);
	glVertex3f(-2.0f, 0.0f, -2.0f);

	glEnd();

	// plano
	glColor3f(0.4f, 0.4f, 0.4f);
	glBegin(GL_QUADS);
	//glMaterialfv(GL_FRONT, GL_SHININESS, param_SHINE);
	//glMaterialfv(GL_BACK, GL_AMBIENT, param_AMB);
	//glNormal3f(0.0f, 1.0f, 0.0f);
	
	glVertex3f(-2.0f, 0.0f, -2.0f);

	//glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(2.0f, 0.0f, -2.0f);

	//glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(2.0f, 0.0f, 2.0f);

	//glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-2.0f, 0.0f, 2.0f);
	glEnd();

	glPopMatrix();

}

void Display(void)
{
	//Activamos buffer de profundidad
	glEnable(GL_DEPTH_TEST);
	//Habilitamos renderizado con luz
	glEnable(GL_LIGHTING);
	// efecto de luz en materiales por color
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
	
	// glEnable(GL_LIGHT1);
	// glEnable(GL_LIGHT2);
	// glEnable(GL_LIGHT3);
	// glEnable(GL_LIGHT4);
	// glEnable(GL_LIGHT5);
	// glEnable(GL_LIGHT6);
	// glEnable(GL_LIGHT7);
	//glEnable(GL_LIGHT8);
	//glEnable(GL_LIGHT09);

	glLightf(0,GL_AMBIENT, *param_AMB);
	glLightf(0,GL_DIFFUSE, *param_DIFF);
 	glLightf(0,GL_SPECULAR, *param_SPEC);
	glLightf(0,GL_POSITION, *param_POSIT);
	glLightf(0,GL_SPOT_DIRECTION, *param_SPOT_DIR);
	glLightf(0,GL_SPOT_EXPONENT, *param_SPOT_EXP);
	glLightf(0,GL_SPOT_CUTOFF, *param_SPOT_CUT);
	glLightf(0,GL_CONSTANT_ATTENUATION, *param_CONST_ATT);
	glLightf(0,GL_LINEAR_ATTENUATION, *param_LIN_ATT);
	glLightf(0,GL_QUADRATIC_ATTENUATION, *param_QUAD_ATT);

	//Insertado de luz movible
	if (light_up) {
		glEnable(GL_LIGHT0);
	} else {
		glDisable(GL_LIGHT0);
	}

	if(smooth_shade) {
		glShadeModel(GL_SMOOTH);
	} else {
		glShadeModel(GL_FLAT);
	}

	//cambio normal de superficie definida
	//glNormal();

	//glutKeyboardFunc();

	// Borramos la escena
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	draw3DScene();

	glMatrixMode(GL_PROJECTION); // Selecciona la matriz del dibujado
	glLoadIdentity();

	// Cambio de aspect ratio.
	gluPerspective(55.0, new_ratio, 0.2, 150.0);
	gluLookAt(	eye_vector[0], 		eye_vector[1], 		eye_vector[2], 
				center_vector[0], 	center_vector[1], 	center_vector[2], 
				up_vector[0], 		up_vector[1], 		up_vector[2]);

	glMatrixMode(GL_MODELVIEW);

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
	// glMatrixMode(GL_PROJECTION); // Selecciona la matriz del dibujado
	// glLoadIdentity();

	// // Cambio de aspect ratio.
	// gluPerspective(55.0,new_ratio,0.2,150.0);

	// glMatrixMode(GL_MODELVIEW);
	// glLoadIdentity();
}

// void camera_set(int key, int x, int y){
//     if (key == GLUT_KEY_UP) {
//         up_vector[0] = 1;
//     } else if (key == GLUT_KEY_DOWN){
//         //up_vector[] = 0;
//     } else if (key == GLUT_KEY_RIGHT){
//         up_vector[1] = 1;
//     } else if (key == GLUT_KEY_LEFT){
//         //up_vector[] = 0;
//     }
// }

void light_set() {



	//Eleción de sombreado
	if ((GetKeyState(0x20) & 0x8000) != 0) {
		if (smooth_shade) {
			smooth_shade = false;
		} else {
			smooth_shade = true;
		}
	}

	if ((GetKeyState(0x4C) & 0x8000) != 0) {
		if (light_up) {
			light_up = false;
		} else {
			light_up = true;
		}
	}
}

void camera_set()
{
    if ((GetKeyState(0x26) & 0x8000) != 0) { 		//arriba
        angulo_x += 0.5;
    } 
	if ((GetKeyState(0x28) & 0x8000) != 0){	//abajo
        angulo_x -= 0.5;
    } 
	if ((GetKeyState(0x27) & 0x8000) != 0){	//derecha
        angulo_y += 0.5;
    } 
	if ((GetKeyState(0x25) & 0x8000) != 0){	//izquierda
        angulo_y -= 0.5;
	}
	if ((GetKeyState(0x4E) & 0x8000) != 0) {
		radio += 0.01;
	}
	if ((GetKeyState(0x4D) & 0x8000) != 0) {
		radio -= 0.01;
	}
	if ((GetKeyState(0x4C) & 0x8000) != 0) {
		y += 0.01;
	}	 
	if ((GetKeyState(0x4A) & 0x8000) != 0) {
		y -= 0.01;
	}
	if ((GetKeyState(0x49) & 0x8000) != 0) {
		x += 0.01;
	}
	if ((GetKeyState(0x4B) & 0x8000) != 0) {
		x -= 0.01;
	}

	eye_vector[0] = radio * cos(toRadians(angulo_x)) * cos(toRadians(angulo_y));
	eye_vector[1] = radio * sin(toRadians(angulo_x));
	eye_vector[2] = radio * cos(toRadians(angulo_x)) * sin(toRadians(angulo_y));
}

void Timer(GLint t) 
{
	camera_set();

	light_set();

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
	glutCreateWindow("Etapa_5");

	// Indicamos cuales son las funciones de redibujado e idle
	glutDisplayFunc(Display);
	glutTimerFunc(tiempo, Timer, 0.0f);

    // función de direccionamiento d cámara
    //glutSpecialFunc(camera_set);

	//Ajuste de proporciones
	glutReshapeFunc(MyReshape);

	// El color de fondo será el negro (RGBA, RGB + Alpha channel)
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// Comienza la ejecución del core de GLUT
	glutMainLoop();
	return 0;
}