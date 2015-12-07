#ifndef ORBITA_H
#define ORBITA_H

#include "Vector3.hpp"

class Orbita
{
public:
	Orbita(float, Vector3, float);
	~Orbita();
    Vector3 getCentro();
	float getRaio();
	GLfloat getRotacao();
	void atualiza(float);
	void desenha();
private:
	float grausPorSegundo;//velocidade da rotação
	Vector3 centro;//ponto de rotação
	float raio;//distância do ponto
	GLfloat rotacao;//rotação atual
};

#endif
