#include "Camera.h"

/// <summary>
/// Default constructor
/// </summary>
Camera::Camera(){
	cameraPos = glm::vec3(camX, camY, camZ);     // where we are positioned
	cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);  // where we are looking

	Yaw = YAW;
	Pitch = PITCH;

	updateCameraVectors();
}

glm::mat4 Camera::GetView() {
	updateCameraVectors();
	glm::mat4 viewMat = glm::lookAt(cameraPos, cameraTarget, cameraUp);
	return viewMat;
}

/// <summary>
/// Calculates related camera unit vectors from cameraPos, cameraTarget, cameraUp
/// </summary>
void Camera::updateCameraVectors() {
	glm::vec3 front;
	front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	front.y = sin(glm::radians(Pitch));
	front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	this->cameraFront = glm::normalize(front);

	//this->cameraAxis = glm::normalize(cameraTarget - cameraPos);
	//this->cameraFront = glm::normalize(cameraPos - cameraTarget);
	this->cameraRight = glm::normalize(glm::cross(worldUp, cameraFront));
	this->cameraUp = glm::cross(cameraFront, cameraRight);
}

/// <summary>
/// A validation for the LookAt function in glm.
/// </summary>
/// <returns></returns>
glm::mat4 Camera::MyCameraLookAt() {
	glm::mat4 camToWorld = glm::mat4(1.0f);
	updateCameraVectors();

	camToWorld[0][0] = cameraRight[0];
	camToWorld[0][1] = cameraRight[1];
	camToWorld[0][2] = cameraRight[2];
	camToWorld[1][0] = cameraUp[0];
	camToWorld[1][1] = cameraUp[1];
	camToWorld[1][2] = cameraUp[2];
	camToWorld[2][0] = cameraFront[0];
	camToWorld[2][1] = cameraFront[1];
	camToWorld[2][2] = cameraFront[2];

	camToWorld[3][0] = cameraPos[0];
	camToWorld[3][1] = cameraPos[1];
	camToWorld[3][2] = -1* cameraPos[2];

	return camToWorld;
}

void Camera::MoveBackwards() {
	this->cameraPos.z += 0.25f;
}

void Camera::MoveForwards() {
	this->cameraPos.z -= 0.25f;
}

void Camera::MoveLeft() {
	//this->cameraPos.x += 0.25f;
}

void Camera::MoveRight() {
	//this->cameraPos.x -= 0.25f;
}

// processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
void Camera::ProcessKeyboard(Camera_Movement direction)
{
	if (direction == BACKWARD)
		MoveBackwards();
	if (direction == FORWARD)
		MoveForwards();
	//if (direction == LEFT)
	//	MoveLeft();
	//if (direction == RIGHT)
	//	MoveRight();

	updateCameraVectors();
}