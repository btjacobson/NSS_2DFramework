#include "AssetManager.h"

AssetManager* AssetManager::instance = nullptr;
std::mutex AssetManager::mutex;

AssetManager::AssetManager()
{

}

AssetManager::~AssetManager()
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

AssetManager* AssetManager::GetInstance()
{
	std::lock_guard<std::mutex> lock(mutex);

	if (instance == nullptr) 
	{
		instance = new AssetManager();
	}

	return instance;
}

void AssetManager::LoadTextureFromFile(const char* filepath, const char* name)
{
	std::lock_guard<std::mutex> lock(mutex);

	Texture2D* tTexture = new Texture2D(filepath);

	textures.emplace(std::make_pair(name, tTexture));
}

void AssetManager::LoadShaderFromFile(const char* vertexFilepath, const char* fragmentFilePath, const char* name)
{
	std::lock_guard<std::mutex> lock(mutex);

	Shader* tShader = new Shader(vertexFilepath, fragmentFilePath);

	shaders.emplace(std::make_pair(name, tShader));
}

void AssetManager::RemoveTexture(std::string textureName)
{
	std::lock_guard<std::mutex> lock(mutex);

	auto tTexture = textures.find(textureName);
	if (tTexture != textures.end())
	{
		delete tTexture->second;
		textures.erase(tTexture);
	}
}

void AssetManager::RemoveShader(std::string shaderName)
{
	std::lock_guard<std::mutex> lock(mutex);

	auto tShader = shaders.find(shaderName);
	if (tShader != shaders.end())
	{
		delete tShader->second;
		shaders.erase(tShader);
	}
}

Texture2D* AssetManager::GetTexture(std::string textureName)
{
	std::lock_guard<std::mutex> lock(mutex);

	auto tTexture = textures.find(textureName);
	if (tTexture != textures.end())
	{
		return tTexture->second;
	}

	return nullptr;
}

Shader* AssetManager::GetShader(std::string shaderName)
{
	std::lock_guard<std::mutex> lock(mutex);

	auto tShader = shaders.find(shaderName);
	if (tShader != shaders.end())
	{
		return tShader->second;
	}

	return nullptr;
}
