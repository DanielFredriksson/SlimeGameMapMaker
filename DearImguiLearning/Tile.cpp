#include "Tile.h"

Tile::Tile()
{
}

Tile::~Tile()
{
}

void Tile::initialize(std::string texture, sf::Vector2f position)
{
	if (!this->sfData.texture.loadFromFile(texture.c_str())) {
		throw std::exception("Failed to load texture!\n");
	}
	this->sfData.sprite.setTexture(this->sfData.texture);
	this->sfData.sprite.setPosition(position);
	this->sfData.sprite.setScale(0.1f, 0.1f);
}

void Tile::clean()
{
}

void Tile::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(this->sfData.sprite);
}


