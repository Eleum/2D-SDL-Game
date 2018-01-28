#include "AssetManager.h"
#include "ECS/Components.h"

AssetManager::AssetManager(Manager* manager) : _manager(manager)
{
}

AssetManager::~AssetManager() 
{
}

void AssetManager::CreateProjectile(Vector2D pos, Vector2D velocity, int range, int speed, std::string id)
{
	auto& projectile(_manager->addEntity());

	projectile.addComponent<TransformComponent>(pos.x, pos.y, 16, 16, 2);
	projectile.addComponent<SpriteComponent>(id, false);
	projectile.addComponent<ProjectileComponent>(range, speed, velocity);
	projectile.addComponent<ColliderComponent>("projectile");
	projectile.addGroup(Game::groupProjectiles);
}

void AssetManager::AddTexture(std::string id, const char* path)
{
	textures.emplace(id, TextureManager::LoadTexture(path));
}

SDL_Texture* AssetManager::GetTexture(std::string id)
{
	return textures[id];
}