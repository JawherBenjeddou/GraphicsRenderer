#pragma once
#include <iostream>

#include "GL/glew.h"

class EBO {

public:

	 EBO();

	~EBO();

	//BIND AND UNBIND BUFFERS
	void Bind() const;

	void Unbind() const;

	bool isValid() const;

	void BufferData(uint32_t size, const void* data);

private:
	uint32_t m_ID;
};