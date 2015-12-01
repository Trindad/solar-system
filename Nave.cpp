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

  int n = ((int) _vertices.size()) * 3;

  GLfloat vertices[n];
  GLfloat normals[n];
  GLushort elements[n];

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
  n =  (int) _elements.size();
  glDrawElements(GL_TRIANGLES,n, GL_UNSIGNED_SHORT, elements);

  glDisableClientState(GL_NORMAL_ARRAY);
  glDisableClientState(GL_VERTEX_ARRAY);
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
          
          if (els.size() > 1) {
            Vector3 v(atof(els.at(0).c_str()), atof(els.at(1).c_str()), atof(els.at(2).c_str()));
            normals.push_back(v);
          }
        }
        else if (line.substr(0,2).compare("f ") == 0)
        {
          vector<string> els = split(line, ' ');
          for (int k = 0; k < (int) els.size(); k++)
          {
            vector<string> e = split(els[k], '/');
            if (e.size() > 1) {
              elements.push_back(atof(e.at(0).c_str()) - 1);
              // elements.push_back(atof(e.at(1).c_str()) - 1);
              // elements.push_back(atof(e.at(2).c_str()) - 1);
            }
          }
           //  string t = line.substr(2);
           //  cout<<" "<<t<<endl;
           //  istringstream s(t);
           //  GLushort a,b,c;
           //  s >> a; s >> b; s >> c;
           //  cout<<std::setprecision(10)<<a<<" "<<std::setprecision(10)<<b<<" "<<std::setprecision(10)<<c<<endl;
           //  a--; b--; c--;
           // elements.push_back(a); 
           // elements.push_back(b); 
           // elements.push_back(c);
        }
        else if (line.substr(0,2).compare("# ") == 0)
        {
            continue;
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