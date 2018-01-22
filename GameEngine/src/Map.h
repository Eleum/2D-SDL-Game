#pragma once
#include <string>

class Map
{
private:
	const char* _mapFilePath;
	int _mapScale, _tileSize, _scaledSize;

public:
	Map(const char* mapFilePath, int mapScale, int tileSize);
	~Map() {};

    void LoadMap(std::string path, int sizeX, int sizeY, int layerCount);
	void AddTile(int srcX, int srcY, int xpos, int ypos);
};
