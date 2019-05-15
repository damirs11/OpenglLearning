#include "Texture.h"

#define PUSHSTATE() GLint restoreId; glGetIntegerv( GL_TEXTURE_BINDING_2D, &restoreId );
#define POPSTATE() glBindTexture( GL_TEXTURE_2D, restoreId );

Texture::Texture()
{
	glGenTextures(1, &obj);
}

Texture::Texture(const Texture& texture)
{

}

Texture::Texture(const Image& image, int internalFormat)
{
	PUSHSTATE();

	glGenTextures(1, &obj);
	glBindTexture(GL_TEXTURE_2D, obj);

	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, image.width, image.height, 0, internalFormat, GL_UNSIGNED_BYTE, image.data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glGenerateMipmap(GL_TEXTURE_2D);

	POPSTATE();
}

Texture::~Texture()
{
	glDeleteTextures(1, &obj);
}

Texture::operator GLuint() const
{
	return obj;
}

void Texture::SetWrapping(int wrapping_t_s)
{
	PUSHSTATE();

	glBindTexture(GL_TEXTURE_2D, obj);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapping_t_s);

	glBindTexture(GL_TEXTURE_2D, restoreId);

	POPSTATE();
}

void Texture::SetWrapping(int wrapping_t_s, int wrapping_t_t)
{
	PUSHSTATE();

	glBindTexture(GL_TEXTURE_2D, obj);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapping_t_s);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapping_t_t);

	glBindTexture(GL_TEXTURE_2D, restoreId);

	POPSTATE();
}

void Texture::SetWrapping(int wrapping_t_s, int wrapping_t_t, int wrapping_t_r)
{
	PUSHSTATE();

	glBindTexture(GL_TEXTURE_2D, obj);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapping_t_s);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapping_t_t);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, wrapping_t_r);

	glBindTexture(GL_TEXTURE_2D, restoreId);

	POPSTATE();
}

void Texture::SetFilters(int min, int mag)
{
	PUSHSTATE();

	glBindTexture(GL_TEXTURE_2D, obj);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag);

	POPSTATE();
}

