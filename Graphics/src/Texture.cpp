
#include "Texture.h"
#include"stb/stb_image.h"
#include "DebugUtils.h"


Texture::Texture(const char* filepath, std::string& directory, std::string_view TypeName, bool gamma)
	:m_Path(filepath),
	 m_TexType(TypeName),
	 m_nrChannels(0)

{
	std::string filename = std::string(filepath);
	filename = directory + '/' + filename;
	GLCall(glGenTextures(1, &m_ID));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_ID));

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

		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << filename << std::endl;
		stbi_image_free(data);
	}

}


Texture::~Texture()
{
	glDeleteTextures(1, &m_ID);
}

void Texture::Bind(uint32_t unit) const 
{
	GLCall(glActiveTexture(GL_TEXTURE0+unit));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_ID));
}

void Texture::Unbind() const
{
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}

std::string Texture::getPath() const
{
	return m_Path;
}

uint32_t Texture::getID() const
{
	return m_ID;
}

std::string Texture::getType() const
{
	return m_TexType;
}
