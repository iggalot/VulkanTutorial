#pragma once
#include <glm/glm.hpp>
#include <glm\ext\matrix_transform.hpp>
#include <iostream>

/// <summary>
/// A camera object class
/// 
/// GLM helper function notes
/// -------------------------------------
/// LookAt:  eye, target, up
/// VIEW MATRIX:  glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f))
///
/// Perspective:  FOVy, aspect ratio, zNearClip, zFarClip
/// PROJ:  glm::perspective(glm::radians(45.0f), swapChainExtent.width / (float)swapChainExtent.height, 0.1f, 10.0f);

/// </summary>

/// <summary>
/// Enum for defining movement directions
/// </summary>
enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	UP,
	DOWN,
	RESET
};

// Controls a camera viewpoint data for the application
class Camera
{
	// Default camera values
	const glm::vec3 defaultPosition = glm::vec3(0.0f, 0.0f, 10.0f); // the default camera position
	const float YAW = 0.0f;
	const float PITCH = 0.0f;
	const float SPEED = 2.5f;
	const float SENSITIVITY = 1.0f;
    const float ZOOM = 45.0f;

private:	glm::vec3 cameraPos;			// vector that points from origin to camera location -- coords of camera position
private:	glm::vec3 cameraTarget;			// the target coords to which the camera is pointing
private:	glm::vec3 cameraFront;	  	    // unit vector that points to target from camera position
private:	glm::vec3 cameraUp;				// the up vector for the camera
private:	glm::vec3 cameraRight;          // the right vector for the camera
private:	glm::vec3 worldUp;				// unit vector that orients the world upwards.
	
	// Euler angles
private:	float Yaw;
private:	float Pitch;

	// Camera options
private:	float MovementSpeed;
private:	float MouseSensitivity;
public:	float Zoom;

	// Private Methods
private:  void updateCameraVectors();
private: void moveBackwards(float vel);  // moves the camera position along the -Z (out of screen) direction;
private: void moveForwards(float vel);   // moves the camera position along the +Z (into screen) direction;
private: void strafeLeft(float vel);  // moves the camera position along the -Z (out of screen) direction;
private: void strafeRight(float vel);   // moves the camera position along the +Z (into screen) direction;
private: void strafeUp(float vel);    // elevate the camera
private: void strafeDown(float vel);  // de-elevate the camera


	// Default Constructor using vectors
public:	Camera();

	// Public Methods
public:	glm::mat4 GetView(); // returns the view model for the camera
public: void ProcessKeyboard(Camera_Movement direction, float deltaTime);   // process keyboard movement on camera action
public: void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);

public: void CameraMouseCallback(float& lastX, float& lastY, bool& firstMouse, double xpos, double ypos);
public: void CameraMouseScrollCallback(double yoffset);
private: glm::mat4 MyCameraLookAt(); // same as the glm::LookAt function -- used for validation
};

