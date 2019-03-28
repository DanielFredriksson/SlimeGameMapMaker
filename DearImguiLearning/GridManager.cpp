#include "GridManager.h"
#include "Locator.hpp"

GridManager::GridManager()
{
	this->initialize();
}

GridManager::~GridManager()
{
}

void GridManager::initialize()
{
	this->testTile.initialize(
		"../GameData/Assets/Textures/TileTextures/FirstTexture.png",
		sf::Vector2f(0.0f, 0.0f)
	);
}

void GridManager::clean()
{
}

void GridManager::test()
{
	(*Locator::getRenderWindow())->draw(this->testTile);
}
