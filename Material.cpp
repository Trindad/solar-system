#include "Material.hpp"

Material::Material(){}
Material::~Material(){}

void Material::aplica()
{
  // cout << "Kd " << kd.f[0] * 255 << " " << kd.f[1] * 255 <<  " " << kd.f[2] * 255 << endl;
  GLfloat e[4] = {0,0,0,1};
  GLfloat *difuso = kd.vec4();
  difuso[3] = d;
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ka.vec4());
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, difuso);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, ks.vec4());
  glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, e);
  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, ns);
}
