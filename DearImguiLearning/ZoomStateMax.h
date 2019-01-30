#pragma once

#include "ZoomState.h"

class ZoomStateMax : public ZoomState {
private:
public:
	ZoomStateMax(ZoomState *pZoomState);
	~ZoomStateMax();

	void zoomIn();
	void zoomOut();
};