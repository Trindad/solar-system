#include "Camera.hpp"

Camera::Camera(Vector3 pos)
{
	this->posicao = pos;//inicializa câmera
	this->lookAt = Vector3(0,0,0);
	this->up = Vector3(0,1,0);
	this->dir = this->lookAt - this->posicao;
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


	this->lookAt.f[0] = this->lookAt.f[0]*(1-0.2) + x*0.2;
	this->lookAt.f[2] = this->lookAt.f[2]*(1-0.2) + z*0.2;

	this->posicao.f[0] = this->lookAt.f[0] + 1;
	this->posicao.f[2] = this->lookAt.f[2] + 1;
}

void Camera::desenha()
{
	gluLookAt(this->posicao.f[0],
			  this->posicao.f[1],
			  this->posicao.f[2],
			  this->lookAt.f[0],
			  this->lookAt.f[1],
			  this->lookAt.f[2],
			  this->up.f[0],
			  this->up.f[1],
			  this->up.f[2]);
}

void Camera::moveFrente()
{
	this->posicao += dir * 0.05f;
	this->lookAt = posicao + dir;
}

void Camera::moveEsquerda()
{
	this->posicao = this->posicao - dir.produtoExterno(up)*0.05f;
	this->lookAt = posicao + dir;
}

void Camera::moveDireita()
{
	this->posicao += (dir.produtoExterno(up)*0.05f);
	this->lookAt = posicao + dir;
}