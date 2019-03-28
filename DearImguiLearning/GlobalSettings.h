#pragma once


struct CameraSettings {
	int zoomSpeed;
	int zoomMax;
	int zoomMin;
	float scrollSpeed;
};


class Settings {
private:
	static CameraSettings gCameraSettings;

public:
	Settings() {}
	~Settings() {}

	static CameraSettings* getCameraSettings() {
		return &gCameraSettings;
	}
};