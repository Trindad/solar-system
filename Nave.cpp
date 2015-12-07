#include "Nave.hpp"

Nave::Nave(){}

Nave::~Nave(){}

/**
 * Carrega objeto na inicialização do programa
 * Não pode ser no construtor
 */
void Nave::init()
{
  carregaObjetos("nave.obj");//carrega arquivo .obj
}

/**
 * Desenha a nave com base na câmera da nave
 * Percorre os objeto, aplicando o material associado ao objeto
 * e desenhando os triângulos na ordem certa
 */
void Nave::desenha(Vector3 posicao, Vector3 dir, Vector3 up, float deltaTempo) {
  
  glDisable(GL_COLOR_MATERIAL);//para opengl não usar cor do vértice e sim só o material
  
  /**
   * Posiciona a nave abaixo da câmera
   */
  Vector3 pos = posicao + (dir * -10) - (up * 15);
  glTranslatef(pos.f[0], pos.f[1], pos.f[2]);

  /**
   * Rotaciona nave, assim ela fica girando
   */
  rotacao = rotacao + deltaTempo * 20.0f;

  while (this->rotacao > 360.0f)
  {
    rotacao -= 360.0f;
  }

  glScalef(5,5,5);//aumenta o tamanho da nave

  /**
   * Faz a inclinação igual a da câmera
   */
  Vector3 y(0,1,0); 
  float cos_angulo = acos(up.produtoInterno(dir)/(up.magnitude()*dir.magnitude())) * (180.0f / PI);
  Vector3 t = dir.produtoExterno(up);
  glRotatef(90 - cos_angulo, t.f[0], t.f[1], t.f[2]);
  glTranslatef(0, -10, 0);//translaciona para baixo, assim a nave não aparece
  glRotatef(rotacao,up.f[0], up.f[1], up.f[2]);

  /**
   * Desenha cada objeto com suas propriedades
   */
  for (int k = 0; k < (int) objetos.size(); k++)
  {
    if (objetos[k]->material) 
    {
      /**
       * Se o objeto for transparente então 
       * tem que desabilitar teste de profundidade
       */
      if (objetos[k]->material->d < 1) 
      {
        glDepthMask(GL_FALSE);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      }

      objetos[k]->material->aplica();//aplica material ao objeto
    }

    /**
     * Desenha triângulos na ordem correta
     */
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < objetos[k]->indices; i++)
    {
      glNormal3f(normais[objetos[k]->indices_normais[i]].f[0], normais[objetos[k]->indices_normais[i]].f[1], normais[objetos[k]->indices_normais[i]].f[2]);
      glVertex3f(vertices[objetos[k]->indices_vertices[i]].f[0], vertices[objetos[k]->indices_vertices[i]].f[1], vertices[objetos[k]->indices_vertices[i]].f[2]);
    }
    glEnd();

    /**
     * Habilita novamente teste de profundidade
     * para objetos translucidos
     */
    if (objetos[k]->material && objetos[k]->material->d < 1) {
      glDisable(GL_BLEND);
      glDepthMask(GL_TRUE);
    }
  }

  glEnable(GL_COLOR_MATERIAL);
}

/**
 * Carrega objetos do arquivo passado como parâmetro
 */
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

  /**
   * Percorre cada linha do arquivo
   */
  while (getline(in, linha))
  {
    /**
     * mtlib indica o nome do arquivo de materiais
     * Então faz a leitura dos materiais
     */
    if (linha.substr(0, 7).compare("mtllib ") == 0)
    {
      leMateriais(linha.substr(7).c_str());
    }
    /**
     * <o> indica que um objeto vai começar, ou seja,
     * até outro <o> aparecer os vértices e normais 
     * irão pertencer a este objeto
     */
    else if (linha.substr(0, 2).compare("o ") == 0)
    {
      objetoAtual = new Objeto();
      string nome = linha.substr(2);
      objetoAtual->nome = nome;
      objetos.push_back(objetoAtual);
    }
    /**
     * Dos materiais lidos vai dizer qual
     * material está associado ao objeto
     */
    else if (linha.substr(0, 7).compare("usemtl ") == 0)
    {
      string nome = linha.substr(7);

      for (int j = 0; j < (int) materiais.size(); j++)
      {
        if (materiais[j]->nome == nome) 
        {
          objetoAtual->material = materiais[j];
        }
      }
    }
    /**
     * <v> indica a leitura de um vértice
     */
    else if (linha.substr(0,2).compare("v ") == 0)
    {
        string t = linha.substr(2);
        istringstream s(t);
        GLfloat _a, _b, _c;
        s >> _a; s >> _b; s >> _c;
        Vector3 v(_a,_b,_c);
        vertices.push_back(v);
    }
    /**
     * <vn> indica a leitura de uma normal de um vértice
     */
    else if (linha.substr(0,3).compare("vn ") == 0)
    {
      vector<string> els = split(linha.substr(3), ' ');

      if ((int)els.size() > 1) {
        Vector3 v(atof(els.at(0).c_str()), atof(els.at(1).c_str()), atof(els.at(2).c_str()));
        normais.push_back(v);
      }
    }
    /**
     * <f> indica uma face/triângulo
     * faz a leitura dos indices dos vértices
     * e das normais que compõe, sendo que o 
     * arquivo é sequencial
     */
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

/**
 * Lê os materiais, armazenando as informações em um vetor da classe
 */
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
    /**
     * <newmtl> indica que um novo material 
     * irá começar
     */
    if (linha.substr(0, 7).compare("newmtl ") == 0)
    {
      materialAtual = new Material();
      materiais.push_back(materialAtual);
      materialAtual->nome = linha.substr(7);
    }
    /**
     * <Ns> indica o coeficiente especular (shininess)
     */
    else if (linha.substr(0, 3).compare("Ns ") == 0)
    {
      materialAtual->ns = atof(linha.substr(3).c_str());
    }
    /**
     * <Ka> indica a cor ambiente
     */
    else if (linha.substr(0, 3).compare("Ka ") == 0)
    {
      vector<string> els = split(linha.substr(3), ' ');

      if ((int)els.size() > 1) {
        materialAtual->ka = Vector3(atof(els.at(0).c_str()), atof(els.at(1).c_str()), atof(els.at(2).c_str()));
      }
    }
    /**
     * <Kd> indica a cor difusa
     */
    else if (linha.substr(0, 3).compare("Kd ") == 0)
    {
      vector<string> els = split(linha.substr(3), ' ');

      if ((int)els.size() > 1) {
        materialAtual->kd = Vector3(atof(els.at(0).c_str()), atof(els.at(1).c_str()), atof(els.at(2).c_str()));
      }
    }
    /**
     * <Ks> indica a cor especular
     */
    else if (linha.substr(0, 3).compare("Ks ") == 0)
    {
      vector<string> els = split(linha.substr(3), ' ');

      if ((int)els.size() > 1) {
        materialAtual->ks = Vector3(atof(els.at(0).c_str()), atof(els.at(1).c_str()), atof(els.at(2).c_str()));
      }
    }
    /**
     * <d> a transparência
     */
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