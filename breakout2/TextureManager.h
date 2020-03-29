#pragma once
#include "ResourceManager.h"

#include <string>
#include <unordered_map>

#include "texture.h"

class TextureManager
{
public:
	TextureManager();
	~TextureManager();
	void loadResource(const char *file, std::string name);
	void addResource(std::string name, Texture2D *res);
	Texture2D getResource(std::string name);
private:
	std::unordered_map<std::string, Texture2D*> map;
};

