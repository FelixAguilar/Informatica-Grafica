// Etapa_5.cpp
// Félix Aguilar y Antonio Pujol
////////////////////////////////////////////////////
#include <GL/freeglut.h>
#include <GL/glu.h>
#define _USE_MATH_DEFINES
#include <math.h>

GLfloat fAngulo1 = 0.0f;  //Subir y Bajar el Brazo.
GLfloat fAngulo2 = 0.0f;  //Subir y bajar Antebrazo.
GLfloat fAngulo3 = 0.0f;  // Subir y bajar Muñeca.
GLfloat fAngulo4 = 0.0f;  //Abrir y cerrar Mano.
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
const GLint W_WIDTH = 800;
const GLint W_HEIGHT = 800;
const GLint W_RATIO = W_WIDTH / W_HEIGHT;

// Vector for camera.
GLdouble angulo_y = 0;
GLdouble angulo_x = 0;
GLdouble angulo_t = 0;
GLdouble angulo_p = 0;
GLdouble radio = 2;
GLdouble x = 0;
GLdouble y = 0;
GLdouble eye_vector[3] = {0.0, 0.0, 1.0};
GLdouble up_vector[3] = {0.0, 1.0, 0.0};
GLdouble center_vector[3] = {0.0, 0.0, 0.0};
GLdouble movement_vector[3] = {0.0, 0.0, 0.0};
GLdouble tilt_vector[2] = {0.0, 0.0};

// Light1 params values
GLfloat param_AMB[4] = {0.4f, 0.4f, 0.4f, 1.0f};   //GL_AMBIENT				[-1,1]
GLfloat param_DIFF[4] = {.8f, .8f, .8f, 1.0f};  //GL_DIFFUSE				[-1,1]
GLfloat param_SPEC[4] = {1.0f, 1.0f, 1.0f, 1.0f};  //GL_SPECULAR				[-1,1]
GLfloat param_POSIT_1[4] = {0.0f, 1.0f, 0.0f, 1.0f}; 	//GL_POSITION				?
GLfloat static_param_POSIT[4]  = {0.,0.,0.,1.};		//GL_POSITION en el origen

// Light2 params values
GLfloat param_AMB_2[4] = {1.0f, 1.0f, 0.0f, 1.0f};
GLfloat param_DIFF_2[4] = {1.0f, 1.0f, 0.0f, 1.0f}; 	
GLfloat param_SPEC_2[4] = {1.0f, 1.0f, 0.0f, 1.0f}; 
GLfloat param_POSIT_2[4] = {-1.5f, 1.01f, 1.5f};

GLfloat param_SPOT_DIR[3] = {1.5f, -1.01f, -1.5f};   //GL_SPOT_DIRECTION			?
GLfloat param_SPOT_EXP = 20.0f;					   //GL_SPOT_EXPONENT			[0,128]
GLfloat param_SPOT_CUT = 25.0f;					   //SPOT_CUTOFF				[0,90]U{180}
GLfloat param_CONST_ATT = 1.0f;					   //GL_CONSTANT_ATTENUATION	[0,1]
GLfloat param_LIN_ATT = 1.0f;					   //GL_LINEAR_ATTENUATION		[0,1]
GLfloat param_QUAD_ATT = 1.0f;					   //GL_QUADRATIC_ATTENUATION	[0,1]

// material param values
GLfloat param_mat_AMB[4] = {0.2f, 0.2f, 0.2f, 1.0f};   //GL_AMBIENT				[-1,1]
GLfloat param_mat_DIFF[4] = {0.8f, 0.8f, 0.8f, 1.0f};  //GL_DIFFUSE				[-1,1]
GLfloat param_mat_SPEC[4] = {1.0f, 1.0f, 1.0f, 1.0f};  //GL_SPECULAR			[-1,1]
GLfloat param_mat_EMISS[4] = {0.0f, 0.0f, 0.0f, 1.0f}; //GL_EMISSION			[-1,1]
GLfloat param_mat_SHINE = 50.0f;					   //GL_SHINENESS			[0,128]
GLfloat param_mat_COL_INDX[3] = {0.0f, 0.0f, 0.0f};	   //GL_COLOR_INDEXES		?

GLboolean smooth_shade = true;
GLboolean light_up_1 = true;
GLboolean light_up_2 = true;

//Button checks
bool light = false;
bool shadow = false;

GLUquadric *cyl_0;

GLfloat toRadians(GLfloat i)
{
	GLfloat r = i * (pi / 180);
	return r;
}

