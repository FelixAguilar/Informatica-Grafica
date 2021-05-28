// Etapa_6.cpp
// Fichero principal.
////////////////////////////////////////////////////
#include <GL/freeglut.h>
#include <GL/glu.h>
#define _USE_MATH_DEFINES
#include <math.h>
#define STB_IMAGE_IMPLEMENTATION
#include "./components/include/stb_image.h"
#include "./components/include/AL/al.h"
#include "./components/include/AL/alc.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
using namespace std;

GLfloat fAngulo1 = 0.0f;  //Subir y Bajar el Brazo.
GLfloat fAngulo2 = 0.0f;  //Subir y bajar Antebrazo.
GLfloat fAngulo3 = 0.0f;  // Subir y bajar Muñeca.
GLfloat fAngulo4 = 0.0f;  //Abrir y cerrar Mano.
GLfloat fAngulo5 = 0.0f; //Giro de la Mano.

// Constantes y variables para dibujar el brazo entero.
const GLfloat pi = M_PI;
const GLint polygon_points = 360;
const GLdouble radius_arm = 0.05;
const GLdouble radius_joints = 0.072;
const GLdouble radius_hand = 0.025;
const GLdouble base_radius = 0.1;
const GLdouble desp = 0.05;
GLfloat lcuerda = 0.4f;
GLfloat lextension = 0.1f;

// aspect ratio
GLdouble new_ratio;

// Constantes de la ventana.
const GLint W_WIDTH = 800;
const GLint W_HEIGHT = 800;
const GLint W_RATIO = W_WIDTH / W_HEIGHT;
const GLint tiempo = 10;

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

// Light0 params values
GLfloat param_AMB[4] = {0.4f, 0.4f, 0.4f, 1.0f};   //GL_AMBIENT				[-1,1]
GLfloat param_DIFF[4] = {.8f, .8f, .8f, 1.0f};  //GL_DIFFUSE				[-1,1]
GLfloat param_SPEC[4] = {1.0f, 1.0f, 1.0f, 1.0f};  //GL_SPECULAR				[-1,1]
GLfloat param_POSIT_1[4] = {0.0f, 1.0f, 0.0f, 1.0f}; 	//GL_POSITION				?
GLfloat param_POSIT_2[4] = {-1.0f, 1.0f, -1.0f, 1.0f};
GLfloat static_param_POSIT[4]  = {0.,0.,0.,1.};		//GL_POSITION en el origen
GLfloat param_SPOT_DIR[3] = {0.0f, 0.0f, -1.0f};   //GL_SPOT_DIRECTION			?
GLfloat param_SPOT_EXP = 0.0f;					   //GL_SPOT_EXPONENT			[0,128]
GLfloat param_SPOT_CUT = 45.0f;					   //SPOT_CUTOFF				[0,90]U{180}
GLfloat param_CONST_ATT = 0.0f;					   //GL_CONSTANT_ATTENUATION	[0,1]
GLfloat param_LIN_ATT = 0.0f;					   //GL_LINEAR_ATTENUATION		[0,1]
GLfloat param_QUAD_ATT = 0.0f;					   //GL_QUADRATIC_ATTENUATION	[0,1]

// Light2 params values
GLfloat param_AMB_2[4] = {0.7f, 0.0f, 0.0f, 1.0f};
GLfloat param_DIFF_2[4] = {0.7f, 0.0f, 0.0f, 1.0f}; 	
GLfloat param_SPEC_2[4] = {0.7f, 0.0f, 0.0f, 1.0f}; 

// material param values
GLfloat param_mat_AMB[4] = {0.2f, 0.2f, 0.2f, 1.0f};   //GL_AMBIENT				[-1,1]
GLfloat param_mat_DIFF[4] = {0.8f, 0.8f, 0.8f, 1.0f};  //GL_DIFFUSE				[-1,1]
GLfloat param_mat_SPEC[4] = {1.0f, 1.0f, 1.0f, 1.0f};  //GL_SPECULAR			[-1,1]
GLfloat param_mat_EMISS[4] = {0.0f, 0.0f, 0.0f, 1.0f}; //GL_EMISSION			[-1,1]
GLfloat param_mat_SHINE = 50.0f;					   //GL_SHINENESS			[0,128]
GLfloat param_mat_COL_INDX[3] = {0.0f, 0.0f, 0.0f};	   //GL_COLOR_INDEXES		?

GLboolean smooth_shade = true;
GLboolean light_up_1 = true;
GLboolean light_up_2 = false;

//Button checks
bool light = false;
bool shadow = false;

//texture variables

GLuint atlas_1;
GLuint atlas_2;
GLuint atlas_3;

GLUquadric *cyl_0;
GLUquadric *cyl_1;
GLUquadric *cyl_2;
GLUquadric *cyl_3;
GLUquadric *cyl_4;
GLUquadric *cyl_5;
GLUquadric *cyl_6;
GLUquadric *cyl_7;

