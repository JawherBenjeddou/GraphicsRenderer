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
	Shader(const char* FragPath, const char* VertPath);

	//USE / ACTIVATE SHADER
	void use();

	// utility uniform functions
	void setUniformBool(std::string_view name, bool value) const;
	
	void setUniformInt(std::string_view name, int value) const;
	
	void setUniformFloat(std::string_view name, float value) const;
	
	void setUniform3Float(std::string_view name, glm::vec3 RGB) const;

	void setUniformMat4f(std::string_view name, glm::mat4 Matrix);

	uint32_t getId() { return m_ID; }

private:
	std::string readShadersCode(const char* filePath);

private:
	//PROGRAM ID
	uint32_t m_ID;
};