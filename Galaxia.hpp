#ifndef GALAXIA_H
#define GALAXIA_H
#include "Vector3.hpp"

class Galaxia
{
public:
	Galaxia(int);
	~Galaxia();
	void desenha();
	void loadTexture(const char*);
  void renderSphere(float cx, float cy, float cz, float r, int p);

	int raio;
	GLuint texture;
};
#endif
