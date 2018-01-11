#include "Game.h"
#include "Collision.h"
#include "ECS/Components.h"
#include "Map.h"

Manager manager;
Map *map;

SDL_Renderer* Game::renderer = nullptr;

SDL_Event Game::event;

//last two numbers are the actual size of map (25x16px)
SDL_Rect Game::camera = { 0, 0, 400, 400 }; 

std::vector<ColliderComponent*> Game::colliders;

bool Game::isRunning = false;

auto& player(manager.addEntity());
auto& hero(manager.addEntity());
auto& wall(manager.addEntity());

const char* mapFile = "assets/map_intro_tileset.png";

enum groupLabels : std::size_t
{
	groupMap,
	groupPlayers,
	groupEnemies,
	groupColliders
};

auto& tiles(manager.getGroup(groupMap));
auto& players(manager.getGroup(groupPlayers));
auto& enemies(manager.getGroup(groupEnemies));

void Game::init(std::string title, int xpos, int ypos, int width, int height, bool fullScreen)
{
	int flags = 0;

	if (fullScreen) flags = SDL_WINDOW_FULLSCREEN;

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Subsystems initialized..." << std::endl; 

		window = SDL_CreateWindow(title.c_str(), xpos, ypos, width, height, flags);
		if (window)
		{
			std::cout << "Window created!" << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "Renderer created!" << std::endl;
		}

		isRunning = true;
	}
	else
	{
		isRunning = false;
	}

	map = new Map();

	//ESC implementations

	Map::LoadMap("assets/map_intro_tilemap.map", 25, 25, 2);

  	player.addComponent<TransformComponent>(2);
    player.addComponent<SpriteComponent>("assets/animations/rogue.png", true);
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player");
	player.addGroup(groupPlayers);

    hero.addComponent<TransformComponent>(60, 0, 1);
    hero.addComponent<SpriteComponent>("assets/tiles/mcu.png");
	hero.addGroup(groupPlayers);
}

void Game::handleEvents()
{
	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	default: 
		break;
	}
}

void Game::update()
{
	manager.refresh();
	manager.update();

	//minus half of screen's dimensions to make player to be in the middle
	camera.x = player.getComponent<TransformComponent>().position.x - 200; 
	camera.y = player.getComponent<TransformComponent>().position.y - 200;

	/*std::cout << "Camera X: " << camera.x << std::endl;
	std::cout << "Player X: " << player.getComponent<TransformComponent>().position.x << std::endl;
	std::cout << "Camera Y: " << camera.y << std::endl;
	std::cout << "Player Y: " << player.getComponent<TransformComponent>().position.y << std::endl;*/

	if (camera.x < 0) 
		camera.x = 0;
	if (camera.y < 0)
		camera.y = 0;
	if (camera.x > camera.w)
		camera.x = camera.w;
	if (camera.y > camera.h)
		camera.y = camera.h;
}

void Game::render()
{
	SDL_RenderClear(renderer);
	for (auto& t : tiles)
	{
		t->draw();
	}
	for (auto& p : players)
	{
		p->draw();
	}
	for (auto& e : enemies)
	{
		e->draw();
	}
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game cleaned!" << std::endl;
}

void Game::AddTile(int srcX, int srcY, int xpos, int ypos)
{
    auto& tile(manager.addEntity());
    tile.addComponent<TileComponent>(srcX, srcY, xpos, ypos, mapFile);
	tile.addGroup(groupMap);
}