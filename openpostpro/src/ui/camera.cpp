#include "camera.h"

Camera::Camera()
{
	reset();
}

void Camera::reset()
{
	_scale = 1.0f;
	_znear = 1.0f;
	_zfar = 0.0f;
	_xcenter = 0.0f;
	_ycenter = 0.0f;
	_left_down = false;
	_right_down = false;
	_modelview = glm::mat4(1.0f);
	_projection = glm::mat4(1.0f);
}