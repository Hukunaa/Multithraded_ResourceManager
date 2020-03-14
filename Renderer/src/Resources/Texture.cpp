#include <../include/Resources/Texture.h>
#include <cstdio>
#include <vector>
#include <GL/glew.h>
#include <stdio.h>
#include <../include/Core/Math/Vector/Vec3.h>
#include <iostream>

using namespace Resources::Texture;

GLuint Texture::GenerateVBO(const std::vector<Vec3>& vertices, const std::vector<Vec3>& uvs, const std::vector<Vec3>& normals)
{
    std::vector<GLfloat> VBO_DATA;
	for (int i = 0; i < vertices.size(); ++i)
	{
		VBO_DATA.emplace_back(vertices[i].mf_x);
		VBO_DATA.emplace_back(vertices[i].mf_y);
		VBO_DATA.emplace_back(vertices[i].mf_z);
		VBO_DATA.emplace_back(normals[i].mf_x);
		VBO_DATA.emplace_back(normals[i].mf_y);
		VBO_DATA.emplace_back(normals[i].mf_z);
	}

    GLuint VBO;
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, VBO_DATA.size() * sizeof(GLfloat), VBO_DATA.data(), GL_STATIC_DRAW);

    return VBO;
}

GLuint Texture::GenerateVAO()
{
	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), nullptr);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), reinterpret_cast<void*>(3 * sizeof(GLfloat)));

    return VAO;


}

GLuint Texture::GenerateEBO(const std::vector<GLuint>& Indices)
{
    std::vector<GLuint> EBO_DATA;
    for (int i = 0; i < Indices.size(); ++i)
    {
        EBO_DATA.emplace_back(i);
    }

	GLuint EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, EBO_DATA.size() * sizeof(GLuint), EBO_DATA.data(), GL_STATIC_DRAW);

    return EBO;
}

