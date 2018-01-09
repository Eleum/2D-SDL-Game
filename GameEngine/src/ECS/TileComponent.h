#pragma once
#include "ECS.h"
#include "SDL.h"
#include "TransformComponent.h"

class TileComponent : public Component
{
public:
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;

	TileComponent() = default;

    TileComponent(int srcX, int srcY, int xpos, int ypos, const char* path)
    {
		texture = TextureManager::LoadTexture(path);

		srcRect.x = srcX;
		srcRect.y = srcY;
		srcRect.w = srcRect.h = 16;

		destRect.x = xpos;
		destRect.y = ypos;
		destRect.w = destRect.h = 32; //onscreen size of a tile
    }

	~TileComponent()
	{
		SDL_DestroyTexture(texture);
	}

	void draw() override
	{
		TextureManager::Draw(texture, srcRect, destRect, SDL_FLIP_NONE);
	}
};