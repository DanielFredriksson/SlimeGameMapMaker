#include "ImGuiManager.hpp"
#include "Locator.hpp"

#include "InputText.h"
#include "DisplayText.h"

ImGuiManager::ImGuiManager()
{
	//this->initialize();
}

ImGuiManager::~ImGuiManager()
{
	this->clean();
}

ImGuiManager& ImGuiManager::getInstance()
{
	static ImGuiManager instance;
	
	return instance;
}

sf::RenderWindow* ImGuiManager::initialize()
{
	/// ---------- Set Up RenderWindow ---------- 
	int screenPixelHeight = sf::VideoMode::getDesktopMode().height;
	int screenPixelWidth = sf::VideoMode::getDesktopMode().width;
	sf::RenderWindow* renderWindow = new sf::RenderWindow(sf::VideoMode(screenPixelWidth, screenPixelHeight), "");
	renderWindow->setVerticalSyncEnabled(true);
	ImGui::SFML::Init(*renderWindow);
	renderWindow->resetGLStates();
	// Provide to locator
	Locator::provide(renderWindow);

	/// ---------- Set Up MapRenderer ----------
//	this->mapRenderer.initialize(renderWindow);
	

	/// ------------- WINDOW_0 TEST -------------
	Window* window0 = new Window("Test window!");
	this->windows.push_back(window0);
	/// ---- Title Widget ----
	// Widget Definition
	InputText* titleW = new InputText(
		new char[250]{ "Title! " },
		new char[250]{ "Contents?" }
	);
	// Behavior Definition
	std::function<void(Widget*)> titleB = [](Widget* self) {
		InputText* real = static_cast<InputText*>(self);
		Locator::getRenderWindow()->setTitle(real->getInput());
	};
	// Add behavior to widget
	titleW->addBehavior(titleB);
	// Add widget to window
	window0->addWidget(titleW);
	
	/// ------------- WINDOW_1 INFORMATION -------------
	Window* informationWindow = new Window("Information Window!");
	this->windows.push_back(informationWindow);
	/// ---- Mouse Coordinations Widget ----
	// Widget Definition
	DisplayText* infoW = new DisplayText();
	// Behavior Definition
	std::function<void(Widget*)> infoB = [](Widget* self) {
		if (ImGui::IsMousePosValid()) {
			// Display mouse coordinates
			ImGui::Text(
				"Mouse Coordinates: (%.1f,%.1f)",
				ImGui::GetIO().MousePos.x, 
				ImGui::GetIO().MousePos.y
			);
		}
	};
	// Add behavior to widget
	infoW->addBehavior(infoB);
	informationWindow->addWidget(infoW);

	/// ------------- WINDOW_2 INFORMATION -------------


	return renderWindow;
}

void ImGuiManager::clean()
{
	// Clean & Delete windows
	for (int i = 0; i < this->windows.size(); i++) {
		this->windows[i]->clean();
		delete this->windows[i];
		this->windows[i] = nullptr;
	}
	// Clear the vector
	this->windows.clear();
}

void ImGuiManager::updateWindows()
{
	// Per window...
	for (auto & it : this->windows) {
		// ... Iterate throughout its widgets and their behaviors
		it->iterate();
	}
}

void ImGuiManager::processEvents(sf::RenderWindow &window)
{
	sf::Event event;
	while (window.pollEvent(event)) {
		ImGui::SFML::ProcessEvent(event);
		if (event.type == sf::Event::Closed) {
			window.close();
		}
	}
}

void ImGuiManager::updateState(sf::RenderWindow &window, sf::Clock &deltaClock)
{
	ImGui::SFML::Update(window, deltaClock.restart());
}

void ImGuiManager::updateWidgets(sf::RenderWindow &window, WidgetInput& wInput)
{
	// Begin window
	ImGui::Begin("Sample Window");

	// ---------- Widgets ----------
	// This simultaneously creates and checks for updates for a textinput with the name "Window title"
	if (ImGui::InputText("Window title", wInput.windowTitle, 255)) {
		window.setTitle(wInput.windowTitle);
	}

	// Background color edit
	if (ImGui::ColorEdit3("Background color", wInput.color)) {
		// this code gets called if color value changes, so
		// the background color is upgraded automatically!
		wInput.bgColor.r = static_cast<sf::Uint8>(wInput.color[0] * 255.f);
		wInput.bgColor.g = static_cast<sf::Uint8>(wInput.color[1] * 255.f);
		wInput.bgColor.b = static_cast<sf::Uint8>(wInput.color[2] * 255.f);
	}

	// Sample button
	if (ImGui::Button("TestButton!")) {
	}
	// ---------- Widgets ----------

	// End Window
	ImGui::End();
}

