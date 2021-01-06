#pragma once
#include <glm/glm.hpp>
#include <glm\ext\matrix_transform.hpp>

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

enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	UP,
	DOWn
};

// Default camera values
const float YAW = 45.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

// Default Camera position
const float camX = 0.0f; // x-coord
const float camY = 0.0f; // y=coord
const float camZ = 2.0f; // z-coord
const glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);

// Controls a camera viewpoint data for the application
class Camera
{

private:	glm::vec3 cameraPos;			// vector that points from origin to camera location -- coords of camera position
private:	glm::vec3 cameraTarget;			// the target coords to which the camera is pointing
private:	glm::vec3 cameraFront;	  	    // unit vector that points to target from camera position
//private:    glm::vec3 cameraAxis;			// unit vector from target to camera position

private:	glm::vec3 cameraUp;				// the up vector for the camera
private:	glm::vec3 cameraRight;          // the right vector for the camera
	
	// Euler angles
private:	float Yaw;
private:	float Pitch;

	// Camera options
private:	float MovementSpeed;
private:	float MouseSensitivity;
private:	float Zoom;

	// Private Methods
private:  void updateCameraVectors();



	// Default Constructor using vectors
public:	Camera();

	// Public Methods
	/// <summary>
	/// Returns the view matrix for this camera based on its orientation
	/// </summary>
	/// <returns></returns>
public:	glm::mat4 GetView(); // returns the view model for the camera
public: void ProcessKeyboard(Camera_Movement direction);   // process keyboard movement on camera action
public: void MoveBackwards();  // moves the camera position along the -Z (out of screen) direction;
public: void MoveForwards();   // moves the camera position along the +Z (into screen) direction;
public: void MoveLeft();  // moves the camera position along the -Z (out of screen) direction;
public: void MoveRight();   // moves the camera position along the +Z (into screen) direction;


private: glm::mat4 MyCameraLookAt(); // same as the glm::LookAt function -- used for validation
};

