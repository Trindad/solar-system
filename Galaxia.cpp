#include "Galaxia.hpp"

class SolidSphere
{
protected:
    std::vector<GLfloat> vertices;
    std::vector<GLfloat> normals;
    std::vector<GLfloat> texcoords;
    std::vector<GLushort> indices;

public:
    SolidSphere(float radius, unsigned int rings, unsigned int sectors)
    {
        float const R = 1.0f/(float)(rings-1);
        float const S = 1.0f/(float)(sectors-1);
        int r, s;

        vertices.resize(rings * sectors * 3);
        normals.resize(rings * sectors * 3);
        texcoords.resize(rings * sectors * 2);

        std::vector<GLfloat>::iterator v = vertices.begin();
        std::vector<GLfloat>::iterator n = normals.begin();
        std::vector<GLfloat>::iterator t = texcoords.begin();
        
        for(r = 0; r < rings; r++) {
            for(s = 0; s < sectors; s++) {
                float const y = sin( -M_PI_2 + M_PI * r * R );
                float const x = cos(2*M_PI * s * S) * sin( M_PI * r * R );
                float const z = sin(2*M_PI * s * S) * sin( M_PI * r * R );

                *t++ = s*S;
                *t++ = r*R;

                *v++ = x * radius;
                *v++ = y * radius;
                *v++ = z * radius;

                *n++ = -x;
                *n++ = -y;
                *n++ = -z;
            }
        }

        indices.resize(rings * sectors * 4);
        std::vector<GLushort>::iterator i = indices.begin();
        
        for(r = 0; r < rings-1; r++) {

            for(s = 0; s < sectors-1; s++) {
                *i++ = r * sectors + s;
                *i++ = r * sectors + (s+1);
                *i++ = (r+1) * sectors + (s+1);
                *i++ = (r+1) * sectors + s;
            }
        }
    }

    void draw(GLfloat x, GLfloat y, GLfloat z)
    {
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glTranslatef(x,y,z);

        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_NORMAL_ARRAY);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);

        glVertexPointer(3, GL_FLOAT, 0, &vertices[0]);
        glNormalPointer(GL_FLOAT, 0, &normals[0]);
        glTexCoordPointer(2, GL_FLOAT, 0, &texcoords[0]);
        glDrawElements(GL_QUADS, (int)indices.size(), GL_UNSIGNED_SHORT, &indices[0]);
        glPopMatrix();
    }
};


Galaxia::Galaxia(int r)
{
	this->raio = r;
}

Galaxia::~Galaxia(){}

void Galaxia::desenha()
{
    glBindTexture (GL_TEXTURE_2D, texture);
    // glTexGeni(GL_S,GL_TEXTURE_GEN_MODE,GL_OBJECT_LINEAR);
    // glEnable(GL_TEXTURE_GEN_S);

    // glTexGeni(GL_T,GL_TEXTURE_GEN_MODE,GL_OBJECT_LINEAR);
    // glEnable(GL_TEXTURE_GEN_T);

    // float s[4] = {1/256,0,0,0};
    // glTexGenfv(GL_S,GL_OBJECT_PLANE,s);

    // float t[4] = {0,0,1/256,0};
    // glTexGenfv(GL_T,GL_OBJECT_PLANE,t);

	glPushMatrix();

	SolidSphere sphere(raio, 50, 50);
	sphere.draw(0, 0, 0);

	glPopMatrix();
}


void Galaxia::loadTexture(const char* filename)
{
  this->texture = Textura::loadTexture(filename);
}

void Galaxia::renderSphere(float cx, float cy, float cz, float r, int p)
{
}
