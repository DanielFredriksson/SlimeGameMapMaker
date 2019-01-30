#pragma once

#include "Locator.hpp"
#include "GlobalSettings.h"

// Forward-Declarations!
class ZoomState;
class ZoomStateMax;
class ZoomStateMid;
class ZoomStateMin;
struct Storage {
	ZoomStateMax* zoomMax = nullptr;
	ZoomStateMid* zoomMid = nullptr;
	ZoomStateMin* zoomMin = nullptr;
	void clean() {
		delete this->zoomMax;
		delete this->zoomMid;
		delete this->zoomMin;
	}
};

class ZoomState {
protected:
	// Variables which allow the ZoomState class to be responsible for 
	// switching the current ZoomState inside the 'Camera' after zooming.
	ZoomState *pZoomState = nullptr;
	const CameraSettings* pCameraSettings = nullptr;
	sf::RenderWindow* pRenderWindow = nullptr;
	const Storage* pStorage = nullptr;
	float currentZoom = 1.0f;

	void zoom(float zoomValue) {
		sf::View view = pRenderWindow->getView();
		view.zoom(zoomValue);
		pRenderWindow->setView(view);
	}

public:
	ZoomState(ZoomState *pZoomState) {
		this->pZoomState = pZoomState;
		this->pCameraSettings = Locator::getSettings()->getCameraSettings();
		this->pRenderWindow = Locator::getRenderWindow();
	}
	virtual ~ZoomState() {}

	/*void initialize(ZoomState *pZoomState) {
		this->pZoomState = pZoomState;
		this->pCameraSettings = Locator::getSettings()->getCameraSettings();
		this->pRenderWindow = Locator::getRenderWindow();
	}*/

	virtual void zoomIn() = 0;
	virtual void zoomOut() = 0;
};
