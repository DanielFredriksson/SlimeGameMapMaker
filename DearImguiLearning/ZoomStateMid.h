#pragma once

#include "ZoomState.h"

class ZoomStateMid : public ZoomState {
private:
public:
	ZoomStateMid(const Storage* pStorage, ZoomState** paZoomState, int* pZoom);
	~ZoomStateMid();

	void zoomIn();
	void zoomOut();
};