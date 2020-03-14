#pragma once
#include <memory>
#include <Core/Math/Vector/Vec4.h>
#include <Core/Math/Vector/Vec3.h>

namespace Math::Matrix
{
    class Mat4
    {
    public:
        float mf_Matrice4[4][4];

		Mat4();
		~Mat4() = default;
		Mat4(Mat4& p_Matrix);
		Mat4(Math::Vector::Vec3& p_vec);

		void SetMatrix(float p_Matrix[][4]);

		Mat4 operator*(const Mat4& p_Matrix);
		Vector::Vec4& operator*(const Math::Vector::Vec4& p_Vector);

    	static Mat4 CreateTranslationMatrix(const Vector::Vec3& p_Translation);
		static Mat4 CreateScaleMatrix(const float& p_Scale);
		static Mat4 CreateRotationMatrix(const float& p_Angle, const bool& isX, const bool& isY, const bool& isZ);
		static Mat4 CreatePerspectiveMatrix(const float& angle_of_view, const float& ratio, const float& near, const float& far);
		static void MatrixToShader(const Mat4& p_matrix, GLfloat (&array)[16]);
    };
}
