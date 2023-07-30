#pragma once
#include "GL/glew.h"
#include<iostream>
#include<fstream>
#include <sstream>
class Shader 
{
public:
	//PROGRAM ID

	Shader(const char* VFilePath, const char* FFilePath);

	//USE / ACTIVATE SHADER
	void use();

	// utility uniform functions
	void setBool(const std::string& name, bool value) const;
	
	void setInt(const std::string& name, int value) const;
	
	void setFloat(const std::string& name, float value) const;
	
	uint32_t getId() { return m_ID; }
private:
	uint32_t m_ID = 0;
};