#include <stdlib.h>
#include <gl/glut.h>
#include <GL/glut.h>
using namespace std;

GLfloat fov, fAspect;

// Função callback chamada para fazer o desenho
void Desenha(void) {

	// Limpa a janela e o depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fov, fAspect, 0.4, 500);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 80, 200, 0, 0, 0, 0, 1, 0);

	// Desenha o teapot com a cor corrente
	glColor3f(0.6f, 0.4f, 0.1f);
	glutSolidTeapot(50.0f);
	glutSwapBuffers();
}

// Inicializa parâmetros de iluminação
void Inicializa(void) {

	// Características da fonte de luz
	GLfloat luzAmbiente[4] = { 0.2, 0.2, 0.2, 1.0 };
	GLfloat luzDifusa[4] = { 0.7, 0.7, 0.7, 1.0 };
	GLfloat luzEspecular[4] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat posicaoLuz[4] = { 0.0, 50.0, 50.0, 1.0 };

	// Ativa o uso da luz ambiente
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);

	// Define os parâmetros da luz de número 0
	glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa);
	glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular);
	glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz);

	// Características do material
	GLfloat especularidade[4] = { 1.0,1.0,1.0,1.0 };
	GLint especMaterial = 60;
	glMaterialfv(GL_FRONT, GL_SPECULAR, especularidade);
	glMateriali(GL_FRONT, GL_SHININESS, especMaterial);
	glShadeModel(GL_SMOOTH); // Modelo de colorização de Gouraud
	glEnable(GL_COLOR_MATERIAL); // Habilita a cor do material
	glEnable(GL_LIGHTING); // Habilita o uso de iluminação
	glEnable(GL_LIGHT0); // Habilita fonte de número 0
	glEnable(GL_DEPTH_TEST); // Habilita o depth-buffering

	// Especifica que a cor de fundo da janela será preta
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	fov = 45;
}

// Função callback chamada quando o tamanho da janela é alterado
void AlteraTamanhoJanela(GLsizei w, GLsizei h) {
	if (h == 0) h = 1; // Para previnir uma divisão por zero
	glViewport(0, 0, w, h); // Especifica o tamanho da viewport
	fAspect = (GLfloat)w / (GLfloat)h; // Correção de aspecto
	glutPostRedisplay(); // Redesenha
}
// Função callback chamada para gerenciar eventos do mouse
void GerenciaMouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON) // Zoom-in
		if (state == GLUT_DOWN) { if (fov >= 10) fov -= 5; }
	if (button == GLUT_RIGHT_BUTTON) // Zoom-out
		if (state == GLUT_DOWN) { if (fov <= 130) fov += 5; }
	glutPostRedisplay(); // Redesenha
}

// Programa Principal
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(400, 350);
	glutCreateWindow("Bule Iluminado");
	glutDisplayFunc(Desenha);
	glutReshapeFunc(AlteraTamanhoJanela);
	glutMouseFunc(GerenciaMouse);
	Inicializa();
	glutMainLoop();
}