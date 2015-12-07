#include "Anel.hpp"

Anel::Anel(GLdouble inner,GLdouble out)
{
  this->innerRadius = inner;
  this->outerRadius = out;
  grausPorSegundo = 180.0f;
}

Anel::~Anel(){}

void Anel::desenha( GLfloat *scale,float deltaTempo)
{
  GLfloat di[] = {0.9, 0.9, 0.9, 1.0f};
  GLfloat ai[] = {1, 1, 1, 1};
  GLfloat em[] = {0,0,0,1};
  GLfloat sp[] = {0,0,0,1.0f};

  glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, em);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, di);
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ai);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, sp);
  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0);
  
  rotacao += deltaTempo * grausPorSegundo;

  while (rotacao > 360.0f)
  {
    rotacao -= 360.0f;
  }

  glPushMatrix();

  // glTranslatef(posicao.f[0],posicao.f[1],posicao.f[2]);

  if (temOrbita)
  {
    this->orbita->atualiza(deltaTempo);
    // glRotatef(this->orbita->getRotacao(), 0, 1, 0);
    float x = this->orbita->getRaio() * cos(this->orbita->getRotacao() / 180.0 * PI);
    float z = this->orbita->getRaio() * sin(this->orbita->getRotacao() / 180.0 * PI)*1.5f;
    glTranslatef(x,0,z);
  } 
  else
  {
    glTranslatef(posicao.f[0],posicao.f[1],posicao.f[2]);
  }

  if (temRotacao)
  {
    glRotatef(rotacao, 0, 1, 0);
  }

  glRotatef(10, 1, 0, 0);
  glRotatef(90, 1, 0, 0);
	glScalef(scale[0], scale[1], scale[2]);
	desenhaTorus(this->innerRadius, this->outerRadius,100, 100, this->texture);
	glPopMatrix();

  glPopMatrix();
  glNormal3f(0,0,1);
}

void Anel::setPosicao(Vector3 pos)
{
  posicao = pos;
}

void Anel::setGrausPorSegundo(float graus)
{
  grausPorSegundo = graus;
}

void Anel::setTemRotacao(bool b)
{
  temRotacao = b;
}

void Anel::setTemOrbita(bool b)
{
  temOrbita = b;
}

void Anel::setOrbita(Orbita* o)
{
  orbita = o;
}


void Anel::loadTexture(const char* filename)
{
  this->texture = Textura::loadTexture(filename);
}

/*
r = torus ring radius
c = torus tube radius
rSeg, cSeg = number of segments/detail
*/
//double r = 0.07, double c = 0.15,
// int rSeg = 16, int cSeg = 8,
// int texture = 0
void Anel::desenhaTorus(double r, double c, int rSeg, int cSeg, int texture)
{
  glFrontFace(GL_CW);

  glBindTexture(GL_TEXTURE_2D, texture);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

  const double TAU = 2 * PI;

  for (int i = 0; i < rSeg; i++) {
    glBegin(GL_QUAD_STRIP);
    for (int j = 0; j <= cSeg; j++) {
      for (int k = 0; k <= 1; k++) {
        double s = (i + k) % rSeg + 0.5f;
        double t = j % (cSeg + 1);

        double x = (c + r * cos(s * TAU / rSeg)) * cos(t * TAU / cSeg);
        double y = (c + r * cos(s * TAU / rSeg)) * sin(t * TAU / cSeg);
        double z = r * sin(s * TAU / rSeg);

        double u = (i + k) / (float) rSeg;
        double v = t / (float) cSeg;

        glTexCoord2d(u, v);
        glNormal3f(2 * x, 2 * y, 2 * z);
        glVertex3d(2 * x, 2 * y, 2 * z);
      }
    }
    glEnd();
  }

  glFrontFace(GL_CCW);
}
