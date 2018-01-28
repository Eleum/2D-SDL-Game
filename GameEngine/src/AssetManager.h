#pragma once
#include <map>
#include <string>
#include "SDL.h"
#include "ECS\ECS.h"
#include "Vector2D.h"
#include "TextureManager.h"

class AssetManager
{
private:
	Manager* _manager;
	std::map<std::string, SDL_Texture*> textures;

public:
	AssetManager(Manager* manager);
	~AssetManager();

	// game objects
	void CreateProjectile(Vector2D pos, Vector2D velocity, int range, int speed, std::string id);

	// texture management
	void AddTexture(std::string id, const char* path);
	SDL_Texture* GetTexture(std::string id);
};