GLUquadric *sphere_1;
GLUquadric *sphere_2;
GLUquadric *sphere_3;
GLUquadric *sphere_4;

GLUquadric *sphere_5;
GLUquadric *sphere_6;
GLUquadric *sphere_7;

GLfloat toRadians(GLfloat i)
{
	GLfloat r = i * (pi / 180);
	return r;
}

void draw3DScene()
{
	//Luz 2
	glPushMatrix();
	
	glTranslatef(param_POSIT_2[0], param_POSIT_2[1], param_POSIT_2[2]);
	
	glLightfv(GL_LIGHT2, GL_POSITION, static_param_POSIT);

	glDisable(GL_LIGHTING);
	
	//imagen foco
	glColor3f(0.7f, 0.0f, 0.0f);
	glutSolidSphere(radius_arm, 50, 50);

	glEnable(GL_LIGHTING);

	glPopMatrix();

	//Luz 1
	glPushMatrix();
	
	glTranslatef(param_POSIT_1[0], param_POSIT_1[1], param_POSIT_1[2]);
	
	glLightfv(GL_LIGHT0, GL_POSITION, static_param_POSIT);

	glDisable(GL_LIGHTING);
	
	//imagen foco
	glColor3f(1.0f, 1.0f, 1.0f);
	glutSolidSphere(radius_arm, 50, 50);

	glEnable(GL_LIGHTING);

	glPopMatrix();

	// Dibujamos los ejes.
	glPushMatrix();
	//glTranslatef(-0.4f, -0.2f, -1.5f);

	glDisable(GL_LIGHTING);

	glEnable(GL_LINE_SMOOTH);
	glBegin(GL_LINES);
	glLineWidth(1);

	glColor3f(1.0f, 1.0f, 0.0f); 	//amarillo - Z
	glVertex3f(-2.0f, 0.0f, 0.0f);
	glVertex3f(2.0f, 0.0f, 0.0f);

	glColor3f(0.0f, 0.6f, 0.0f);	//verde - Y
	glVertex3f(0.0f, -0.9f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);

	glColor3f(0.0f, 0.0f, 1.0f);	//azul - X
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
	glTranslatef(-0.7f, -0.85f, 0.8f);
	glRotatef(90, 1.0, 0.0, 0.0);
	glutSolidTorus(0.2,0.3,50,50);
	glPopMatrix();

	//Boxes

	// Dedo 1.
	glPushMatrix();

	// Colocacion de la primitiva en la figura y rotacion de la figura completa.
	glRotatef(fAngulo5, 0.0f, 1.f, 0.f);
	glTranslatef(cos(toRadians(fAngulo1)) * (0.4 + desp) + cos(toRadians(fAngulo2)) * (0.4 + desp * 2 + lextension), sin(toRadians(fAngulo1)) * (0.4 + desp) + sin(toRadians(fAngulo2)) * (0.4 + desp * 2 + lextension) - lcuerda, 0);

	// Añade la base de la garra.
	glBindTexture(GL_TEXTURE_2D, atlas_3);
	gluSphere(sphere_7, radius_joints, 50, 50);

	// Rota y coloca el dedo en la posicion adecuada dentro de la garra.
	glTranslatef(0.0f, 0.013f, 0.0f);

	// Rotacion para abrir y cerrar el dedo.
	glRotatef(45 - fAngulo4, 1.0f, 0.0f, 0.0f);

	// Dibuja la parte superior del dedo.
	glBindTexture(GL_TEXTURE_2D, atlas_1); // Textura de metal.
	gluCylinder(cyl_6, radius_hand, radius_hand, 0.2f, 50, 50);

	// Dibuja la union entre las dos partes del dedo.
	glTranslatef(0.0f, 0.0f, 0.2f);
	gluSphere(sphere_1, radius_hand, 50, 50);

	// Rota la parte del dedo inferior para unirlo a la superior.
	glRotatef(90, 1.0f, 0.0f, 0.0f);

	// Dibuja la parte del dedo inferior.
	glBindTexture(GL_TEXTURE_2D, atlas_1); // Textura de metal.
	gluCylinder(cyl_5, radius_hand, radius_hand, .2f, 50, 50);
	glTranslatef(0.0f, 0.0f, 0.2f);

	// Dibuja la punta del dedo.
	glBindTexture(GL_TEXTURE_2D, atlas_2); // Textura de goma.
	gluSphere(sphere_2, radius_hand, 50, 50);
	glBindTexture(GL_TEXTURE_2D, GL_NONE);
	glPopMatrix();

	// Dedo 2.
	glPushMatrix();

	// Colocacion de la primitiva en la figura y rotacion de la figura completa.
	glRotatef(fAngulo5, 0.0f, 1.f, 0.f);
	glTranslatef(cos(toRadians(fAngulo1))* (0.4 + desp) + cos(toRadians(fAngulo2)) * (0.4 + desp * 2 + lextension), sin(toRadians(fAngulo1))* (0.4 + desp) + sin(toRadians(fAngulo2)) * (0.4 + desp * 2 + lextension) - lcuerda, 0);

	// Rota y coloca el dedo en la posicion adecuada dentro de la garra.
	glTranslatef(0.0f, 0.013f, 0.0f);
	glRotatef(120, 0.0f, 1.0f, 0.0f);

	// Rotacion para abrir y cerrar el dedo.
	glRotatef(45 - fAngulo4, 1.0f, 0.0f, 0.0f);

	// Dibuja la parte superior del dedo.
	glBindTexture(GL_TEXTURE_2D, atlas_1); // Textura de metal.
	gluCylinder(cyl_6, radius_hand, radius_hand, 0.2f, 50, 50);

	// Dibuja la union entre las dos partes del dedo.
	glTranslatef(0.0f, 0.0f, 0.2f);
	gluSphere(sphere_1, radius_hand, 50, 50);

	// Rota la parte del dedo inferior para unirlo a la superior.
	glRotatef(90, 1.0f, 0.0f, 0.0f);

	// Dibuja la parte del dedo inferior.
	glBindTexture(GL_TEXTURE_2D, atlas_1); // Textura de metal.
	gluCylinder(cyl_5, radius_hand, radius_hand, .2f, 50, 50);
	glTranslatef(0.0f, 0.0f, 0.2f);

	// Dibuja la punta del dedo.
	glBindTexture(GL_TEXTURE_2D, atlas_2); // Textura de goma.
	gluSphere(sphere_2, radius_hand, 50, 50);
	glBindTexture(GL_TEXTURE_2D, GL_NONE);
	glPopMatrix();

	// Dedo 3.
	glPushMatrix();

	// Colocacion de la primitiva en la figura y rotacion de la figura completa.
	glRotatef(fAngulo5, 0.0f, 1.f, 0.f);
	glTranslatef(cos(toRadians(fAngulo1))* (0.4 + desp) + cos(toRadians(fAngulo2)) * (0.4 + desp * 2 + lextension), sin(toRadians(fAngulo1))* (0.4 + desp) + sin(toRadians(fAngulo2)) * (0.4 + desp * 2 + lextension) - lcuerda, 0);

	// Rota y coloca el dedo en la posicion adecuada dentro de la garra.
	glTranslatef(0.0f, 0.013f, 0.0f);
	glRotatef(-120, 0.0f, 1.0f, 0.0f);

	// Rotacion para abrir y cerrar el dedo.
	glRotatef(45 - fAngulo4, 1.0f, 0.0f, 0.0f);

	// Dibuja la parte superior del dedo.
	glBindTexture(GL_TEXTURE_2D, atlas_1); // Textura de metal.
	gluCylinder(cyl_6, radius_hand, radius_hand, 0.2f, 50, 50);

	// Dibuja la union entre las dos partes del dedo.
	glTranslatef(0.0f, 0.0f, 0.2f);
	gluSphere(sphere_1, radius_hand, 50, 50);

	// Rota la parte del dedo inferior para unirlo a la superior.
	glRotatef(90, 1.0f, 0.0f, 0.0f);

	// Dibuja la parte del dedo inferior.
	glBindTexture(GL_TEXTURE_2D, atlas_1); // Textura de metal.
	gluCylinder(cyl_5, radius_hand, radius_hand, .2f, 50, 50);
	glTranslatef(0.0f, 0.0f, 0.2f);

	// Dibuja la punta del dedo.
	glBindTexture(GL_TEXTURE_2D, atlas_2); // Textura de goma.
	gluSphere(sphere_2, radius_hand, 50, 50);
	glBindTexture(GL_TEXTURE_2D, GL_NONE);
	glPopMatrix();

	//Cuerda
	glPushMatrix();

	// Coloca la primitiva dentro de la figura en la posicion adecuada.
	glRotatef(fAngulo5, 0.0f, 1.f, 0.f);
	glTranslatef(cos(toRadians(fAngulo1)) * (0.4 + desp) + cos(toRadians(fAngulo2)) * (0.4 + desp * 2 + lextension), sin(toRadians(fAngulo1))* (0.4 + desp) + sin(toRadians(fAngulo2)) * (0.4 + desp * 2 + lextension), 0);

	// Coloca esta bocaabajo en el escenario.
	glRotatef(90, 1.0f, 0.0f, 0.0f);

	// Dibuja la cuerda.
	glBindTexture(GL_TEXTURE_2D, atlas_1);
	gluCylinder(cyl_2, 0.01, 0.01, lcuerda, 50, 50); // Cambiar textura.
	glBindTexture(GL_TEXTURE_2D, GL_NONE);
	glPopMatrix();

	// Extensor.
	glPushMatrix();
	glRotatef(fAngulo5, 0.0f, 1.f, 0.f);
	glTranslatef(cos(toRadians(fAngulo1))* (0.4 + desp) + cos(toRadians(fAngulo2)) * (0.4 + desp), sin(toRadians(fAngulo1))* (0.4 + desp) + sin(toRadians(fAngulo2)) * (0.4 + desp), 0);

	glRotatef(90, 0.0f, 1.f, 0.f);
	glRotatef(-fAngulo2, 1.0f, 0.0f, 0.0f);

	// Dibuja el extensor.
	glBindTexture(GL_TEXTURE_2D, atlas_1); // Textura de metal.
	gluCylinder(cyl_2, 0.03, 0.03, lextension, 50, 50);

	// Dibuja la union con la garra.
	glTranslatef(0.0f, 0.0f, lextension + desp);
	glBindTexture(GL_TEXTURE_2D, atlas_3); // Textura de metal para esferas.
	gluSphere(sphere_6, radius_joints, 50, 50);
	glBindTexture(GL_TEXTURE_2D, GL_NONE);
	glPopMatrix();

	// Conexion entre el extensor y el brazo
	glPushMatrix();

	// Coloca la primitiva en su posicion correspondiente dentro de la figura.
	glRotatef(fAngulo5, 0.0f, 1.f, 0.f);
	glTranslatef(cos(toRadians(fAngulo1))* (0.4 + desp) + cos(toRadians(fAngulo2)) * (0.4), sin(toRadians(fAngulo1))* (0.4 + desp) + sin(toRadians(fAngulo2)) * (0.4), 0);
	glRotatef(90, 0.0f, 1.f, 0.f);
	glRotatef(-fAngulo2, 1.0f, 0.0f, 0.0f);

	// Dibuja el brazo.
	glBindTexture(GL_TEXTURE_2D, atlas_2); // Textura de goma.
	gluCylinder(cyl_2, radius_arm, 0.03, desp, 50, 50);
	glBindTexture(GL_TEXTURE_2D, GL_NONE);
	glPopMatrix();

	// Antebrazo
	glPushMatrix();

	// Coloca la primitiva en su posicion correspondiente dentro de la figura.
	glRotatef(fAngulo5, 0.0f, 1.f, 0.f);
	glTranslatef(cos(toRadians(fAngulo1)) * (0.4 + desp), sin(toRadians(fAngulo1)) * (0.4+desp), 0);
	glRotatef(90, 0.0f, 1.f, 0.f);
	glRotatef(-fAngulo2, 1.0f, 0.0f, 0.0f);

	// Dibuja la union con el brazo.
	glBindTexture(GL_TEXTURE_2D, atlas_3); // Textura de metal para esferas.
	gluSphere(sphere_7, radius_joints, 50, 50);

	// Dibuja el brazo.
	glBindTexture(GL_TEXTURE_2D, atlas_1); // Textura de metal.
	gluCylinder(cyl_2, radius_arm, radius_arm, .4f, 50, 50);
	glBindTexture(GL_TEXTURE_2D, GL_NONE);
	glPopMatrix();

	// Brazo
	glPushMatrix();

	// Coloca la primitiva en su posicion en la figura.
	glRotatef(90 + fAngulo5, 0.0f, 1.f, 0.f);
	glRotatef(-fAngulo1, 1.0f, 0.0f, 0.0f);

	// Dibuja la union con la base.
	glBindTexture(GL_TEXTURE_2D, atlas_3); // Textura de metal para esferas.
	gluSphere(sphere_5, radius_joints, 50, 50);

	// Dibuja la parte inferior del brazo.
	glTranslatef(0.0f, 0.0f, desp);
	glBindTexture(GL_TEXTURE_2D, atlas_1); // Textura de metal.
	gluCylinder(cyl_1, radius_arm, radius_arm, 0.4f, 50, 50);
	glBindTexture(GL_TEXTURE_2D, GL_NONE);
	glPopMatrix();

	//Soporte cilíndrico
	glPushMatrix();

	glRotatef(90, 1.0f, 0.0f, 0.0f);

	glBindTexture(GL_TEXTURE_2D, atlas_1);

	gluCylinder(cyl_0, radius_arm, radius_arm, 1.0f, 50, 50);

	glBindTexture(GL_TEXTURE_2D, GL_NONE);

	glPopMatrix();

	//Base cilíndrica
	glPushMatrix();

	glTranslatef(0.0f, -0.7f, 0.0f);
	glRotatef(90, 1.0f, 0.0f, 0.0f);

	glBindTexture(GL_TEXTURE_2D, atlas_1);

	gluCylinder(cyl_7, radius_arm, base_radius, 0.3f, 50, 50);

	glBindTexture(GL_TEXTURE_2D, GL_NONE);

	glPopMatrix();

	// Plano
	glPushMatrix();

	glTranslatef(0.0f, -1.0f, 0.0f);

	glBindTexture(GL_TEXTURE_2D, atlas_1);

	GLfloat inc = 0.02;

	for (GLfloat i = -2.0; i < 2; i = i + inc){
		for (GLfloat j = -2.0; j < 2; j = j + inc) {
			glBegin(GL_QUADS);

			glNormal3f(.0f, 1.0f, .0f);
			glTexCoord2f((j+2.)/4, (i+2.)/4);
			glVertex3f(j, 0.0f, i);

			glNormal3f(.0f, 1.0f, .0f);
			glTexCoord2f((j+2.+inc)/4, (i+2.)/4);
			glVertex3f(j + inc, 0.0f, i);

			glNormal3f(.0f, 1.0f, .0f);
			glTexCoord2f((j+2.+inc)/4, (i+2.+inc)/4);
			glVertex3f(j + inc, 0.0f, i + inc);

			glNormal3f(.0f, 1.0f, .0f);
			glTexCoord2f((j+2.)/4, (i+2.+inc)/4);
			glVertex3f(j, 0.0f, i + inc);
			glEnd();
		}
	}

	glBindTexture(GL_TEXTURE_2D, GL_NONE);
	
	glPopMatrix();
}

