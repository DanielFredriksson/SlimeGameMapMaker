#ifndef I_RENDERWINDOW_HPP
#define I_RENDERWINDOW_HPP

/// SFML
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/System.hpp"

/// IMGUI
#include "imgui.h"
#include "../imgui-sfml-master/imgui-SFML.h"


class iRenderWindow {
public:
	iRenderWindow() {}
	virtual ~iRenderWindow() {}
	
	virtual sf::RenderWindow* get() = 0;
};

#endif
