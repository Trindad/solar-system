#include "Nave.hpp"

Nave::Nave(){
  load_obj("nave.obj", _vertices, _normals, _elements);
}
Nave::~Nave(){}

void Nave::asa()
{
  glBegin(GL_POLYGON);

  glColor3f(1,1,1);
  glVertex3f(0,0,0);
  glVertex3f(150, 0, 0);
  glVertex3f(150, 0, 50);
  glVertex3f(0, 0, 250);

  glEnd();
}

void Nave::desenha() {
  GLfloat vertices[((int) _vertices.size()) * 3];
  GLfloat normals[((int) _vertices.size()) * 3];
  GLushort elements[((int) _vertices.size()) * 3];

  int c = 0;

  for (int i = 0; i < (int) _vertices.size(); i++)
  {
    vertices[c] = _vertices[i].f[0];
  	c++;
    vertices[c] = _vertices[i].f[1];
    c++;
    vertices[c] = _vertices[i].f[2];
    c++;
  }

  c = 0;
  for (int i = 0; i < (int) _normals.size(); i++)
  {
    normals[c++] = _normals[i].f[0];
    normals[c++] = _normals[i].f[1];
    normals[c++] = _normals[i].f[2];
  }

  c = 0;
  for (int i = 0; i < (int) _elements.size(); i++)
  {
    elements[c++] = _elements[i];
  }

  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_NORMAL_ARRAY);
  glVertexPointer(3,GL_FLOAT, 0,vertices);
  glNormalPointer(GL_FLOAT, 0, normals);
  glDrawElements(GL_TRIANGLES, (int) _elements.size(), GL_UNSIGNED_SHORT, elements);

  glDisableClientState(GL_NORMAL_ARRAY);
  glDisableClientState(GL_VERTEX_ARRAY);
}

void Nave::load_obj(const char* filename, vector<Vector3> &vertices, vector<Vector3> &normals, vector<GLushort> &elements)
{
    ifstream in(filename, ios::in);
    if (!in)
    {
        cerr << "Cannot open " << filename << endl; exit(1);
    }

    string line;
    while (getline(in, line))
    {
        if (line.substr(0,2) == "v ")
        {
            istringstream s(line.substr(2));
            Vector3 v; s >> v.f[0]; s >> v.f[1]; s >> v.f[2];
            vertices.push_back(v);
        }
        else if (line.substr(0,2) == "f ")
        {
            istringstream s(line.substr(2));
            GLushort a,b,c;
            s >> a; s >> b; s >> c;
            a--; b--; c--;
           elements.push_back(a); elements.push_back(b); elements.push_back(c);
        }
        else if (line[0] == '#')
        {
            /* ignoring this line */
        }
        else
        {
            /* ignoring this line */
        }
    }

    normals.resize(vertices.size(), Vector3(0.0, 0.0, 0.0));
    for (int i = 0; i < elements.size(); i+=3)
    {
        GLushort ia = elements[i];
        GLushort ib = elements[i+1];
        GLushort ic = elements[i+2];
        Vector3 normal = (vertices[ib] - vertices[ia]).produtoExterno(vertices[ic] - vertices[ia]).normalizado();
        normals[ia] = normals[ib] = normals[ic] = normal;
    }
}
