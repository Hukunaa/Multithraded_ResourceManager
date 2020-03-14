#pragma once
#include <vector>
#include <atomic>
#include <future>
#include <iostream>
#include <string>

#include <Core/Math/Vector/Vec3.h>

using namespace Math::Vector;

namespace Resources::Model
{
	class Model
	{
	public:
		Model() = default;
        Model(const std::string& p_name) : m_name{ p_name } {}

		~Model() = default;



        std::string& GetName() { return m_name; }
        void SetName(const std::string& p_name) { m_name = p_name; }

        std::future<bool>& GetLoadedStatePromise() { return m_isLoadedFuture; }
        std::promise<bool>& GetPromise() { return m_loadedPromise; }

        std::atomic<bool>& GetLoadedState() { return m_loadedState; }
        std::atomic<bool>& GetQuadsState() { return m_isQuads; }

        std::vector<Vec3>& GetVertices() { return m_vertices; }
        std::vector<Vec3>& GetUVs() { return m_uvs; }
        std::vector<Vec3>& GetNormals() { return m_normals; }
        std::vector<unsigned int>& GetIndices() { return m_vIndices; }

    private:

		std::vector<Vec3> m_vertices;
		std::vector<Vec3> m_uvs;
		std::vector<Vec3> m_normals;

		std::vector<unsigned int> m_vIndices;

        std::future<bool> m_isLoadedFuture;
        std::promise<bool> m_loadedPromise;

        std::atomic<bool> m_isQuads{ false };
        std::atomic<bool> m_loadedState{ false };

        std::string m_name;
	};	
}

