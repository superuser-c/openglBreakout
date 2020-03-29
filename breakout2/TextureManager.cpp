#include "TextureManager.h"

//#define STB_IMAGE_IMPLEMENTATION
//#include "stb_image.h"
#include <SOIL.h>

#include "flog.h"

TextureManager::TextureManager()
{
}

TextureManager::~TextureManager()
{
}

void TextureManager::loadResource(const char *file, std::string name)
{
	Texture2D texture;
	texture.Internal_Format = GL_RGBA8;
	texture.Image_Format = GL_RGBA;
	// Load image
	int width, height;
	unsigned char* image = SOIL_load_image(file, &width, &height, 0, SOIL_LOAD_RGBA);
	// Now generate texture
	texture.Generate(width, height, image);
	// And finally free image data
	SOIL_free_image_data(image);
	map[name] = &texture;
}

void TextureManager::addResource(std::string name, Texture2D *res)
{
	map[name] = res;
}

Texture2D TextureManager::getResource(std::string name)
{
	return *map[name];
}
