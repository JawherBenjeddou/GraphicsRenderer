#include "Shader.h"


Shader::Shader(std::string_view FragPath, std::string_view VertPath)
{
	//Handling Files
	std::string vShaderCode = readShadersCode(VertPath);
	std::string fShaderCode = readShadersCode(FragPath);
	const char* vCode = vShaderCode.c_str();
	const char* fCode = fShaderCode.c_str();

	uint32_t vertex, fragment;
	int success;
	char VertexinfoLog[512];
	//Create and Compile the vertex shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	GLCall(glShaderSource(vertex, 1, &vCode, NULL));
	GLCall(glCompileShader(vertex));
	// print compile errors if any
	GLCall(glGetShaderiv(vertex, GL_COMPILE_STATUS, &success));
	if (!success)
	{
		GLCall(glGetShaderInfoLog(vertex, 512, NULL, VertexinfoLog));
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" <<
			VertexinfoLog << std::endl;
	};

	char FragmentinfoLog[512];
	//Create and Compile the fragment shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	GLCall(glShaderSource(fragment, 1, &fCode, NULL));
	GLCall(glCompileShader(fragment));
	//check for compile errors for fragment Shader
	GLCall(glGetShaderiv(fragment, GL_COMPILE_STATUS, &success));
	if (!success)
	{
		glGetShaderInfoLog(fragment, 512, NULL, FragmentinfoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" <<
			FragmentinfoLog << std::endl;
	}

	//LINKING SHADERS TO THE PROGRAM
	m_ID = glCreateProgram();
	GLCall(glAttachShader(m_ID, vertex));
	GLCall(glAttachShader(m_ID, fragment));
	GLCall(glLinkProgram(m_ID));

	// print linking errors if any
	GLCall(glGetProgramiv(m_ID, GL_LINK_STATUS, &success));
	if (!success)
	{
		glGetProgramInfoLog(m_ID, 512, NULL, VertexinfoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" <<
			FragmentinfoLog << std::endl;
	}
	GLCall(glDeleteShader(vertex));
	GLCall(glDeleteShader(fragment));
}

void Shader::use()
{
	GLCall(glUseProgram(m_ID));
}


std::string Shader::readShadersCode(std::string_view filePath) {
	std::string code;
	std::ifstream shaderFile;
	// ensure ifstream objects can throw exceptions:
	shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try {
		shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		shaderFile.open(filePath.data());
		std::stringstream shaderStream;
		shaderStream << shaderFile.rdbuf();
		shaderFile.close();
		code = shaderStream.str();
	}
	catch (std::ifstream::failure e) {
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
	}
	return code;
}