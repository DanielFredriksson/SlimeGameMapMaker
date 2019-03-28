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
	ZoomState** paZoomState = nullptr;	// Pointer to the zoom-state in 'Camera'
	const CameraSettings* pCameraSettings = nullptr;
	sf::RenderWindow** pRenderWindow = nullptr;
	const Storage* pStorage = nullptr;
	int *currentZoom;

	void zoom(float zoomValue) {
		sf::View view = (*pRenderWindow)->getView();
		view.zoom(1 + zoomValue*0.1);
		(*pRenderWindow)->setView(view);
	}

public:
	ZoomState(const Storage* pStorage, ZoomState** paZoomState, int* pZoom) {
		this->pStorage = pStorage;
		this->paZoomState = paZoomState;
		this->currentZoom = pZoom;
		this->pCameraSettings = (*Locator::getSettings())->getCameraSettings();
		this->pRenderWindow = Locator::getRenderWindow();
	}
	virtual ~ZoomState() {}

	virtual void zoomIn() = 0;
	virtual void zoomOut() = 0;
	float getCurrentZoom() { return *this->currentZoom; }
};
