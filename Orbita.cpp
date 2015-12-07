#include "Orbita.hpp"

/**
 * Inicializa variáveis:
 *    quantos graus por segundo irá rotacionar
 *    o raio, a rotação em 0 e o centro da rotação
 */
Orbita::Orbita(float g, Vector3 c, float r)
{
	this->grausPorSegundo = g;
	this->centro = c;
	this->raio = r;
	this->rotacao = 0.0f;
}

Orbita::~Orbita(){}

/**
 *  Atualiza rotação em relação ao ângulo
 */
void Orbita::atualiza(float deltaTempo)
{
	this->rotacao += deltaTempo * this->grausPorSegundo;

	while (this->rotacao > 360.0f)
	{
		this->rotacao -= 360.0f;
	}
}

Vector3 Orbita::getCentro()
{
	return centro;
}

float Orbita::getRaio()
{
	return raio;
}

GLfloat Orbita::getRotacao()
{
	return rotacao;
}

/**
 * Desenha o trájeto percorrido por um planeta em volta do Sol
 */
void Orbita::desenha()
{
   // Desabilita textura
   glBindTexture(GL_TEXTURE_2D, 0);
   glDisable(GL_LIGHTING);
   glColor3f(1,1,1);

   float degInRad = PI/180.0f;

   for (int i = 0; i <= 360; i++) {
      glPushMatrix();
      glTranslatef((float)cos(i*PI/180.0f)*raio, 0,(float)sin(i*PI/180.0f)*raio*1.5f);//faz com que o desenho seja em forma de elipse
      glutWireCube(2);//cubo de tamanho 2
      glPopMatrix();
   }

   glEnable(GL_LIGHTING);
}
