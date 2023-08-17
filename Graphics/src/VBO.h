#pragma once
#include <iostream>

#include "GL/glew.h"

class VBO {

public:
	VBO();
	~VBO();

	//BIND AND UNBIND BUFFERS
	void Bind() const;
	void Unbind() const;

	void BufferSubData(uint32_t offset, uint32_t size, const void* data);

	void BufferData(uint32_t size, const void* data);

private:
	uint32_t m_ID;
};