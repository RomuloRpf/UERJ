#include <windows.h>
#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>
#include "RgbImage.h"

#define _CRT_SECURE_NO_WARNINGS
#define PI 3.141592654

using namespace std;

char* filenameTexMetal = (char *)"./metalTexture.bmp"; 
char* filenameTexEye = (char*)"./texture_eye.bmp";

GLuint _textureIdEye;
GLuint _textureIdMetal;
GLuint _textureIdSphere; 
GLuint _textureIdCylinder; 
GLUquadric *quadSphere;
GLUquadric *quadCylinder;

bool textureOn = true;
bool headLightsOn = false;

int lightOn = 0;
int legMove = 0;
int armMove = 0;

float bodySize = 5.0;
float headSize = 3.0;
float feetsize = 1.0;

float feetSphere = 0.5;
float feetDiamC = 0.4;
float feetLenC = 3.0;
float shoulderDiameter = 1.0;
float neckDiameter = 0.5;
float neckLenght = 2.5;

float angleHead = 0.0;
float angleShoulder1 = 90.0;
float angleFeet1 = 0.0;
float angleKnee1 = 0.0;
float angleLeg1 = 0.0;

float angleShoulder2 = 90.0;
float angleFeet2 = 0.0;
float angleKnee2 = 0.0;
float angleLeg2 = 0.0;

float diameterCylinder = 0.3;
float diameterSphere = 0.4;
float sizeArm = 4.5;
float sizeForearm = 3.0;
float sizeHand = 2.0;
float sizeClampPart = 1.0;
float diameterBase = 2.0;
float heightBase = 0.5;

float eyeDistance = 30.0; 
float eyeX;
float eyeY;
float eyeZ;
float viewAngleX = 0.0;
float viewAngleZ = 15.0;

float angleArm1 = 90.0;
float angleForearm1 = 90.0;
float angleHand1 = 0.0;
float angleClampZ1 = 0.0;
float angleClampY1 = 0.0;

float angleArm2 = 90.0;
float angleForearm2 = 90.0;
float angleHand2 = 0.0;
float angleClampZ2 = 0.0;
float angleClampY2 = 0.0;

GLfloat luzDifusa0[4] = { 0.3, 0.3, 0.3, 1.0 };
GLfloat luzDifusa0_p[4] = { -10.0f, -10.0f, 5.0f, 1.0f };

GLfloat luzDifusa1[4] = { 0.7, 0.7, 0.7, 1.0 };
GLfloat luzDifusa1_p[4] = { 10.0f, 10.0f, 8.0f, 1.0f };

GLfloat especularidade[4] = { 1.0,1.0,1.0,1.0 };
GLint especMaterial = 80;

GLfloat emissaoPadrao[4] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat emissaoHeadSpheres[4] = { 1.0, 0.0, 0.0, 1.0 };


//defines light source (LIGHT0)
void initLighting(void)
{
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHTING);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, especularidade);
	glMateriali(GL_FRONT, GL_SHININESS, especMaterial);
	glMaterialfv(GL_FRONT, GL_EMISSION, emissaoPadrao);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	// Especifica que a cor de fundo da janela será preta
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// Habilita o modelo de colorização de Gouraud
	glShadeModel(GL_SMOOTH);

	// Define os parâmetros das luzes de número 0 e 1
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa0);
	glLightfv(GL_LIGHT0, GL_POSITION, luzDifusa0_p);

	glLightfv(GL_LIGHT1, GL_DIFFUSE, luzDifusa1);
	glLightfv(GL_LIGHT1, GL_POSITION, luzDifusa1_p);


	// Materials will follow current color
	glEnable(GL_COLOR_MATERIAL);
}

