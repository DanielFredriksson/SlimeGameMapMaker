// DearImguiLearning.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <iostream>
#include <crtdbg.h>

/// SFML
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/System.hpp"

/// IMGUI
#include "imgui.h"
#include "../imgui-sfml-master/imgui-SFML.h"

/// Widgets
#include "InputText.hpp"

/// Locator
#include "Locator.hpp"
#include "RenderWindow.hpp"

/// IMGUI-Manager
#include "ImGuiManager.hpp"
#include "Window.hpp"

// TESTING
#include "MapRenderer.hpp"


int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	// Initialize ImGuiManager, which sets up the ImGui as well as windows & widgets
	ImGuiManager& manager = ImGuiManager::getInstance();
	sf::RenderWindow* renderWindow = manager.initialize();
	MapRenderer mapRenderer;

	// If additional input to the widgets is needed, add one in the WidgetInput definition.
	WidgetInput wInput;
	Locator::getRenderWindow()->setTitle(wInput.windowTitle);

	sf::Clock deltaClock;
	while (renderWindow->isOpen()) {
		// Process Events
		manager.processEvents(*renderWindow);

		// Update State
		ImGui::SFML::Update(*renderWindow, deltaClock.restart());

		// --- Render with SFML
		renderWindow->draw(mapRenderer);
		// --- Render with SFML

		// Update Windows & Widgets
		manager.updateWindows();

		// Clear, Render, and display
	//	ImGui::ShowTestWindow(); USED FOR TESTING!!!
		manager.display(*renderWindow, wInput.bgColor);
	}

	ImGui::SFML::Shutdown();
	delete renderWindow;
}