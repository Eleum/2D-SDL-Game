#pragma once
#include "ECS.h"
#include "SDL.h"
#include "TransformComponent.h"

class TileComponent : public Component
{
public:
    TransformComponent *transform;
    SpriteComponent *sprite;
    
    SDL_Rect tileRect;
    int tileID;
    char* path;

    TileComponent() = default;

    TileComponent(int x, int y, int w, int h, int id)
    {
        tileRect.x = x;
        tileRect.y = y;
        tileRect.w = w;
        tileRect.h = h;
        tileID = id;

        switch (tileID)
        {
        case 0:
            path = "assets/tiles/grass.png";
            break;
        case 1:
            path = "assets/tiles/grass-medium.png";
            break;
        case 2:
            path = "assets/tiles/grass-big.png";
            break;
        case 3:
            path = "assets/tiles/flowers.png";
            break;
        case 4:
            path = "assets/tiles/brickWallRed.png";
            break;
		case 5:
			path = "assets/tiles/brickWallBlue.png";
			break;
        }
    }

    void init()
    {
        entity->addComponent<TransformComponent>((float)tileRect.x, (float)tileRect.y, tileRect.w, tileRect.h, 2);
        transform = &entity->getComponent<TransformComponent>();

        entity->addComponent<SpriteComponent>(path);
        sprite = &entity->getComponent<SpriteComponent>();
    }
};