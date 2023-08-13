#include "SceneCamera.h"

SceneCamera::SceneCamera() :
	position(0.0f, 0.0f, 5.0f),
	ViewDirection(0.0f, 0.0f, -1.0f),
	up(0.0f, 1.0f, 0.0f)
{
	 
}

glm::mat4 SceneCamera::getViewMatrix() const
{
	return glm::lookAt(position, position + ViewDirection, up);
}


// processes input received from a mouse input system.
void SceneCamera::mouseUpdate(const glm::vec2& newMousePostion)
{
	return;
}

// processes input received from any keyboard-like input system.
void SceneCamera::processKeyboardInput(GLFWwindow* window,float DeltaTime)
{
	const float velocity = MovementSpeed * DeltaTime; // adjust Camera Speed
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		position += velocity * ViewDirection;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		position -= velocity * ViewDirection;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		position -= glm::normalize(glm::cross(ViewDirection, up)) * velocity;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		position += glm::normalize(glm::cross(ViewDirection, up)) * velocity;
}