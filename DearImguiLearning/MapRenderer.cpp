#include "MapRenderer.hpp"

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
