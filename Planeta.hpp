#ifndef PLANETA_H
#define PLANETA_H
#include "Orbita.hpp"

class Planeta
{
public:
  Planeta(int, bool);
  ~Planeta();

  void desenha(float);

  void setPosicao(Vector3);
  void setGrausPorSegundo(float);
  void setTemOrbita(bool);
  void setTemRotacao(bool);
  void setDesenharOrbita(bool);
  void setOrbita(Orbita*);
  void carregaTextura(const char*);
  void desenhaLua(float,float,float);

  int raio;
  int temOrbita;
  int temRotacao;
  bool desenharOrbita;
  Orbita *orbita;
  GLfloat rotacao;
  Vector3 posicao;
  GLfloat grausPorSegundo;
  GLuint texture;
  //variáveis da lua
  bool temLua;
  GLuint texturaLua;
  float orbita_lua;
  float rotacao_lua;
};

#endif
