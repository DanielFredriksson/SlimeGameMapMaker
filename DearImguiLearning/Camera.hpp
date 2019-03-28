#ifndef CAMERA_HPP
#define CAMERA_HPP

/// SFML
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/System.hpp"

/// INTERNAL

class Storage;
class ZoomState;

class Camera {
private:
	// Contains States
	Storage* storage;

	// Modified by the states: 
	ZoomState* zoomState;
	int currentZoom;

	// Initialized via locator
	float scrollSpeed;

public:
	Camera();
	~Camera();
	void initialize();
	void clean();

	void move(sf::Vector2i deltaMousePos);
	void zoomIn();
	void zoomOut();
	float getZoom();
};


#endif
