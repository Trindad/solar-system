#ifndef PLANETA_H
#define PLANETA_H
#include "Orbita.hpp"

class Planeta
{
public:
  Planeta(int raio);
  ~Planeta();

  void desenha(float);

  void setPosicao(Vector3);
  void setGrausPorSegundo(float);
  void setTemOrbita(bool);
  void setTemRotacao(bool);
  void setOrbita(Orbita*);
  void loadTexture(const char*);

  int raio;
  int temOrbita;
  int temRotacao;
  Orbita *orbita;
  GLfloat rotacao;
  Vector3 posicao;
  GLfloat grausPorSegundo;
  GLuint texture;
};

#endif
