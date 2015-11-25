#include "Galaxia.hpp"

Galaxia::Galaxia(int r)
{
	this->raio = r;
}

Galaxia::~Galaxia(){}

void Galaxia::desenha()
{
	glBindTexture (GL_TEXTURE_2D, this->texture);

	glPushMatrix();

	GLUquadricObj  *esfera = gluNewQuadric();

	/**
	* Ativando textura da esfera
	*/
	gluQuadricDrawStyle(esfera,GLU_FILL);
	gluQuadricNormals(esfera,GLU_SMOOTH);
	gluQuadricOrientation(esfera,GLU_OUTSIDE);
	gluQuadricTexture(esfera,GL_TRUE);

	gluSphere(esfera, this->raio, 32, 32);

	glPopMatrix();
}


void Galaxia::loadTexture(const char* filename)
{
  this->texture = Textura::loadTexture(filename);
}