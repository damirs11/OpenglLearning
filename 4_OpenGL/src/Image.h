#pragma once

#ifndef IMAGE_H
#define IMAGE_H

class Image
{
public:

	Image(const char* path);
	~Image();


	int width, height, nrChannels;
	unsigned char* data;
private:
};

#endif // IMAGE_H