void draw3DScene()
{
	//Luz 2
	glPushMatrix();
	
	glTranslatef(param_POSIT_2[0] + sin(toRadians(60.0f))*0.18, param_POSIT_2[1] - sin(toRadians(25.0f))*0.17, param_POSIT_2[2] - cos(toRadians(60.0f))*0.20);
	
	//segmento direccion de foco con longitud = longitud poste/sin(angulo inclinacion del foco)
	//segmento para ejeX y ejeZ = sin(angulo opuesto de inclinacion del foco) * segmento direccion de foco

	param_SPOT_DIR[0] = sin(toRadians(60.0f))* (sin(toRadians(25.0f))*2/sin(toRadians(65.0f)));
	param_SPOT_DIR[1] = -sin(toRadians(25.0f))* ((sin(toRadians(25.0f))*2/sin(toRadians(65.0f)))) /cos(toRadians(65.0f));
	param_SPOT_DIR[2] = -cos(toRadians(60.0f))* ((sin(toRadians(25.0f))*2/sin(toRadians(65.0f))));

	glLightfv(GL_LIGHT2, GL_POSITION, static_param_POSIT);

	glDisable(GL_LIGHTING);
	
	//objeto lumínico
	glColor3f(1.0f, 1.0f, 0.0f);
	glutSolidSphere(0.04, 50, 50);

	glEnable(GL_LIGHTING);

	glPopMatrix();

	//Luz 1
	glPushMatrix();
	
	glTranslatef(param_POSIT_1[0], param_POSIT_1[1], param_POSIT_1[2]);
	
	glLightfv(GL_LIGHT0, GL_POSITION, static_param_POSIT);

	glDisable(GL_LIGHTING);
	
	//objeto lumínico
	glColor3f(1.0f, 1.0f, 1.0f);
	glutSolidSphere(radius_arm, 50, 50);

	glEnable(GL_LIGHTING);

	glPopMatrix();

	// Dibujamos los ejes.
	glPushMatrix();

	glDisable(GL_LIGHTING);

	glEnable(GL_LINE_SMOOTH);
	glBegin(GL_LINES);
	glLineWidth(1);

	glColor3f(1.0f, 1.0f, 0.0f); 	//amarillo - X
	glVertex3f(-2.0f, 0.0f, 0.0f);
	glVertex3f(2.0f, 0.0f, 0.0f);

	glColor3f(0.0f, 0.6f, 0.0f);	//verde - Y
	glVertex3f(0.0f, -0.9f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);

	glColor3f(0.0f, 0.0f, 1.0f);	//azul - Z
	glVertex3f(0.0f, 0.0f, -2.0f);
	glVertex3f(0.0f, 0.0f, 2.0f);

	glEnd();

	glEnable(GL_LIGHTING);

	glPopMatrix();

	//Teapot
    glPushMatrix();
    glTranslatef(0.7f, -0.842f,-0.6f);
    glutSolidTeapot(0.2);
    glPopMatrix();

    //Donut
    glPushMatrix();
    glTranslatef(-0.7f, -0.80f, 0.8f);
    glRotatef(90, 1.0, 0.0, 0.0);
    glutSolidTorus(0.2,0.3,50,50);
    glPopMatrix();

	// Mano Superior
	glPushMatrix();

	glRotatef(fAngulo5, 0.0f, 1.f, 0.f);

	glTranslatef(cos(toRadians(fAngulo1)) * 0.4 + cos(toRadians(fAngulo2)) * 0.4, sin(toRadians(fAngulo1)) * 0.4 + sin(toRadians(fAngulo2)) * 0.4, 0);

	glColor3f(0.4f, 0.4f, 0.4f);
	glutSolidSphere(radius_arm, 50, 50);

	glRotatef(45 + fAngulo3 + fAngulo4, 0.0f, 0.0f, 1.0f);
	glTranslatef(0.0f, 0.013f, 0.0f);
	glRotatef(90, 0.0f, 1.0f, 0.0f);
	glColor3f(1.0f, 0.0f, 0.0f);
	glutSolidCylinder(radius_hand, 0.2f, 50, 50);

	glTranslatef(0.0f, 0.0f, 0.2f);

	glColor3f(0.4f, 0.4f, 0.4f);
	glutSolidSphere(radius_hand, 50, 50);

	glRotatef(90, 1.0f, 0.0f, 0.0f);
	glColor3f(1.0f, 0.0f, 0.0f);
	glutSolidCylinder(radius_hand, 0.2f, 50, 50);

	glTranslatef(0.0f, 0.0f, 0.2f);

	glColor3f(0.4f, 0.4f, 0.4f);
	glutSolidSphere(radius_hand, 50, 50);

	glPopMatrix();

	// Mano inferior.
	glPushMatrix();

	glRotatef(fAngulo5, 0.0f, 1.f, 0.f);

	glTranslatef(cos(toRadians(fAngulo1)) * 0.4 + cos(toRadians(fAngulo2)) * 0.4, sin(toRadians(fAngulo1)) * 0.4 + sin(toRadians(fAngulo2)) * 0.4, 0);

	glRotatef(-45 + fAngulo3 - fAngulo4, 0.0f, 0.0f, 1.0f);
	glTranslatef(0.0f, -0.013f, 0.0f);
	glRotatef(90, 0.0f, 1.0f, 0.0f);
	glColor3f(1.0f, 0.0f, 0.0f);
	glutSolidCylinder(radius_hand, 0.2f, 50, 50);

	glTranslatef(0.0f, 0.0f, 0.2f);

	glColor3f(0.4f, 0.4f, 0.4f);
	glutSolidSphere(radius_hand, 50, 50);

	glRotatef(-90, 1.0f, 0.0f, 0.0f);
	glColor3f(1.0f, 0.0f, 0.0f);
	glutSolidCylinder(radius_hand, 0.2f, 50, 50);

	glTranslatef(0.0f, 0.0f, 0.2f);

	glColor3f(0.4f, 0.4f, 0.4f);
	glutSolidSphere(radius_hand, 50, 50);

	glPopMatrix();

	// Antebrazo
	glPushMatrix();

	glRotatef(fAngulo5, 0.0f, 1.f, 0.f);

	glTranslatef(cos(toRadians(fAngulo1)) * 0.4, sin(toRadians(fAngulo1)) * 0.4, 0);
	glRotatef(fAngulo2, 0.0f, 0.0f, 1.0f);
	glRotatef(90, 0.0f, 1.0f, 0.0f);

	glColor3f(1.0f, 0.0f, 0.0f);
	glutSolidCylinder(radius_arm, 0.4f, 50, 50);

	glColor3f(0.4f, 0.4f, 0.4f);
	glutSolidSphere(radius_arm, 50, 50);

	glPopMatrix();

	// Brazo
	glPushMatrix();

	glRotatef(fAngulo5, 0.0f, 1.f, 0.f);

	glRotatef(fAngulo1, 0.0f, 0.0f, 1.0f);
	glRotatef(90, 0.0f, 1.0f, 0.0f);

	glColor3f(1.0f, 0.0f, 0.0f);
	glutSolidCylinder(radius_arm, 0.4f, 50, 50);

	glColor3f(0.4f, 0.4f, 0.4f);
	glutSolidSphere(radius_arm, 50, 50);

	glPopMatrix();

	// Cono de luz
	glPushMatrix();

	glTranslatef(-1.5f, 1.01f, 1.5f);

	glRotatef(-25.0f, 0.0f, 0.0f, 1.0f);
	glRotatef(120.0f, 0.0f, 1.0f, 0.0f);

	cyl_0 = gluNewQuadric();

	gluCylinder(cyl_0, 0.01, radius_arm, 0.2f, 50, 50);

	glPopMatrix();

	// Poste de luz
	glPushMatrix();

	glTranslatef(-1.5f, 1.01f, 1.5f);

	glColor3f(0.4f, 0.4f, 0.4f);
	glutSolidSphere(0.01, 50, 50);

	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);

	glutSolidCylinder(0.01, 2.0f, 50, 50);

	glPopMatrix();

	// Plano
	glPushMatrix();

	glTranslatef(0.0f, -1.0f, 0.0f);

	glColor3f(0.4f, 0.4f, 0.4f);

	GLfloat inc = 0.02;

	for (GLfloat i = -2.0; i < 2; i = i + inc){
		for (GLfloat j = -2.0; j < 2; j = j + inc) {
			glBegin(GL_QUADS);
			glNormal3f(.0f, 1.0f, .0f);

			glVertex3f(j, 0.0f, i);

			glNormal3f(.0f, 1.0f, .0f);
			glVertex3f(j + inc, 0.0f, i);

			glNormal3f(.0f, 1.0f, .0f);
			glVertex3f(j + inc, 0.0f, i + inc);

			glNormal3f(.0f, 1.0f, .0f);
			glVertex3f(j, 0.0f, i + inc);
			glEnd();
		}
	}
	
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

	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, param_mat_SHINE);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, param_mat_AMB);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, param_mat_SPEC);

	glLightfv(GL_LIGHT0, GL_AMBIENT, param_AMB);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, param_DIFF);
	glLightfv(GL_LIGHT0, GL_SPECULAR, param_SPEC);

	glLightfv(GL_LIGHT2, GL_AMBIENT, param_AMB_2);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, param_DIFF_2);
	glLightfv(GL_LIGHT2, GL_SPECULAR, param_SPEC_2);

	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, param_SPOT_DIR);

	glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, param_SPOT_EXP);
	glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, param_SPOT_CUT);
	glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, param_CONST_ATT);
	glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, param_LIN_ATT);
	glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, param_QUAD_ATT);

	//Apagado/Encendido Luz 1
	if (light_up_1)
	{
		glEnable(GL_LIGHT0);
	}
	else
	{
		glDisable(GL_LIGHT0);
	}

	//Apagado/Encendido Luz 2
	if (light_up_2)
	{
		glEnable(GL_LIGHT2);
	}
	else
	{
		glDisable(GL_LIGHT2);
	}

	if (smooth_shade)
	{
		glShadeModel(GL_SMOOTH);
	}
	else
	{
		glShadeModel(GL_FLAT);
	}

	// Borramos la escena
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION); // Selecciona la matriz de proyección
	glLoadIdentity();

	// Cambio de aspect ratio.
	gluPerspective(55.0, new_ratio, 0.2, 100.0);
	

	glMatrixMode(GL_MODELVIEW); // Selecciona la matriz de modelado
	glLoadIdentity();
	gluLookAt(eye_vector[0], eye_vector[1], eye_vector[2],
			  center_vector[0], center_vector[1], center_vector[2],
			  up_vector[0], up_vector[1], up_vector[2]);
	draw3DScene();

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

