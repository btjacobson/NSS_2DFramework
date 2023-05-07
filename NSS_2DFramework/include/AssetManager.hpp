#ifndef ASSET_MANAGER_HPP
#define ASSET_MANAGER_HPP

#include <unordered_map>
#include <mutex>
#include <string>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "Texture2D.hpp"
#include "Shader.hpp"

class AssetManager
{
public:
	static AssetManager* GetInstance();

	AssetManager(AssetManager& other) = delete;
	
	void operator=(const AssetManager& other) = delete;

	void LoadTextureFromFile(const char* filepath, const char* name, int x, int y);
	void LoadShaderFromFile(const char* vertexFilepath, const char* fragmentFilePath, const char* name);
	void RemoveTexture(std::string textureName);
	void RemoveShader(std::string shaderName);

	Texture2D* GetTexture(std::string textureName);
	Shader* GetShader(std::string shaderName);

protected:
	static AssetManager* instance;
	static std::mutex mutex;

	AssetManager();
	~AssetManager();

private:
	std::unordered_map<std::string, Texture2D*> textures;
	std::unordered_map<std::string, Shader*> shaders;
};

#endif
