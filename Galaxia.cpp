#include "Galaxia.hpp"

Galaxia::Galaxia(int r)
{
	this->raio = r;
}

Galaxia::~Galaxia(){}

void Galaxia::desenha()
{
    glBindTexture (GL_TEXTURE_2D, texture);
   
	glPushMatrix();

    GLUquadricObj  *esfera = gluNewQuadric();

    /**
    * Ativando textura da esfera
    */
    gluQuadricDrawStyle(esfera,GLU_FILL);
    gluQuadricNormals(esfera,GLU_SMOOTH);
    gluQuadricOrientation(esfera,GLU_OUTSIDE);
    gluQuadricTexture(esfera,GL_TRUE);

    gluSphere(esfera, this->raio,100, 100);

    glDisable(GL_TEXTURE_GEN_S);
    glDisable(GL_TEXTURE_GEN_T); 

	glPopMatrix();
    glNormal3f(0,0,1);
}


void Galaxia::carregaTextura(const char* filename)
{
  this->texture = Textura::carregaTextura(filename);
}