#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H

#include <unordered_map>
#include <mutex>
#include <string>

#include "Texture2D.h"
#include "Shader.h"

class AssetManager
{
public:
	static AssetManager* GetInstance();

	AssetManager(AssetManager& other) = delete;
	
	void operator=(const AssetManager& other) = delete;

	void LoadTextureFromFile(const char* filepath, const char* name);
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
