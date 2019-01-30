#include "Camera.hpp"
#include "Locator.hpp"

#include "ZoomState.h"
#include "ZoomStateMax.h"
#include "ZoomStateMid.h"
#include "ZoomStateMin.h"

Camera::Camera()
{
	this->initialize();
}

Camera::~Camera()
{
}

void Camera::initialize()
{
	// Initialize Storage
	this->storage = new Storage;
	this->storage->zoomMax = new ZoomStateMax(this->zoomState);
	this->storage->zoomMid = new ZoomStateMid(this->zoomState);
	this->storage->zoomMin = new ZoomStateMin(this->zoomState);

	// Initialize States
	this->zoomState = this->storage->zoomMid;
}

void Camera::clean()
{
	// Clean Storage
	this->storage->clean();
	delete this->storage;

	// Clean zoomState not needed
}

void Camera::move(sf::Vector2i deltaMousePos)
{
	sf::View view = Locator::getRenderWindow()->getView();	// Get old view,
	view.move(sf::Vector2f((-1) * deltaMousePos));			// make changes to it,
	Locator::getRenderWindow()->setView(view);				// set it as new view
}

void Camera::zoomIn()
{
	this->zoomState->zoomIn();
}

void Camera::zoomOut()
{
	this->zoomState->zoomOut();
}
