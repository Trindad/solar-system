#include "Anel.hpp"


Anel::Anel(GLdouble inner,GLdouble out)
{
  this->innerRadius = inner;//raio interno
  this->outerRadius = out;//raio externo
  grausPorSegundo = 180.0f;//velocidade de rotação
}

Anel::~Anel(){}

/**
 * desenha torus e faz a translação e rotação necessária,
 * recebe escala e milissegundos desde o último frame
 */
void Anel::desenha( GLfloat *scale,float deltaTempo)
{
  /**
   * Insere as características do material
   * Como o material irá refletir a luz:
   *   difusa, especular, quanto vai emitir, e
   *   ambiente
   */
  GLfloat di[] = {0.9f, 0.9f, 0.9f, 1.0f};
  GLfloat ai[] = {1, 1, 1, 1};
  GLfloat em[] = {0,0,0,0.1f};
  GLfloat sp[] = {0,0,0,1.0f};

  glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, em);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, di);
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ai);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, sp);
  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0.0f);

  rotacao += deltaTempo * grausPorSegundo;//atualiza a rotação sobre si mesmo

  while (rotacao > 360.0f)
  {
    rotacao -= 360.0f;
  }

  glPushMatrix();

  /**
   * Verifica se tem órbita ,se tiver faz:
   *       atualiza deltaTempo
   *       Calcula o valor de x e z
   *       Faz uma translação em x e z
   */
  if (temOrbita)
  {
    this->orbita->atualiza(deltaTempo);
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

  glRotatef(10, 1, 0, 0);//rotação para inclinar o anel
  glRotatef(90, 1, 0, 0);//arrumar textura
	glScalef(scale[0], scale[1], scale[2]);//escala
	desenhaTorus(this->innerRadius, this->outerRadius,100, 100, this->texture);
  glPopMatrix();

  glPopMatrix();
  glNormal3f(0,0,1);//reseta normal depois normal
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


/**
 * Carrega textura dado arquivo de entrada
 */
void Anel::carregaTextura(const char* filename)
{
  this->texture = Textura::carregaTextura(filename);
}

/**
 * Desenha um torus
 * Parâmetros:
 *   r = raio interno
 *   c = raio externo
 *   rSeg, cSeg = número de segmentos/detalhes
 */
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
