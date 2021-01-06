#pragma once
#include <glm/glm.hpp>
#include <glm\ext\matrix_transform.hpp>

// Controls a camera viewpoint data for the application
class Camera
{

public:
	float camX = 0.0f;
	float camY = 0.0f;
	float camZ = 2.0f;

	glm::mat4 GetView();

	glm::vec3 cameraPos = glm::vec3(camX, camY, camZ); // vector that points from origin to camera location
	glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);  //vector that points from target to camera position

	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
	glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);

	//LookAt:  eye, target, up
	// VIEWL glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f))

	//Perspective:  FOVy, aspect ratio, zNearClip, zFarClip
	// PROJ:  glm::perspective(glm::radians(45.0f), swapChainExtent.width / (float)swapChainExtent.height, 0.1f, 10.0f);

	//glm::lookAt(glm)
	//glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);

	//glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);

	//glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	//glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
	//glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);

	//glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f),
	//	glm::vec3(0.0f, 0.0f, 0.0f),
	//	glm::vec3(0.0f, 1.0f, 0.0f));
};

