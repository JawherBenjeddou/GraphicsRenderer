#pragma once
#include <iostream>
#include "GL/glew.h"

class EBO {

public:
	EBO(const void* DATA, uint32_t size,uint32_t count);
	~EBO();

	//BIND AND UNBIND BUFFERS
	void Bind() const;

	void Unbind() const;

	inline uint32_t getCount() const { return m_Count; }

	bool isValid() const;

private:
	uint32_t m_ID;
	uint32_t m_Count;
};