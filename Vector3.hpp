#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>
#include <vector>
#include <iostream>

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