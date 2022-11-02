#include <stdlib.h>
#include <GL/glut.h>
#include "RgbImage.h"

#define _CRT_SECURE_NO_WARNINGS

// variaveis globais
GLfloat xRotated, yRotated, zRotated; //angulos de rotacao
GLuint texture[1]; // id da textura
char* filename = (char *)"./textura.bmp"; //arquivo com a textura

// callback para redimensionar janela glut
void resizeWindow(int x, int y) {
	if (y == 0 || x == 0) return;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1.5, 1.5, -1.5, 1.5, 3.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
	if (x > y) glViewport(0, 0, y, y);
	else glViewport(0, 0, x, x);
}

void loadTextureFromFile(char* filename) {// lê textura de arquivo
	RgbImage theTexMap(filename);
	glGenTextures(1, &texture[0]); // Cria a textura
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, //Sempre GL_TEXTURE_2D
		0, //Nível de detalhe da textura (0)
		3, //Número de componentes de cor
		theTexMap.GetNumCols(), //Largura
		theTexMap.GetNumRows(), //Altura
		0, //Bordas (deve ser 0)
		GL_RGB, //Formato interno: RGB
		GL_UNSIGNED_BYTE, //Pixels armazenados como unsigned
		theTexMap.ImageData()); //A imagem/pixels da textura
}

// desenha cubo
void drawScene(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -5);
	glRotatef(yRotated, 0, 1, 0);
	glRotatef(zRotated, 0, 0, 1);
	glBegin(GL_QUADS); // Face posterior
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
	glEnd();
	glBegin(GL_QUADS); // Face frontal
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
	glEnd();
	glBegin(GL_QUADS); // Face lateral esquerda
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
	glEnd();
	glBegin(GL_QUADS); // Face lateral direita
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
	glEnd();
	glBegin(GL_QUADS); // Face superior
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
	glEnd();
	glBegin(GL_QUADS); // Face inferior
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, -1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
	glEnd();
	glutSwapBuffers();
}

// callback de teclado
void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 27:
		exit(0);
		break;
	default:
		break;
	}
}

// callback idle
void idleFunc(void) {
	yRotated += 0.05;
	zRotated += 0.05;
	drawScene();
}
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(240, 240);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Cubo com textura");
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	loadTextureFromFile(filename);
	glutDisplayFunc(drawScene);
	glutReshapeFunc(resizeWindow);
	glutKeyboardFunc(keyboard);
	glutIdleFunc(idleFunc);
	glutMainLoop();
	return 0;
}