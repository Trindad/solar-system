#ifndef ANEL_H
#define ANEL_H
#include "Orbita.hpp"

class Anel
{
public:
	Anel(GLdouble,GLdouble);
	~Anel();
	void desenha(GLfloat *, float);
	void setPosicao(Vector3);
	void setGrausPorSegundo(float);
	void setTemOrbita(bool);
	void setTemRotacao(bool);
	void setOrbita(Orbita*);
	void loadTexture(const char*);
	void desenhaTorus(double, double, int, int, int);

	int temOrbita;
	int temRotacao;
	Orbita *orbita;
	GLfloat rotacao;
	Vector3 posicao;
	GLfloat grausPorSegundo;
	GLuint texture;
	GLdouble innerRadius;
	GLdouble outerRadius;
};
#endif