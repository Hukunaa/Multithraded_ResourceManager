#pragma once
#include "Core/Math/Matrix/Mat4.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace Math::Matrix;
using namespace Math::Vector;


namespace LowRenderer::Camera
{
	class Camera
	{
	public:
		Camera();
		~Camera();

		Vec3 m_position;
		Vec3 m_target;
		Vec3 m_up;
		Vec3 m_rightDir;
		Vec3 m_forwardDir;
		Vec3 m_resultVec;

		Mat4 m_transform;


		void UpdatePositionWithKeyBoard(float speed, GLFWwindow* window);
		void SetPosition(const Vec3& position);
		void SetTarget(const Vec3& target);
	};
}

