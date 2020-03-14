#pragma once
#include <GL/glew.h>

#include <cstdio>
#include <vector>
#include <../include/Core/Math/Vector/Vec3.h>

using namespace Math::Vector;

namespace Resources::Texture
{
	class Texture
	{
	public:
		Texture() = default;
		~Texture() = default;

		static GLuint GenerateVBO(const std::vector<Vec3>& vertices, const std::vector<Vec3>& uvs, const std::vector<Vec3>& normals);
		static GLuint GenerateVAO();
		static GLuint GenerateEBO(const std::vector<GLuint>& Indices);
	};
}