void Display(void)
{
	//Activamos buffer de profundidad
	glEnable(GL_DEPTH_TEST);
	//Activamos textura
	glEnable(GL_TEXTURE_2D);
	//Habilitamos renderizado con luz
	glEnable(GL_LIGHTING);
	// efecto de luz en materiales por color
	//glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

	//si se activa el color afecta al color de la textura de objetos
	//glEnable(GL_COLOR_MATERIAL);

	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, param_mat_SHINE);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, param_mat_AMB);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, param_mat_SPEC);

	//glLightfv(GL_LIGHT0, GL_POSITION, static_array);
	glLightfv(GL_LIGHT0, GL_AMBIENT, param_AMB);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, param_DIFF);
	glLightfv(GL_LIGHT0, GL_SPECULAR, param_SPEC);
	// glLightf(GL_LIGHT0, GL_SPOT_DIRECTION, *param_SPOT_DIR);
	// glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, param_SPOT_EXP);
	// glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, param_SPOT_CUT);
	// glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, param_CONST_ATT);
	// glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, param_LIN_ATT);
	// glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, param_QUAD_ATT);

	glLightfv(GL_LIGHT2, GL_AMBIENT, param_AMB_2);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, param_DIFF_2);
	glLightfv(GL_LIGHT2, GL_SPECULAR, param_SPEC_2);

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

	//cambio normal de superficie definida
	//glNormal();

	//glutKeyboardFunc();

	// Borramos la escena
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION); // Selecciona la matriz del dibujado
	glLoadIdentity();

	// Cambio de aspect ratio.
	gluPerspective(55.0, new_ratio, 0.2, 100.0);
	

	glMatrixMode(GL_MODELVIEW);
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