//makes the image into a texture, and returns the id of the texture
GLuint loadTexture(char *filename) {
	GLuint textureId;

	RgbImage theTexMap(filename); //Image with texture

	glGenTextures(1, &textureId); //Make room for our texture
	glBindTexture(GL_TEXTURE_2D, textureId);	//Tell OpenGL which texture to edit
												//Map the image to the texture
	glTexImage2D(GL_TEXTURE_2D,	//Always GL_TEXTURE_2D
		0,						//0 for now
		GL_RGB,					//Format OpenGL uses for image
		theTexMap.GetNumCols(),	//Width 
		theTexMap.GetNumRows(),	//Height
		0,						//The border of the image
		GL_RGB,					//GL_RGB, because pixels are stored in RGB format
		GL_UNSIGNED_BYTE,		//GL_UNSIGNED_BYTE, because pixels are stored as unsigned numbers
		theTexMap.ImageData());	//The actual pixel data
	return textureId; //Returns the id of the texture
}

void initRendering(void) {
	quadSphere = gluNewQuadric();
	quadCylinder = gluNewQuadric();
	_textureIdMetal = loadTexture(filenameTexMetal);
	_textureIdEye = loadTexture(filenameTexEye);
	_textureIdCylinder = _textureIdMetal;
	_textureIdSphere = _textureIdEye;
}

