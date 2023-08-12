#include "SceneCamera.h"

SceneCamera::SceneCamera() :
	position(0.0f, 0.0f, 3.0f),
	ViewDirection(0.0f, 0.0f, -1.0f),
	up(0.0f, 1.0f, 0.0f)
{
	 
}

SceneCamera::~SceneCamera()
{

}

glm::mat4 SceneCamera::getViewMatrix() const
{
	return glm::lookAt(position, position + ViewDirection, up);
}

void SceneCamera::mouseUpdate(const glm::vec2& newMousePostion)
{
	return;
}

void SceneCamera::processKeyboardInput(GLFWwindow* window,float DeltaTime)
{
	const float cameraSpeed = 3.5f * DeltaTime; // adjust Camera Speed
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		position += cameraSpeed * ViewDirection;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		position -= cameraSpeed * ViewDirection;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		position -= glm::normalize(glm::cross(ViewDirection, up)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		position += glm::normalize(glm::cross(ViewDirection, up)) * cameraSpeed;
}