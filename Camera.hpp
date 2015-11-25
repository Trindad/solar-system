#ifndef CAMERA_H
#define CAMERA_H

#include "Vector3.hpp"

class Camera
{
public:
	Camera(Vector3);
	~Camera();
	void zoom(int,int,int);
	void desenha();
	void moveFrente();
	void moveEsquerda();
	void moveDireita();
private:
	Vector3 posicao;//posição da câmera
	Vector3 lookAt;
	Vector3 up; // vetor 'pra cima' do gluLookAt
	Vector3 dir;
};

#endif
