#include "Planeta.hpp"
#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>

Planeta::Planeta(int r)
{
  raio = r;
  grausPorSegundo = 180.0f;
}

Planeta::~Planeta()
{}

void Planeta::desenha(float deltaTempo)
{
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

  gluSphere(gluNewQuadric(), raio, 32, 32);

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