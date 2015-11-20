#include "Planeta.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Planeta::Planeta(int r)
{
  raio = r;
  grausPorSegundo = 180.0f;
}

Planeta::~Planeta()
{}

void Planeta::desenha(float deltaTempo)
{
  glBindTexture (GL_TEXTURE_2D, this->texture);
  rotacao += deltaTempo * grausPorSegundo;

  while (rotacao > 360.0f)
  {
    rotacao -= 360.0f;
  }

  glPushMatrix();

  if (temOrbita)
  {
    this->orbita->atualiza(deltaTempo);
    glRotatef(this->orbita->getRotacao(), 0, 1, 0);
    glTranslatef(this->orbita->getCentro().f[0] - this->orbita->getRaio(),posicao.f[1],posicao.f[2]);
  } else
  {
    glTranslatef(posicao.f[0],posicao.f[1],posicao.f[2]);
  }

  if (temRotacao)
  {
    glRotatef(rotacao, 0, 1, 0);
  }

  // glTranslatef(-raio,-raio,0);
  GLUquadricObj  *esfera = gluNewQuadric();

  /**
   * Ativando textura da esfera
   */
  gluQuadricDrawStyle(esfera,GLU_FILL);
  gluQuadricNormals(esfera,GLU_SMOOTH);
  gluQuadricOrientation(esfera,GLU_OUTSIDE);
  gluQuadricTexture(esfera,GL_TRUE);

  gluSphere(esfera, raio, 32, 32);

  // glBegin(GL_POLYGON);

  // glColor3f(0,1,1);
  // glVertex3f(0,0,0);
  // glVertex3f(0,100,0);

  // glColor3f(100,100,0);
  // glVertex3f(100,0,0);
  // glVertex3f(100,100,0);

  // glEnd();

  glPopMatrix();
}

void Planeta::setPosicao(Vector3 pos)
{
  posicao = pos;
}

void Planeta::setGrausPorSegundo(float graus)
{
  grausPorSegundo = graus;
}

void Planeta::setTemRotacao(bool b)
{
  temRotacao = b;
}

void Planeta::setTemOrbita(bool b)
{
  temOrbita = b;
}

void Planeta::setOrbita(Orbita* o)
{
  orbita = o;
}


void Planeta::loadTexture(const char* filename)
{
  GLuint t;
  glGenTextures(1, &t);
  this->texture = t;
  glBindTexture(GL_TEXTURE_2D, texture);

  int width = 0, height = 0;
  int n = 0;

  unsigned char* image = stbi_load(filename,&width,&height,&n,0);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
              GL_UNSIGNED_BYTE, image);


   glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE , GL_MODULATE);
   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);

   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   gluBuild2DMipmaps(GL_TEXTURE_2D,3, width, height, GL_RGB, GL_UNSIGNED_BYTE, image);
}