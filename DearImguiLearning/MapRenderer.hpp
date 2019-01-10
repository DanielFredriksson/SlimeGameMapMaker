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
	sf::Sprite *sprite;
	sf::Texture *texture;
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

	sf::Vector2f toIsometric(sf::Vector2f vector) {
		sf::Vector2f output = {
			vector.x - vector.y,
			(vector.x + vector.y) * 0.5f
		};
		
		return output;
	}

	void drawLine(int originX, int originY) {
		sf::Vector2f rectLine(100, 1);
		sf::RectangleShape line(rectLine);
		line.setOrigin(Locator::getRenderWindow()->mapPixelToCoords(sf::Vector2i(rectLine)));
		
		Locator::getRenderWindow()->draw(line);
	}

	void drawSquare() {
		


	}


public:
	MapRenderer();
	~MapRenderer();

	void renderGrid() {

		for (int i = 0; i < 10; i++) {
			this->drawLine(0, 30 * i);
		}


	}


};

#endif
