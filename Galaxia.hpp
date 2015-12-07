#ifndef GALAXIA_H
#define GALAXIA_H
#include "Vector3.hpp"

class Galaxia
{
public:
	Galaxia(int);
	~Galaxia();
	void desenha();
	void carregaTextura(const char*);
	int raio;
	GLuint texture;
};
#endif
