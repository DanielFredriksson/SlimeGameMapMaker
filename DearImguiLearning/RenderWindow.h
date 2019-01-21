#ifndef RENDERWINDOW_HPP
#define RENDERWINDOW_HPP


#include "iRenderWindow.h"


class RenderWindow : public iRenderWindow {
private:
	sf::RenderWindow* renderWindow = nullptr;

public:
	RenderWindow(sf::RenderWindow* window) { this->renderWindow = window; }
	~RenderWindow() {}

	sf::RenderWindow* get() {
		return this->renderWindow;
	}
};

#endif
