#ifndef LOCATOR_HPP
#define LOCATOR_HPP

#include "iRenderWindow.hpp"

class Locator {
private:
	static sf::RenderWindow* gRenderWindow;

public:
	Locator() {}
	~Locator() {}

	// PROVIDE
	static void provide(sf::RenderWindow* renderWindow) { gRenderWindow = renderWindow; }

	// GET
	static sf::RenderWindow* getRenderWindow() { return gRenderWindow; }
};

#endif
