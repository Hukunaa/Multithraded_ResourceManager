#include <../include/Resources/Shader.h>
#include <iostream>
#include <GL/glew.h>
#include <string>
#include <fstream>
#include <sstream>

using namespace Resources::Shader;

GLuint Shader::CompileShader(const GLuint& p_type, const std::string& p_source)
{

	const char* vertexShaderChar = p_source.c_str();
	GLuint vertexShaderId = glCreateShader(p_type);

	glShaderSource(vertexShaderId, 1, &vertexShaderChar, nullptr);
	glCompileShader(vertexShaderId);

	int success;
	char infoLog[512];
	glGetShaderInfoLog(vertexShaderId, 512, nullptr, infoLog);
	glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		std::cout << "Error Vertex shader compilation failed\n" << infoLog << std::endl;
	}
	return vertexShaderId;
}

std::string Shader::ShaderProgramSource(const std::string& p_filePath)
{
	std::string fileString;
	std::ifstream fileStream;
	std::stringstream dataStream;

	try
	{
		fileStream.open(p_filePath);
		dataStream << fileStream.rdbuf();
		fileString = dataStream.str();
		fileStream.close();
	}
	catch (std::ifstream::failure& exception)
	{
		std::cout << "Issue occured with specified file\n";
		std::cout << exception.what() << '\n';
	}

	return fileString;
}

void Shader::LoadRainBowShader()
{
	GLuint vertexShaderId = CompileShader(GL_VERTEX_SHADER, ShaderProgramSource("res/Shaders/VerticesShader.vert"));
	GLuint fragmentShaderId = CompileShader(GL_FRAGMENT_SHADER, ShaderProgramSource("res/Shaders/FragmentShader.frag"));
	glAttachShader(m_shader, vertexShaderId);
	glAttachShader(m_shader, fragmentShaderId);
	glLinkProgram(m_shader);

	glDeleteShader(vertexShaderId);
	glDeleteShader(fragmentShaderId);
}

void Shader::SetupRainBowShader()
{

	const GLint lightPos = glGetUniformLocation(m_shader, "lightPos");
	const GLint viewPos = glGetUniformLocation(m_shader, "viewPos");
	const GLint ModelMatrix = glGetUniformLocation(m_shader, "ModelMatrix");
	const GLint Camera = glGetUniformLocation(m_shader, "CameraMatrix");
	const GLint Projection = glGetUniformLocation(m_shader, "ProjectionMatrix");
	const GLint lightColor = glGetUniformLocation(m_shader, "lightColor");
	const GLint time = glGetUniformLocation(m_shader, "time");

	m_shaderData[0] = lightPos;
	m_shaderData[1] = viewPos;
	m_shaderData[2] = ModelMatrix;
	m_shaderData[3] = Camera;
	m_shaderData[4] = Projection;
	m_shaderData[5] = lightColor;
	m_shaderData[6] = time;
	
}
