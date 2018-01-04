#pragma once

struct Animation
{
	int index;
	int frames;
	int speed;

	Animation() {}
	
	Animation(int _index, int _frames, int _speed)
	{
		index = _index;
		frames = _frames;
		speed = _speed;
	}
};
