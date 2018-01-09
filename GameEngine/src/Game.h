#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "SDL_image.h"
#include "SDL.h"

class ColliderComponent;

class Game
{
public: 
	Game() {}
	~Game() {}

	void init(std::string title, int xpos, int ypos, int width, int height, bool fullScreen);
	
	void handleEvents();
	void update();
	void render();
	void clean();
	bool running() { return isRunning; }

    static void AddTile(int srcX, int srcY, int xpos, int ypos);

	static SDL_Renderer *renderer;
	static SDL_Event event;
    static std::vector<ColliderComponent*> colliders;

private:
	int count = 0;
	bool isRunning;
	SDL_Window *window;
};

