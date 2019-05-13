#pragma once

#ifndef IMAGE_H
#define IMAGE_H

class Image
{
public:

	Image(const char* path);
	Image(const char* path, bool flip);
	~Image();


	int width, height, nrChannels;
	unsigned char* data;
private:
};

#endif // IMAGE_H