
#include "Texture.h"
#include"stb/stb_image.h"
#include "DebugUtils.h"

//Constructor for using custom simple Texture
// @param[in] PATH path of the texture.
//@param[in] TexType texture type written in form of texture_type where type can be (diffuse or specular).
Texture::Texture(const char* PATH, const std::string& TypeName)
	:m_TexType(TypeName)
{
	GLCall(glGenTextures(1, &m_ID));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_ID));
	// set the texture wrapping/filtering options (on currently bound texture)
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	// load and generate the texture
	unsigned char* image = stbi_load(PATH, &m_Width, &m_Height, &m_nrChannels, 0);
	if (image)
	{
		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image));
		GLCall(glGenerateMipmap(GL_TEXTURE_2D));
	}
	else
	{
		std::cout << "Texture failed to load at path: " << PATH << std::endl;
	}
	//stbi_set_flip_vertically_on_load(true); //FLIP IMAGE AFTER LOADED
	stbi_image_free(image);
}

//Constructor For using complex models Texture
Texture::Texture(const char* PATH, const std::string& directory, bool gamma)
{
	std::string filename = std::string(PATH);
	filename = directory + '/' + filename;

	
	GLCall(glGenTextures(1, &m_ID));

	unsigned char* data = stbi_load(filename.c_str(), &m_Width, &m_Height, &m_nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (m_nrComponents == 1)
			format = GL_RED;
		else if (m_nrComponents == 3)
			format = GL_RGB;
		else if (m_nrComponents == 4)
			format = GL_RGBA;

		GLCall(glBindTexture(GL_TEXTURE_2D, m_ID));
		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, format, m_Width, m_Height, 0, format, GL_UNSIGNED_BYTE, data));
		GLCall(glGenerateMipmap(GL_TEXTURE_2D));

		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT)));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << PATH << std::endl;
		stbi_image_free(data);
	}
;
}


Texture::~Texture()
{
	glDeleteTextures(1, &m_ID);
}

void Texture::Bind(const uint32_t& unit) const {
	glActiveTexture(GL_TEXTURE0+unit);
	glBindTexture(GL_TEXTURE_2D, m_ID);
}

void Texture::Unbind() const
{
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}

uint32_t Texture::getID() const
{
	return m_ID;
}

std::string Texture::getType() const
{
	return m_TexType;
}
