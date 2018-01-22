#pragma once
#include "ECS.h"
#include "SDL.h"
#include "TransformComponent.h"

class TileComponent : public Component
{
public:
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;
	Vector2D position;
	 
	TileComponent() = default;

    TileComponent(int srcX, int srcY, int xpos, int ypos, int tsize, int tscale, const char* path)
    {
		texture = TextureManager::LoadTexture(path);

		position.x = xpos;
		position.y = ypos;

		srcRect.x = srcX;
		srcRect.y = srcY;
		srcRect.w = srcRect.h = tsize;

		destRect.x = xpos;
		destRect.y = ypos;
		destRect.w = destRect.h = tsize * tscale; //onscreen size of a tile
    }

	~TileComponent()
	{
		SDL_DestroyTexture(texture);
	}

	void update() override
	{
		destRect.x = position.x - Game::camera.x;
		destRect.y = position.y - Game::camera.y;
	}

	void draw() override
	{
		TextureManager::Draw(texture, srcRect, destRect, SDL_FLIP_NONE);
	}
};