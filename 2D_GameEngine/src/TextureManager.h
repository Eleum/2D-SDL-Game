#pragma once
#include "Game.h"

class TextureManager
{
public:
	static SDL_Texture *LoadTexture(std::string fileName);
	static void Draw(SDL_Texture* text, SDL_Rect src, SDL_Rect dest);
};