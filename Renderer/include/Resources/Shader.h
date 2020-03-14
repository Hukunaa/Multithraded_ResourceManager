#pragma once
#include <iostream>
#include <GL/glew.h>
#include <Core/Math/Vector/Vec3.h>

using namespace Math::Vector;

namespace Resources::Shader
{
	class Shader
	{
	public:
        Shader() { m_shader = glCreateProgram(); };
		~Shader() = default;

        GLint m_shaderData[7]{};

        float m_time{ 0 };

		static GLuint CompileShader(const GLuint& p_type, const std::string& p_source);
		static std::string ShaderProgramSource(const std::string& p_filePath);

		void LoadRainBowShader();
		void SetupRainBowShader();

        GLuint& GetShaderID() { return m_shader; }
        Vec3& GetColor() { return m_color; }

    private:

		Vec3 m_color;
		GLuint m_shader;

	};
}
