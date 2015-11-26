#include "Planeta.hpp"

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
  
  GLUquadricObj  *esfera = gluNewQuadric();

  /**
   * Ativando textura da esfera
   */
  gluQuadricDrawStyle(esfera,GLU_FILL);
  gluQuadricNormals(esfera,GLU_SMOOTH);
  gluQuadricOrientation(esfera,GLU_OUTSIDE);
  gluQuadricTexture(esfera,GL_TRUE);

  gluSphere(esfera, raio, 32, 32);
  // renderSphere(0.1, 0.1, 0.1, raio,10);

  glPopMatrix();
  glNormal3f(0,0,1);
}

void Planeta::setPosicao(Vector3 pos)
{
  posicao = pos;
}


void Planeta::renderSphere(float cx, float cy, float cz, float r, int p)
{
 
  float theta1 = 0.0, theta2 = 0.0, theta3 = 0.0;
  float ex = 0.0f, ey = 0.0f, ez = 0.0f;
  float px = 0.0f, py = 0.0f, pz = 0.0f;
  GLfloat vertices[p*6+6], normals[p*6+6], texCoords[p*4+4];

  if( r < 0 ) r = -r;

  if( p < 0 ) p = -p;

  for(int i = 0; i < p/2; ++i)
  {
      theta1 = i * (M_PI*2) / p - M_PI_2;
      theta2 = (i + 1) * (M_PI*2) / p - M_PI_2;

      for(int j = 0; j <= p; ++j)
      {

          theta3 = j * (M_PI*2) / p;

          ex = cosf(theta2) * cosf(theta3);
          ey = sinf(theta2);
          ez = cosf(theta2) * sinf(theta3);
          px = cx + r * ex;
          py = cy + r * ey;
          pz = cz + r * ez;


          vertices[(6*j)+(0%6)] = px;

          vertices[(6*j)+(1%6)] = py;

          vertices[(6*j)+(2%6)] = pz;

          normals[(6*j)+(0%6)] = ex;

          normals[(6*j)+(1%6)] = ey;

          normals[(6*j)+(2%6)] = ez;

          texCoords[(4*j)+(0%4)] = -(j/(float)p);

          texCoords[(4*j)+(1%4)] = 2*(i+1)/(float)p;

          ex = cosf(theta1) * cosf(theta3);

          ey = sinf(theta1);

          ez = cosf(theta1) * sinf(theta3);

          px = cx + r * ex;

          py = cy + r * ey;

          pz = cz + r * ez;

          vertices[(6*j)+(3%6)] = px;

          vertices[(6*j)+(4%6)] = py;

          vertices[(6*j)+(5%6)] = pz;

          normals[(6*j)+(3%6)] = ex;

          normals[(6*j)+(4%6)] = ey;

          normals[(6*j)+(5%6)] = ez;


          texCoords[(4*j)+(2%4)] = -(j/(float)p);

          texCoords[(4*j)+(3%4)] = 2*i/(float)p;

      }

      glVertexPointer(3, GL_FLOAT, 0, vertices);
      glNormalPointer(GL_FLOAT, 0, normals);
      glTexCoordPointer(2, GL_FLOAT, 0, texCoords);
      glDrawArrays(GL_TRIANGLE_STRIP, 0, (p+1)*2);
  }
 
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