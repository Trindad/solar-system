#include "Material.hpp"

class Objeto
{
public:
	Objeto();
	~Objeto();

	/**
	* Ordem para a criação dos triângulos
	* de forma correta
	*/
	int indices;//utilizado para saber quantos vértices
	vector<int> indices_vertices;//vértices em ordem dos triângulos
	vector<int> indices_normais;//vetor de normais 
	Material *material;//material do objeto
	string nome;//nome do objeto
};
