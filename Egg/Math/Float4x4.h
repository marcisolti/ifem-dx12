#pragma once

#include "Float3.h"
#include "Float4.h"
#include <cmath>
#include <cfloat>

namespace Egg {
	namespace Math {

		class Float3;
		class Float4;

		class Float4x4
		{
		public:
			union
			{
				struct
				{
					float        _00, _01, _02, _03;
					float        _10, _11, _12, _13;
					float        _20, _21, _22, _23;
					float        _30, _31, _32, _33;
				};
				float m[4][4];
				float l[16];
			};

			Float4x4() noexcept;

			Float4x4(
				float _00, float _01, float _02, float _03,
				float _10, float _11, float _12, float _13,
				float _20, float _21, float _22, float _23,
				float _30, float _31, float _32, float _33) noexcept;

			static const Float4x4 Identity;

			Float4x4 ElementwiseProduct(const Float4x4& o) const noexcept;

			Float4x4 operator+(const Float4x4& o) const noexcept;

			Float4x4 operator-(const Float4x4& o) const noexcept;

			Float4x4& AssignElementwiseProduct(const Float4x4& o) noexcept;

			Float4x4& operator*=(float s) noexcept;

			Float4x4& operator/=(float s) noexcept;

			Float4x4& operator+=(const Float4x4& o) noexcept;

			Float4x4& operator-=(const Float4x4& o) noexcept;

			Float4x4 Mul(const Float4x4& o) const noexcept;

			Float4x4 operator<<(const Float4x4& o) const noexcept;

			Float4x4& operator <<=(const Float4x4& o) noexcept;

			Float4x4 operator*(const Float4x4& o) const noexcept;

			Float4x4& operator*=(const Float4x4& o) noexcept;

			Float4 Mul(const Float4& v) const noexcept;

			Float4 Transform(const Float4& v) const noexcept;

			Float4 operator*(const Float4& v) const noexcept;

			Float4x4 operator*(float s) const noexcept;

			static Float4x4 Scaling(const Float3& factors) noexcept;

			static Float4x4 Translation(const Float3& offset) noexcept;

			static Float4x4 Rotation(const Float3& axis, float angle) noexcept;

			static Float4x4 Reflection(const Float4& plane) noexcept;

			static Float4x4 View(const Float3& eye, const Float3& ahead, const Float3& up) noexcept;

			static Float4x4 Proj(float fovy, float aspect, float zn, float zf) noexcept;

			Float4x4 Transpose() const noexcept;

			Float4x4 _Invert() const noexcept;

			Float4x4 Invert() const noexcept;
		};

		inline Float4 operator*(const Float4& v, const Float4x4& m) noexcept
		{
			return m.Transform(v);
		}

		inline const Float4& operator*=(Float4& v, const Float4x4& m) noexcept
		{
			v = m.Transform(v);
			return v;
		}
	}
}


