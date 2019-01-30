#ifndef LOCATOR_HPP
#define LOCATOR_HPP

#include "iRenderWindow.h"
#include "GlobalSettings.h"

class Locator {
private:
	static sf::RenderWindow* gRenderWindow;
	static Settings* gSettings;

public:
	Locator() {}
	~Locator() {}

	// PROVIDE
	static void provide(sf::RenderWindow* renderWindow) { gRenderWindow = renderWindow; }
	static void provide(Settings* settings) { gSettings = settings; }

	// GET
	static sf::RenderWindow* getRenderWindow() { return gRenderWindow; }
	static Settings* getSettings() { return gSettings; }
};

#endif
