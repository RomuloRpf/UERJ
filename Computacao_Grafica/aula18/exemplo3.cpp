#include <windows.h>
#include <GL/glut.h>
#include<iostream>
using namespace std;


// Função callback chamada para fazer o desenho
void Desenha(void) {

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Limpa a janela de visualização com a cor de fundo especificada
	glClear(GL_COLOR_BUFFER_BIT);

	// Especifica que a cor corrente é verde
	glColor3f(0.0f, 1.0f, 0.0f);

	glBegin(GL_QUADS); // Desenha quadrado com a cor corrente
	glVertex2i(100, 150);
	glVertex2i(100, 100);
	glVertex2i(150, 100);
	glVertex2i(150, 150);
	glEnd();
	glFlush(); // Executa os comandos OpenGL
}


// Inicializa parâmetros de desenho
void Inicializa(void) {

	// Define a cor de fundo da janela de visualização como preta
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}


// Função callback chamada quando o tamanho da janela é alterado
void AlteraTamanhoJanela(GLsizei w, GLsizei h) {

	if (h == 0) h = 1; // Evita a divisao por zero
	glViewport(0, 0, w, h); // Especifica as dimensões da Viewport
	glMatrixMode(GL_PROJECTION); // Inicializa a matriz de projeção
	glLoadIdentity();
	// Estabelece World Window (left, right, bottom, top)
	if (w <= h)
		gluOrtho2D(0.0f, 250.0f, 0.0f, 250.0f * h / w);
	else
		gluOrtho2D(0.0f, 250.0f * w / h, 0.0f, 250.0f);
}


// Programa Principal
int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(400, 350);
	glutInitWindowPosition(10, 10);
	glutCreateWindow("Quadrado");
	glutDisplayFunc(Desenha);
	glutReshapeFunc(AlteraTamanhoJanela);
	Inicializa();
	glutMainLoop();
}