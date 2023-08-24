#include "SceneCamera.h"

SceneCamera::SceneCamera() :
    m_position(0.0f, 0.0f, 7.0f),
    m_ViewDirection(0.0f, 0.0f, -1.0f),
    m_up(0.0f, 1.0f, 0.0f),
    m_LastMousePosition(0.0f, 0.0f)
{
	 
}

glm::mat4 SceneCamera::getViewMatrix() const
{
	return glm::lookAt(m_position, m_position + m_ViewDirection, m_up);
}

glm::mat4 SceneCamera::getProjectionMatrix() const
{
	return glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 500.0f);
}

void SceneCamera::setMouseSensitivity(float NewSens)
{
    m_MouseSensitivity = NewSens;
}

// processes input received from a mouse input system.
void SceneCamera::MouseRotation(const glm::vec2& newMousePosition)
{
    // Calculate the mouse's offset since the last frame
    glm::vec2 mouseOffset = newMousePosition - m_LastMousePosition;
    m_LastMousePosition = newMousePosition;

    // Apply mouse sensitivity to the offset
    mouseOffset *= m_MouseSensitivity;

    // Calculate new yaw and pitch angles based on the mouse offset
    m_Yaw += mouseOffset.x;
    m_Pitch -= mouseOffset.y;

    // Clamp pitch to avoid gimbal lock
    if (m_Pitch > 89.0f)
        m_Pitch = 89.0f;
    if (m_Pitch < -89.0f)
        m_Pitch = -89.0f;

    // Calculate new m_ViewDirection vector
    glm::vec3 front;
    front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
    front.y = sin(glm::radians(m_Pitch));
    front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
    m_ViewDirection = glm::normalize(front);
}

// processes input received from any keyboard-like input system.
void SceneCamera::ProcessKeyboardInput(GLFWwindow* window,float DeltaTime)
{
	const float velocity = MovementSpeed * DeltaTime; // adjust Camera Speed
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		m_position += velocity * m_ViewDirection;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		m_position -= velocity * m_ViewDirection;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		m_position -= glm::normalize(glm::cross(m_ViewDirection, m_up)) * velocity;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		m_position += glm::normalize(glm::cross(m_ViewDirection, m_up)) * velocity;
}

glm::vec3 SceneCamera::getViewDirection()
{
    return m_ViewDirection;
}

glm::vec3 SceneCamera::getCameraPosition()
{
    return m_position;
}