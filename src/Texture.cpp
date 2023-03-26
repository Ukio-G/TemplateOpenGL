#if defined(__APPLE__)
	#include <OpenGL/gl.h>
#else
	#include <GL/gl.h>
#endif

#include <stdexcept>
#include "Texture.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture(const std::string &path) : path(path) {
	init();
}

Texture::Texture(const std::string &path, const TextureParameters &parameters) : path(path), parameters(parameters) {
	init();
}

void Texture::init() {
	stbi_set_flip_vertically_on_load(true);
	data = stbi_load(path.c_str(), &width, &height, &numChannels, 0);

	if (!data)
		throw std::runtime_error("Failed to load texture: " + path);

	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);

	parameters.apply();

	glTexImage2D(GL_TEXTURE_2D, // The first argument specifies the texture target; (targets GL_TEXTURE_1D or GL_TEXTURE_3D will not be affected)
				0, // mipmap level for which we want to create a texture
				GL_RGB,  // kind of format we want to store the texture
				width,
				height,
				0, // legacy
				GL_RGB, // loaded the image with RGB values (from RAM)
				GL_UNSIGNED_BYTE, // loaded data in UNSIGNED 1 byte format
				data);

	stbi_image_free(data);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::bind() {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, id);
}


