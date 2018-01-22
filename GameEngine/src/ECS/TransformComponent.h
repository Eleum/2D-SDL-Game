#pragma once
#include "Components.h"
#include "../Vector2D.h"

class TransformComponent : public Component
{
private:
    //TODO: somehow change values of h and w for the values of the pic
	//do i really need to do this tho...
	int height = 32;
	int width = 32;
	int scale = 1;
	int speed = 2;

public:
	Vector2D position;
	Vector2D velocity;

	TransformComponent()
	{
        position.zero();
	}

	TransformComponent(int _scale)
	{
		position.x = 96;
		position.y = 64;
		scale = _scale;
	}

	TransformComponent(float x, float y)
	{
		position.x = x;
		position.y = y;
	}

    TransformComponent(float x, float y, int scale)
    {
        position.x = x;
        position.y = y;
        this->scale = scale;
    }

	TransformComponent(float x, float y, int h, int w, int scale)
	{
		position.x = x;
		position.y = y;
		height = h;
		width = w;
		this->scale = scale;
	}

	void init() override
	{
        velocity.zero();
	}

	void update() override
	{
		position.x += velocity.x * speed;
		position.y += velocity.y * speed;
	}

	int getHeigth()
	{
		return height;
	}

	int getWidth()
	{
		return width;
	}

    void setScale(int scale)
    {
        this->scale = scale;
    }

	int getScale()
	{
		return scale;
	}

	int getSpeed()
	{
		return speed;
	}
};
