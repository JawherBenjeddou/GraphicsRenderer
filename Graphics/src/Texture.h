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
	int32_t m_Width;
	int32_t m_Height; 
	int32_t m_nrChannels;
};