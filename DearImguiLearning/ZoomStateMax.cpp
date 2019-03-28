#include "ZoomStateMax.h"
#include "ZoomStateMid.h"

ZoomStateMax::ZoomStateMax(const Storage* pStorage, ZoomState** pZoomState, int* pZoom)
	: ZoomState(pStorage, pZoomState, pZoom)
{
}

ZoomStateMax::~ZoomStateMax() 
{
}

void ZoomStateMax::zoomIn() 
{
	// Zoom
	this->zoom(-1*this->pCameraSettings->zoomSpeed);
	// Save Zoom Value
	*this->currentZoom += this->pCameraSettings->zoomSpeed;
	// Change state!
	*this->paZoomState = this->pStorage->zoomMid;
}

void ZoomStateMax::zoomOut()
{
	// Do nothing, camera is already zoomed out to max.
}