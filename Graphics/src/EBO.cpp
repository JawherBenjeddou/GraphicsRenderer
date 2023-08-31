#include "EBO.h"
#include "DebugUtils.h"

EBO::EBO() : m_ID(NULL)
{
	
	GLCall(glGenBuffers(1, &m_ID));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID););
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

bool EBO::isValid() const
{
	return m_ID != 0;
}

void EBO::BufferData(uint32_t size, const void* data)
{
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}
