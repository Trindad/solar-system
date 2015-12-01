#include "Vector3.hpp"

class Nave
{
public:
	Nave();
	~Nave();

  void desenha();
  void asa();
  void load_obj(const char* filename, vector<Vector3> &vertices, vector<Vector3> &normals, vector<GLushort> &elements);
  vector<string> &split(const string &s, char delim, vector<string> &elems);
  vector<string> split(const string &s, char delim);
  vector<Vector3> _vertices;
  vector<Vector3> _normals;
  vector<GLushort> _elements;
};
