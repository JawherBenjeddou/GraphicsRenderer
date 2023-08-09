#pragma once
#include <iostream>
#include "GL/glew.h"

class VBO {

public:
	VBO(const void* DATA, uint32_t size);
	~VBO();

	//BIND AND UNBIND BUFFERS
	void Bind() const;
	void Unbind() const;
private:
	uint32_t m_ID;
};