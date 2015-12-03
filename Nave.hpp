#include "Vector3.hpp"

class Nave
{
public:
	Nave();
	~Nave();

  void desenha();
  void init();
  void carrega_obj(const char* arquivo);
  vector<string> &split(const string &s, char delim, vector<string> &elems);
  vector<string> split(const string &s, char delim);
  vector<Vector3> vertices;
  vector<Vector3> normais;
  vector<GLushort> indices;

  /**
   * Ordem para a criação dos triângulos
   * de forma correta
   */
  vector<int> indices_vertices;
  vector<int> indices_normais;
};
