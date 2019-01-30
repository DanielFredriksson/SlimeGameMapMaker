#pragma once

#include "ZoomState.h"

class ZoomStateMin : public ZoomState {
private:
public:
	ZoomStateMin(ZoomState *pZoomState);
	~ZoomStateMin();

	void zoomIn();
	void zoomOut();
};