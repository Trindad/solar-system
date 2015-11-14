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

  if (rotacao > 360.0f)
  {
    rotacao -= 360.0f;
  }

  glPushMatrix();

  glTranslatef(0,0,0);
  glRotatef(rotacao, 0, 1, 0);
  gluSphere(gluNewQuadric(), raio, 32, 32);

  glPopMatrix();
}
