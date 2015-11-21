#include "Camera.hpp"

Camera::Camera()
{
	this->posicao = Vector3(0.1,5000,0.1);//inicializa câmera
}

Camera::~Camera(){}

/**
 * Aumenta ou diminui o zoom da câmera
 */
void Camera::zoom(int pos)
{
	this->posicao = this->posicao + Vector3(0,pos*80,0);

  if (this->posicao.f[1] < 1500) {
    this->posicao.f[1] = 1500;
  }

  if (this->posicao.f[1] > 5000) {
    this->posicao.f[1] = 5000;
  }
}

void Camera::desenha()
{
	gluLookAt(this->posicao.f[0],this->posicao.f[1],this->posicao.f[2],0,0,0,0,1,0);
}
