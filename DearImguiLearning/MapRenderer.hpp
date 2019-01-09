#ifndef MAPRENDERER_HPP
#define MAPRENDERER_HPP

/// SFML
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/System.hpp"

// TESTING
#include <iostream>

class MapRenderer : public sf::Drawable {
private:
	sf::Sprite *sprite;
	sf::Texture *texture;
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

public:
	MapRenderer();
	~MapRenderer();

};

#endif
