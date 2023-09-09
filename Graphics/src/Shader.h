#pragma once
#include "GL/glew.h"


#include <iostream>
#include <fstream>
#include <sstream>


#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "DebugUtils.h"

class Shader 
{
public:
	//Constructor
	Shader(std::string_view FragPath,std::string_view VertPath);

	//USE / ACTIVATE SHADER
	void use();

	template <typename Type>
	void setUniformValue(std::string_view name, Type value) const = delete;

	template <>
	void setUniformValue<int>(std::string_view name, int value) const {
		GLCall(glUniform1i(glGetUniformLocation(m_ID, name.data()), value));
	}

	template <>
	void setUniformValue<float>(std::string_view name, float value) const {
		GLCall(glUniform1f(glGetUniformLocation(m_ID, name.data()), value));
	}
	template <>
	void setUniformValue<glm::vec3>(std::string_view name, glm::vec3 RGB) const {
		GLCall(glUniform3f(glGetUniformLocation(m_ID, name.data()), RGB.x, RGB.y, RGB.z));
	}
	template<>
	void setUniformValue<glm::mat4>(std::string_view name, glm::mat4 Matrix) const {
		uint32_t Location = glGetUniformLocation(m_ID, name.data()); //Get uniform location
		GLCall(glUniformMatrix4fv(Location, 1, GL_FALSE, glm::value_ptr(Matrix))); //pass uniform location to glUniformMatrix() and pass matrix using glm::value_ptr()}
	}

	uint32_t getId() const { 
		return m_ID; 
	}

private:

	std::string readShadersCode(std::string_view filePath);

private:
	//PROGRAM ID
	uint32_t m_ID;
};