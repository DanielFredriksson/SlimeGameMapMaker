#include "Window.hpp"

Window::Window()
{
	this->initialize();
}

Window::~Window()
{
	this->clean();
}

void Window::initialize()
{
}

void Window::clean()
{
	for (int i = 0; i < this->widgets.size(); i++) {
		this->widgets[i]->~Widget();
		delete this->widgets[i];
	}
	this->widgets.clear();
}

void Window::addWidget(Widget * widget)
{
	this->widgets.push_back(widget);
}

void Window::iterate()
{
	// Begin window
	ImGui::Begin("Sample Window");

	for (auto & it : this->widgets) {
		it->iterateBehaviors();
	}

	// End Window
	ImGui::End();
}
