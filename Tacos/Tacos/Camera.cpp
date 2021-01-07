#include "Camera.h"

/// <summary>
/// Default constructor
/// </summary>
Camera::Camera(){
	cameraPos = glm::vec3(0.0f, 0.0f, 0.0f);     // where we are positioned
	cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);  // where we are looking
	worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
	Zoom = ZOOM;
	MouseSensitivity = SENSITIVITY;
	MovementSpeed = SPEED;
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

void Camera::moveBackwards(float vel) {
	this->cameraPos -= cameraFront * vel;
}

void Camera::moveForwards(float vel) {
	this->cameraPos += cameraFront * vel;
}

// TODO:  Rename STRAFE functions

void Camera::strafeRight(float vel) {
	this->cameraPos += cameraRight * vel;
}

void Camera::strafeLeft(float vel) {
	this->cameraPos -= cameraRight * vel;
}

void Camera::strafeUp(float vel) {
	this->cameraPos += cameraUp * vel;
}

void Camera::strafeDown(float vel) {
	this->cameraPos -= cameraUp * vel;
}

/// <summary>
/// processes input received from any keyboard-like input system. 
/// Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
/// </summary>
/// <param name="direction">direction of the movemnt (ENUM) </param>
/// <param name="deltaTime">change in time</param>
void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime)
{
	float velocity = MovementSpeed * deltaTime;
	if (direction == BACKWARD)
		moveBackwards(velocity);
	if (direction == FORWARD)
		moveForwards(velocity);
	if (direction == LEFT)
		strafeLeft(velocity);
	if (direction == RIGHT)
		strafeRight(velocity);
	if (direction == UP)
		strafeUp(velocity);
	if (direction == DOWN)
		strafeDown(velocity);

	updateCameraVectors();
}

void Camera::CameraMouseCallback(float& lastX, float& lastY, bool& firstMouse, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	this->ProcessMouseMovement(xoffset, yoffset);
}

// processes input received from a mouse input system. Expects the offset value in both the x and y direction.
void Camera::ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch)
{
	xoffset *= MouseSensitivity;
	yoffset *= MouseSensitivity;

	Yaw += xoffset;
	Pitch += yoffset;

	// make sure that when pitch is out of bounds, screen doesn't get flipped
	if (constrainPitch)
	{
		if (Pitch > 89.0f)
			Pitch = 89.0f;
		if (Pitch < -89.0f)
			Pitch = -89.0f;
	}

	// update Front, Right and Up Vectors using the updated Euler angles
	updateCameraVectors();
}

// processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
void Camera::CameraMouseScrollCallback(double yoffset)
{
	std::cout << "scroll callback relayed to camera -- BEFORE: Zoom: " << Zoom << std::endl;
	Zoom -= (float)yoffset;
	if (Zoom < 1.0f)
		Zoom = 1.0f;
	if (Zoom > 45.0f)
		Zoom = 45.0f;
	std::cout << "scroll callback relayed to camera -- After: Zoom: " << Zoom << std::endl;
}