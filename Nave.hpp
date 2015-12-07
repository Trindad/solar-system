#include "Objeto.hpp"

class Nave
{
public:
	Nave();
	~Nave();

  void desenha(Vector3, Vector3, Vector3, float);
  void init();
  void carregaObjetos(const char*);
  void leMateriais(const char*);
  Vector3 rotacionaVetor(Vector3, Vector3, float);
  vector<string> &split(const string &s, char, vector<string> &);
  vector<string> split(const string &s, char);

  vector<Objeto*> objetos;
  vector<Material*> materiais;
  vector<Vector3> vertices;
  vector<Vector3> normais;
  float rotacao;//acumula rotação da nave
};
