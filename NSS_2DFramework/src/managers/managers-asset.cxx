module;
#include "ft2build.h"
#include FT_FREETYPE_H
#include <unordered_map>
#include <mutex>
#include <string>
#include <filesystem>
#include <ranges>
#include <iostream>
export module framework:managers.asset;

import <compare>;

import :renderer.texture2d;
import :renderer.shader;

export class Asset_Manager
{
public:
	static Asset_Manager* GetInstance();

	Asset_Manager(Asset_Manager& other) = delete;

	void operator=(const Asset_Manager& other) = delete;
	void operator=(const Asset_Manager&& other) = delete;

	void LoadTextureFromFile(const std::filesystem::path &filePath, const std::string &name);
	void LoadShaderFromFile(const std::filesystem::path &vertPath, const std::filesystem::path &fragPath,const std::string &name);
	void LoadAllShaders(const std::filesystem::path &shaderDirectory);
	void RemoveTexture(const std::string &textureName);
	void RemoveShader(const std::string &shaderName);

	Texture2D* GetTexture(const std::string &textureName);
	Shader* GetShader(const std::string &shaderName);

protected:
	static Asset_Manager* instance;
	static std::mutex mutex;

	Asset_Manager();
	~Asset_Manager();

private:
	std::unordered_map<std::string, std::unique_ptr<Texture2D>> textures;
	std::unordered_map<std::string, std::unique_ptr<Shader>> shaders;
};


Asset_Manager* Asset_Manager::instance = nullptr;
std::mutex Asset_Manager::mutex;

Asset_Manager::Asset_Manager()
{

}

Asset_Manager::~Asset_Manager()
{
	textures.clear();
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

void Asset_Manager::LoadTextureFromFile(const std::filesystem::path& filepath, const std::string& name)
{
	std::lock_guard<std::mutex> lock(mutex);

	auto exists = textures.find(name);
	if (exists != textures.end())
	{
		return;
	}

	std::unique_ptr<Texture2D> tTexture{std::make_unique<Texture2D>(filepath)};

	textures.try_emplace(name, std::move(tTexture));
}

void Asset_Manager::LoadShaderFromFile(const std::filesystem::path& vertexFilepath, const std::filesystem::path& fragmentFilepath, const std::string& name)
{
	std::lock_guard<std::mutex> lock(mutex);

	auto exists = shaders.find(name);
	if (exists != shaders.end())
	{
		return;
	}

	std::unique_ptr<Shader> tShader{ std::make_unique<Shader>(vertexFilepath, fragmentFilepath) };

	shaders.try_emplace(name, std::move(tShader));
}

void Asset_Manager::LoadAllShaders(const std::filesystem::path& shaderDirectory)
{
	auto absolutePath{ std::filesystem::current_path() / shaderDirectory };
	auto shaderFilter{[](std::filesystem::directory_entry file) {return file.path().extension().string() == ".vert";}};
	for (auto&& file : std::filesystem::recursive_directory_iterator(absolutePath) | std::views::filter(shaderFilter)) //skips all non .vert files, assumes vert shaders have their counterpart
	{
		auto shaderName{file.path().stem().string()};
		LoadShaderFromFile(absolutePath / (shaderName + ".vert"), absolutePath / (shaderName + ".frag"), shaderName);
	}
}

void Asset_Manager::RemoveTexture(const std::string &textureName)
{
	std::lock_guard<std::mutex> lock(mutex);

	auto tTexture = textures.find(textureName);
	if (tTexture != textures.end())
	{
		textures.erase(tTexture);
	}
}

void Asset_Manager::RemoveShader(const std::string &shaderName)
{
	std::lock_guard<std::mutex> lock(mutex);

	auto tShader = shaders.find(shaderName);
	if (tShader != shaders.end())
	{
		shaders.erase(tShader);
	}
}

Texture2D* Asset_Manager::GetTexture(const std::string &textureName)
{
	std::lock_guard<std::mutex> lock(mutex);

	auto tTexture = textures.find(textureName);
	if (tTexture != textures.end())
	{
		return tTexture->second.get();
	}

	return nullptr;
}

Shader* Asset_Manager::GetShader(const std::string &shaderName)
{
	std::lock_guard<std::mutex> lock(mutex);

	auto tShader = shaders.find(shaderName);
	if (tShader != shaders.end())
	{
		return tShader->second.get();
	}

	return nullptr;
}
