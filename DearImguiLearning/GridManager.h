#ifndef GRIDMANAGER_H
#define GRIDMANAGER_H

#include "Tile.h"
/*
The GridManager class is responsible for dealing with every tile that exists!
Currently it only tests rendering a tile!
*/

struct Grid {
	// Data
	Tile** tiles = nullptr;
	sf::Vector2f origin;
	sf::Vector2i tileCounts;
	float tileSize;

	// Render Data
	sf::Vertex* vertices = nullptr;
	size_t verticeCount;

	// Utilities
	void clean() {
		delete this->vertices;
	}
};

class GridManager {
private:
	// Grid
	Grid grid;
	Tile testTile;	// Textured

	// Vector-Math
	sf::Vector2f toIsometric(sf::Vector2f vector);
	sf::Vector2f normalize(sf::Vector2f vector);

	// Test Functions
	void generateGrid();

	// 


public:
	GridManager();
	~GridManager();
	void initialize(sf::Vector2i gridSize, sf::Vector2f origin, float tileSize);
	void clean();

	void test();
	void testRenderVoidTiles();
	void renderCurrentGrid();

};



#endif