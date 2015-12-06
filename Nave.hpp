#include "Objeto.hpp"

class Nave
{
public:
	Nave();
	~Nave();

  void desenha(Vector3, Vector3, Vector3, float);
  void init();
  void carregaObjetos(const char* arquivo);
  void leMateriais(const char* arquivo);
  Vector3 rotacionaVetor(Vector3 u, Vector3 v, float graus);
  vector<string> &split(const string &s, char delim, vector<string> &elems);
  vector<string> split(const string &s, char delim);

  vector<Objeto*> objetos;
  vector<Material*> materiais;
  vector<Vector3> vertices;
  vector<Vector3> normais;
  float rotacao;//acumula rotação da nave
};
