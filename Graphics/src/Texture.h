#pragma once
#include <iostream>

#include "GL/glew.h"



class Texture {

public:
	
	Texture(const char* PATH,std::string_view TypeName);

	Texture(const char* PATH, const std::string& directory, std::string_view TypeName, bool gamma = 0);
	
	Texture(const Texture& other) = delete; // explicitly delete the copy constructor

	Texture(Texture&& other) noexcept
		:m_ID(std::move(other.m_ID)),
		 m_Width(std::move(other.m_Width)),
		 m_Height(std::move(other.m_Height)),
		 m_nrChannels(std::move(other.m_nrChannels)),
		 m_TexType(std::move(other.m_TexType)) 
	{
		other.m_ID = 0;
		other.m_Width = 0;
		other.m_Height = 0;
		other.m_nrChannels = 0;
		other.m_TexType.clear();
	}

	~Texture();

	//BIND AND UNBIND TEXTURE
	//const uint32_t& : this is used so the function accepts l and r values (r value = "0" l value = "i")
	//bcs using only int& make us unable to use r values

	void Bind(uint32_t unit = 0) const; 

	void Unbind() const;

	uint32_t getID() const;

	std::string getType() const;

	std::string getPath() const;
private:
	uint32_t m_ID;
	std::string m_TexType;
	std::string m_Path;

	int32_t m_Width;
	int32_t m_Height; 
	int32_t m_nrChannels;
	int32_t m_nrComponents;
};