void handleKeypress(unsigned char key, int x, int y) {
	switch (key) {
	case 27: //Escape key
		exit(0);
	case 'w': //Increase view angle z axis
		if (viewAngleZ < 180) viewAngleZ += 3;
		glutPostRedisplay();
		break;
	case 'z': //Decrease view angle z axis
		if (viewAngleZ > 0) viewAngleZ -= 3;
		glutPostRedisplay();
		break;
	case 'a': //Decrease view angle x axis
		if (viewAngleX > 0) viewAngleX -= 3;
		glutPostRedisplay();
		break;
	case 's': //Increase view angle x axis
		if (viewAngleX < 180) viewAngleX += 3;
		glutPostRedisplay();
		break;
	case 't': //Use texture or not
		textureOn = !textureOn;
		glutPostRedisplay();
		break;
	case '1': //Increase arm angle
		if (armMove == 0) {
			angleArm1 += 3;
			angleArm2 += 3;
		}
		else {
			if (armMove == 1) {
				angleArm1 += 3;
			}
			else {
				angleArm2 += 3;
			}
		}
		if (angleArm1 >= 360) angleArm1 = 0;
		if (angleArm2 >= 360) angleArm2 = 0;
		glutPostRedisplay();
		break;
	case '2': //Decrease arm angle
		if (armMove == 0) {
			angleArm1 -= 3;
			angleArm2 -= 3;
		}
		else {
			if (armMove == 1) {
				angleArm1 -= 3;
			}
			else {
				angleArm2 -= 3;
			}
		}
		if (angleArm1 <= 0) angleArm1 = 360;
		if (angleArm2 <= 0) angleArm2 = 360;
		glutPostRedisplay();
		break;
	case '3': //Increase forearm angle
		if (armMove == 0) {
			if (angleForearm1 < 90) angleForearm1 += 3;
			if (angleForearm2 < 90) angleForearm2 += 3;
		}
		else {
			if (armMove == 1) {
				if (angleForearm1 < 90) angleForearm1 += 3;
			}
			else {
				if (angleForearm2 < 90) angleForearm2 += 3;
			}
		}
		glutPostRedisplay();
		break;
	case '4': //Decrease forearm angle
		if (armMove == 0) {
			if (angleForearm1 > -90) angleForearm1 -= 3;
			if (angleForearm2 > -90) angleForearm2 -= 3;
		}
		else {
			if (armMove == 1) {
				if (angleForearm1 > -90) angleForearm1 -= 3;
			}
			else {
				if (angleForearm2 > -90) angleForearm2 -= 3;
			}
		}
		glutPostRedisplay();
		break;
	case '5': //Increase clamp angle y axis
		if (armMove == 0) {
			if (angleClampY1 < 60) angleClampY1 += 3;
			if (angleClampY2 < 60) angleClampY2 += 3;
		}
		else {
			if (armMove == 1) {
				if (angleClampY1 < 60) angleClampY1 += 3;
			}
			else {
				if (angleClampY2 < 60) angleClampY2 += 3;
			}
		}
		glutPostRedisplay();
		break;
	case '6': //Decrease clamp angle y axis
		if (armMove == 0) {
			if (angleClampY1 > 0) angleClampY1 -= 3;
			if (angleClampY2 > 0) angleClampY2 -= 3;
		}
		else {
			if (armMove == 1) {
				if (angleClampY1 > 0) angleClampY1 -= 3;
			}
			else {
				if (angleClampY2 > 0) angleClampY2 -= 3;
			}
		}
		glutPostRedisplay();
		break;
	case '7':
		if (armMove == 0) {
			if (angleShoulder1 < 180) angleShoulder1 += 3;
			if (angleShoulder2 < 180) angleShoulder2 += 3;
		}
		else {
			if (armMove == 1) {
				if (angleShoulder1 < 180) angleShoulder1 += 3;
			}
			else {
				if (angleShoulder2 < 180) angleShoulder2 += 3;
			}
		}
		glutPostRedisplay();
		break;
	case '8':
		if (armMove == 0) {
			if (angleShoulder1 > 0) angleShoulder1 -= 3;
			if (angleShoulder2 > 0) angleShoulder2 -= 3;
		}
		else {
			if (armMove == 1) {
				if (angleShoulder1 > 0) angleShoulder1 -= 3;
			}
			else {
				if (angleShoulder2 > 0) angleShoulder2 -= 3;
			}
		}
		glutPostRedisplay();
		break;
	case '9':
		angleHead += 3;
		glutPostRedisplay();
		break;
	case '0':
		angleHead -= 3;
		glutPostRedisplay();
		break;
	case 'u':
		if (legMove == 0) {
			if (angleLeg1 < 90) angleLeg1 += 3;
			if (angleLeg2 < 90) angleLeg2 += 3;
		}
		else {
			if (legMove == 1) {
				if (angleLeg1 < 90) angleLeg1 += 3;
			}
			else {
				if (angleLeg2 < 90) angleLeg2 += 3;
			}
		}
		glutPostRedisplay();
		break;
	case 'i':
		if (legMove == 0) {
			if (angleLeg1 > -90) angleLeg1 -= 3;
			if (angleLeg2 > -90) angleLeg2 -= 3;
		}
		else {
			if (legMove == 1) {
				if (angleLeg1 > -90) angleLeg1 -= 3;
			}
			else {
				if (angleLeg2 > -90) angleLeg2 -= 3;
			}
		}
		glutPostRedisplay();
		break;
	case 'j':
		if (legMove == 0) {
			if (angleKnee1 < 120) angleKnee1 += 3;
			if (angleKnee2 < 120) angleKnee2 += 3;
		}
		else {
			if (legMove == 1) {
				if (angleKnee1 < 120) angleKnee1 += 3;
			}
			else {
				if (angleKnee2 < 120) angleKnee2 += 3;
			}
		}
		glutPostRedisplay();
		break;
	case 'k':
		if (legMove == 0) {
			if (angleKnee1 > 0) angleKnee1 -= 3;
			if (angleKnee2 > 0) angleKnee2 -= 3;
		}
		else {
			if (legMove == 1) {
				if (angleKnee1 > 0) angleKnee1 -= 3;
			}
			else {
				if (angleKnee2 > 0) angleKnee2 -= 3;
			}
		}
		glutPostRedisplay();
		break;
	case 'n':
		if (legMove == 0) {
			if (angleFeet1 < 90) angleFeet1 += 3;
			if (angleFeet2 < 90) angleFeet2 += 3;
		}
		else {
			if (legMove == 1) {
				if (angleFeet1 < 90) angleFeet1 += 3;
			}
			else {
				if (angleFeet2 < 90) angleFeet2 += 3;
			}
		}
		glutPostRedisplay();
		break;
	case 'm':
		if (legMove == 0) {
			if (angleFeet1 > 0) angleFeet1 -= 3;
			if (angleFeet2 > 0) angleFeet2 -= 3;
		}
		else {
			if (legMove == 1) {
				if (angleFeet1 > 0) angleFeet1 -= 3;
			}
			else {
				if (angleFeet1 > 0) angleFeet2 -= 3;
			}
		}
		glutPostRedisplay();
		break;
	case 'l':
		if (lightOn == 3) {
			lightOn = 0;
		}
		else {
			lightOn += 1;
		}
		glutPostRedisplay();
		break;
	case 'h':
		headLightsOn = !headLightsOn;
		glutPostRedisplay();
		break;
	case 'p':
		if(legMove == 2) {
			legMove = 0;
		}
		else {
			legMove += 1;
		}
		glutPostRedisplay();
		break;
	case 'b':
		if (armMove == 2) {
			armMove = 0;
		}
		else {
			armMove += 1;
		}
		glutPostRedisplay();
		break;
	}
}

