#pragma once

#include "ZoomState.h"

class ZoomStateMax : public ZoomState {
private:
public:
	ZoomStateMax(const Storage* pStorage, ZoomState** pZoomState, int* pZoom);
	~ZoomStateMax();

	void zoomIn();
	void zoomOut();
};