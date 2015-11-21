#include "Camera.hpp"

Camera::Camera()
{
	this->posicao = Vector3(0.1,5000,0.1);//inicializa câmera
	this->lookAtX = 0;
	this->lookAtY = 0;
}

Camera::~Camera(){}

/**
 * Aumenta ou diminui o zoom da câmera
 */
void Camera::zoom(int pos, int x, int y)
{
	this->posicao = this->posicao + Vector3(0,pos*80,0);

  if (this->posicao.f[1] < 1500) {
    this->posicao.f[1] = 1500;
  }

  if (this->posicao.f[1] > 5000) {
    this->posicao.f[1] = 5000;
  }

  	std::cout << x << " " << y << std::endl;
	this->lookAtX = x;
	this->lookAtY = y;
}

void Camera::desenha()
{
	gluLookAt(this->posicao.f[0],this->posicao.f[1],this->posicao.f[2],this->lookAtX,this->lookAtY,0,0,1,0);
}
