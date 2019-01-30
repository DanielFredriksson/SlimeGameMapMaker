#include "ZoomStateMax.h"
#include "ZoomStateMid.h"

ZoomStateMax::ZoomStateMax(ZoomState *pZoomState) : ZoomState(pZoomState)
{
}

ZoomStateMax::~ZoomStateMax() 
{
}

void ZoomStateMax::zoomIn() 
{
	// Zoom
	this->zoom(1 + this->pCameraSettings->scrollSpeed);
	// Save Zoom Value
	this->currentZoom += this->pCameraSettings->zoomSpeed;
	// Change state!
	this->pZoomState = this->pStorage->zoomMid;
}

void ZoomStateMax::zoomOut()
{
	// Do nothing, camera is already zoomed out to max.
}