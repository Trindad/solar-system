#include "Nave.hpp"

Nave::Nave(){

}
Nave::~Nave(){}

void Nave::init()
{
  load_obj("nave.obj", _vertices, _normals, _elements);
}

void Nave::desenha() {
  glPushMatrix();
  glBegin(GL_TRIANGLES);
  for (int i = 0; i < (int) _elements.size(); i++)
  {
    glNormal3f(_normals[indexed_normals[i]].f[0], _normals[indexed_normals[i]].f[1], _normals[indexed_normals[i]].f[2]);
    glVertex3f(_vertices[indexed_vertices[i]].f[0], _vertices[indexed_vertices[i]].f[1], _vertices[indexed_vertices[i]].f[2]);
  }
  glEnd();
  glPopMatrix();
}

void Nave::load_obj(const char* filename, vector<Vector3> &vertices, vector<Vector3> &normals, vector<GLushort> &elements)
{
    ifstream in(filename, ios::in);

    if (!in)
    {
      cerr << "Cannot open " << filename << endl;
      exit(1);
    }

    string line;

    while (getline(in, line))
    {
        if (line.substr(0,2).compare("v ") == 0)
        {
            string t = line.substr(2);
            istringstream s(t);
            GLfloat _a, _b, _c;
            s >> _a; s >> _b; s >> _c;
            Vector3 v(_a,_b,_c);
            vertices.push_back(v);
        }
        else if (line.substr(0,3).compare("vn ") == 0)
        {
          vector<string> els = split(line.substr(3), ' ');

          if ((int)els.size() > 1) {
            Vector3 v(atof(els.at(0).c_str()), atof(els.at(1).c_str()), atof(els.at(2).c_str()));
            normals.push_back(v);
          }
        }
        else if (line.substr(0,2).compare("f ") == 0)
        {
          vector<string> str = split(line, 'f');
          vector<string> els = split(str[1], ' ');

          for (int k = 0; k < (int) els.size(); k++)
          {
            vector<string> e = split(els[k], '/');

            if ((int)e.size() > 1)
            {
              elements.push_back(0);
              indexed_vertices.push_back(atoi(e.at(0).c_str()) - 1);
              indexed_normals.push_back(atoi(e.at(2).c_str()) - 1);
            }
          }
        }
    }

    // normals.resize(vertices.size(), Vector3(0.0f, 0.0f, 0.0f));
    // for (int i = 0; i < (int)elements.size(); i+=3)
    // {
    //     GLushort ia = elements[i];
    //     GLushort ib = elements[i+1];
    //     GLushort ic = elements[i+2];

    //     Vector3 normal = (vertices[ib] - vertices[ia]).produtoExterno(vertices[ic] - vertices[ia]).normalizado();
    //     normals[ia] = normals[ib] = normals[ic] = normal;
    // }
}


vector<string> &Nave::split(const string &s, char delim, vector<string> &elems) {
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}


vector<string> Nave::split(const string &s, char delim) {
   vector<string> elems;
    split(s, delim, elems);
    return elems;
}
