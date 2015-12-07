#include "Material.hpp"

Material::Material(){}
Material::~Material(){}

/**
 * Aplica as características do material
 */
void Material::aplica()
{
  GLfloat e[4] = {0,0,0,1};//emite cor preta
  GLfloat *difuso = kd.vec4();
  difuso[3] = d;

  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ka.vec4());
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, difuso);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, ks.vec4());
  glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, e);
  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, ns);
}
