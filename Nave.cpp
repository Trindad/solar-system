#include "Nave.hpp"

Nave::Nave(){

}
Nave::~Nave(){}

void Nave::init()
{
  carregaObjetos("nave.obj");
}

void Nave::desenha(Vector3 posicao, Vector3 dir, Vector3 up, float deltaTempo) {
  glDisable(GL_COLOR_MATERIAL);
  Vector3 pos = posicao + (dir * -10) - (up * 15);
  
  glTranslatef(pos.f[0], pos.f[1], pos.f[2]);

  rotacao = rotacao + deltaTempo * 20.0f;

  while (this->rotacao > 360.0f)
  {
    rotacao -= 360.0f;
  }
  glScalef(5,5,5);

  Vector3 y(0,1,0); 
  float cos_angulo = acos(up.produtoInterno(dir)/(up.magnitude()*dir.magnitude())) * (180.0f / PI);
  
  Vector3 t = dir.produtoExterno(up);

  glRotatef(90 - cos_angulo, t.f[0], t.f[1], t.f[2]);
  glTranslatef(0, -10, 0);//translaciona para baixo, assim a nave não aparece
  glRotatef(rotacao,up.f[0], up.f[1], up.f[2]);

  for (int k = 0; k < (int) objetos.size(); k++)
  {
    if (objetos[k]->material) {
      if (objetos[k]->material->d < 1) {
        glDepthMask(GL_FALSE);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      }

      objetos[k]->material->aplica();
    }

    glBegin(GL_TRIANGLES);
    for (int i = 0; i < objetos[k]->indices; i++)
    {
      glNormal3f(normais[objetos[k]->indices_normais[i]].f[0], normais[objetos[k]->indices_normais[i]].f[1], normais[objetos[k]->indices_normais[i]].f[2]);
      glVertex3f(vertices[objetos[k]->indices_vertices[i]].f[0], vertices[objetos[k]->indices_vertices[i]].f[1], vertices[objetos[k]->indices_vertices[i]].f[2]);
    }
    glEnd();

    if (objetos[k]->material && objetos[k]->material->d < 1) {
      glDisable(GL_BLEND);
      glDepthMask(GL_TRUE);
    }
  }

  // glPopMatrix();
  glEnable(GL_COLOR_MATERIAL);
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
            if (materiais[j]->nome == nome) {
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
              objetoAtual->indices++;
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

Vector3 Nave::rotacionaVetor(Vector3 u, Vector3 v, float graus) {

  float angulo = graus * PI/180.0f;//transforma de graus para radianos

  float ca = cos(angulo);
  float sa = sin(angulo);

  Vector3 cross = u.produtoExterno(v);

  float dot = u.produtoInterno(v);

  Vector3 novo;

  novo.f[0] = u.f[0]*ca + cross.f[0]*sa + dot*v.f[0]*(1-ca);
  novo.f[1] = u.f[1]*ca + cross.f[1]*sa + dot*v.f[1]*(1-ca);
  novo.f[2] = u.f[2]*ca + cross.f[2]*sa + dot*v.f[2]*(1-ca);

  return novo;
}