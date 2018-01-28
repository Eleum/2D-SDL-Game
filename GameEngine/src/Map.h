#pragma once
#include <string>

class Map
{
private:
	std::string _textureId;
	int _mapScale, _tileSize, _scaledSize;

public:
	Map(std::string textureId, int mapScale, int tileSize);
	~Map() {};

    void LoadMap(std::string path, int sizeX, int sizeY, int layerCount);
	void AddTile(int srcX, int srcY, int xpos, int ypos);
};
