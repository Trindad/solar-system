#include "Nave.hpp"

Nave::Nave(){

}
Nave::~Nave(){}

void Nave::init()
{
  carregaObjetos("nave.obj");
}

void Nave::desenha(Vector3 posicao, Vector3 dir, Vector3 up) {
  Vector3 pos = posicao + (dir * 2) - (up * 7);
  glPushMatrix();
  glTranslatef(pos.f[0], pos.f[1], pos.f[2]);

  // cout << "Objetos " << (int) objetos.size() << endl;

  for (int k = 0; k < (int) objetos.size(); k++)
  {
    if (objetos[k]->material) {
      objetos[k]->material->aplica();
    }

    glBegin(GL_TRIANGLES);
    // cout << "INDICES " << k << " : " << (int) objetos[k]->indices.size() << endl;
    for (int i = 0; i < (int) objetos[k]->indices.size(); i++)
    {
      glNormal3f(objetos[k]->normais[objetos[k]->indices_normais[i]].f[0], objetos[k]->normais[objetos[k]->indices_normais[i]].f[1], objetos[k]->normais[objetos[k]->indices_normais[i]].f[2]);
      glVertex3f(objetos[k]->vertices[objetos[k]->indices_vertices[i]].f[0], objetos[k]->vertices[objetos[k]->indices_vertices[i]].f[1], objetos[k]->vertices[objetos[k]->indices_vertices[i]].f[2]);
    }
    glEnd();
  }

  glPopMatrix();
}

void Nave::carregaObjetos(const char* arquivo)
{
    ifstream in(arquivo, ios::in);

    if (!in)
    {
      cerr << "Não foi possível carregar o arquivo: " << arquivo << endl;
      exit(1);
    }

    string linha;
    Objeto *objetoAtual;

    while (getline(in, linha))
    {
        if (linha.substr(0, 7).compare("mtllib ") == 0)
        {
          leMateriais(linha.substr(7).c_str());
        }
        else if (linha.substr(0, 2).compare("o ") == 0)
        {
          objetoAtual = new Objeto();
          objetos.push_back(objetoAtual);
        }
        else if (linha.substr(0, 7).compare("usemtl ") == 0)
        {
          string nome = linha.substr(7);

          for (int j = 0; j < (int) materiais.size(); j++)
          {
            if (materiais[j]->nome.compare(nome) == 0) {
              objetoAtual->material = materiais[j];
            }
          }
        }
        else if (linha.substr(0,2).compare("v ") == 0)
        {
            string t = linha.substr(2);
            istringstream s(t);
            GLfloat _a, _b, _c;
            s >> _a; s >> _b; s >> _c;
            Vector3 v(_a,_b,_c);
            objetoAtual->vertices.push_back(v);
        }
        else if (linha.substr(0,3).compare("vn ") == 0)
        {
          vector<string> els = split(linha.substr(3), ' ');

          if ((int)els.size() > 1) {
            Vector3 v(atof(els.at(0).c_str()), atof(els.at(1).c_str()), atof(els.at(2).c_str()));
            objetoAtual->normais.push_back(v);
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
              objetoAtual->indices.push_back(0);
              objetoAtual->indices_vertices.push_back(atoi(e.at(0).c_str()) - 1);
              objetoAtual->indices_normais.push_back(atoi(e.at(2).c_str()) - 1);
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

void Nave::leMateriais(const char* arquivo)
{
  ifstream in(arquivo, ios::in);

    if (!in)
    {
      cerr << "Não foi possível carregar o arquivo: " << arquivo << endl;
      exit(1);
    }

    string linha;
    Material *materialAtual;

    while (getline(in, linha))
    {
        if (linha.substr(0, 7).compare("newmtl ") == 0)
        {
          materialAtual = new Material();
          materiais.push_back(materialAtual);
          materialAtual->nome = linha.substr(7);
        }
        else if (linha.substr(0, 3).compare("Ns ") == 0)
        {
          materialAtual->ns = atof(linha.substr(3).c_str());
        }
        else if (linha.substr(0, 3).compare("Ka ") == 0)
        {
          vector<string> els = split(linha.substr(3), ' ');

          if ((int)els.size() > 1) {
            materialAtual->ka = Vector3(atof(els.at(0).c_str()), atof(els.at(1).c_str()), atof(els.at(2).c_str()));
          }
        }
        else if (linha.substr(0, 3).compare("Kd ") == 0)
        {
          vector<string> els = split(linha.substr(3), ' ');

          if ((int)els.size() > 1) {
            materialAtual->kd = Vector3(atof(els.at(0).c_str()), atof(els.at(1).c_str()), atof(els.at(2).c_str()));
          }
        }
        else if (linha.substr(0, 3).compare("Ks ") == 0)
        {
          vector<string> els = split(linha.substr(3), ' ');

          if ((int)els.size() > 1) {
            materialAtual->ks = Vector3(atof(els.at(0).c_str()), atof(els.at(1).c_str()), atof(els.at(2).c_str()));
          }
        }
        else if (linha.substr(0, 2).compare("d ") == 0)
        {
          materialAtual->d = atof(linha.substr(2).c_str());
        }
    }
}
