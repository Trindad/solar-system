#include "Orbita.hpp"

/**
 * Inicializa variáveis
 */
Orbita::Orbita(float g, Vector3 c, float r)
{
	this->grausPorSegundo = g;
	this->centro = c;
	this->raio = r;
	this->rotacao = 0.0f;
}

Orbita::~Orbita()
{}

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

void Orbita::desenha()
{
   int i;

   // Desabilita textura
   glBindTexture(GL_TEXTURE_2D, 0);
   glDisable(GL_LIGHTING);
   glColor3f(1,1,1);

   float degInRad = PI/180.0f;

   for(i = 0; i < 360;i++)
   {
      float rad = i*(PI/180.0f);
      glPushMatrix();
      glTranslatef(raio*cos(rad), 0, raio*sin(rad));
      glutWireCube(2);
      glPopMatrix();
   }
   
   // for (int i=0; i<=360; i++) {
   //    glPushMatrix();
   //    glTranslatef((float)cos(i*PI/180.0f)*raio, 0,(float)sin(i*PI/180.0f)*raio*1.5f);
   //    glutWireCube(2);
   //    glPopMatrix();
   // }

   glEnable(GL_LIGHTING);
}
