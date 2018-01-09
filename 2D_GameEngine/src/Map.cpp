#include <fstream>
#include "Map.h"
#include "Game.h"

Map::Map() {}

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
				srcY = atoi(&c) * 16;
				mapFile.get(c);
				srcX = atoi(&c) * 16;
				//the bigger the number - the bigger the space between cells
				Game::AddTile(srcX, srcY, x * 32, y * 32);
				mapFile.ignore();
			}
		}
	}
    mapFile.close();
}
