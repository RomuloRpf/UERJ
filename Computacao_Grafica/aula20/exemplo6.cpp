#include <stdio.h>
#include <GL/glut.h>
#include <iostream>
using namespace std;


// variaveis globais
GLint Width = 800;
GLint Height = 800;
static GLfloat spin_z = 0.0;
static GLfloat spin_y = 0.0;
char objectId = 'b';
// prototipos
void drawObject(void); // desenha o bule
void spinDisplay(void); // rotaciona bule
void initLighting(void); // define a fonte de luz
void reshape(int width, int height); // callback de redesenho
void display(void); // callback de desenho
void keyboard(unsigned char key, int x, int y); // callback de teclado

// programa principal
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(Width, Height);
	glutCreateWindow("Bule em 4 vistas");
	initLighting();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}

// desenha o objeto
void drawObject(void) {
	switch (objectId) {
	case 'b':
		glColor3f(1.0, 1.0, 1.0);
		glutSolidTeapot(2.0);
		break;
	case 'o':
		glColor3f(1.0, 1.0, 1.0);
		glutSolidDodecahedron();
		break;
	default:
		return;
	}
}

// rotaciona objeto
void spinDisplay(void) {
	if (spin_z > 360.0)
		spin_z = spin_z - 360.0;
	if (spin_y > 360.0)
		spin_y = spin_y - 360.0;
	glutPostRedisplay();
}
// callback de redesenho da janela glut
void reshape(int width, int height) {
	Width = width;
	Height = height;
	//glViewport(0, 0, width, height);
	glutPostRedisplay();
}

// define a fonte de luz (LIGHT0)
void initLighting(void) {
	GLfloat lightposition[] = { 3.0, -3.0, 3.0, 0.0 };
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glLightfv(GL_LIGHT0, GL_POSITION, lightposition);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	glEnable(GL_COLOR_MATERIAL);
	glClearColor(0.0, 1.0, 1.0, 0.0);
}

// callback de teclado
void keyboard(unsigned char key, int x, int y) {
	cout << key;
	switch (key) {
	case 27: exit(0); break;
	case 'a': spin_z = spin_z - 2.0; spinDisplay(); break;
	case 's': spin_z = spin_z + 2.0; spinDisplay(); break;
	case 'z': spin_y = spin_y - 2.0; spinDisplay(); break;
	case 'w': spin_y = spin_y + 2.0; spinDisplay(); break;
	case 'o':
		if (objectId == 'b') objectId = 'o'; else objectId = 'b';
		glutPostRedisplay(); break;
	default:
		return;
	}
}

// callback de desenho
void display(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// viewport topo/esquerda
	glViewport(0, Height / 2, Width / 2, Height / 2);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-3.0, 3.0, -3.0, 3.0, 0.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1.0);
	drawObject();

	// viewport topo/direita
	glViewport(Width / 2, Height / 2, Width / 2, Height / 2);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-3.0, 3.0, -3.0, 3.0, 1.0, 50.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(5.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	drawObject();

	// viewport baixo/esquerda
	glViewport(0, 0, Width / 2, Height / 2);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-3.0, 3.0, -3.0, 3.0, 1.0, 50.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	drawObject();

	// viewport baixo/direita
	glViewport(Width / 2, 0, Width / 2, Height / 2);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-3.0, 3.0, -3.0, 3.0, 2.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glRotatef(45.0, 1.0, 0.0, 0.0);
	glRotatef(spin_z, 0.0, 0.0, 1.0);
	glRotatef(spin_y, 0.0, 1.0, 0.0);
	drawObject();
	glutSwapBuffers();
}