void camera_set()
{
	GLdouble eye_x = radio * cos(toRadians(angulo_x)) * cos(toRadians(angulo_y));
	GLdouble eye_y = radio * sin(toRadians(angulo_x));
	GLdouble eye_z = radio * cos(toRadians(angulo_x)) * sin(toRadians(angulo_y));

	GLdouble center_x = movement_vector[0] * cos(toRadians(angulo_y)) - movement_vector[2] * sin(toRadians(angulo_y));
	GLdouble center_y = movement_vector[1];
	GLdouble center_z = movement_vector[2] * cos(toRadians(angulo_y)) + movement_vector[0] * sin(toRadians(angulo_y));

	GLdouble camera_x = -tilt_vector[0] * sin(toRadians(angulo_y));
	GLdouble camera_y = tilt_vector[1];
	GLdouble camera_z = tilt_vector[0] * cos(toRadians(angulo_y));

	camera_y = camera_z * sin(toRadians(angulo_x)) + camera_y * cos(toRadians(angulo_x));
	camera_z = camera_z * cos(toRadians(angulo_x)) - camera_y * sin(toRadians(angulo_x));

	center_vector[0] = camera_x + center_x;
	center_vector[1] = camera_y + center_y;
	center_vector[2] = camera_z + center_z;

	eye_vector[0] = eye_x + center_x;
	eye_vector[1] = eye_y + center_y;
	eye_vector[2] = eye_z + center_z;
}

