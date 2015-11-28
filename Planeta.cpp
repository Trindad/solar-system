#include "Planeta.hpp"

Planeta::Planeta(int r)
{
  raio = r;
  grausPorSegundo = 180.0f;
  desenharOrbita = true;
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

  if (temOrbita && desenharOrbita)
  {
    orbita->desenha();
  }

  glPushMatrix();
  glBindTexture (GL_TEXTURE_2D, this->texture);

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

  glRotatef(90,1.0f,0.0f,0.0f);

  GLUquadricObj  *esfera = gluNewQuadric();

  /**
   * Ativando textura da esfera
   */
  gluQuadricDrawStyle(esfera,GLU_FILL);
  gluQuadricNormals(esfera,GLU_SMOOTH);
  gluQuadricOrientation(esfera,GLU_OUTSIDE);
  gluQuadricTexture(esfera,GL_TRUE);

  gluSphere(esfera, raio, 32, 32);

  glPopMatrix();
  glNormal3f(0,0,1);
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
  this->texture = Textura::loadTexture(filename);
}

void Planeta::setDesenharOrbita(bool b)
{
  desenharOrbita = b;
}
