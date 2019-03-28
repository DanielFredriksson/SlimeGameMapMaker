#ifndef LOCATOR_HPP
#define LOCATOR_HPP

#include "iRenderWindow.h"
#include "GlobalSettings.h"

class Camera;

class Locator {
private:
	static sf::RenderWindow* gRenderWindow;
	static Settings* gSettings;
	static Camera* gCamera;

public:
	Locator() {}
	~Locator() {}

	// PROVIDE
	static void provide(sf::RenderWindow** renderWindow) { gRenderWindow = *renderWindow; }
	static void provide(Settings** settings) { gSettings = *settings; }
	static void provide(Camera** camera) { gCamera = *camera; }

	// GET
	static sf::RenderWindow** getRenderWindow() { return &gRenderWindow; }
	static Settings** getSettings() { return &gSettings; }
	static Camera** getCamera() { return &gCamera; }
};

#endif
