#include "EBO.h"
#include "DebugUtils.h"
EBO::EBO(const void* DATA, uint32_t size,uint32_t count)
{
	m_Count = count;
	GLCall(glGenBuffers(1, &m_ID));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID););
	// Combine position, color, and texture coordinate data into a single buffer
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, DATA, GL_STATIC_DRAW));
}

EBO::~EBO()
{
	GLCall(glDeleteBuffers(1, &m_ID));
}

void EBO::Bind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID));
}

void EBO::Unbind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}