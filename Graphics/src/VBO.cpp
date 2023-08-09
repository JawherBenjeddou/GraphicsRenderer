#include "VBO.h"
#include "DebugUtils.h"

VBO::VBO()
{
	GLCall(glGenBuffers(1, &m_ID));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_ID));
}

VBO::~VBO()
{
	GLCall(glDeleteBuffers(1, &m_ID));
}

void VBO::Bind() const
{ 
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_ID));
}

void VBO::Unbind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void VBO::BufferData(uint32_t size, const void* data)
{
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

void VBO::BufferSubData(uint32_t offset, uint32_t size, const void* data)
{
	GLCall(glBufferSubData(GL_ARRAY_BUFFER, offset, size, data));
}