#include "Texture.h"

Texture::Texture()
{
	glGenTextures(1, &obj);
}

Texture::Texture(const Texture& texture)
{

}

Texture::Texture(const Image& image, int internalFormat)
{
	glGenTextures(1, &obj);

	glBindTexture(GL_TEXTURE_2D, obj);

	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, image.width, image.height, 0, internalFormat, GL_UNSIGNED_BYTE, image.data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, obj);

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
	glGenTextures(1, &obj);

	glBindTexture(GL_TEXTURE_2D, obj);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapping_t_s);

	glBindTexture(GL_TEXTURE_2D, obj);
}

void Texture::SetWrapping(int wrapping_t_s, int wrapping_t_t)
{
	glGenTextures(1, &obj);

	glBindTexture(GL_TEXTURE_2D, obj);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapping_t_s);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapping_t_t);


	glBindTexture(GL_TEXTURE_2D, obj);
}

void Texture::SetWrapping(int wrapping_t_s, int wrapping_t_t, int wrapping_t_r)
{
	glGenTextures(1, &obj);

	glBindTexture(GL_TEXTURE_2D, obj);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapping_t_s);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapping_t_t);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, wrapping_t_r);

	glBindTexture(GL_TEXTURE_2D, obj);
}

