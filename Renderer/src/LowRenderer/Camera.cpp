#include <../include/LowRenderer/Camera.h>
#include <Core/Math/Vector/Vec3.h>
#include <Core/Math/Matrix/Mat4.h>

using namespace Math::Vector;
using namespace  Math::Matrix;
using namespace LowRenderer::Camera;

Camera::Camera()
{
	m_position = { 0.0f, 0.0f, -20.0f };
	m_target = { 0.0f,0.0f,0.0f };
	m_up = { 0.0f,-1.0f,0.0f };

	m_forwardDir = m_position - m_target;
	m_forwardDir.Normalize();

	m_rightDir = Vec3::crossProduct(m_forwardDir, m_up);
	m_rightDir.Normalize();

	m_resultVec = Vec3::crossProduct(m_forwardDir, m_rightDir);

	float Camera[4][4]
	{
		{ m_rightDir.mf_x, m_resultVec.mf_x, m_forwardDir.mf_x, m_position.mf_x },
		{ m_rightDir.mf_y, m_resultVec.mf_y, m_forwardDir.mf_y, m_position.mf_y },
		{ m_rightDir.mf_z, m_resultVec.mf_z, m_forwardDir.mf_z, m_position.mf_z },
		{ 0.0f,0.0f,0.0f,1.0f }
	};

	m_transform.SetMatrix(Camera);
}




Camera::~Camera()
{
}


void Camera::UpdatePositionWithKeyBoard(float speed, GLFWwindow * window)
{
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		SetPosition(Vec3(0, -speed, 0));
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		SetPosition(Vec3(0, speed, 0));
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		SetPosition(Vec3(-speed, 0, 0));
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		SetPosition(Vec3(speed, 0, 0));
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		SetPosition(Vec3(0, 0, speed));
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		SetPosition(Vec3(0, 0, -speed));
	}

	if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}

void Camera::SetPosition(const Vec3& position)
{
	Vec3 addPos = position;
	m_position = m_position + addPos;

	float Camera[4][4]
	{
		{ m_rightDir.mf_x, m_resultVec.mf_x, m_forwardDir.mf_x, m_position.mf_x },
	{ m_rightDir.mf_y, m_resultVec.mf_y, m_forwardDir.mf_y, m_position.mf_y },
	{ m_rightDir.mf_z, m_resultVec.mf_z, m_forwardDir.mf_z, m_position.mf_z },
	{ 0.0f,0.0f,0.0f,1.0f }
	};

	m_transform.SetMatrix(Camera);
}

void Camera::SetTarget(const Vec3& target)
{
	m_target = target;

	m_forwardDir = m_position - m_target;
	m_forwardDir.Normalize();

	m_rightDir = Vec3::crossProduct(m_forwardDir, m_up);
	m_rightDir.Normalize();

	m_resultVec = Vec3::crossProduct(m_rightDir, m_forwardDir);

	float Camera[4][4]
	{
		{ m_rightDir.mf_x, m_resultVec.mf_x, m_forwardDir.mf_x, m_position.mf_x },
	{ m_rightDir.mf_y, m_resultVec.mf_y, m_forwardDir.mf_y, m_position.mf_y },
	{ m_rightDir.mf_z, m_resultVec.mf_z, m_forwardDir.mf_z, m_position.mf_z },
	{ 0.0f,0.0f,0.0f,1.0f }
	};

	m_transform.SetMatrix(Camera);
}
