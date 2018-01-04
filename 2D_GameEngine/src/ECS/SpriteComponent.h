#pragma once
#include "Components.h"
#include "SDL.h"
#include "../TextureManager.h"
#include "Animation.h"
#include <map>

/*ЗАВИСИМОСТИ РАЗМЕРОВ ТЕКСТУР:

Здесь: 
	закомменченные строки

TransformComponent.h: 
	height + width = реальный размер текстуры

Map.cpp:
	число в функции LoadMap = коэффициент для координаты tile

TileComponent.h:
	число в функции init = скейл одного tile

Game.cpp: 
	число в функции AddTile = размер одного tile (всегда 16, НЕ ТРОГАТЬ!)
*/

class SpriteComponent : public Component
{
private:
	TransformComponent *transform;
	SDL_Texture *texture;
	SDL_Rect srcR, destR;

	bool animated = false;
	int frames = 0;
	int speed = 100;

public:
	int animIndex = 0;
	std::map<const char*, Animation> animations;

	SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

	SpriteComponent() = default;
	SpriteComponent(const char* path)
	{
		setTex(path);
		//SDL_QueryTexture(texture, NULL, NULL, &tw, &th);
	}

	SpriteComponent(const char* path, bool isAnimated)
	{	
		animated = isAnimated;

		Animation idle = Animation(0, 10, 100);
		Animation gesture = Animation(1, 10, 100);
		Animation walk = Animation(2, 10, 100);
	
		animations.emplace("idle", idle);
		animations.emplace("gesture", gesture);
		animations.emplace("walk", walk);

		play("idle");

		setTex(path);
		//SDL_QueryTexture(texture, NULL, NULL, &tw, &th);
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
        srcR.w = transform->getWidth(); //tw
        srcR.h = transform->getHeigth(); //th		
	}

	void update() override
	{
		if (animated)
		{
			srcR.x = srcR.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
		}

		srcR.y = animIndex * transform->getHeigth();

		destR.x = static_cast<int>(transform->position.x);
		destR.y = static_cast<int>(transform->position.y);
        destR.w = transform->getWidth() * transform->getScale(); //srcR.w
        destR.h = transform->getHeigth() * transform->getScale(); //srcR.h
	}

	void draw() override
	{
		TextureManager::Draw(texture, srcR, destR, spriteFlip);
	}

	void play(const char* animName)
	{
		frames = animations[animName].frames;
		animIndex = animations[animName].index;
		speed = animations[animName].speed;
	}
};
