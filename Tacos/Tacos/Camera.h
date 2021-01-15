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
	NONE,
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	UP,
	DOWN,
	RESET,
	ORBIT_XY,
	ORBIT_YZ,
	ORBIT_XZ,
	PIVOT_LEFT,
	PIVOT_RIGHT
};

// Controls a camera viewpoint data for the application
class Camera
{
	// Default camera values
	const glm::vec3 defaultPosition = glm::vec3(0.0f, 0.0f, -3.0f); // the default camera position
	const glm::vec3 defaultTarget = glm::vec3(0.0f, 0.0f, 0.0f);  // the dedault target view location
	const glm::vec3 defaultWorldUp = glm::normalize(glm::vec3(0.0f, 1.0f, 0.0f)); // unit vector for the World UP directions
	const float YAW =  90.0f; // yaw is initialized to +90 degrees in Vulkan since a yaw of 0.0 results in a direction vector pointing to the left of hte object so we initiallt rotate a bit to the right.
	const float PITCH = 0.0f;
	const float SPEED = 2.5f;
	const float SENSITIVITY = 0.1f;
    const float FOV = 45.0f; // Field of View angle

	const float ORBIT_INTERVAL_DEGREES = 5.0f;


private:	glm::vec3 cameraPos;			// vector that points from origin to camera location -- coords of camera position
private:	glm::vec3 cameraTarget;			// the target coords to which the camera is pointing

private:	glm::vec3 cameraDirection;     
private:	glm::vec3 cameraFront;	  	    // unit vector that points to target from camera position
private:	glm::vec3 cameraUp;				// the up vector for the camera
private:	glm::vec3 cameraRight;          // the right vector for the camera
private:	glm::vec3 worldUp;				// unit vector that orients the world upwards.
	
public:  bool isOrbitting = false;
private: float orbitCount = 0.0f;   // a counter for the number of orbit intervals
private: float orbitTime = 0.0f;
private: float orbit_radius_XZ = 10.0f; // default orbit radius
private: float orbit_radius_YZ = 10.0f; // default orbit radius
private: float orbit_radius_XY = 10.0f; // default orbit radius
private: Camera_Movement movementDirection = Camera_Movement::NONE;  // stores the current movement direction

	// Euler angles
private:	float Yaw;
private:	float Pitch;
private:	float Fov;



	// Camera options
private:	float MovementSpeed;
private:	float MouseSensitivity;

public:	float GetFov() { return Fov; }

	// Private Methods
private:  void updateCameraVectors();
private: void moveBackwards(float vel);  // moves the camera position along the -Z (out of screen) direction;
private: void moveForwards(float vel);   // moves the camera position along the +Z (into screen) direction;
private: void pivotLeft(float vel);		 // turn the camera view to the left	
private: void pivotRight(float vel);     // turn the camera view to the right
private: void strafeLeft(float vel);  // moves the camera position along the -Z (out of screen) direction;
private: void strafeRight(float vel);   // moves the camera position along the +Z (into screen) direction;
private: void strafeUp(float vel);    // elevate the camera
private: void strafeDown(float vel);  // de-elevate the camera
private: void orbitXZ(float deltaTime);  // orbit the camera around the origin horizontally (XZ plane) while lookinhg at the object
private: void orbitYZ(float deltatTime);  // orbit the camera around the origin vertically (YZ plane) while looking at the object
private: void orbitXY(float deltatTime);  // orbit the camera in the XY plane while looking at the object

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

