#ifndef _CAMERA_CONTROLLER_H_
#define _CAMERA_CONTROLLER_H_

// Camera controller for position
#include "engine\render\renderer.h"

class CameraController
{
public:
	CameraController(NYCamera * camera);

	void inputDown(char key);
	void inputUp(char key);

	void update(float elapsed_time);

	float speed;	// Camera speed
	NYCamera * camera;	// Controlled camera

	~CameraController();

private:
	bool forward_step, backward_step;	// Step forward/backward
	bool left_step, right_step;	// Step right/left
	bool up, down;				// Down or Up

};

#endif _CAMERA_CONTROLLER_H_