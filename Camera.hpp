#ifndef CAMERA_H
#define CAMERA_H

#include "Vector3.hpp"

class Camera
{
public:
	Camera();
	~Camera();
	void zoom(int,int,int);
	void desenha();
private:
	Vector3 posicao;//posição da câmera
	float lookAtX;
	float lookAtZ;
};

#endif
