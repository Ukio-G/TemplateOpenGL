#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <string>
#include "TextureParameters.hpp"


class Texture {
public:
	Texture(const std::string & path);
	Texture(const std::string & path, const TextureParameters &parameters);
	unsigned int id;
	std::string path;
	TextureParameters parameters;
	int width;
	int height;
	int numChannels;
	unsigned char *data;

	void init();
	void bind();
};


#endif
