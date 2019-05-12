#pragma once

#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>
#include "Image.h"

class Texture
{
public:
	Texture();
	Texture( const Texture& texture);
	Texture( const Image& image, int internalFormat = GL_RGBA);

	~Texture();

	operator GLuint() const;
	
	void SetWrapping(int wrapping_t_s);
	void SetWrapping(int wrapping_t_s, int wrapping_t_t);
	void SetWrapping(int wrapping_t_s, int wrapping_t_t, int wrapping_t_r);

private:
	GLuint obj;
};

#endif //TEXTURE_H