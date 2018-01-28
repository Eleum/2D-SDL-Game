#pragma once
#include <iostream>
#include <vector>
#include "SDL.h"
#include "SDL_image.h" 

class AssetManager;
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

	static SDL_Renderer *renderer;
	static SDL_Event event;
	static bool isRunning;
	static SDL_Rect camera;
	static AssetManager* assets;

	enum groupLabels : std::size_t
	{
		groupMap,
		groupPlayers,
		groupColliders,
		groupProjectiles
	};

private:
	int count = 0;
	SDL_Window *window;
};

