#pragma once
#include "Components.h"
#include "SDL.h"
#include "../TextureManager.h"

class SpriteComponent : public Component
{
private:
	TransformComponent *transform;
	SDL_Texture *texture;
	int tw, th;
	SDL_Rect srcR, destR;

	bool animated = false;
	int frames = 0;
	int speed = 100;

public:
	SpriteComponent() = default;
	SpriteComponent(const char* path)
	{
		/*texture = TextureManager::LoadTexture(path);
		SDL_QueryTexture(texture, NULL, NULL, &tw, &th);*/
		setTex(path);
	}

	SpriteComponent(const char* path, int nFrames, int mSpeed)
	{
		/*texture = TextureManager::LoadTexture(path);
		SDL_QueryTexture(texture, NULL, NULL, &tw, &th);*/
		animated = true;
		frames = nFrames;
		speed = mSpeed;
		setTex(path);
	}

	~SpriteComponent()
	{
		SDL_DestroyTexture(texture);
	}

	void setTex(const char* path)
	{
		texture = TextureManager::LoadTexture(path);
	}

	void init() override
	{
	    transform = &entity->getComponent<TransformComponent>();
		
		srcR.x = srcR.y = 0;
        srcR.w = tw;//transform->getWidth();
        srcR.h = th;//transform->getHeigth();
		
	}

	void update() override
	{
		if (animated)
		{
			srcR.x = srcR.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
		}
		destR.x = static_cast<int>(transform->position.x);
		destR.y = static_cast<int>(transform->position.y);
        destR.w = srcR.w * transform->getScale();
        destR.h = srcR.h * transform->getScale();
	}

	void draw() override
	{
		TextureManager::Draw(texture, srcR, destR);
	}

	int getHeigth()
	{
		return th;
	}

	int getWidth()
	{
		return tw;
	}
};
