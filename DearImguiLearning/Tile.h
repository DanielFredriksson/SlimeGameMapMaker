#ifndef TILE_H
#define TILE_H

/// SFML
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/System.hpp"

/*
The Tile class is responsible for its own appearance as an object as well as information
regarding everything that resides on it.

*/


struct SFMLData {
	sf::Texture texture;
	sf::Sprite sprite;
};

class Tile {
private:
	// Contains all relevant SFML data
	SFMLData sfData;
	// Contains all data about which static objects reside on it.
	/// std::vector<staticObjectClass*> occupants;
	// Contains all data about which dynamic objects reside on it.
	/// std::vector<dynamicObjectClass*> occupants;
	// Contains wether the player is on the tile or not.
	/// bool isPlayerOn?
	// Contains all data about this tile's position in the world.
	/// worldData wData;

public:
	Tile();
	~Tile();
};


#endif
