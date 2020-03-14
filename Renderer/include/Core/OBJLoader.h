#pragma once
#include <cstdio>
#include <vector>
#include <string>
#include <Core/Math/Vector/Vec3.h>
#include <Core/OBJLoader.h>
#include <Resources/Model.h>
#include <LowRenderer/Mesh.h>

using namespace Math::Vector;

namespace Resources::Model::OBJParser
{
	class OBJLoader
	{
	public:
		OBJLoader() = default;
		~OBJLoader() = default;

        static void CalculateTriangles(const char* filePath, std::vector<Vec3>& tmp_vertices);
        static void CalculateUV(const char* filePath, std::vector<Vec3>& tmp_uvs);
        static void CalculateNormals(const char* filePath, std::vector<Vec3>& o_normals);

		static void LoadObj(const std::string& path, std::shared_ptr<Resources::Model::Model> p_mesh);
	};
}
