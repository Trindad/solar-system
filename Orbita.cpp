#include "Orbita.hpp"
#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>

/**
 * Inicializa variáveis
 */
Orbita::Orbita(float g, Vector3 c, float r)
{ 
	this->grausPorSegundo = g;
	this->centro = c;
	this->raio = r;
	this->rotacao = 0.0f;
}

Orbita::~Orbita()
{}

void Orbita::atualiza(float deltaTempo)
{
	this->rotacao += deltaTempo * this->grausPorSegundo;

	while (this->rotacao > 360.0f)
	{
		this->rotacao -= 360.0f;
	}
}

Vector3 Orbita::getCentro()
{
	return centro;
}

float Orbita::getRaio()
{
	return raio;
}

GLfloat Orbita::getRotacao()
{
	return rotacao;
}