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
		if (fAngulo1 < 100)
		{
			fAngulo1 += 1.0f;
		}
	}
	if ((GetKeyState(0x57) & 0x8000) != 0)
	{
		if (fAngulo1 > -45)
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
			fAngulo3 += 1.0f;
		}
	}
	if ((GetKeyState(0x47) & 0x8000) != 0)
	{
		if (fAngulo3 > -30)
		{
			fAngulo3 -= 1.0f;
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

	// función de direccionamiento d cámara
	//glutSpecialFunc(camera_set);

	//Ajuste de proporciones
	glutReshapeFunc(MyReshape);

	// El color de fondo será el negro (RGBA, RGB + Alpha channel)
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	//param_SPOT_DIR[0] = param_SPOT_DIR[0] + sin(toRadians(25.0f))*0.17;
	param_SPOT_DIR[3] = param_SPOT_DIR[3] - cos(toRadians(60.0f))*0.20;

	// Comienza la ejecución del core de GLUT
	glutMainLoop();
	return 0;
}