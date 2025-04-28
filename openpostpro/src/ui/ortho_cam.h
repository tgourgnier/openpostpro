#pragma once
#include "camera.h"
class OrthoCamera :	public Camera
{
private:
	float _tx = 0.0f;
	float _ty = 0.0f;
	int _zoom_inc = 0;

	void compute();

public:
	OrthoCamera();
	~OrthoCamera() {}

	void set_size(float width, float height) override;
	void center() override;

	void mouseMove(float xpos, float ypos) override;
	void mouseWheel(float xdelta, float ydelta) override;

	glm::vec2 getPosition(float x, float y) override;
};

