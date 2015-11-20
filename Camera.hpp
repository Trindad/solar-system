#ifndef CAMERA_H
#define CAMERA_H

#include "Vector3.hpp"

class Camera
{
public:
	Camera();
	~Camera();
	void zoom(int pos); 
	void desenha();
private:
	Vector3 posicao;//posição da câmera
};

#endif