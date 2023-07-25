module;
#include <unordered_map>
#include <mutex>
#include <string>
#include "ft2build.h"
#include FT_FREETYPE_H
export module framework:managers.asset;

import :renderer.texture2d;
import :renderer.shader;

export class Asset_Manager
{
public:
	static Asset_Manager* GetInstance();

	Asset_Manager(Asset_Manager& other) = delete;

	void operator=(const Asset_Manager& other) = delete;

	void LoadTextureFromFile(const char* filepath, const char* name);
	void LoadShaderFromFile(const char* vertexFilepath, const char* fragmentFilePath, const char* name);
	void RemoveTexture(std::string textureName);
	void RemoveShader(std::string shaderName);

	Texture2D* GetTexture(std::string textureName);
	Shader* GetShader(std::string shaderName);

protected:
	static Asset_Manager* instance;
	static std::mutex mutex;

	Asset_Manager();
	~Asset_Manager();

private:
	std::unordered_map<std::string, Texture2D*> textures;
	std::unordered_map<std::string, Shader*> shaders;
};


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

	auto exists = textures.find(name);
	if (exists != textures.end())
	{
		return;
	}

	Texture2D* tTexture = new Texture2D(filepath);

	textures.emplace(std::make_pair(name, tTexture));
}

void Asset_Manager::LoadShaderFromFile(const char* vertexFilepath, const char* fragmentFilePath, const char* name)
{
	std::lock_guard<std::mutex> lock(mutex);

	auto exists = shaders.find(name);
	if (exists != shaders.end())
	{
		return;
	}

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
