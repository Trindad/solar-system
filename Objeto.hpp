#include "Material.hpp"

class Objeto
{
public:
	Objeto();
	~Objeto();

	
	int indices;

	/**
	* Ordem para a criação dos triângulos
	* de forma correta
	*/
	vector<int> indices_vertices;
	vector<int> indices_normais;
	Material *material;
};
