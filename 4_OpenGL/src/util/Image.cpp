#include "Image.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


Image::Image(const char* path)
{
	data = stbi_load(path, &width, &height, &nrChannels, 0);
}

Image::Image(const char* path, bool flip)
{
	stbi_set_flip_vertically_on_load(flip);
	data = stbi_load(path, &width, &height, &nrChannels, 0);
}

Image::~Image()
{
	if(data)
		stbi_image_free(data);
}
