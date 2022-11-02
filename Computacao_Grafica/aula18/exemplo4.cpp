#include <windows.h>
#include <GL/glut.h>
#include<iostream>
using namespace std;

// Funções callback
void desenha(void);
void movimento(int x, int y);
void botao(int button, int state, int x, int y);
void alteraTamanhoJanela(GLsizei w, GLsizei h);

// Variáveis globais
float largura, altura; // tamanho da world window e do viewport
float rx, ry; // posição inicial do retângulo vermelho

int main(int argc, char* argv[]) {
	largura = 600;
	altura = 600;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glClearColor(0, 0, 0, 1);
	glutPositionWindow(200, 100);
	glutReshapeWindow(largura, altura);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, largura, 0, altura);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glutDisplayFunc(desenha);
	glutIdleFunc(desenha);
	glutMotionFunc(movimento);
	glutMouseFunc(botao);
	glutReshapeFunc(alteraTamanhoJanela);
	glutMainLoop();
	return 0;
}


// Função callback chamada para fazer o desenho
void desenha(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1, 1, 0); // desenha em amarelo
	glRectf(100, 100, 300, 200); // desenha retângulo amarelo
	glColor3f(1, 0, 0); // desenha em vermelho
	glRectf(rx, ry, 100 + rx, 20 + ry); // desenha retângulo vermelho
	glutSwapBuffers(); // buffer de cor duplo
}


// Função callback para o mouse se movimentando com botão pressionado
void movimento(int x, int y) {
	rx = x; ry = altura - y;
}


// Função callback chamada quando o botão do mouse é pressionado
void botao(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		rx = x; ry = altura - y;
}


// Função callback chamada quando o tamanho da janela é alterado
void alteraTamanhoJanela(GLsizei w, GLsizei h) {
	largura = w;
	altura = h;
	// Especifica as dimensões da Viewport
	glViewport(0, 0, largura, altura); // comando não necessário:
	// comportamento default
	// Inicializa o sistema de coordenadas do mundo
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// Dimensões da World Window (left, right, bottom, top)
	gluOrtho2D(0, largura, 0, altura);
}