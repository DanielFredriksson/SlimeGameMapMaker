#ifndef MAPRENDERER_HPP
#define MAPRENDERER_HPP

/// SFML
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/System.hpp"

/// INTERNAL
#include "GridManager.h"

// TESTING
#include <iostream>

#include "Locator.hpp"

class MapRenderer : public sf::Drawable {
private:
	GridManager gridManager;
	sf::Sprite *sprite = nullptr;
	sf::Texture *texture = nullptr;
	sf::View *view = nullptr;

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	int tileSize = 10;

	void initializeView(sf::RenderWindow *renderWindow);
	void drawLine(sf::Vector2f origin);

public:
	MapRenderer();
	~MapRenderer();
	void initialize(sf::RenderWindow *renderWindow);
	void clean();


	void renderGrid();
	void renderNonTiledGrid();

};

#endif
