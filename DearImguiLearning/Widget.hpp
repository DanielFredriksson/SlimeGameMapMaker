#ifndef WIDGET_HPP
#define WIDGET_HPP

/// SFML
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/System.hpp"

/// IMGUI
#include "imgui.h"
#include "../imgui-sfml-master/imgui-SFML.h"

#include <functional>

class Widget {
protected:
	std::vector<std::function<void(Widget*)>> behaviors;

public:
	Widget();
	virtual ~Widget();

	void addBehavior(std::function<void(Widget*)> behavior) {
		this->behaviors.push_back(behavior);
	}
	virtual void iterateBehaviors() = 0;

};

#endif