void arrow_set(int key, int x, int y) {
	switch(key) {
	case GLUT_KEY_UP: // Flecha arriba
		angulo_x += 0.5;
		break;
	case GLUT_KEY_DOWN: // Flecha abajo
		angulo_x -= 0.5;
		break;
	case GLUT_KEY_LEFT: // Flecha izquierda
		angulo_y += 0.5;
		break;
	case GLUT_KEY_RIGHT: // Flecha derecha
		angulo_y -= 0.5;
		break;
	}
}

void key_set(unsigned char key, int x , int y) {
	switch (key)
	{
	case 32: // espacio
		if (smooth_shade) // Activa o desactiva las sombras suaves por las sombras planas
		{
			smooth_shade = false;
		}
		else
		{
			smooth_shade = true;
		}
		break;
	case 112: // p
		if (light_up_1) // Enciede o paga la luz 1
		{
			light_up_1 = false;
		}
		else
		{
			light_up_1 = true;
		}
		break;
	case 80: // P
		if (light_up_2) // Enciede o paga la luz 2
		{
			light_up_2 = false;
		}
		else
		{
			light_up_2 = true;
		}
		break;
	
	//posicionamiento de la luz 1

	//Eje X
	case 97: // a (-)
		param_POSIT_1[0] -= 0.01;
		break;
	case 122: // z (+)
		param_POSIT_1[0] += 0.01;
		break;

	//Eje Z
	case 115: // s (-)
		param_POSIT_1[2] -= 0.01;
		break;
	case 120: // x (+)
		param_POSIT_1[2] += 0.01;
		break;

	//Eje Y
	case 100: // d (-)
		param_POSIT_1[1] -= 0.01;
		break;
	case 99: // c (+)
		param_POSIT_1[1] += 0.01;
		break;
	
	//posicionamiento de la luz 2

	//Eje X
	case 65: // A (-)
		param_POSIT_2[0] -= 0.01;
		break;
	case 90: // Z (+)
		param_POSIT_2[0] += 0.01;
		break;

	//Eje Z
	case 83: // S (-)
		param_POSIT_2[2] -= 0.01;
		break;
	case 88: // X (+)
		param_POSIT_2[2] += 0.01;
		break;

	//Eje Y
	case 68: // D (-)
		param_POSIT_2[1] -= 0.01;
		break;
	case 67: // C (+)
		param_POSIT_2[1] += 0.01;
		break;

	case 114: // r
		fAngulo5 += 1.0f; // Rotacion de la grua (+)
		break;
	case 102: // f
		fAngulo5 -= 1.0f; // Rotacion de la grua (-)
		break;

	case 116: // t
		if (fAngulo1 < 90)
		{
			fAngulo1 += 1.0f; // Angulo del brazo inferior (+)
		}
		break;
	case 103: // g
		if (fAngulo1 > 0)
		{
			fAngulo1 -= 1.0f; // Angulo del brazo inferior (-)
		}
		break;

	case 121: // y
		if (fAngulo2 < 45)
		{
			fAngulo2 += 1.0f; // Angulo del brazo superior (+)
		}
		break;
	case 104: // h
		if (fAngulo2 > -50)
		{
			fAngulo2 -= 1.0f; // Angulo del brazo superior (-)
		}
		break;

	case 110: // n
		if (radio > 0.1) {
			radio -= 0.01; // Realiza zoom de la camara (-)
		}
		break;
	case 109: // m
		radio += 0.01; // Realiza zoom de la camara (+)
		break;
	case 78: // N
		movement_vector[1] -= 0.01; // Mueve la camara hacia abajo (-)
		break;
	case 77: // M
		movement_vector[1] += 0.01; // Mueve la camara hacia arriba (-)
		break;
	case 84: // T
		movement_vector[0] -= 0.01; // Mueve la camara hacia delante (+)
		break;
	case 71: // G
		movement_vector[0] += 0.01; // Mueve la camara hacia delante (+)
		break;
	case 70: // F
		movement_vector[2] += 0.01; // Mueve la camara hacia la izquierda
		break;
	case 72: // H
		movement_vector[2] -= 0.01; // Mueve la camara hacia la derecha
		break;
	case 73: // I
		tilt_vector[1] += 0.01; // Cabecea la camara (+)
		break;
	case 75: // K
		tilt_vector[1] -= 0.01; // Cabecea la camara (-)
		break;
	case 74: // J
		tilt_vector[0] += 0.01; // Tiltea la camara a la izquierda
		break;
	case 76: // L
		tilt_vector[0] -= 0.01; // Tiltea la camara a la derecha
		break;
	case 113: // q resetea los valores de visión esférica
		angulo_y = 0;
		angulo_x = 0;
		radio = 3;
		break;
	case 119: // w resetea los valores de visión posicionada
		movement_vector[0] = 0;
		movement_vector[1] = 0;
		movement_vector[2] = 0;
		break;
	case 101: // e resetea los valores de tilteo
		tilt_vector[0] = 0;
		tilt_vector[1] = 0;
		break;
	}
}

void Timer(GLint t)
{
	glutKeyboardFunc(key_set);
	glutSpecialFunc(arrow_set);
	camera_set();
	glutPostRedisplay();
	glutTimerFunc(tiempo, Timer, 0.0f);
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
	glutCreateWindow("Etapa_5");

	// Indicamos cuales son las funciones de redibujado e idle
	glutDisplayFunc(Display);
	glutTimerFunc(tiempo, Timer, 0.0f);

	//Ajuste de proporciones
	glutReshapeFunc(MyReshape);

	// El color de fondo será el negro (RGBA, RGB + Alpha channel)
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// Comienza la ejecución del core de GLUT
	glutMainLoop();
	return 0;
}