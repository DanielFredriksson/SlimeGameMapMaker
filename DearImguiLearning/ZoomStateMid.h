#pragma once

#include "ZoomState.h"

class ZoomStateMid : public ZoomState {
private:
public:
	ZoomStateMid(ZoomState *pZoomState);
	~ZoomStateMid();

	void zoomIn();
	void zoomOut();
};