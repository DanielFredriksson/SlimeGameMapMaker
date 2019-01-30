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
	Storage* storage;
	ZoomState* zoomState;

public:
	Camera();
	~Camera();
	void initialize();
	void clean();

	void move(sf::Vector2i deltaMousePos);
	void zoomIn();
	void zoomOut();
};


#endif
