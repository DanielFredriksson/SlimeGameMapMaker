#ifndef IMGUIMANAGER_HPP
#define IMGUIMANAGER_HPP

/// SFML
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/System.hpp"

/// IMGUI
#include "imgui.h"
#include "../imgui-sfml-master/imgui-SFML.h"

#include "Window.hpp"
#include <vector>
#include "MapRenderer.hpp"

/*
This struct is used to simplify input to widgets. Widgets need references so that
input to the window can be given to data which has been allocated in advance.
To shorten the eventually unnecesarily long input-paramters to 'updateWidgets'
i made this struct, which should be passed as a reference to 'updateWidgets'
*/
struct WidgetInput {
	sf::Color bgColor;
	float color[3] = { 0.0f, 0.0f, 0.0f };
	char windowTitle[255] = "ImGui + SFML = <3";
};

/*
The ImGuiManager simplifies the usage of ImGui-windows by keeping everything in
one, beautifully decoupled, class.
*/
class ImGuiManager {
private:
	// Something that contains internal-windows + widget information.
	// Like an 'InternalWindow' class which keeps track of it's widgets and whatnot.
	std::vector<Window*> windows;
	MapRenderer mapRenderer;

public:
	ImGuiManager();
	~ImGuiManager();

	static ImGuiManager& getInstance();
	sf::RenderWindow* initialize();
	void clean();

	void renderTEST();
	
	void updateWindows();
	void processEvents(sf::RenderWindow &window);
	void updateState(sf::RenderWindow &window, sf::Clock &deltaClock);
	void updateWidgets(sf::RenderWindow &window, WidgetInput& wInput);
};


#endif
