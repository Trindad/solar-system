#include "Camera.hpp"

Camera::Camera()
{
	this->posicao = Vector3(0.1,5000,0.1);//inicializa câmera
	this->lookAtX = 0;
	this->lookAtZ = 0;
}

Camera::~Camera(){}

/**
 * Aumenta ou diminui o zoom da câmera
 */
void Camera::zoom(int pos, int x, int z)
{
	this->posicao = this->posicao + Vector3(0,pos*50,0);

  if (this->posicao.f[1] < 1500) {
    this->posicao.f[1] = 1500;
  }

  if (this->posicao.f[1] > 5000) {
    this->posicao.f[1] = 5000;
  }

	this->lookAtX = this->lookAtX*(1-0.2) + x*0.2;
	this->lookAtZ = this->lookAtZ*(1-0.2) + z*0.2;
}

void Camera::desenha()
{
	gluLookAt(this->lookAtX+1,this->posicao.f[1],this->lookAtZ+1,this->lookAtX,0,this->lookAtZ,0,1,0);
}
