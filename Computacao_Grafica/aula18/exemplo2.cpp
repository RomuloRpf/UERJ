#include <GL/glut.h>
#include<iostream>
using namespace std;

// Função callback chamada para fazer o desenho
void Desenha(void) {

	//Limpa a janela de visualização com a cor branca
	glClearColor(1, 1, 1, 0);
	glClear(GL_COLOR_BUFFER_BIT);

	//Define a cor de desenho: vermelho
	glColor3f(1, 0, 0);

	//Desenha um triângulo no centro da janela
	glBegin(GL_TRIANGLES);
	glVertex2f(-0.5, -0.5);
	//glColor3f(0,1,0);
	glVertex2f(0.0, 0.5);
	//glColor3f(0, 0, 1);
	glVertex2f(0.5, -0.5);
	glEnd();

	//Executa os comandos OpenGL
	glFlush();
}


//Função callback chamada para gerenciar eventos de teclas
void Teclado(unsigned char key, int x, int y) {
	if (key == 27)
		exit(0);
}


// Inicializa parâmetros e variáveis
void Inicializa(void) {

	// Define a janela de visualização 2D
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
}


// Programa Principal
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(400, 400);
	glutCreateWindow("Segundo Programa");
	glutDisplayFunc(Desenha);
	glutKeyboardFunc(Teclado);
	Inicializa();
	glutMainLoop();
	return 0;
}