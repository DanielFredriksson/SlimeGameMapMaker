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

	sf::Vector2f toIsometric(sf::Vector2f vector) {
		sf::Vector2f output = {
			vector.x - vector.y,
			(vector.x + vector.y) * 0.5f
		};
		
		return output;
	}

	void drawLine(sf::Vector2f origin) {
		sf::RectangleShape line(sf::Vector2f(
			10.0f,
			0.5f
		));
		line.setPosition(Locator::getRenderWindow()->mapPixelToCoords(sf::Vector2i(origin)));
		
		Locator::getRenderWindow()->draw(line);
	}

	void drawSquare(sf::Vector2i tiles) {
		sf::Vector2f currentLinesOrigin;
		sf::Vector2f centre = Locator::getRenderWindow()->getView().getCenter();

		// Where is the origin?
		// Make it, Flip it.
		// Render it.

		for (int x = 0; x < tiles.x; x++) {
			for (int y = 0; y < tiles.y; y++) {
				currentLinesOrigin.x = centre.x + (x * this->tileSize);
				currentLinesOrigin.y = centre.y + (y * this->tileSize);
				this->drawLine(currentLinesOrigin);
			}
		}
	}


public:
	MapRenderer();
	~MapRenderer();
	void initialize(sf::RenderWindow *renderWindow) {
		this->view = new sf::View();

		view->reset(sf::FloatRect(
			0.0f,		// Origin-X
			0.0f,		// Origin-Y
			200.0f,		// Size-X
			200.0f		// Size-Y
		));
		view->setViewport(sf::FloatRect(
			0.0f,		// Origin-X
			0.0f,		// Origin-Y
			1.0f,		// Percentage-X
			1.0f		// Percentage-Y
		));
		renderWindow->setView(*view);
	}
	void clean() {
		delete this->view;
	}

	void renderGrid() {
		sf::Vector2i tileCount{
			10,	// Number of x-tiles
			10	// Number of y-tiles
		};



		sf::Vector2f center = this->view->getCenter();
		this->drawSquare(tileCount);

		//this->drawSquare(5, 5);
	}

};

#endif
