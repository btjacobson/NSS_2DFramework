#include "AssetManager.hpp"

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
	instance = nullptr;
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

void AssetManager::LoadTextureFromFile(const char* filepath, const char* name, int x, int y)
{
	int width;
	int height;
	int channels;

	unsigned char* data = stbi_load(filepath, &width, &height, &channels, STBI_rgb_alpha);
	unsigned char* data2 = stbi_load(filepath, &width, &height, &channels, STBI_rgb_alpha);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture: " << filepath << std::endl;
	}

	Texture2D* tTexture = new Texture2D(x, y, data);
	stbi_image_free(data);

	textures.emplace(std::make_pair(name, tTexture));
}

void AssetManager::LoadShaderFromFile(const char* vertexFilepath, const char* fragmentFilePath, const char* name)
{
	Shader* tShader = new Shader(vertexFilepath, fragmentFilePath);

	shaders.emplace(std::make_pair(name, tShader));
}

void AssetManager::RemoveTexture(std::string textureName)
{
	auto tTexture = textures.find(textureName);
	if (tTexture != textures.end())
	{
		delete tTexture->second;
		textures.erase(tTexture);
	}
}

void AssetManager::RemoveShader(std::string shaderName)
{
	auto tShader = shaders.find(shaderName);
	if (tShader != shaders.end())
	{
		delete tShader->second;
		shaders.erase(tShader);
	}
}

Texture2D* AssetManager::GetTexture(std::string textureName)
{
	auto tTexture = textures.find(textureName);
	if (tTexture != textures.end())
	{
		return tTexture->second;
	}

	return nullptr;
}

Shader* AssetManager::GetShader(std::string shaderName)
{
	auto tShader = shaders.find(shaderName);
	if (tShader != shaders.end())
	{
		return tShader->second;
	}

	return nullptr;
}