void handleMouseButton(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON) { // Zoom-in
		if (eyeDistance > 10) {
			eyeDistance -= 1;
		}
	}
	if (button == GLUT_RIGHT_BUTTON) { // Zoom-out
		if (eyeDistance < 47) { 
			eyeDistance += 1; 
		}
	}
	glutPostRedisplay(); // Redesenha
}

void handleResize(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (float)w / (float)h, 1.0, 50.0);
}

void drawCylinder(float diameter, float lenght) {
	if (textureOn) {
		glBindTexture(GL_TEXTURE_2D, _textureIdCylinder);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		gluQuadricTexture(quadCylinder, 1);
	}
	else 
		gluQuadricTexture(quadCylinder, 0);
	gluCylinder(quadCylinder, diameter, diameter, lenght, 40.0, lenght*30.0);
}

void drawCone(float diameter, float lenght) {
	if (textureOn) {
		glBindTexture(GL_TEXTURE_2D, _textureIdCylinder);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		gluQuadricTexture(quadCylinder, 1);
	} else
		gluQuadricTexture(quadCylinder, 0);
	gluCylinder(quadCylinder, diameter, 0, lenght, 40.0, lenght*30.0);
}

void drawDisk(float diameterInner, float diameterOuter) {
	if (textureOn) {
		glBindTexture(GL_TEXTURE_2D, _textureIdCylinder);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		gluQuadricTexture(quadCylinder, 1);
	}
	else
		gluQuadricTexture(quadCylinder, 0);
	gluDisk(quadCylinder, diameterInner, diameterOuter, 40.0, 30.0);
}

void drawSphere(float diameter) {
	if (headLightsOn == true) {
		glMaterialfv(GL_FRONT, GL_EMISSION, emissaoHeadSpheres);
	}
	else {
		glMaterialfv(GL_FRONT, GL_EMISSION, emissaoPadrao);
	}
	if (textureOn) {
		glBindTexture(GL_TEXTURE_2D, _textureIdSphere);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		gluQuadricTexture(quadSphere, 1);
	} else
		gluQuadricTexture(quadSphere, 0);
	gluSphere(quadSphere, diameter, 40.0, 40.0);
	glMaterialfv(GL_FRONT, GL_EMISSION, emissaoPadrao);
}

