#pragma once
#include <iostream>
#include "GL/glew.h"

class Texture {

public:
	Texture(const char* PATH);
	~Texture();



	//BIND AND UNBIND TEXTURE
	void Bind(int unit) const;
	void Unbind() const;

private:
	uint32_t m_ID;
	int m_Width,m_Height,m_nrChannels;
};