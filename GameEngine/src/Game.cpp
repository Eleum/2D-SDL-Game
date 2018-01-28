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

AssetManager* Game::assets = new AssetManager(&manager);

bool Game::isRunning = false;

auto& player(manager.addEntity());
auto& hero(manager.addEntity());

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

	assets->AddTexture("terrain", "assets/map_intro_tileset.png"); 
	assets->AddTexture("player", "assets/animations/rogue.png");
	assets->AddTexture("projectile", "assets/Projectile.png");

	map = new Map("terrain", 2, 16);

	//ESC implementations

	map->LoadMap("assets/map_intro_tilemap.map", 25, 25, 2);

  	player.addComponent<TransformComponent>(2);
	player.addComponent<SpriteComponent>("player", true);
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player");
	player.addGroup(groupPlayers);

    hero.addComponent<TransformComponent>(60, 0, 1);
    hero.addComponent<SpriteComponent>("assets/tiles/mcu.png");
	hero.addGroup(groupPlayers);

	assets->CreateProjectile(Vector2D(200, 100), Vector2D(2, 0), 200, 2, "projectile");
	assets->CreateProjectile(Vector2D(200, 200), Vector2D(2, 0), 200, 2, "projectile");
	assets->CreateProjectile(Vector2D(200, 250), Vector2D(2, 1), 200, 2, "projectile");
	assets->CreateProjectile(Vector2D(200, 300), Vector2D(2, -1), 200, 2, "projectile");
}

auto& tiles(manager.getGroup(Game::groupMap));
auto& players(manager.getGroup(Game::groupPlayers));
auto& colliders(manager.getGroup(Game::groupColliders));
auto& projectiles(manager.getGroup(Game::groupProjectiles));

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
	SDL_Rect playerCollider = player.getComponent<ColliderComponent>().collider;
	Vector2D playerPosition = player.getComponent<TransformComponent>().position;
	
	manager.refresh();
	manager.update();

	for (auto& c : colliders)
	{
		SDL_Rect cCollider = c->getComponent<ColliderComponent>().collider;
		if (Collision::AABB(cCollider, playerCollider))
		{
			player.getComponent<TransformComponent>().position = playerPosition;
		}
	}

	for (auto& p : projectiles)
	{
		if (Collision::AABB(player.getComponent<ColliderComponent>().collider, p->getComponent<ColliderComponent>().collider))
		{
			std::cout << "hit the player" << std::endl;
			p->destroy();
		}
	}

	//minus half of screen's dimensions to make player to be in the middle
	camera.x = player.getComponent<TransformComponent>().position.x - 200; 
	camera.y = player.getComponent<TransformComponent>().position.y - 200;

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
	
	for (auto& c : colliders)
	{
		c->draw();
	}

	for (auto& p : projectiles)
	{
		p->draw();
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