#ifndef MAPRENDERER_HPP
#define MAPRENDERER_HPP

/// SFML
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/System.hpp"

// TESTING
#include <iostream>

#include "Locator.hpp"

class MapRenderer : public sf::Drawable {
private:
	sf::Sprite *sprite = nullptr;
	sf::Texture *texture = nullptr;
	sf::View *view = nullptr;

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	int tileSize = 10;

	sf::Vector2f toIsometric(sf::Vector2f vector);
	sf::Vector2f normalize(sf::Vector2f vector);

	void drawLine(sf::Vector2f origin);

	void drawNonTiledGrid(sf::Vector2i tileCounts, float tileSize, sf::Vector2i origin);

	void drawSquare(sf::Vector2i origin, float length);


public:
	MapRenderer();
	~MapRenderer();
	void initialize(sf::RenderWindow *renderWindow);
	void clean();

	void renderGrid();

};

#endif
