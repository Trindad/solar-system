#include "Nave.hpp"

Nave::Nave(){

}
Nave::~Nave(){}

void Nave::init()
{
  carrega_obj("nave.obj");
}

void Nave::desenha() {
  glPushMatrix();
  glTranslatef(200, -200, 200);
  glBegin(GL_TRIANGLES);
  for (int i = 0; i < (int) indices.size(); i++)
  {
    glNormal3f(normais[indices_normais[i]].f[0], normais[indices_normais[i]].f[1], normais[indices_normais[i]].f[2]);
    glVertex3f(vertices[indices_vertices[i]].f[0], vertices[indices_vertices[i]].f[1], vertices[indices_vertices[i]].f[2]);
  }
  glEnd();
  glPopMatrix();
}

void Nave::carrega_obj(const char* arquivo)
{
    ifstream in(arquivo, ios::in);

    if (!in)
    {
      cerr << "Não foi possível carregar o arquivo: " << arquivo << endl;
      exit(1);
    }

    string linha;

    while (getline(in, linha))
    {
        if (linha.substr(0,2).compare("v ") == 0)
        {
            string t = linha.substr(2);
            istringstream s(t);
            GLfloat _a, _b, _c;
            s >> _a; s >> _b; s >> _c;
            Vector3 v(_a,_b,_c);
            vertices.push_back(v);
        }
        else if (linha.substr(0,3).compare("vn ") == 0)
        {
          vector<string> els = split(linha.substr(3), ' ');

          if ((int)els.size() > 1) {
            Vector3 v(atof(els.at(0).c_str()), atof(els.at(1).c_str()), atof(els.at(2).c_str()));
            normais.push_back(v);
          }
        }
        else if (linha.substr(0,2).compare("f ") == 0)
        {
          vector<string> els = split(linha.substr(2), ' ');

          for (int k = 0; k < (int) els.size(); k++)
          {
            vector<string> e = split(els[k], '/');

            if ((int)e.size() > 1)
            {
              indices.push_back(0);
              indices_vertices.push_back(atoi(e.at(0).c_str()) - 1);
              indices_normais.push_back(atoi(e.at(2).c_str()) - 1);
            }
          }
        }
    }
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
