#pragma once
#include <iostream>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "GLFW/glfw3.h"


class SceneCamera {
public:
	SceneCamera();

	glm::mat4 getViewMatrix() const;

	glm::mat4 getProjectionMatrix() const;

	void MouseRotation(const glm::vec2& newMousePostion);

	void ProcessKeyboardInput(GLFWwindow* window,float DeltaTime);

	void setMouseSensitivity(float NewSens);

private: 
	glm::vec3 m_position;
	glm::vec3 m_ViewDirection;
	const glm::vec3 m_up;
	float m_MouseSensitivity = 0.1f;
	glm::vec2 m_LastMousePosition;
	float m_Yaw = -90.0f;
	float m_Pitch = 0.0f;
	const float MovementSpeed = 10.0f;
};