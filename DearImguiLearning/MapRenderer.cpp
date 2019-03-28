#include "MapRenderer.h"
#include <math.h>

void MapRenderer::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	// Draw shit yo.
	target.draw(*this->sprite, states);
}

MapRenderer::MapRenderer()
{
	this->sprite = new sf::Sprite();
	this->texture = new sf::Texture();

	std::string filePath = "../slimeTrail.png";
	std::string fileName = "slime";

	if (!texture->loadFromFile(filePath.c_str()))
		std::cout << "ERROR: " << fileName.c_str() << " failed to load!";
	else
		this->sprite->setTexture(*texture);

	this->sprite->setPosition(100, 100);
	this->sprite->setScale(2.0f, 2.0f);
}

MapRenderer::~MapRenderer()
{
	delete this->sprite;
	delete this->texture;
}

void MapRenderer::initializeView(sf::RenderWindow *renderWindow)
{
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

void MapRenderer::drawLine(sf::Vector2f origin)
{
	sf::RectangleShape line(sf::Vector2f(
		10.0f,	// Height
		0.5f	// Width
	));
	line.setPosition((*Locator::getRenderWindow())->mapPixelToCoords(sf::Vector2i(origin)));

	(*Locator::getRenderWindow())->draw(line);
}

void MapRenderer::initialize(sf::RenderWindow *renderWindow)
{
	// Initialize View!
	this->initializeView(renderWindow);

	// Initialize Grid!
	sf::Vector2i gridSize{ 15, 15 };
	sf::Vector2f gridOrigin{ 10, 10 };
	int tileSize = 7;
	this->nonTiledManager.initialize(gridSize, gridOrigin, tileSize);

}

void MapRenderer::clean()
{
	delete this->view;
}

void MapRenderer::renderGrid() 
{
	this->gridManager.test();
}

void MapRenderer::renderNonTiledGrid()
{
	this->nonTiledManager.drawNonTiledGrid();
}
