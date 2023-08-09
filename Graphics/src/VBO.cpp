#include "VBO.h"
#include "DebugUtils.h"
VBO::VBO(const void* DATA, uint32_t size)
{
	GLCall(glGenBuffers(1, &m_ID));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_ID));
    // Combine position, color, and texture coordinate data into a single buffer
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, DATA, GL_STATIC_DRAW));

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
