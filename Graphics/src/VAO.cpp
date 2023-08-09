#include "VAO.h"
#include "DebugUtils.h"
VAO::VAO()
{
	GLCall(glGenVertexArrays(1, &m_ID));
	GLCall(glBindVertexArray(m_ID));
}

VAO::~VAO()
{
	GLCall(glDeleteVertexArrays(1, &m_ID));
}

void VAO::Bind() const
{
	GLCall(glBindVertexArray(m_ID));
}

void VAO::Unbind() const
{
	GLCall(glBindVertexArray(0));
}