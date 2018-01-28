#pragma once
#include "ECS.h"
#include "Components.h"
#include "../Vector2D.h"

class ProjectileComponent : public Component
{
private:
	TransformComponent* transform;
	int _range = 0, _speed = 0, _distance = 0;
	Vector2D _velocity;

public:
	ProjectileComponent(int range, int speed, Vector2D velocity) : _range(range), _speed(speed), _velocity(velocity) {}

	~ProjectileComponent() {}

	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
		transform->velocity = _velocity;
	}
	
	void update() override 
	{
		_distance += _speed;

		if (_distance > _range)
		{
			std::cout << "Out of range" << std::endl;
			entity->destroy();
		}
		else if(transform->position.x > Game::camera.x + Game::camera.w || 
			transform->position.x < Game::camera.x ||
			transform->position.y > Game::camera.y + Game::camera.h || 
			transform->position.y < Game::camera.y)
		{
			std::cout << "Out of bounds" << std::endl;
			entity->destroy();
		}
	}
};
