#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "GLFW/glfw3.h"

class SceneCamera {
public:
	SceneCamera();

	~SceneCamera();

	glm::mat4 getViewMatrix() const;

	void mouseUpdate(const glm::vec2& newMousePostion);

	void processKeyboardInput(GLFWwindow* window,float DeltaTime);
private: 
	glm::vec3 position;
	glm::vec3 ViewDirection;
	const glm::vec3 up;
};