#include "Planeta.hpp"

Planeta::Planeta(int r, bool lua)
{
  raio = r;//recebe o raio da esfera
  grausPorSegundo = 180.0f;
  desenharOrbita = true;
  temRotacao = true;
  temLua = lua;//diz se planeta terá lua

  /**
   * Carrega textura caso planeta tenha lua
   */
  if (lua == true)
  {
    orbita_lua = 0;
    texturaLua = Textura::carregaTextura("texture_moon.jpg");
  }
}

Planeta::~Planeta(){}

/**
 * Desenha lua 
 * Insere a sua textura
 * Calcula a rotação 
 */
void Planeta::desenhaLua(float x, float z, float deltaTempo)
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

  /**
   * Se passar muito tempo o laço 
   * faz com que o valor fique entre
   * 0 e 360.
   */
  rotacao_lua += deltaTempo * -30.0f;

  while (rotacao_lua > 360.0f)
  {
    rotacao_lua -= 360.0f;
  }

  /**
   * Calcula a próxima posição pela órbita
   */
  float lua_x = x + (raio+15) * cos(orbita_lua / 180.0f * PI);
  float lua_z = z + (raio+15) * sin(orbita_lua / 180.0f * PI)*1.5f;
  
  glTranslatef(lua_x, 0,lua_z);//faz translação com base na terra
  glRotatef(rotacao_lua,0,1,0);
  gluSphere(esfera, raio*0.4f,50, 50);

  glPopMatrix();
}

void Planeta::desenha(float deltaTempo)
{
  float x = 0.0f, z = 0.0f;

  rotacao += deltaTempo * grausPorSegundo;
  /**
   * Se passar muito tempo o laço 
   * faz com que o valor fique entre
   * 0 e 360.
   */
  while (this->rotacao > 360.0f)
  {
    this->rotacao -= 360.0f;
  }

  //verifica se tem órbita para desenhar trajeto
  if (this->temOrbita == true && desenharOrbita == true)
  {
    this->orbita->desenha();
  }

  glPushMatrix();
  glBindTexture (GL_TEXTURE_2D, this->texture);

  /**
   * Atualiza orbita com base no deltaTempo
   * e calcula os valores de x e z para a transladar
   */
  if (this->temOrbita == true)
  {
    this->orbita->atualiza(deltaTempo);

    x = this->orbita->getRaio() * cos(this->orbita->getRotacao() / 180.0 * PI);
    z = this->orbita->getRaio() * sin(this->orbita->getRotacao() / 180.0 * PI)*1.5f;
    
    glTranslatef(x, 0, z);
  }
  else
  {
    glTranslatef(posicao.f[0],posicao.f[1],posicao.f[2]);
  }

  //rotaciona planeta
  if (temRotacao == true)
  {
    glRotatef(rotacao, 0, 1, 0);
  }

  glRotatef(90,1.0f,0.0f,0.0f);//rotaciona para textura ficar certa nos polos dos planetas

  GLUquadricObj  *esfera = gluNewQuadric();

  /**
   * Ativando textura da esfera
   */
  gluQuadricDrawStyle(esfera,GLU_FILL);
  gluQuadricNormals(esfera,GLU_SMOOTH);
  gluQuadricOrientation(esfera,GLU_OUTSIDE);
  gluQuadricTexture(esfera,GL_TRUE);

  gluSphere(esfera, raio,100, 100);//desenha planeta

  glPopMatrix();

  /**
   * Desenha lua caso exista
   */
  if (temLua == true) 
  {
    desenhaLua(x,z,deltaTempo);
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


void Planeta::carregaTextura(const char* filename)
{
  this->texture = Textura::carregaTextura(filename);
}

void Planeta::setDesenharOrbita(bool b)
{
  this->desenharOrbita = b;
}
