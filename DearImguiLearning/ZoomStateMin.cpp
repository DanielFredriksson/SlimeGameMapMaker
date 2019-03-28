#include "ZoomStateMin.h"
#include "ZoomStateMid.h"

ZoomStateMin::ZoomStateMin(const Storage* pStorage, ZoomState** paZoomState, int* pZoom)
	: ZoomState(pStorage, paZoomState, pZoom)
{
}
ZoomStateMin::~ZoomStateMin() 
{
}

void ZoomStateMin::zoomIn()
{
	// Do nothing, we're already maximumly zoomed in!
}

void ZoomStateMin::zoomOut()
{
	// Zoom
	this->zoom(this->pCameraSettings->zoomSpeed);
	// Save Zoom Value
	*this->currentZoom -= this->pCameraSettings->zoomSpeed;
	// Change state!
	*this->paZoomState = this->pStorage->zoomMid;
}