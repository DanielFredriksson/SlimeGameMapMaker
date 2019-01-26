#ifndef NON_TILED_GRID_MANAGER
#define NON_TILED_GRID_MANAGER

/// SFML
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/System.hpp"

/// IMGUI
#include "imgui.h"
#include "../imgui-sfml-master/imgui-SFML.h"

/*
The NonTiledGridManager is responsible for manging the grid of possible tiles.
It creates the grid upon being initialized with the size and what not, and then
draws this grid with 'drawNonTiledGrid()'
*/
class NonTiledGridManager {
private:
	sf::Vector2i tileCounts;
	sf::Vector2f origin;
	float tileSize;
	
	// Vector math
	sf::Vector2f toIsometric(sf::Vector2f vector);
	sf::Vector2f normalize(sf::Vector2f vector);

	// Processed Grid Data
	void generateGrid();
	sf::Vertex* vertices = nullptr;
	size_t verticeCount;

public:
	NonTiledGridManager();
	~NonTiledGridManager();
	void initialize(sf::Vector2i gridSize, sf::Vector2f origin, float tileSize);
	void clean();
	
	void drawNonTiledGrid();
};



#endif
