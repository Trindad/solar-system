#include "Camera.hpp"

Camera::Camera(Vector3 pos)
{
	this->posicao = pos;//inicializa câmera
	this->lookAt = Vector3(0,0,0);
	this->up = Vector3(0,1,0);
	this->dir = (this->lookAt - this->posicao).normalizado();
}

Camera::~Camera(){}

/**
 * Aumenta ou diminui o zoom da câmera
 */
void Camera::zoom(int pos, int x, int z)
{

	this->posicao = this->posicao + Vector3(0,pos*50,0);

	//limite do zoom
	if (this->posicao.f[1] < 300) {
		this->posicao.f[1] = 300;
	}

	if (this->posicao.f[1] > 10000) {
		this->posicao.f[1] = 10000;
	}

	this->lookAt.f[0] = this->lookAt.f[0]*(1-0.01) + x*0.01;
	this->lookAt.f[2] = this->lookAt.f[2]*(1-0.01) + z*0.01;

	if (this->lookAt.f[0] > 5000) {
		this->lookAt.f[0] = 5000;
	}

	if (this->lookAt.f[0] < -5000) {
		this->lookAt.f[0] = -5000;
	}

	if (this->lookAt.f[2] > 5000) {
		this->lookAt.f[2] = 5000;
	}

	if (this->lookAt.f[2] < -5000) {
		this->lookAt.f[2] = -5000;
	}

	this->posicao.f[0] = this->lookAt.f[0] + 1;
	this->posicao.f[2] = this->lookAt.f[2] + 1;
}

void Camera::limita()
{
	int limiteHorizontal = 4900;
	int limiteVertical = 2500;

	posicao.f[0] = max(-limiteHorizontal, min(limiteHorizontal, posicao.f[0]));
	posicao.f[1] = max(-limiteVertical, min(limiteVertical, posicao.f[1]));
	posicao.f[2] = max(-limiteHorizontal, min(limiteHorizontal, posicao.f[2]));
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
	this->posicao += dir * 8.0f;
	limita();
	this->lookAt = posicao + dir;
}

void Camera::moveEsquerda()
{
	this->posicao = this->posicao - dir.produtoExterno(up)*8.0f;
	limita();
	this->lookAt = posicao + dir;
}

void Camera::moveDireita()
{
	this->posicao += (dir.produtoExterno(up)*8.0f);
	limita();
	this->lookAt = posicao + dir;
}

void Camera::rotacionaParaEsquerda()
{

	dir = rotacionaVetor(dir,up,-1.0f);//rotaciona 1 graus

	this->lookAt = posicao + dir;
}

void Camera::rotacionaParaDireita()
{
	dir = rotacionaVetor(dir,up,1.0f);//rotaciona 1 graus

	this->lookAt = posicao + dir;
}


void Camera::rotacionaParaCima()
{
	Vector3 t = dir.produtoExterno(up);

	dir = rotacionaVetor(dir,t,-1.0f);//rotaciona 1 graus
	this->lookAt = posicao + dir;
}


void Camera::rotacionaParaBaixo()
{
	Vector3 t = dir.produtoExterno(up);

	dir = rotacionaVetor(dir,t,1.0f);//rotaciona 1 graus
	this->lookAt = posicao + dir;
}

/**
 * Rotaciona vetor (ux, uy, uz) em torno (vx, vy, vz) por "angulo"
 */
Vector3 Camera::rotacionaVetor(Vector3 u, Vector3 v, float graus) {

  float angulo = graus * PI/180.0f;//transforma de graus para radianos

  float ca = cos(angulo);
  float sa = sin(angulo);

  Vector3 cross = u.produtoExterno(v);

  float dot = u.produtoInterno(v);

  Vector3 novo;

  novo.f[0] = u.f[0]*ca + cross.f[0]*sa + dot*v.f[0]*(1-ca);
  novo.f[1] = u.f[1]*ca + cross.f[1]*sa + dot*v.f[1]*(1-ca);
  novo.f[2] = u.f[2]*ca + cross.f[2]*sa + dot*v.f[2]*(1-ca);

  return novo;
}

float Camera::min(float a, float b)
{
	return a >= b ? b : a;
}

float Camera::max(float a, float b)
{
	return a >= b ? a : b;
}
