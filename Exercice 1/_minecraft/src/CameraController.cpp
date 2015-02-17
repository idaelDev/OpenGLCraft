#include "CameraController.h"


CameraController::CameraController(NYCamera * l_camera)
	:camera(l_camera)
{
	forward_step = false;
	backward_step = false;
	right_step = false;
	left_step = false;
	up = false;
	down = false;

	speed = 100.f;
}

void CameraController::inputDown(char key)
{
	switch (key)
	{
	case 'z': forward_step = true; break;
	case 's': backward_step = true; break;
	case 'q': right_step = true; break;
	case 'd': left_step = true; break;
	case ' ': up = true; break;
	case 'a': down = true; break;
	}
}

void CameraController::inputUp(char key)
{
	switch (key)
	{
	case 'z': forward_step = false; break;
	case 's': backward_step = false; break;
	case 'q': right_step = false; break;
	case 'd': left_step = false; break;
	case ' ': up = false; break;
	case 'a': down = false; break;
	}
}

void CameraController::update(float elapsed_time)
{
	// Forward/Backward step
	if (forward_step)
		camera->move(camera->_Direction * speed * elapsed_time);
	else if (backward_step)
		camera->move(NYVert3Df(-camera->_Direction.X, -camera->_Direction.Y, -camera->_Direction.Z) * speed * elapsed_time);

	// Left/Right step
	if (left_step)
		camera->move(camera->_NormVec * speed * elapsed_time);
	else if (right_step)
		camera->move(NYVert3Df(-camera->_NormVec.X, -camera->_NormVec.Y, -camera->_NormVec.Z) * speed * elapsed_time);

	// Up/Down
	if (down)
		camera->move(NYVert3Df(-camera->_UpRef.X, -camera->_UpRef.Y, -camera->_UpRef.Z) * speed * elapsed_time);
	else if (up)
		camera->move(camera->_UpRef  * speed * elapsed_time);
}


CameraController::~CameraController()
{
}