void light_set()
{

	//Eleción de sombreado -SPACEBAR
	if ((GetKeyState(0x20) & 0x8000) != 0 && !shadow)
	{
		shadow = true;
		if (smooth_shade)
		{
			smooth_shade = false;
		}
		else
		{
			smooth_shade = true;
		}
	}

	if ((GetKeyState(0x20) & 0x8000) == 0) {
		shadow = false;
	}

	if(!(GetKeyState(0x10) & 0x8000) != 0){
		// switch luz on/off -L
		if ((GetKeyState(0x4C) & 0x8000) != 0 && !light)
		{
			light = true;
			if (light_up_1)
			{
				light_up_1 = false;
			}
			else
			{
				light_up_1 = true;
			}
		}

		if ((GetKeyState(0x4C) & 0x8000) == 0) {
			light = false;
		}

		// movimiento de luz
		if ((GetKeyState(0x41) & 0x8000) != 0)
		{ //A
			param_POSIT_1[0] -= 0.01;
		}
		if ((GetKeyState(0x5A) & 0x8000) != 0)
		{ //Z
			param_POSIT_1[0] += 0.01;
		}
		if ((GetKeyState(0x53) & 0x8000) != 0)
		{ //S
			param_POSIT_1[2] -= 0.01;
		}
		if ((GetKeyState(0x58) & 0x8000) != 0)
		{ //X
			param_POSIT_1[2] += 0.01;
		}
		if ((GetKeyState(0x44) & 0x8000) != 0)
		{ //D
			param_POSIT_1[1] -= 0.01;
		}
		if ((GetKeyState(0x43) & 0x8000) != 0)
		{ //C
			param_POSIT_1[1] += 0.01;
		}
	}else if((GetKeyState(0x10) & 0x8000) != 0){ //SHIFT luz 2
		// switch luz on/off -L
		if ((GetKeyState(0x4C) & 0x8000) != 0 && !light)
		{
			light = true;
			if (light_up_2)
			{
				light_up_2 = false;
			}
			else
			{
				light_up_2 = true;
			}
		}

		if ((GetKeyState(0x4C) & 0x8000) == 0) {
			light = false;
		}

		// movimiento de luz
		if ((GetKeyState(0x41) & 0x8000) != 0)
		{ //A
			param_POSIT_2[0] -= 0.01;
		}
		if ((GetKeyState(0x5A) & 0x8000) != 0)
		{ //Z
			param_POSIT_2[0] += 0.01;
		}
		if ((GetKeyState(0x53) & 0x8000) != 0)
		{ //S
			param_POSIT_2[2] -= 0.01;
		}
		if ((GetKeyState(0x58) & 0x8000) != 0)
		{ //X
			param_POSIT_2[2] += 0.01;
		}
		if ((GetKeyState(0x44) & 0x8000) != 0)
		{ //D
			param_POSIT_2[1] -= 0.01;
		}
		if ((GetKeyState(0x43) & 0x8000) != 0)
		{ //C
			param_POSIT_2[1] += 0.01;
		}

	}
}