void drawCube(float cubeSize) {
	if (textureOn) {

		glBindTexture(GL_TEXTURE_2D, _textureIdMetal);

		glBegin(GL_QUADS); // Face inferior
		glNormal3f(0.0, 0.0, -1.0);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-cubeSize / 2, -cubeSize / 2, -cubeSize / 2);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-cubeSize / 2, cubeSize / 2, -cubeSize / 2);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(cubeSize / 2, cubeSize / 2, -cubeSize / 2);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(cubeSize / 2, -cubeSize / 2, -cubeSize / 2);
		glEnd();

		glBegin(GL_QUADS); // Face superior
		glNormal3f(0.0, 0.0, 1.0);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-cubeSize / 2, -cubeSize / 2, cubeSize / 2);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(cubeSize / 2, -cubeSize / 2, cubeSize / 2);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(cubeSize / 2, cubeSize / 2, cubeSize / 2);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-cubeSize / 2, cubeSize / 2, cubeSize / 2);
		glEnd();

		glBegin(GL_QUADS); // Face posterior 
		glNormal3f(-1.0, 0.0, 0.0);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-cubeSize / 2, -cubeSize / 2, -cubeSize / 2);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-cubeSize / 2, -cubeSize / 2, cubeSize / 2);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-cubeSize / 2, cubeSize / 2, cubeSize / 2);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-cubeSize / 2, cubeSize / 2, -cubeSize / 2);
		glEnd();

		glBegin(GL_QUADS); // Face frontal 
		glNormal3f(1.0, 0.0, 0.0);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(cubeSize / 2, -cubeSize / 2, -cubeSize / 2);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(cubeSize / 2, cubeSize / 2, -cubeSize / 2);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(cubeSize / 2, cubeSize / 2, cubeSize / 2);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(cubeSize / 2, -cubeSize / 2, cubeSize / 2);
		glEnd();

		glBegin(GL_QUADS); // Face lateral direita
		glNormal3f(0.0, 1.0, 0.0);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-cubeSize / 2, cubeSize / 2, -cubeSize / 2);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-cubeSize / 2, cubeSize / 2, cubeSize / 2);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(cubeSize / 2, cubeSize / 2, cubeSize / 2);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(cubeSize / 2, cubeSize / 2, -cubeSize / 2);
		glEnd();

		glBegin(GL_QUADS); // Face lateral esquerda
		glNormal3f(0.0, -1.0, 0.0);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-cubeSize / 2, -cubeSize / 2, -cubeSize / 2);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(cubeSize / 2, -cubeSize / 2, -cubeSize / 2);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(cubeSize / 2, -cubeSize / 2, cubeSize / 2);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-cubeSize / 2, -cubeSize / 2, cubeSize / 2);
		glEnd();
	}
	else {
		glutSolidCube(cubeSize);
	}
}


void drawArm(float angleArm, float angleForearm, float angleHand, float angleClampZ, float angleClampY) {

	// move to arm referential
	glRotatef(angleArm, 0.0f, 0.0f, 1.0f);

	//draws the arm
	drawCylinder(diameterCylinder, sizeArm);

	// move to forearm referential
	glTranslatef(0.0f, 0.0f, sizeArm + diameterSphere / 5);
	glRotatef(angleForearm, 1.0f, 0.0f, 0.0f);

	//draws the forearm
	drawSphere(diameterSphere);
	glTranslatef(0.0f, 0.0f, diameterSphere / 5);
	drawCylinder(diameterCylinder, sizeForearm);

	//move to clamp referential
	glTranslatef(0.0f, 0.0f, sizeForearm + diameterSphere / 5);
	glRotatef(angleClampZ, 0.0f, 0.0f, 1.0f);

	//draws the clamp sphere
	drawSphere(diameterSphere);
	glTranslatef(0.0f, 0.0f, diameterSphere / 2);

	glPushMatrix();

	//draws top part of clamp
	glRotatef(angleClampY + 60, 0.0f, 1.0f, 0.0f);

	drawCylinder(diameterCylinder / 3, sizeClampPart);
	glTranslatef(0.0f, 0.0f, sizeClampPart + diameterSphere / 15);
	drawSphere(diameterSphere / 3);

	glTranslatef(0.0f, 0.0f, diameterSphere / 15);
	glRotatef(-60, 0.0f, 1.0f, 0.0f);

	drawCylinder(diameterCylinder / 3, sizeClampPart);
	glTranslatef(0.0f, 0.0f, sizeClampPart + diameterSphere / 15);
	drawSphere(diameterSphere / 3);

	glTranslatef(0.0f, 0.0f, diameterSphere / 15);
	glRotatef(-60, 0.0f, 1.0f, 0.0f);
	drawCone(diameterCylinder / 3, sizeClampPart);

	glPopMatrix();
	glPushMatrix();

	//draws bottom part of clamp
	glRotatef(-angleClampY - 60, 0.0f, 1.0f, 0.0f);

	drawCylinder(diameterCylinder / 3, sizeClampPart);
	glTranslatef(0.0f, 0.0f, sizeClampPart + diameterSphere / 15);
	drawSphere(diameterSphere / 3);

	glTranslatef(0.0f, 0.0f, diameterSphere / 15);
	glRotatef(60, 0.0f, 1.0f, 0.0f);

	drawCylinder(diameterCylinder / 3, sizeClampPart);
	glTranslatef(0.0f, 0.0f, sizeClampPart + diameterSphere / 15);
	drawSphere(diameterSphere / 3);

	glTranslatef(0.0f, 0.0f, diameterSphere / 15);
	glRotatef(60, 0.0f, 1.0f, 0.0f);
	drawCone(diameterCylinder / 3, sizeClampPart);

	glPopMatrix();
}

