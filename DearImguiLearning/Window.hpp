#ifndef WINDOW_HPP
#define WINDOW_HPP

/// SFML
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/System.hpp"

/// IMGUI
#include "imgui.h"
#include "../imgui-sfml-master/imgui-SFML.h"

#include "Widget.hpp"

#include <vector>
#include <functional>

class Window {
private:
	std::vector<char> title;
	std::vector<Widget*> widgets;

public:
	Window();
	~Window();
	void initialize();
	void clean();

	void addWidget(Widget* widget);
	void iterate();
};

#endif

