#pragma once

#include "ZoomState.h"

class ZoomStateMin : public ZoomState {
private:
public:
	ZoomStateMin(const Storage* pStorage, ZoomState** paZoomState, int* pZoom);
	~ZoomStateMin();

	void zoomIn();
	void zoomOut();
};