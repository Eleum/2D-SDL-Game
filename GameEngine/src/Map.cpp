#include <fstream>
#include "Map.h"
#include "Game.h"
#include "ECS/ECS.h"
#include "ECS/Components.h"

extern Manager manager;

Map::Map(std::string textureId, int mapScale, int tileSize) : _textureId(textureId), 
_mapScale(mapScale), _tileSize(tileSize) 
{
	_scaledSize = tileSize * mapScale;
}

void Map::LoadMap(std::string path, int sizeX, int sizeY, int layerCount)
{
    char c;
    std::fstream mapFile;
    mapFile.open(path);
    
	int srcX, srcY;

	for (int layer = 0; layer < layerCount; layer++)
	{
		for (int y = 0; y < sizeY; y++)
		{
			for (int x = 0; x < sizeX; x++)
			{
				mapFile.get(c);
				if (c == '-')
				{
					mapFile.ignore();
					mapFile.ignore();
					continue;
				}
				srcY = atoi(&c) * _tileSize;
				mapFile.get(c);
				srcX = atoi(&c) * _tileSize;
				//the bigger the number - the bigger the space between cells
				AddTile(srcX, srcY, x * _scaledSize, y * _scaledSize);
				mapFile.ignore();
			}
		}
	}

	for (int y = 0; y < sizeY; y++)
	{
		for (int x = 0; x < sizeX; x++)
		{
			mapFile.get(c);
			if (c == '1')
			{
				auto& tcol(manager.addEntity());
				tcol.addComponent<ColliderComponent>("terrain", x * _scaledSize, y * _scaledSize, _scaledSize);
				tcol.addGroup(Game::groupColliders);
			}
			mapFile.ignore();
		}
	}

    mapFile.close();
}

void Map::AddTile(int srcX, int srcY, int xpos, int ypos)
{
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(srcX, srcY, xpos, ypos, _tileSize, _mapScale, _textureId);
	tile.addGroup(Game::groupMap);
}
