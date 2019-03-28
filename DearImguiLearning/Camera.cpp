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
	//
	this->currentZoom = 0.0;
	this->scrollSpeed = (*Locator::getSettings())->getCameraSettings()->scrollSpeed;

	// Initialize Storage
	this->storage = new Storage;
	this->storage->zoomMax = new ZoomStateMax(this->storage, &this->zoomState, &this->currentZoom);
	this->storage->zoomMid = new ZoomStateMid(this->storage, &this->zoomState, &this->currentZoom);
	this->storage->zoomMin = new ZoomStateMin(this->storage, &this->zoomState, &this->currentZoom);

	// Initialize States
	this->zoomState = this->storage->zoomMid;
}

void Camera::clean()
{
	// Clean Storage
	this->storage->clean();
	delete this->storage;
}

void Camera::move(sf::Vector2i deltaMousePos)
{
	sf::View view = (*Locator::getRenderWindow())->getView();	// Get old view,
	view.move(sf::Vector2f(										// make changes to it,
		(-1) * deltaMousePos.x * this->scrollSpeed,
		(-1) * deltaMousePos.y * this->scrollSpeed
	));			
	(*Locator::getRenderWindow())->setView(view);				// set it as new view
}

void Camera::zoomIn()
{
	this->zoomState->zoomIn();
}

void Camera::zoomOut()
{
	this->zoomState->zoomOut();
}

float Camera::getZoom()
{
	return this->zoomState->getCurrentZoom();
}