void drawHead(void){

	//desenha cabeça
	glTranslatef(0.0f, 0.0f, bodySize / 2);
	glRotatef(angleHead, 0.0f, 0.0f, 1.0f);

	drawCylinder(neckDiameter, neckLenght);
	glTranslatef(0.0f, 0.0f, neckLenght);
	drawCube(headSize);

	glPushMatrix();

	//desenha olho esquerdo
	glTranslatef(headSize/2, -0.75f, 0.5f);
	glRotatef(90, 0.0f, 0.0f, 1.0f);
	drawSphere(0.5);

	glPopMatrix();
	glPushMatrix();

	//desenha olho direito
	glTranslatef(headSize / 2, 0.75f, 0.5f);
	glRotatef(90, 0.0f, 0.0f, 1.0f);
	drawSphere(0.5);

	glPopMatrix();
	glPushMatrix();

	//desenha antena direita
	glTranslatef( 0.0f, headSize / 2, 0.0f);
	glRotatef(-90, 1.0f, 0.0f, 0.0f);
	drawCylinder(1.0, 0.7);
	glTranslatef(0.0f, 0.0f, 0.7f);
	drawDisk(0.0,1.0);

	
	glRotatef(90, 1.0f, 0.0f, 0.0f);
	glTranslatef(0.0f, -0.25f, 0.5f);
	drawCylinder(0.15, 1.5);
	glTranslatef(0.0f, 0.0f, 1.5f);
	drawSphere(0.15);
	
	glPopMatrix();

	//desenha antena esquerda
	glTranslatef(0.0f, -(headSize / 2), 0.0f);
	glRotatef(90, 1.0f, 0.0f, 0.0f);
	drawCylinder(1.0, 0.7);
	glTranslatef(0.0f, 0.0f, 0.7f);
	drawDisk(0.0, 1.0);


	glRotatef(-90, 1.0f, 0.0f, 0.0f);
	glTranslatef(0.0f, 0.25f, 0.5f);
	drawCylinder(0.15, 1.5);
	glTranslatef(0.0f, 0.0f, 1.5f);
	drawSphere(0.15);
}


