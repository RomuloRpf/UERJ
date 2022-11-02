#include <GL/glut.h>
#include<iostream>
using namespace std;

// Fun��o callback chamada para fazer o desenho
void Desenha(void) { 
	
	glClear(GL_COLOR_BUFFER_BIT); //Limpa a janela de visualiza��o com a cor de fundo especificada
	glFlush(); //Executa os comandos OpenGL
}

// Inicializa par�metros de desenho
void Inicializa(void) { 
	
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Define a cor de fundo da janela de visualiza��o como preta
}


// Programa Principal
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutCreateWindow("Primeiro Programa");
	glutDisplayFunc(Desenha);
	Inicializa();
	glutMainLoop();
	return 0;
}