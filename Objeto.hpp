#include "Material.hpp"

class Objeto
{
public:
	Objeto();
	~Objeto();

	vector<Vector3> vertices;
	vector<Vector3> normais;
	vector<GLushort> indices;

	/**
	* Ordem para a criação dos triângulos
	* de forma correta
	*/
	vector<int> indices_vertices;
	vector<int> indices_normais;
	Material *material;
};
