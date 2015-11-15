/**
 * *********************************************************
 * Trabalho final:
 *
 * Descrição: Desenhar bandeira de Wallis e Fortuna e bandeira de Israel
 * por malha de triângulos, usando simulação de tecido
 *
 * Alunos: Silvana Trindade e Maurício André Cinelli
 * *********************************************************
 */

#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>
#include <vector>
#include <iostream>
#include "Planeta.hpp"
using namespace std;

vector<Planeta> planetas;
float oldTimeSinceStart = 0;

void init()
{

	Planeta sol(500);
	sol.setPosicao(Vector3(0,0,150));
	sol.setTemRotacao(false);
	planetas.push_back(sol);

	Planeta terra(200);
	terra.setPosicao(Vector3(-800,0,0));
	terra.setGrausPorSegundo(100);
	planetas.push_back(terra);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_COLOR_MATERIAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glEnable(GL_LIGHT0);
	GLfloat lightPos[4] = {-1.0,1.0,0.5,0.0};
	glLightfv(GL_LIGHT0,GL_POSITION,(GLfloat *) &lightPos);

	glEnable(GL_LIGHT1);

	GLfloat lightAmbient1[4] = {0.0,0.0,0.0,0.0};
	GLfloat lightPos1[4] = {1.0,0.0,-0.2,0.0};
	GLfloat lightDiffuse1[4] = {0.5,0.5,0.3,0.0};

	glLightfv(GL_LIGHT1,GL_POSITION,(GLfloat *) &lightPos1);
	glLightfv(GL_LIGHT1,GL_AMBIENT,(GLfloat *) &lightAmbient1);
	glLightfv(GL_LIGHT1,GL_DIFFUSE,(GLfloat *) &lightDiffuse1);

	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,GL_TRUE);
	glEnable(GL_LIGHTING);
	glEnable(GL_NORMALIZE);

	/**
	 * Habilita anti-serrilhado
	 */
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_POINT_SMOOTH);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

/**
 * Função chamada para cada frame
 */
void display(void)
{
	// desenha
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	// mudança de perspectiva são feitas em modo de projeção
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// Define angulo de visão e o quão longo a câmera vê
	gluPerspective(90, 1, 0.1, 5000);

	// para desenhar, devemos voltar ao modo do modelo
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(0.1,5000,0.1,0,0,0,0,1,0);

	glColor3f(1.0, 1.0, 1.0);

	float timeSinceStart = glutGet(GLUT_ELAPSED_TIME);
	float deltaTime = (timeSinceStart - oldTimeSinceStart) / 1000;
  oldTimeSinceStart = timeSinceStart;

	for (int i = 0; i < (int) planetas.size(); i++)
	{
		planetas[i].desenha(deltaTime);
	}

	glutSwapBuffers();
	glutPostRedisplay();
}


int main ( int argc, char** argv )
{
	glutInit( &argc, argv );

	glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(600, 600 );

	glutCreateWindow( "Bandeira" );
	init();
	glutDisplayFunc(display);

	glutMainLoop();
}
