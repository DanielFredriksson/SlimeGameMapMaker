#include "ZoomStateMid.h"
#include "ZoomStateMax.h"
#include "ZoomStateMin.h"

ZoomStateMid::ZoomStateMid(const Storage* pStorage, ZoomState** paZoomState, int* pZoom)
	: ZoomState(pStorage, paZoomState, pZoom)
{
}

ZoomStateMid::~ZoomStateMid()
{
}

void ZoomStateMid::zoomIn() {
	// Zoom
	this->zoom(-1*this->pCameraSettings->zoomSpeed);
	// Save Zoom Value
	*this->currentZoom += this->pCameraSettings->zoomSpeed;
	// Check if Min is met...
	if (*this->currentZoom >= this->pCameraSettings->zoomMin) {
		// ... And if it is, change current zoomstate!
		*this->paZoomState = this->pStorage->zoomMin;
	}
}

void ZoomStateMid::zoomOut() {
	// Zoom
	this->zoom(this->pCameraSettings->zoomSpeed);
	// Save Zoom Value
	*this->currentZoom -= this->pCameraSettings->zoomSpeed;
	// Check if Max is met...
	if (*this->currentZoom <= this->pCameraSettings->zoomMax) {
		// ... And if it is, change current zoomstate!
		*this->paZoomState = this->pStorage->zoomMax;
	}
}