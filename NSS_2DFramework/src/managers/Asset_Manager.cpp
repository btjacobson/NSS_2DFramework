#include "managers/Asset_Manager.h"

Asset_Manager* Asset_Manager::instance = nullptr;
std::mutex Asset_Manager::mutex;

Asset_Manager::Asset_Manager()
{

}

Asset_Manager::~Asset_Manager()
{
	for (auto textureItr = textures.begin(); textureItr != textures.end(); textureItr++)
	{
		delete textureItr->second;
	}
	textures.clear();

	for (auto shaderItr = shaders.begin(); shaderItr != shaders.end(); shaderItr++)
	{
		delete shaderItr->second;
	}
	shaders.clear();

	delete instance;
}

Asset_Manager* Asset_Manager::GetInstance()
{
	std::lock_guard<std::mutex> lock(mutex);

	if (instance == nullptr) 
	{
		instance = new Asset_Manager();
	}

	return instance;
}

void Asset_Manager::LoadTextureFromFile(const char* filepath, const char* name)
{
	std::lock_guard<std::mutex> lock(mutex);

	Texture2D* tTexture = new Texture2D(filepath);

	textures.emplace(std::make_pair(name, tTexture));
}

void Asset_Manager::LoadShaderFromFile(const char* vertexFilepath, const char* fragmentFilePath, const char* name)
{
	std::lock_guard<std::mutex> lock(mutex);

	Shader* tShader = new Shader(vertexFilepath, fragmentFilePath);

	shaders.emplace(std::make_pair(name, tShader));
}

void Asset_Manager::RemoveTexture(std::string textureName)
{
	std::lock_guard<std::mutex> lock(mutex);

	auto tTexture = textures.find(textureName);
	if (tTexture != textures.end())
	{
		delete tTexture->second;
		textures.erase(tTexture);
	}
}

void Asset_Manager::RemoveShader(std::string shaderName)
{
	std::lock_guard<std::mutex> lock(mutex);

	auto tShader = shaders.find(shaderName);
	if (tShader != shaders.end())
	{
		delete tShader->second;
		shaders.erase(tShader);
	}
}

Texture2D* Asset_Manager::GetTexture(std::string textureName)
{
	std::lock_guard<std::mutex> lock(mutex);

	auto tTexture = textures.find(textureName);
	if (tTexture != textures.end())
	{
		return tTexture->second;
	}

	return nullptr;
}

Shader* Asset_Manager::GetShader(std::string shaderName)
{
	std::lock_guard<std::mutex> lock(mutex);

	auto tShader = shaders.find(shaderName);
	if (tShader != shaders.end())
	{
		return tShader->second;
	}

	return nullptr;
}
