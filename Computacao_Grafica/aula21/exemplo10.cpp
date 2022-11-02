#include <windows.h>
#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>
#include "RgbImage.h"
#define _CRT_SECURE_NO_WARNINGS
using namespace std;

void defineStencilArea(void);

char view = 's';
bool stencil = false;
float rotationAngle;
float width = 800.0;
float height = 500.0;
char* filenameEarth = (char *)"./earthmap1k.bmp"; //image file with Earth's text.
char* filenameMetal = (char *)"./textura_metal.bmp"; //image file with metal text.
GLuint _textureIdEarth;
GLuint _textureIdMetal;
GLUquadric* quadEarth;

void handleKeypress(unsigned char key, int x, int y) {
	switch (key) {
	case 27: //Escape key
		exit(0); break;
	case 't': //Top view
		view = key; glutPostRedisplay(); break;
	case 's': //Side view
		view = key; glutPostRedisplay(); break;
	case 'b': //Bottom view
		view = key; glutPostRedisplay(); break;
	case 'z': //Use stencil
		stencil = !stencil;
		glutPostRedisplay();
		break;
	}
}

//Makes the image into a texture, and returns the id of the texture
GLuint loadTexture(char* filename) {
	GLuint textureId;
	RgbImage theTexMap(filename); //Image with texture
	glGenTextures(1, &textureId); //Make room for our texture
	glBindTexture(GL_TEXTURE_2D, textureId); //Which texture to edit
	//Map the image to the texture
	glTexImage2D(GL_TEXTURE_2D, //Always GL_TEXTURE_2D
		0, //0 for now
		GL_RGB, //Format OpenGL uses for image
		theTexMap.GetNumCols(), //Width
		theTexMap.GetNumRows(), //Height
		0, //The border of the image
		GL_RGB, //Pixels are stored in RGB format
		GL_UNSIGNED_BYTE, //Pixels are stored as unsigned
		theTexMap.ImageData()); //The actual pixel data
	return textureId; //Returns the id of the texture
}

void initRendering() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_STENCIL_TEST);
	glEnable(GL_TEXTURE_2D);
	glClearStencil(0x0);
	quadEarth = gluNewQuadric();
	_textureIdEarth = loadTexture(filenameEarth);
	_textureIdMetal = loadTexture(filenameMetal);
}
void handleResize(int w, int h) {
	glViewport(0, 0, width, height);
	defineStencilArea();
}

void defineStencilArea(void) {
	glStencilMask(0xFF); //Enables writing in stencil mask
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClear(GL_STENCIL_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-8.0, 8.0, -6.0, 6.0);
	glStencilFunc(GL_ALWAYS, 0x1, 0x1);
	glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);
	glBegin(GL_QUADS);
	glVertex2f(-5.0, -2.0); glVertex2f(-1.0, -2.0);
	glVertex2f(-1.0, 2.0); glVertex2f(-5.0, 2.0);
	glEnd();
	glBegin(GL_QUADS);
	glVertex2f(1.0, -2.0); glVertex2f(5.0, -2.0);
	glVertex2f(5.0, 2.0); glVertex2f(1.0, 2.0);
	glEnd();
	glStencilMask(0x00); //Disables writing in stencil mask
}

void drawScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (float)width / (float)height, 1.0, 200.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	switch (view) {
	case 't': //Top view
		gluLookAt(0.0f, 0.0f, 20.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f);
		break;
	case 's': //Side view
		gluLookAt(20.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
		break;
	case 'b': //Bottom view
		gluLookAt(0.0f, 0.0f, -20.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
		break;
	}
	if (stencil) {
		//Paint the metal texture (inside spacecraft)
		glPushMatrix();
		switch (view) {
		case 't': //Top view
			glRotatef(180, 1.0f, 0.0f, 0.0f);
			break;
		case 's': //Side view
			glRotatef(-90, 0.0f, 1.0f, 0.0f);
			glRotatef(-90, 0.0f, 0.0f, 1.0f);
			break;
		}
		glBindTexture(GL_TEXTURE_2D, _textureIdMetal);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glStencilFunc(GL_NOTEQUAL, 0x1, 0x1); //Draw outside stencil
		glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0, -5.0, -1.0);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0, -5.0, -1.0);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0, 5.0, -1.0);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0, 5.0, -1.0);
		glEnd();
		glPopMatrix();
		glStencilFunc(GL_EQUAL, 0x1, 0x1); //Draw inside stencil area
		glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
	}
	else {
		glStencilFunc(GL_ALWAYS, 0x1, 0x1); //Ignore stencil area
		glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);
	}
	// Rotate and paint the Earth
	glRotatef(rotationAngle, 0.0f, 0.0f, 1.0f);
	glBindTexture(GL_TEXTURE_2D, _textureIdEarth);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	gluQuadricTexture(quadEarth, GLU_TRUE);
	gluSphere(quadEarth, 4, 40, 40);
	glutSwapBuffers();
}


void update(int value) {
	rotationAngle += 1.0f;
	if (rotationAngle > 360.f) {
		rotationAngle -= 360;
	}
	glutPostRedisplay();
	glutTimerFunc(25, update, 0);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_STENCIL);
	glutInitWindowSize(width, height);
	glutCreateWindow("Textured Earth");
	initRendering();
	glutTimerFunc(25, update, 0);
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(handleKeypress);
	glutReshapeFunc(handleResize);
	glutMainLoop();
	return 0;
}