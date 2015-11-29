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
#include <GL/glew.h>
#include <GL/glut.h>
#include <math.h>
#include <vector>
#include <iostream>

#include "Camera.hpp"
#include "Planeta.hpp"
#include "Galaxia.hpp"
#include "Anel.hpp"

vector<Planeta> planetas;
Galaxia galaxia(10000);//insere textura na galaxia
Anel anelDeSaturno(80, 300);//anel de saturno entra com o raio interno e externo do torus
float oldTimeSinceStart = 0;
// Camera deus(Vector3(0.1,8000,0.1));
Camera deus(Vector3(-4000,500,0.1));
Camera cameraNave(Vector3(1800,0,1800));
bool modoDeus = true;

float orbita = 1.0f/10000.0f;

void init()
{
	/**
	 * Desenha corpos
	 * Inserindo o tamanho, posição
	 * e velocidade de rotação se rotacionar
	 */
	Planeta sol(1200);//tamanho real 1391900 km (diam)
	sol.setPosicao(Vector3(0,0,0));
	sol.setTemRotacao(false);
	sol.setTemOrbita(false);
	planetas.push_back(sol);

	Planeta mercurio( (4866*1200)/1391900);
	mercurio.setPosicao(Vector3(-1500,0,0));
	mercurio.setGrausPorSegundo(20);
	mercurio.setTemOrbita(true);
	mercurio.setOrbita(new Orbita(5795*orbita, Vector3(0,0,0), 1500));
	planetas.push_back(mercurio);

	Planeta venus((12106*1200)/1391900);
	venus.setPosicao(Vector3(-1500,0,0));
	venus.setGrausPorSegundo(20);
	venus.setTemOrbita(true);
	venus.setOrbita(new Orbita(10811*orbita, Vector3(0,0,0), 1700));
	planetas.push_back(venus);

	Planeta terra((12742*1200)/1391900);
	terra.setPosicao(Vector3(-2100,0,0));
	terra.setGrausPorSegundo(20);
	terra.setTemOrbita(true);
	terra.setOrbita(new Orbita(14957*orbita, Vector3(0,0,0), 2100));
	planetas.push_back(terra);


	Planeta lua(((12742*1200)/1391900) * 0.4);
	lua.setPosicao(Vector3(-2250,0,0));
	lua.setGrausPorSegundo(20);
	lua.setTemOrbita(true);
	lua.setOrbita(new Orbita(14957*orbita, terra.posicao, 20));
	planetas.push_back(lua);

	Planeta marte((6760*1200)/1391900);
	marte.setPosicao(Vector3(-2900,0,0));
	marte.setGrausPorSegundo(20);
	marte.setTemOrbita(true);
	marte.setOrbita(new Orbita(22784*orbita, Vector3(0,0,0), 2900));
	planetas.push_back(marte);

	Planeta jupiter((142984*1200)/1391900);
	jupiter.setPosicao(Vector3(-3500,0,0));
	jupiter.setGrausPorSegundo(20);
	jupiter.setTemOrbita(true);
	jupiter.setOrbita(new Orbita(77814*orbita, Vector3(0,0,0), 3500));
	planetas.push_back(jupiter);

	Planeta saturno((116438*1200)/1391900);
	saturno.setPosicao(Vector3(-4000,0,0));
	saturno.setGrausPorSegundo(0);
	saturno.setTemOrbita(true);//
	saturno.setOrbita(new Orbita(142700*orbita, Vector3(0,0,0), 4000));
	planetas.push_back(saturno);

	anelDeSaturno.setPosicao(Vector3(-4000,0,0));
	anelDeSaturno.setGrausPorSegundo(0);
	anelDeSaturno.setTemOrbita(true);//142700*orbita
	anelDeSaturno.setOrbita(new Orbita(142700*orbita, Vector3(0,0,0), 4000));

	Planeta uranus((46940*1200)/1391900);
	uranus.setPosicao(Vector3(-4500,0,0));
	uranus.setGrausPorSegundo(20);
	uranus.setTemOrbita(true);
	uranus.setOrbita(new Orbita(287030*orbita, Vector3(0,0,0), 4500));
	planetas.push_back(uranus);

	Planeta neturno((45432*1200)/1391900);
	neturno.setPosicao(Vector3(-5000,0,0));
	neturno.setGrausPorSegundo(20);
	neturno.setTemOrbita(true);
	neturno.setOrbita(new Orbita(449990*orbita, Vector3(0,0,0), 5000));
	planetas.push_back(neturno);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_COLOR_MATERIAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	float vAmbientLightBright[4] = {0.05f, 0.05f, 0.05f, 1.0f};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, vAmbientLightBright);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,GL_TRUE);

	glEnable(GL_LIGHT0);

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
	gluPerspective(50, 1, 50.0f, 50000);

	// para desenhar, devemos voltar ao modo do modelo
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_TEXTURE_2D);

	planetas[0].loadTexture( "texture_sun.jpg" );//adicionando textura do sol
  	planetas[1].loadTexture("texture_mercury.jpg");//adiciona textura para mercurio
	planetas[2].loadTexture("texture_venus_surface.jpg");//adiciona textura para venus
	planetas[3].loadTexture("texture_earth_clouds.jpg");//adiciona textura para terra
	planetas[4].loadTexture("texture_moon.jpg");//adiciona textura para lua
	planetas[5].loadTexture("texture_mars.jpg");//adiciona textura para marte
	planetas[6].loadTexture("texture_jupiter.jpg");//adiciona textura para jupiter
	planetas[7].loadTexture("texture_saturn.jpg");//adiciona textura para saturno
	planetas[8].loadTexture("texture_uranus.jpg");//adiciona textura para uranu
	planetas[9].loadTexture("texture_neptune.jpg");//adiciona textura para Neturno
	anelDeSaturno.loadTexture("texture_saturn_ring.png");//anel de saturno
	galaxia.loadTexture("large_medium_to_low_density_starfield_5400x3600_by_garryts-d7tni3c.jpg");//adiciona textura a galaxia
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

	GLfloat lightAmbient1[4] = {0.0,0.0,0.0,1};
	GLfloat lightPos1[4] = {0,0.0,0,1};
	GLfloat lightDiffuse1[4] = {1,1,1,1};

	glLightfv(GL_LIGHT0,GL_POSITION,(GLfloat *) &lightPos1);
	glLightfv(GL_LIGHT0,GL_AMBIENT,(GLfloat *) &lightAmbient1);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,(GLfloat *) &lightDiffuse1);

	glColor3f(1.0, 1.0, 1.0);

	float timeSinceStart = glutGet(GLUT_ELAPSED_TIME);
	float deltaTime = (timeSinceStart - oldTimeSinceStart) / 1000;
  	oldTimeSinceStart = timeSinceStart;

	for (int i = 0; i < (int) planetas.size(); i++)
	{
		planetas[i].setDesenharOrbita(modoDeus);

		if (i > 0) {
			GLfloat di[] = {0.9, 0.9, 0.9, 1.0};
			GLfloat ai[] = {0, 0, 0, 1};
			GLfloat em[] = {0,0,0,0};

			glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, em);
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, di);
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ai);
			planetas[i].desenha(deltaTime);
		} else {
			GLfloat di[] = {1, 1, 1, 0.1};
			GLfloat ai[] = {1, 1, 1, 0.1};
			GLfloat em[] = {247.0f/255.0f, 225.0f/255.0f, 56.0f/255,1.0};//emissão de luz do objeto

			glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, em);
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, di);
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ai);
			// glDisable(GL_LIGHTING);
			planetas[i].desenha(deltaTime);
			// glEnable(GL_LIGHTING);
		}

	}

	glDisable(GL_LIGHTING);
	galaxia.desenha();
	glEnable(GL_LIGHTING);

	//Configurações do anel
	GLfloat confAnel[][3] = {
					{400.0f,0.0f,0.0f},//posição
					{400.0f,0.0f,0.0f},//rotação
					{0.3f,0.3f,0.03f}//escala
					};
	anelDeSaturno.desenha(confAnel[2],deltaTime);

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

	gluPerspective (50,aspect,50.0f,15000.0f );

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
		return;
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
