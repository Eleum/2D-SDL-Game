#pragma once
#include <map>
#include "SDL.h"
#include "Components.h"
#include "Animation.h"
#include "../TextureManager.h"
#include "../AssetManager.h"

/*����������� �������� �������:

�����: 
	�������������� ������

TransformComponent.h: 
	height + width = �������� ������ ��������

Map.cpp:
	����� � ������� LoadMap = ����������� ��� ���������� tile

TileComponent.h:
	����� � ������� init = ����� ������ tile

Game.cpp: 
	����� � ������� AddTile = ������ ������ tile (������ 16, �� �������!)
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
	SpriteComponent(std::string id)
	{
		setTex(id);
		//SDL_QueryTexture(texture, NULL, NULL, &tw, &th);
	}

	SpriteComponent(std::string id, bool isAnimated)
	{	
		animated = isAnimated;

		Animation idle = Animation(0, 10, 100);
		Animation gesture = Animation(1, 10, 100);
		Animation walk = Animation(2, 10, 100);
	
		animations.emplace("idle", idle);
		animations.emplace("gesture", gesture);
		animations.emplace("walk", walk);

		play("idle");

		setTex(id);
		//SDL_QueryTexture(texture, NULL, NULL, &tw, &th);
	}

	~SpriteComponent()
	{
		
	}

	void setTex(std::string id)
	{
		texture = Game::assets->GetTexture(id);
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
			srcR.y = animIndex * transform->getHeigth();
		}

		destR.x = static_cast<int>(transform->position.x) - Game::camera.x;
		destR.y = static_cast<int>(transform->position.y) - Game::camera.y;
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
