#pragma once

#include <string>
#include <unordered_map>

template <class T>
class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();
	virtual void loadResource(const char *file, std::string name) = 0;
	virtual void addResource(std::string name, T res) = 0;
	virtual T getResource(std::string name) = 0;
protected:
};