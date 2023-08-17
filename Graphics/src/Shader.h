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
	Shader();

	//USE / ACTIVATE SHADER
	void use();

	// utility uniform functions
	void setUniformBool(const std::string& name, bool value) const;
	
	void setUniformInt(const std::string& name, int value) const;
	
	void setUniformFloat(const std::string& name, float value) const;
	
	void setUniformMat4f(const std::string& name, glm::mat4 Matrix);

	uint32_t getId() { return m_ID; }

private:
	std::string readShadersCode(const char* filePath);

private:
	//PROGRAM ID
	uint32_t m_ID;
};