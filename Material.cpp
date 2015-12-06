#include "Material.hpp"

Material::Material(){}
Material::~Material(){}

void Material::aplica()
{
  // glMaterialfv(GL_FRONT, GL_AMBIENT, ka.vec4());
  glMaterialfv(GL_FRONT, GL_DIFFUSE, kd.vec4());
  // glMaterialfv(GL_FRONT, GL_SPECULAR, ks.vec4());
  // glMaterialf(GL_FRONT, GL_SHININESS, ns);
}
