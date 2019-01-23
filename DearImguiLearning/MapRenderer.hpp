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

	void drawSquares() {

	}

	void drawSquare(sf::Vector2i origin, float length) {
		sf::Vector2f currentLinesOrigin;
		sf::Vector2f centre = Locator::getRenderWindow()->getView().getCenter();

		// Cartesian coordinates
		sf::Vector2f cartPoints[4] = {
			sf::Vector2f(origin.x, origin.y),
			sf::Vector2f(origin.x + length, origin.y),
			sf::Vector2f(origin.x + length, origin.y + length),
			sf::Vector2f(origin.x, origin.y + length)
		};
		/*sf::Vector2f cartPoints[4] = {
			sf::Vector2f(25.0f, 25.0f),
			sf::Vector2f(30.0f, 25.0f),
			sf::Vector2f(30.0f, 30.0f),
			sf::Vector2f(25.0f, 30.0f)
		};*/
		sf::Vector2f isoPoints[4] = {
				toIsometric(cartPoints[0]),
				toIsometric(cartPoints[1]),
				toIsometric(cartPoints[2]),
				toIsometric(cartPoints[3]),
		};

		for (int i = 0; i < 4; i++) {
			isoPoints[i].x += 50;
			isoPoints[i].y += 50;
		}

		sf::Vertex lines[8] = {
			sf::Vertex(isoPoints[0], sf::Color::White, sf::Vector2f(0,0)),
			sf::Vertex(isoPoints[1], sf::Color::White, sf::Vector2f(0,0)),
			sf::Vertex(isoPoints[1], sf::Color::White, sf::Vector2f(0,0)),
			sf::Vertex(isoPoints[2], sf::Color::White, sf::Vector2f(0,0)),
			sf::Vertex(isoPoints[2], sf::Color::White, sf::Vector2f(0,0)),
			sf::Vertex(isoPoints[3], sf::Color::White, sf::Vector2f(0,0)),
			sf::Vertex(isoPoints[3], sf::Color::White, sf::Vector2f(0,0)),
			sf::Vertex(isoPoints[0], sf::Color::White, sf::Vector2f(0,0))
		};
		Locator::getRenderWindow()->draw(lines, 8, sf::Lines);





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
		sf::Vector2i origin{
			10,	// Number of x-tiles
			10	// Number of y-tiles
		};
		int length = 10;
		int size = 15;

	//	this->drawSquare(origin, length);


		for (int x = 0; x < size; x++) {
			for (int y = 0; y < size; y++) {
				origin.x = 25 + x * length;
				origin.y = 25 + y * length;
				this->drawSquare(origin, length);
			}
		}
	}

};

#endif
