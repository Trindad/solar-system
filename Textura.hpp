#ifndef TEXTURA_H
#define TEXTURA_H

#include "stb_image.hpp"

class Textura
{
public:

	Textura(){}
	~Textura(){}

	static GLuint loadTexture(const char* filename)
	{
	  GLuint t;
	  glGenTextures(1, &t);
	  GLuint texture = t;
	  glBindTexture(GL_TEXTURE_2D, texture);

	  int width = 0, height = 0;
	  int n = 0;

	  unsigned char* image = stbi_load(filename,&width,&height,&n,0);
	  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
	              GL_UNSIGNED_BYTE, image);


	   glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,image);
	
		glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);

		glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	  
		glEnable(GL_TEXTURE_GEN_S);
	    glEnable(GL_TEXTURE_GEN_T);

		glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);
		gluBuild2DMipmaps(GL_TEXTURE_2D,GL_RGB, width, height, GL_RGB, GL_UNSIGNED_BYTE, image);
			return texture;
	}
};

#endif