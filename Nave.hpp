#include "Objeto.hpp"

class Nave
{
public:
	Nave();
	~Nave();

  void desenha(Vector3, Vector3, Vector3);
  void init();
  void carregaObjetos(const char* arquivo);
  void leMateriais(const char* arquivo);
  vector<string> &split(const string &s, char delim, vector<string> &elems);
  vector<string> split(const string &s, char delim);
  vector<Objeto*> objetos;
  vector<Material*> materiais;
};
