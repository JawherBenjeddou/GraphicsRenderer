#pragma once
#include <iostream>

#include "GL/glew.h"
class VAO {

public:
	VAO();
	~VAO();

	//BIND AND UNBIND BUFFERS
	void Bind() const;
	void Unbind() const;
private:
	uint32_t m_ID;
};