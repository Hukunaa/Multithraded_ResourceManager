#pragma once
#include <string>

#include <Core/Math/Matrix/Mat4.h>
#include <../include/Resources/Model.h>

using namespace Math::Matrix;
using namespace Resources::Model;

namespace LowRenderer::Mesh
{
	class Mesh
	{
	public:

        Mesh() : m_isLoaded { false }, m_canInit{ true }{}
        Mesh(const std::string& modelName) : m_modelName{ modelName }, m_isLoaded{ false }, m_canInit{ true }
        {
            CreateMesh();
        }
        
        ~Mesh() = default;

        std::shared_ptr<Model> m_model{};
        std::string m_modelName;

        GLuint VBO{};
        GLuint VAO{};
        GLuint EBO{};

        void CreateMesh();
        void Init();
		void UpdateRotation(const float& angle, bool Xaxis, bool Yaxis, bool Zaxis);
		void UpdateScale(const float& scale);
		void UpdatePosition(float Xaxis, float Yaxis, float Zaxis);

        void SetModel(const std::string& p_name) { m_modelName = p_name; CreateMesh(); }

		Mat4 GetTransform();
		Mat4 GetPosition();
		Mat4 GetRotation();
		Mat4 GetScale();

        bool& GetInitStatus() { return m_canInit; }
        bool& GetLoadedStatus() { return m_isLoaded; }

        void SetInitStatus(const bool& value) { m_canInit = value; }
        void SetLoadedStatus(const bool& value) { m_isLoaded = value; }

    private:

        bool m_canInit;
        bool m_isLoaded;

        Mat4 Transform;
        Mat4 Position;
        Mat4 Rotation;
        Mat4 Scale;
	};
}

