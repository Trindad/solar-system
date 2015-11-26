#ifndef VECTOR3_H
#define VECTOR3_H

#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>
#include <vector>
#include <iostream>
#include <fstream>

#include <malloc.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>

#include <unistd.h>

#include "Textura.hpp"

#define PI 3.1415926535897932384626433832795//usado para rotação

class Vector3 
{
public:
	
	float f[3];

	Vector3(float, float, float);
	Vector3();

	float magnitude();
	Vector3 normalizado();

	void operator+= (const Vector3 &);
	Vector3 operator/ (const float &);
	Vector3 operator- (const Vector3 &);
	Vector3 operator+ (const Vector3 &);
	Vector3 operator* (const float &);
	Vector3 operator-();
	
	Vector3 produtoExterno(const Vector3 &);
	float produtoInterno(const Vector3 &);
};

#endif