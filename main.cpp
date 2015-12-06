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

#include "Camera.hpp"
#include "Planeta.hpp"
#include "Galaxia.hpp"
#include "Anel.hpp"
#include "Nave.hpp"

 #define ESCALA_PLANETAS 2
 #define VELOCIDADE_ORBITAL 0.5f

vector<Planeta> planetas;
Galaxia galaxia(13000);//insere textura na galaxia
Anel anelDeSaturno(80*ESCALA_PLANETAS, 300*ESCALA_PLANETAS);//anel de saturno entra com o raio interno e externo do torus
float oldTimeSinceStart = 0;
// Camera deus(Vector3(0.1,8000,0.1));
Camera deus(Vector3(0,10000,0.1));
Camera cameraNave(Vector3(1800,0,1800));
bool modoDeus = true;

float orbita = 1.0f/10000.0f;

Nave nave;

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

	Planeta mercurio( ((4866*1200)/1391900)*ESCALA_PLANETAS);
	mercurio.setPosicao(Vector3(-1400 - 57.9f,0,0));
	mercurio.setGrausPorSegundo(40);
	mercurio.setTemOrbita(true);
	mercurio.setOrbita(new Orbita(47.89*VELOCIDADE_ORBITAL, Vector3(0,0,0), 1400 + 57.9f + (((4866*1200)/1391900)*ESCALA_PLANETAS)));
	planetas.push_back(mercurio);

	Planeta venus(((12106*1200)/1391900)*ESCALA_PLANETAS);
	venus.setPosicao(Vector3(-1400 - 108.2f,0,0));
	venus.setGrausPorSegundo(-20);
	venus.setTemOrbita(true);
	venus.setOrbita(new Orbita(35.03*VELOCIDADE_ORBITAL, Vector3(0,0,0), 1400 + 118.2f + (((12106*1200)/1391900)*ESCALA_PLANETAS)));
	planetas.push_back(venus);

	Planeta terra(((12742*1200)/1391900)*ESCALA_PLANETAS);
	terra.setPosicao(Vector3(-1400 - 149.6f,0,0));
	terra.setGrausPorSegundo(110);
	terra.setTemOrbita(true);
	terra.setOrbita(new Orbita(29.79*VELOCIDADE_ORBITAL, Vector3(0,0,0), 1400 + 189.6f + (((12742*1200)/1391900)*ESCALA_PLANETAS)));
	planetas.push_back(terra);

	Planeta lua((((12742*1200)/1391900) * 0.4)*ESCALA_PLANETAS);
	lua.setPosicao(Vector3(-2250,0,0));
	lua.setGrausPorSegundo(0);
	lua.setTemRotacao(false);
	lua.setTemOrbita(true);
	lua.setOrbita(new Orbita(15, terra.posicao, 20*ESCALA_PLANETAS));
	planetas.push_back(lua);

	Planeta marte(((6760*1200)/1391900)*ESCALA_PLANETAS);
	marte.setPosicao(Vector3(-1400 - 227.9f,0,0));
	marte.setGrausPorSegundo(95);
	marte.setTemOrbita(true);
	marte.setOrbita(new Orbita(24.13*VELOCIDADE_ORBITAL, Vector3(0,0,0), 1400 + 297.9f + (((6760*1200)/1391900)*ESCALA_PLANETAS)));
	planetas.push_back(marte);

	Planeta jupiter(((142984*1200)/1391900)*ESCALA_PLANETAS);
	jupiter.setPosicao(Vector3(-1400 - 778.3f,0,0));
	jupiter.setGrausPorSegundo(190);
	jupiter.setTemOrbita(true);
	jupiter.setOrbita(new Orbita(13.6*VELOCIDADE_ORBITAL, Vector3(0,0,0), 1400 + 778.3f + (((142984*1200)/1391900)*ESCALA_PLANETAS)));
	planetas.push_back(jupiter);

	Planeta saturno(((116438*1200)/1391900)*ESCALA_PLANETAS);
	saturno.setPosicao(Vector3(-1400 - 1427.9f,0,0));
	saturno.setGrausPorSegundo(190);
	saturno.setTemOrbita(true);//
	saturno.setOrbita(new Orbita(9.64*VELOCIDADE_ORBITAL, Vector3(0,0,0), 1400 + 1427.9f + (((116438*1200)/1391900)*ESCALA_PLANETAS) + 300));
	planetas.push_back(saturno);

	anelDeSaturno.setPosicao(Vector3(-1400 - 1427.9f,0,0));
	anelDeSaturno.setGrausPorSegundo(0);
	anelDeSaturno.setTemOrbita(true);//142700*orbita
	anelDeSaturno.setOrbita(new Orbita(9.64*VELOCIDADE_ORBITAL, Vector3(0,0,0), 1400 + 1427.9f + (((116438*1200)/1391900)*ESCALA_PLANETAS) + 300));

	Planeta uranus(((46940*1200)/1391900)*ESCALA_PLANETAS);
	uranus.setPosicao(Vector3(-1400 - 2871.9f,0,0));
	uranus.setGrausPorSegundo(-150);
	uranus.setTemOrbita(true);
	uranus.setOrbita(new Orbita(6.81*VELOCIDADE_ORBITAL, Vector3(0,0,0), 1400 + 2871.9f + (((46940*1200)/1391900)*ESCALA_PLANETAS) + 300));
	planetas.push_back(uranus);

	Planeta netuno(((45432*1200)/1391900)*ESCALA_PLANETAS);
	netuno.setPosicao(Vector3(-1400 - 4497.9f,0,0));
	netuno.setGrausPorSegundo(140);
	netuno.setTemOrbita(true);
	netuno.setOrbita(new Orbita(5.43*VELOCIDADE_ORBITAL, Vector3(0,0,0), 1400 + 4497.9f + (((45432*1200)/1391900)*ESCALA_PLANETAS)));
	planetas.push_back(netuno);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
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


	// mudança de perspectiva são feitas em modo de projeção
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// Define angulo de visão e o quão longo a câmera vê
	gluPerspective(50, 1, 0.1f, 80000);

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
	}
	else
	{
		cameraNave.desenha();
	}

	GLfloat lightAmbient1[4] = {0.0f,0.0f,0.0f,1};
	GLfloat lightPos1[4] = {1.0f,1.0f,1.0f,1};
	GLfloat lightDiffuse1[4] = {1.0f,1.0f,1.0f,1.0f};

	glLightfv(GL_LIGHT0,GL_POSITION,(GLfloat *) &lightPos1);
	glLightfv(GL_LIGHT0,GL_AMBIENT,(GLfloat *) &lightAmbient1);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,(GLfloat *) &lightDiffuse1);


	// glColor3f(1.0f, 1.0f, 1.0f);

	float timeSinceStart = glutGet(GLUT_ELAPSED_TIME);
	float deltaTime = (timeSinceStart - oldTimeSinceStart) / 1000.0f;
  	oldTimeSinceStart = timeSinceStart;


	for (int i = 0; i < (int) planetas.size(); i++)
	{
		planetas[i].setDesenharOrbita(i != 0 && i != 4);

		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0);

		if (i > 0) {
			GLfloat di[] = {0.9, 0.9, 0.9, 1.0f};
			GLfloat ai[] = {1, 1, 1, 1};
			GLfloat em[] = {0,0,0,0};
			GLfloat sp[] = {0,0,0,1.0f};

			glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, em);
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, di);
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ai);
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, sp);

			planetas[i].desenha(deltaTime);
		} else {
			GLfloat di[] = {1.5f, 1.5f, 1.5f, 0.9f};
			GLfloat ai[] = {1.0f, 1.0f, 1.0f, 1.0f};
			GLfloat em[] = {247.0f/255.0f, 225.0f/255.0f, 56.0f/255,1.0f};//emissão de luz do objeto
			GLfloat sp[] = {1.0f, 1.0f, 1.0f,0.1f};
			// GLfloat sh[] = {1.0f, 1.0f, 1.0f,100.0f};

			glShadeModel(GL_SMOOTH);
			glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, em);
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, di);
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ai);
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, sp);

			planetas[i].desenha(deltaTime);
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

	glPushMatrix();
	nave.desenha(cameraNave.posicao, cameraNave.dir, cameraNave.up);
	glPopMatrix();

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

	gluPerspective (50,aspect,0.1f,80000);

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
	nave.init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(specialKeyboard);

	glutMainLoop();
}
