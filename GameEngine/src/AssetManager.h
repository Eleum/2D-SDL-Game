#pragma once
#include <map>
#include <string>
#include "SDL.h"
#include "ECS\ECS.h"
#include "Vector2D.h"
#include "TextureManager.h"
#include "SDL_ttf.h"

class AssetManager
{
private:
	Manager* _manager;
	std::map<std::string, SDL_Texture*> textures;
	std::map<std::string, TTF_Font*> fonts;

public:
	AssetManager(Manager* manager);
	~AssetManager();

	// game objects
	void CreateProjectile(Vector2D pos, Vector2D velocity, int range, int speed, std::string id);

	// texture management
	void AddTexture(std::string id, const char* path);
	SDL_Texture* GetTexture(std::string id);

	void AddFont(std::string id, std::string path, int fontSize);
	TTF_Font* GetFont(std::string id);
};