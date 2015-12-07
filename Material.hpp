#include "Vector3.hpp"

class Material
{
public:
	Material();
	~Material();
 	void aplica();

	string nome;//nome do objeto
	Vector3 ka;//cor ambiente
	Vector3 kd;//difuso
	Vector3 ks;//especular
	GLfloat ns;//shininess
	GLfloat d;//transparência
};
