#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H

#include <unordered_map>
#include <mutex>
#include <string>

#include "renderer/Texture2D.h"
#include "renderer/Shader.h"

class Asset_Manager
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

#endif
