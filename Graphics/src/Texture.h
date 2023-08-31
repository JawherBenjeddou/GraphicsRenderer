#pragma once
#include <iostream>

#include "GL/glew.h"

class Texture {

public:
	Texture(const char* PATH,std::string TexName);
	~Texture();



	//BIND AND UNBIND TEXTURE
	void Bind(uint32_t unit = 0) const;

	void Unbind() const;

	uint32_t getID() const;

	std::string getType() const;

private:
	uint32_t m_ID;
	int32_t m_Width;
	int32_t m_Height; 
	int32_t m_nrChannels;
	std::string m_TexType;
};