void camera_set()
{

	if ((GetKeyState(0x10) & 0x8000) != 0)
	{
		if ((GetKeyState(0x26) & 0x8000) != 0)
		{ //Arrow_UP

			movement_vector[0] -= 0.01;
		}

		if ((GetKeyState(0x28) & 0x8000) != 0)
		{ //Arrow_Down

			movement_vector[0] += 0.01;
		}

		if ((GetKeyState(0x27) & 0x8000) != 0)
		{ //Arrow_Right

			movement_vector[2] -= 0.01;
		}

		if ((GetKeyState(0x25) & 0x8000) != 0)
		{ //Arrow_Left

			movement_vector[2] += 0.01;
		}

		if ((GetKeyState(0x4E) & 0x8000) != 0)
		{ //M

			movement_vector[1] -= 0.01;
		}

		if ((GetKeyState(0x4D) & 0x8000) != 0)
		{ //N

			movement_vector[1] += 0.01;
		}

		if ((GetKeyState(0x50) & 0x8000) != 0)
		{ //B

			movement_vector[0] = 0;
			movement_vector[1] = 0;
			movement_vector[2] = 0;
		}
	}
	else if ((GetKeyState(0x11) & 0x8000) != 0)
	{
		if ((GetKeyState(0x26) & 0x8000) != 0)
		{ //Arrow_UP

			tilt_vector[1] += 0.01;
		}

		if ((GetKeyState(0x28) & 0x8000) != 0)
		{ //Arrow_Down
			tilt_vector[1] -= 0.01;
		}

		if ((GetKeyState(0x27) & 0x8000) != 0)
		{ //Arrow_Right
			tilt_vector[0] -= 0.01;
		}

		if ((GetKeyState(0x25) & 0x8000) != 0)
		{ //Arrow_Left
			tilt_vector[0] += 0.01;
		}

		if ((GetKeyState(0x50) & 0x8000) != 0)
		{ //B
			tilt_vector[0] = 0;
			tilt_vector[1] = 0;
		}
	}
	else
	{
		if ((GetKeyState(0x26) & 0x8000) != 0)
		{ //Arrow_UP

			angulo_x += 0.5;
		}

		if ((GetKeyState(0x28) & 0x8000) != 0)
		{ //Arrow_Down
			angulo_x -= 0.5;
		}

		if ((GetKeyState(0x27) & 0x8000) != 0)
		{ //Arrow_Right
			angulo_y += 0.5;
		}

		if ((GetKeyState(0x25) & 0x8000) != 0)
		{ //Arrow_Left
			angulo_y -= 0.5;
		}

		if ((GetKeyState(0x4E) & 0x8000) != 0)
		{ //M
			radio += 0.01;
		}

		if ((GetKeyState(0x4D) & 0x8000) != 0)
		{ //N
			radio -= 0.01;
		}

		if ((GetKeyState(0x50) & 0x8000) != 0)
		{ //P
			angulo_y = 0;
			angulo_x = 0;
			radio = 2;
		}
	}

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

void Timer(GLint t)
{
	camera_set();

	light_set();

	// Control Angulo1 teclas Q - W
	if ((GetKeyState(0x51) & 0x8000) != 0)
	{
		if (fAngulo1 < 90)
		{
			fAngulo1 += 1.0f;
		}
	}
	if ((GetKeyState(0x57) & 0x8000) != 0)
	{
		if (fAngulo1 > 0)
		{
			fAngulo1 -= 1.0f;
		}
	}

	// Control Angulo2 teclas E - R
	if ((GetKeyState(0x45) & 0x8000) != 0)
	{
		if (fAngulo2 < 45)
		{
			fAngulo2 += 1.0f;
		}
	}
	if ((GetKeyState(0x52) & 0x8000) != 0)
	{
		if (fAngulo2 > -50)
		{
			fAngulo2 -= 1.0f;
		}
	}

	// Control Angulo3 teclas T - G
	if ((GetKeyState(0x54) & 0x8000) != 0)
	{
		if (fAngulo3 < 30)
		{
			lextension += 0.01;
		}
	}
	if ((GetKeyState(0x47) & 0x8000) != 0)
	{
		if (fAngulo3 > -30)
		{
			lextension -= 0.01;
		}
	}

	// Control Angulo4 teclas Y - H
	if ((GetKeyState(0x59) & 0x8000) != 0)
	{
		if (fAngulo4 < 45)
		{
			fAngulo4 += 1.0f;
		}
	}
	if ((GetKeyState(0x48) & 0x8000) != 0)
	{
		if (fAngulo4 > 0)
		{
			fAngulo4 -= 1.0f;
		}
	}

	// Control Angulo5 teclas U - J
	if ((GetKeyState(0x55) & 0x8000) != 0)
	{
		if (fAngulo5 < 100)
		{
			fAngulo5 += 1.0f;
		}
	}
	if ((GetKeyState(0x4A) & 0x8000) != 0)
	{
		if (fAngulo5 > -100)
		{
			fAngulo5 -= 1.0f;
		}
	}

	glutPostRedisplay();
	glutTimerFunc(tiempo, Timer, 0.0f);
}

//EXTRACTED

bool isBigEndian()
{
    int a = 1;
    return !((char*)&a)[0];
}

//EXTRACTED

int convertToInt(char* buffer, int len)
{
    int a = 0;
    if (!isBigEndian())
        for (int i = 0; i<len; i++)
            ((char*)&a)[i] = buffer[i];
    else
        for (int i = 0; i<len; i++)
            ((char*)&a)[3 - i] = buffer[i];
    return a;
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
	glutCreateWindow("Etapa_6");

	// Indicamos cuales son las funciones de redibujado e idle
	glutDisplayFunc(Display);
	glutTimerFunc(tiempo, Timer, 0.0f);

	// función de direccionamiento d cámara
	//glutSpecialFunc(camera_set);

	//Ajuste de proporciones
	glutReshapeFunc(MyReshape);

	// El color de fondo será el negro (RGBA, RGB + Alpha channel)
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	//cargado texturas
	stbi_set_flip_vertically_on_load(1);

	cyl_0 = gluNewQuadric();
	cyl_1 = gluNewQuadric();
	cyl_2 = gluNewQuadric();
	cyl_3 = gluNewQuadric();
	cyl_4 = gluNewQuadric();
	cyl_5 = gluNewQuadric();
	cyl_6 = gluNewQuadric();
	cyl_7 = gluNewQuadric();

	sphere_1 = gluNewQuadric();
	sphere_2 = gluNewQuadric();
	sphere_3 = gluNewQuadric();
	sphere_4 = gluNewQuadric();

	sphere_5 = gluNewQuadric();
	sphere_6 = gluNewQuadric();
	sphere_7 = gluNewQuadric();

	gluQuadricTexture(cyl_0, GL_TRUE);
	gluQuadricTexture(cyl_1, GL_TRUE);
	gluQuadricTexture(cyl_2, GL_TRUE);
	gluQuadricTexture(cyl_3, GL_TRUE);
	gluQuadricTexture(cyl_4, GL_TRUE);
	gluQuadricTexture(cyl_5, GL_TRUE);
	gluQuadricTexture(cyl_6, GL_TRUE);
	gluQuadricTexture(cyl_7, GL_TRUE);

	gluQuadricTexture(sphere_1, GL_TRUE);
	gluQuadricTexture(sphere_2, GL_TRUE);
	gluQuadricTexture(sphere_3, GL_TRUE);
	gluQuadricTexture(sphere_4, GL_TRUE);

	gluQuadricTexture(sphere_5, GL_TRUE);
	gluQuadricTexture(sphere_6, GL_TRUE);
	gluQuadricTexture(sphere_7, GL_TRUE);

	{
		int width, height, channels;
    	unsigned char *data = stbi_load("./unknown.png", &width, &height, &channels,
        	STBI_rgb);
		glGenTextures(1, &atlas_1);
		glBindTexture(GL_TEXTURE_2D, atlas_1);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
			GL_UNSIGNED_BYTE, data);
		stbi_image_free(data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	}

	{
		int width, height, channels;
    	unsigned char *data = stbi_load("./rubber.png", &width, &height, &channels,
        	STBI_rgb);
		glGenTextures(1, &atlas_2);
		glBindTexture(GL_TEXTURE_2D, atlas_2);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
			GL_UNSIGNED_BYTE, data);
		stbi_image_free(data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	}

	{
		int width, height, channels;
    	unsigned char *data = stbi_load("./metal_sphere.png", &width, &height, &channels,
        	STBI_rgb);
		glGenTextures(1, &atlas_3);
		glBindTexture(GL_TEXTURE_2D, atlas_3);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
			GL_UNSIGNED_BYTE, data);
		stbi_image_free(data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	}

	glBindTexture(GL_TEXTURE_2D, GL_NONE);

	//SOUND

	//sound variables
	/*ALCdevice *device;
	ALCcontext *context;
	ALuint audio_source_1;
	ALuint audio_buffer_1;

	ALsizei audio_size_1, audio_freq_1;
	ALenum audio_format_1;
	ALvoid *audio_data_1;
	ALboolean audio_loop_1 = AL_FALSE;*/

	//device = alcOpenDevice(NULL);
	//context = alcCreateContext(device,NULL);

 //   alcMakeContextCurrent(context);

	////1 source
	//alGenSources((ALuint)1, &audio_source_1);

	////source parameters
	//alSourcef(audio_source_1, AL_PITCH, 1);
	//alSourcef(audio_source_1, AL_GAIN, 10);
	//alSource3f(audio_source_1, AL_POSITION, 0.0f, 0.0f, 0.0f);
	//alSource3f(audio_source_1, AL_VELOCITY, 0.0f, 0.0f, 0.0f);
	//alSourcei(audio_source_1, AL_LOOPING, AL_TRUE);

	////listener parameters
	//alListener3f(AL_POSITION, 0.0f, 0.0f, 0.0f);
	//alListener3f(AL_VELOCITY, 0.0f, 0.0f, 0.0f );
	////alListenerfv(AL_ORIENTATION, {0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f});

	////buffer generation
	//alGenBuffers((ALuint)1, &audio_buffer_1);

	////load file
	//FILE * audio_file;
	//FILE * test_file;
	//char * bit_per_sample = (char*) malloc(sizeof(char)*2);
	//char * num_channels= (char*) malloc(sizeof(char)*2);
	//char * sample_rate= (char*) malloc(sizeof(char)*4);
	//char * sub_chunk_2_size= (char*) malloc(sizeof(char)*4);
	//char * audio_file_1;
	////long * size_of_file = (long*) malloc(sizeof(long));
	//int64_t audio_file_size = 0;
	//string size_append = "";
	//int sample_rate_1 = 0;

	//audio_file = fopen("./test.wav", "r");
	//test_file = fopen("./test.txt", "w");

	////file size
	//// fseek(audio_file, 0, SEEK_END);
	//// size_of_file = ftell(audio_file);
	//// fwrite(size_of_file, sizeof(long), 1, stdout);

	////num channels and so the format
	//fseek(audio_file, 22, SEEK_SET);
	//fread(num_channels, sizeof(char)*2, 1, audio_file);

	////sample rate
	//fseek(audio_file, 24, SEEK_SET);
	//fread(sample_rate, sizeof(char), 4, audio_file);
	//sample_rate_1 = convertToInt(sample_rate, 4);

	////bits per sample
	//fseek(audio_file, 34, SEEK_SET);
	//fread(bit_per_sample, sizeof(char)*2, 1, audio_file);
	////fwrite(bit_per_sample, sizeof(char)*2, 1, test_file);

	//if(device) fprintf(test_file, "device exit\n");
	//if(context) fprintf(test_file, "context exit\n");


	//if(bit_per_sample[0] == 16){
	//	if (num_channels[0] == 1){
 //   		audio_format_1 = AL_FORMAT_MONO16;
	//	} else {
 //   		audio_format_1 = AL_FORMAT_STEREO16;
	//	}
	//} else {
	//	if (num_channels[0] == 1){
 //   		audio_format_1 = AL_FORMAT_MONO8;
	//	} else {
 //   		audio_format_1 = AL_FORMAT_STEREO8;
	//	}
	//}

	////size of data -> posición 732 en test.wav // DATA = 64 61 74 61
	//fseek(audio_file, 732, SEEK_SET);
	//fread(sub_chunk_2_size, sizeof(char)*4, 1, audio_file);
	////fwrite(sub_chunk_2_size, sizeof(char)*4, 1, test_file);

	//audio_file_size = 2229537289;

	//audio_data_1 = (ALvoid*) malloc(sizeof(char)*audio_file_size);

	//fseek(audio_file, 732 + 4, SEEK_SET);
	////fread(audio_data_1, sizeof(char)*audio_file_size, 1, audio_file);
	////fwrite(audio_data_1, sizeof(char)*audio_file_size, 1, test_file);

	////memcpy(audio_buffer_1, &audio_file_1, audio_file_size);

	//fclose(audio_file);
	//fclose(test_file);

	//free(bit_per_sample);
	//free(num_channels);
	//free(sample_rate);
	// free(sub_chunk_2_size);
	// free(size_of_data);

	////link audio fileto buffer
	//alBufferData(audio_buffer_1,audio_format_1, audio_data_1, sizeof(audio_data_1), sample_rate_1);

	////link buffer to source
	//alSourcei(audio_source_1, AL_BUFFER, audio_buffer_1);
	////play audio
	//alSourcePlay(audio_source_1);
	
	// Comienza la ejecución del core de GLUT
	glutMainLoop();
	return 0;
}