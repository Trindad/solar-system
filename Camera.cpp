#include "Camera.hpp"

/**
 * Construtor da classe
 * Recebe: 
 * 		um Vector3 com as posições iniciais da câmera
 * Inicia as variáveis:
 * 		lookAt que indica para onde a câmera está olhando
 * 		up que indica o vetor para cima utilizado pela função gluLookAt
 * 		dir a direção que câmera está vendo
 */
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
 * Utilizada pelo modo Deus
 * Recebe a posição onde irá dar zoom (x,z)
 * pos indica se o zoom é para frente ou para trás
 */
void Camera::zoom(int pos, int x, int z)
{

	this->posicao = this->posicao + Vector3(0,pos*50,0);//calcula próxima posição

	/**
	 * Limite do zoom de y para baixo e para cima
	 */
	if (this->posicao.f[1] < 300) {
		this->posicao.f[1] = 300;
	}

	if (this->posicao.f[1] > 10000) {
		this->posicao.f[1] = 10000;
	}

	/**
	 * Calcula quanto vai ir para os lados em direção ao ponto
	 * Utiliza de interpolação.
	 */
	this->lookAt.f[0] = this->lookAt.f[0]*(1-0.01) + x*0.01;
	this->lookAt.f[2] = this->lookAt.f[2]*(1-0.01) + z*0.01;

	/**
	 * Limite do zoom de x para direita e esquerda
	 */
	if (this->lookAt.f[0] > 5000) {
		this->lookAt.f[0] = 5000;
	}

	if (this->lookAt.f[0] < -5000) {
		this->lookAt.f[0] = -5000;
	}

	/**
	 * Limite do zoom de z para frente e para trás
	 */
	if (this->lookAt.f[2] > 5000) {
		this->lookAt.f[2] = 5000;
	}

	if (this->lookAt.f[2] < -5000) {
		this->lookAt.f[2] = -5000;
	}

	/**
	 * Calcula nova posição de x e z para 
	 * ficar perpendicular ao ponto
	 */
	this->posicao.f[0] = this->lookAt.f[0] + 100;
	this->posicao.f[2] = this->lookAt.f[2] + 1;
}

/**
 * Limite utilizado pela câmera da nave
 * para não passar do skybox
 */
void Camera::limita()
{
	int limiteHorizontal = 4900;
	int limiteVertical = 2500;

	posicao.f[0] = max(-limiteHorizontal, min(limiteHorizontal, posicao.f[0]));
	posicao.f[1] = max(-limiteVertical, min(limiteVertical, posicao.f[1]));
	posicao.f[2] = max(-limiteHorizontal, min(limiteHorizontal, posicao.f[2]));
}

/**
 * Projeta a câmera
 */
void Camera::desenha()
{
	gluLookAt(this->posicao.f[0],//posição da câmera
			  this->posicao.f[1],//posição da câmera
			  this->posicao.f[2],//posição da câmera
			  this->lookAt.f[0],//qual ponto esta olhando
			  this->lookAt.f[1],//qual ponto esta olhando
			  this->lookAt.f[2],//qual ponto esta olhando
			  this->up.f[0],//vetor up
			  this->up.f[1],//vetor up
			  this->up.f[2]);//vetor up
}

/**
 * Função utilizada pela câmera da nave 
 * Indica o quanto para frente ela irá
 */
void Camera::moveFrente()
{
	this->posicao += dir * 8.0f;//vai 8 unidades para frente
	limita();//limita posição
	this->lookAt = posicao + dir;//faz sempre olhar pra frente
}

/**
 * Move visão da câmera da nave para a esquerda 8 unidades
 * Calcula o produto externo da direção com o vetor up, que 
 * resulta em um vetor perpendicular
 */
void Camera::moveEsquerda()
{
	this->posicao = this->posicao - dir.produtoExterno(up)*8.0f;
	limita();
	this->lookAt = posicao + dir;//faz ir sempre para a esquerda
}

/**
 * Move camera para a direita 8 unidades
 * Faz a soma com o produto externo de dir com up
 */
void Camera::moveDireita()
{
	this->posicao += (dir.produtoExterno(up)*8.0f);
	limita();
	this->lookAt = posicao + dir;
}

/**
 * Rotaciona camera para a esquerda
 */
void Camera::rotacionaParaEsquerda()
{

	dir = rotacionaVetor(dir,up,-1.0f);//rotaciona 1 graus o vetor dir sobre o vetor up

	this->lookAt = posicao + dir;
}

/**
 * Rotaciona para a direita 
 */
void Camera::rotacionaParaDireita()
{
	dir = rotacionaVetor(dir,up,1.0f);//rotaciona 1 graus o vetor dir sobre o vetor up
	
	this->lookAt = posicao + dir;
}

/**
 * Rotaciona para cima
 * 	Calcula produto externo de dir sobre up
 * 	Rotaciona o vetor dir sobre um novo vetor perpendicular
 */
void Camera::rotacionaParaCima()
{
	Vector3 t = dir.produtoExterno(up);

	dir = rotacionaVetor(dir,t,-1.0f);//rotaciona 1 graus
	this->lookAt = posicao + dir;
}

/**
 * Rotaciona para baixo
 * 	Calcula produto externo de dir sobre up
 * 	Rotaciona o vetor dir sobre um novo vetor perpendicular
 */
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

  /**
   * Calcula seno e cosseno do novo vetor que será gerado
   */
  float ca = cos(angulo);
  float sa = sin(angulo);

  Vector3 cross = u.produtoExterno(v);

  float dot = u.produtoInterno(v);

  /**
   * Calcula os valores x, y, e z do novo vetor
   */
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
