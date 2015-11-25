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
#include <GL/glut.h>
#include <math.h>
#include <vector>
#include <iostream>

#include "Camera.hpp"
#include "Planeta.hpp"

using namespace std;

vector<Planeta> planetas;
float oldTimeSinceStart = 0;
Camera deus(Vector3(0.1,5000,0.1));
Camera cameraNave(Vector3(1200,0,1200));
bool modoDeus = true;

void init()
{

	/**
	 * Desenha corpos
	 * Inserindo o tamanho, posição
	 * e velocidade de rotação se rotacionar
	 */
	Planeta sol(500);
	sol.setPosicao(Vector3(0,0,0));
	sol.setTemRotacao(false);
	sol.setTemOrbita(false);
	planetas.push_back(sol);

	Planeta mercurio(80);
	mercurio.setPosicao(Vector3(-1000,0,0));
	mercurio.setGrausPorSegundo(100);
	mercurio.setTemOrbita(true);
	mercurio.setOrbita(new Orbita(38.0f, Vector3(0,0,0), 1000));
	planetas.push_back(mercurio);

	Planeta venus(190);
	venus.setPosicao(Vector3(-1500,0,0));
	venus.setGrausPorSegundo(100);
	venus.setTemOrbita(true);
	venus.setOrbita(new Orbita(25.0f, Vector3(0,0,0), 1500));
	planetas.push_back(venus);

	Planeta terra(200);
	terra.setPosicao(Vector3(-2100,0,0));
	terra.setGrausPorSegundo(20);
	terra.setTemOrbita(true);
	terra.setOrbita(new Orbita(15.0f, Vector3(0,0,0), 2100));
	planetas.push_back(terra);


	Planeta lua(50);
	lua.setPosicao(Vector3(-2450,0,0));
	lua.setGrausPorSegundo(20);
	lua.setTemOrbita(true);
	lua.setOrbita(new Orbita(15.0f, terra.posicao, 350));
	planetas.push_back(lua);

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

	// mudança de perspectiva são feitas em modo de projeção
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// Define angulo de visão e o quão longo a câmera vê
	gluPerspective(50, 1, 200.0f, 5000);

	// para desenhar, devemos voltar ao modo do modelo
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_TEXTURE_2D);

	planetas[0].loadTexture( "texture_sun.jpg" );//adicionando textura do sol
  	planetas[1].loadTexture("texture_mercury.jpg");//adiciona textura para mercurio
	planetas[2].loadTexture("texture_venus_surface.jpg");//adiciona textura para venus
	planetas[3].loadTexture("texture_earth_clouds.jpg");//adiciona textura para terra
	planetas[4].loadTexture("texture_moon.jpg");//adiciona textura para lua

}

/**
 * Função chamada para cada frame
 */
void display(void)
{
	// desenha
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	if (modoDeus) {
		deus.desenha();
	} else {
		cameraNave.desenha();
	}

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

/**
 * Configurações da janela de visualização
 */
void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	float aspect = 1.0f*w/h;

	gluPerspective (50,aspect,200.0f,5000.0f );

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

Vector3 retornaCoordenadasMundo(int x, int y)
{
	GLint viewport[4];
	GLdouble modelview[16];
	GLdouble projection[16];
	GLfloat winX, winY, winZ;
	GLdouble posX, posY, posZ;

	glGetIntegerv(GL_VIEWPORT, viewport);
	glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
	glGetDoublev(GL_PROJECTION_MATRIX, projection);

	winX = (float)x;
    winY = (float)viewport[3] - (float)y;

	glReadPixels(winX, winY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);
	gluUnProject( winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);

	return Vector3(posX, posY, posZ);
}

void mouse(int button, int state, int x, int y)
{
	// 3 rolou pra cima, 4 rolou pra baixo
	if (button == 3 || button == 4)
	{
		if (state == GLUT_UP || !modoDeus)
		{
			return;
		}

		Vector3 coords = retornaCoordenadasMundo(x, y);
		// GLint viewport[4];
		// glGetIntegerv(GL_VIEWPORT, viewport);

		deus.zoom(button == 3 ? -1 : 1,coords.f[0],coords.f[2]);
		// deus.zoom(button == 3 ? -1 : 1,x,viewport[3] - y);
	}
}

void keyboard(unsigned char key, int x, int y)
{
	if (key == 99)
	{
		modoDeus = !modoDeus;
	}
	else
	{
		switch(key) {
			case 115://para baixo
				cameraNave.rotacionaParaBaixo();
				break;
			case 119://para cima
				cameraNave.rotacionaParaCima();
				break;
			case 97://para esquerda 
				cameraNave.rotacionaParaEsquerda();
				break;
			case 100://para direita 
				cameraNave.rotacionaParaDireita();
				break;
			default :
				break;
		}
	}
}

void specialKeyboard(int key, int x, int y)
{
	if (modoDeus) {

	} else {
		switch(key) {
			case GLUT_KEY_UP:
				cameraNave.moveFrente();
				break;
			case GLUT_KEY_LEFT:
				cameraNave.moveEsquerda();
				break;
			case GLUT_KEY_RIGHT:
				cameraNave.moveDireita();
				break;
		}
	}

	glutPostRedisplay();
}

int main ( int argc, char** argv )
{
	glutInit( &argc, argv );

	glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(600, 600 );
	glutCreateWindow( "Sistema Solar" );
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(specialKeyboard);

	glutMainLoop();
}