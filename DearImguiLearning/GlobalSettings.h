#pragma once


struct CameraSettings {
	float zoomSpeed;
	float zoomMax;
	float zoomMin;
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