void drawLeg(float angleFeet,float angleKnee,float angleLeg){

	//desenha virilha
	glRotatef(angleLeg, 0.0f, 1.0f, 0.0f);
	drawSphere(0.75);
	
	// desenha coxa e joelho 
	glTranslatef(0.0f, 0.0f, -feetLenC);
	drawCylinder(feetDiamC, feetLenC);

	glTranslatef(0.0f, 0.0f, -(feetSphere/2));
	glRotatef(angleKnee, 0.0f, 1.0f, 0.0f);

	drawSphere(feetSphere);

	//desenha a canela e tornozelo
	glTranslatef(0.0f, 0.0f, -feetLenC);
	drawCylinder(feetDiamC, feetLenC);

	glTranslatef(0.0f, 0.0f, -(feetSphere / 2));
	glRotatef(angleFeet, 0.0f, 1.0f, 0.0f);

	drawSphere(feetSphere);
	glTranslatef(0.0f, 0.0f, -(feetsize/2));

	// desenha o pé
	drawCube(feetsize);
	glTranslatef(feetsize,0.0f, 0.0f);
	drawCube(feetsize);
	glTranslatef(feetsize, 0.0f, 0.0f);
	drawCube(feetsize);
}

void drawScene(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_TEXTURE_2D);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	eyeX = eyeDistance * cos(viewAngleZ*PI / 180) * cos(viewAngleX*PI / 180);
	eyeY = eyeDistance * cos(viewAngleZ*PI / 180) * sin(viewAngleX*PI / 180);
	eyeZ = eyeDistance * sin(viewAngleZ*PI / 180);
	if (viewAngleZ<90)
		gluLookAt(eyeX, eyeY, eyeZ, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
	else
		gluLookAt(eyeX, eyeY, eyeZ, 0.0, 0.0, 0.0, 0.0, 0.0, -1.0);

	switch (lightOn) {
	case 0:
		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHT1);
		break;
	case 1:
		glEnable(GL_LIGHT0);
		glDisable(GL_LIGHT1);
		break;
	case 2:
		glDisable(GL_LIGHT0);
		glEnable(GL_LIGHT1);
		break;
	case 3:
		glDisable(GL_LIGHT0);
		glDisable(GL_LIGHT1);
		break;
	}
	glLightfv(GL_LIGHT0, GL_POSITION, luzDifusa0_p);
	glLightfv(GL_LIGHT1, GL_POSITION, luzDifusa1_p);


	// drawing color
	glColor3f(1.0f, 1.0f, 1.0f);

	//desenha o corpo
	drawCube(bodySize);

	glPushMatrix();

	//desenha ombro esquerdo 
	glTranslatef(0.0f, -(bodySize/2), 0.0f);
	drawSphere(shoulderDiameter);

	glRotatef(angleShoulder1, 1.0f, 0.0f, 0.0f);

	//desenha braço esquerdo
	drawArm(angleArm1, angleForearm1, angleHand1, angleClampZ1, angleClampY1);

	glPopMatrix();
	glPushMatrix();

	//desenha ombro direito 
	glTranslatef( 0.0f, bodySize/2, 0.0f);
	drawSphere(shoulderDiameter);

	glRotatef(-angleShoulder2, 1.0f, 0.0f, 0.0f);

	//desenha braço direito 
	drawArm(angleArm2, angleForearm2, angleHand2, angleClampZ2, angleClampY2);

	glPopMatrix();
	glPushMatrix();

	//desenha cabeça
	drawHead();

	glPopMatrix();

	//desenha a junção das pernas
	glTranslatef(0.0f, 0.0f, -(bodySize / 2) - 0.5f);
	drawCube(2.0);

	glPushMatrix();

	// desenha perna esquerda
	glTranslatef(0.0f, -1.5f, -0.4f);
	drawLeg(angleFeet1, angleKnee1, angleLeg1);

	glPopMatrix();

	// desenha perna direita
	glTranslatef(0.0f, 1.5f, -0.4f);
	drawLeg(angleFeet2, angleKnee2, angleLeg2);

	glutSwapBuffers();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(900, 900);
	glutCreateWindow("Robo");

	initLighting();
	initRendering();
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(handleKeypress);
	glutMouseFunc(handleMouseButton);
	glutReshapeFunc(handleResize);

	glutMainLoop();
	return 0;
}
