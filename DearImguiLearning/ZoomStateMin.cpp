#include "ZoomStateMin.h"
#include "ZoomStateMid.h"

ZoomStateMin::ZoomStateMin(ZoomState *pZoomState) : ZoomState(pZoomState) 
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
	this->zoom(1 + this->pCameraSettings->scrollSpeed);
	// Save Zoom Value
	this->currentZoom -= this->pCameraSettings->zoomSpeed;
	// Change state!
	this->pZoomState = this->pStorage->zoomMid;
}