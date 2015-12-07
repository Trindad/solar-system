#include "Planeta.hpp"

Planeta::Planeta(int r, bool lua)
{
  raio = r;
  grausPorSegundo = 180.0f;
  desenharOrbita = true;
  temRotacao = true;
  temLua = lua;

  if (lua == true)
  {
    orbita_lua = 0;
    texturaLua = Textura::loadTexture("texture_moon.jpg");
  }
}

Planeta::~Planeta()
{}

void Planeta::desenhaLua(float x, float y, float deltaTempo)
{
  glPushMatrix();
  glBindTexture (GL_TEXTURE_2D, texturaLua);
  GLUquadricObj  *esfera = gluNewQuadric();

  /**
   * Ativando textura da esfera
   */
  gluQuadricDrawStyle(esfera,GLU_FILL);
  gluQuadricNormals(esfera,GLU_SMOOTH);
  gluQuadricOrientation(esfera,GLU_OUTSIDE);
  gluQuadricTexture(esfera,GL_TRUE);

  this->orbita_lua += deltaTempo * 30;

  while (this->orbita_lua > 360.0f)
  {
    this->orbita_lua -= 360.0f;
  }

  rotacao_lua += deltaTempo * -30.0f;

  while (rotacao_lua > 360.0f)
  {
    rotacao_lua -= 360.0f;
  }

  float moon_x = x + (raio+15) * cos(orbita_lua / 180.0f * PI);
  float moon_y = y + (raio+15) * sin(orbita_lua / 180.0f * PI)*1.5f;
  glTranslatef(moon_x, 0,moon_y);
  glRotatef(rotacao_lua,0,1,0);
  gluSphere(esfera, raio*0.4f,50, 50);

  glDisable(GL_TEXTURE_GEN_S);
  glDisable(GL_TEXTURE_GEN_T);
  glPopMatrix();
}

void Planeta::desenha(float deltaTempo)
{
  float x,y;

  rotacao += deltaTempo * grausPorSegundo;

  while (this->rotacao > 360.0f)
  {
    this->rotacao -= 360.0f;
  }

  if (this->temOrbita == true && desenharOrbita == true)
  {
    this->orbita->desenha();
  }

  glPushMatrix();
  glBindTexture (GL_TEXTURE_2D, this->texture);

  if (this->temOrbita == true)
  {
    this->orbita->atualiza(deltaTempo);
    x = this->orbita->getRaio() * cos(this->orbita->getRotacao() / 180.0 * PI);
    y = this->orbita->getRaio() * sin(this->orbita->getRotacao() / 180.0 * PI)*1.5f;
    // glTranslatef(this->orbita->getCentro().f[0],posicao.f[1],posicao.f[2]);
    glTranslatef(x, 0, y);
    // glTranslatef(-this->orbita->getRaio(),0,0);

  }
  else
  {
    glTranslatef(posicao.f[0],posicao.f[1],posicao.f[2]);
  }

  if (temRotacao == true)
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

  gluSphere(esfera, raio,50, 50);

  glDisable(GL_TEXTURE_GEN_S);
  glDisable(GL_TEXTURE_GEN_T);

  glPopMatrix();
  if (temLua == true) 
  {
    desenhaLua(x,y,deltaTempo);
  }

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
  this->desenharOrbita = b;
}
