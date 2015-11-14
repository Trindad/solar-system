#ifndef PLANETA_H
#define PLANETA_H

#include <GL/gl.h>
#include "Vector3.hpp"
#include "Orbita.hpp"

class Planeta
{
public:
  Planeta(int raio);
  ~Planeta();

  void desenha(float);

  void setPosition(Vector3);
  void setTemOrbita(bool);
  void setOrbita(Orbita);

  int raio;
  int temOrbita;
  Orbita orbita;
  GLfloat rotacao;
  Vector3 posicao;
  GLfloat grausPorSegundo;
};

#endif
