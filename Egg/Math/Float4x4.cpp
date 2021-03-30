#include "Float4x4.h"

namespace Egg {
	namespace Math {


		Float4x4::Float4x4() noexcept :
			_00(1.0f), _01(0.0f), _02(0.0f), _03(0.0f),
			_10(0.0f), _11(1.0f), _12(0.0f), _13(0.0f),
			_20(0.0f), _21(0.0f), _22(1.0f), _23(0.0f),
			_30(0.0f), _31(0.0f), _32(0.0f), _33(1.0f)
		{ }

		Float4x4::Float4x4(
			float _00, float _01, float _02, float _03,
			float _10, float _11, float _12, float _13,
			float _20, float _21, float _22, float _23,
			float _30, float _31, float _32, float _33) noexcept :
			_00(_00), _01(_01), _02(_02), _03(_03),
			_10(_10), _11(_11), _12(_12), _13(_13),
			_20(_20), _21(_21), _22(_22), _23(_23),
			_30(_30), _31(_31), _32(_32), _33(_33)
		{ }

		const Float4x4 Float4x4::Identity{};

		Float4x4 Float4x4::ElementwiseProduct(const Float4x4& o) const noexcept
		{
			Float4x4 r;
			for(int i = 0; i < 16; i++)
				r.l[i] = l[i] * o.l[i];
			return r;
		}

		Float4x4 Float4x4::operator+(const Float4x4& o) const noexcept
		{
			Float4x4 r;
			for(int i = 0; i < 16; i++)
				r.l[i] = l[i] + o.l[i];
			return r;
		}

		Float4x4 Float4x4::operator-(const Float4x4& o) const noexcept
		{
			Float4x4 r;
			for(int i = 0; i < 16; i++)
				r.l[i] = l[i] - o.l[i];
			return r;
		}

		Float4x4& Float4x4::AssignElementwiseProduct(const Float4x4& o) noexcept
		{
			for(int i = 0; i < 16; i++)
				l[i] *= o.l[i];
			return *this;
		}

		Float4x4& Float4x4::operator*=(float s) noexcept
		{
			for(int i = 0; i < 16; i++)
				l[i] *= s;
			return *this;
		}

		Float4x4& Float4x4::operator/=(float s) noexcept
		{
			float is = 1 / s;
			for(int i = 0; i < 16; i++)
				l[i] *= is;
			return *this;
		}

		Float4x4& Float4x4::operator+=(const Float4x4& o) noexcept
		{
			for(int i = 0; i < 16; i++)
				l[i] += o.l[i];
			return *this;
		}

		Float4x4& Float4x4::operator-=(const Float4x4& o) noexcept
		{
			for(int i = 0; i < 16; i++)
				l[i] -= o.l[i];
			return *this;
		}

		Float4x4 Float4x4::Mul(const Float4x4& o) const noexcept
		{
			Float4x4 product;

			for(int r = 0; r < 4; r++)
				for(int c = 0; c < 4; c++)
					product.m[r][c] =
					m[r][0] * o.m[0][c] +
					m[r][1] * o.m[1][c] +
					m[r][2] * o.m[2][c] +
					m[r][3] * o.m[3][c];

			return product;
		}

		Float4x4 Float4x4::operator<<(const Float4x4& o) const noexcept
		{
			return Mul(o);
		}

		Float4x4& Float4x4::operator <<=(const Float4x4& o) noexcept
		{
			*this = *this << o;
			return *this;
		}

		Float4x4 Float4x4::operator*(const Float4x4& o) const noexcept
		{
			return Mul(o);
		}

		Float4x4& Float4x4::operator*=(const Float4x4& o) noexcept
		{
			*this = *this * o;
			return *this;
		}

		Float4 Float4x4::Mul(const Float4& v) const noexcept
		{
			return Float4(v.Dot(*(Float4*)m[0]), v.Dot(*(Float4*)m[1]), v.Dot(*(Float4*)m[2]), v.Dot(*(Float4*)m[3]));
		}

		Float4 Float4x4::Transform(const Float4& v) const noexcept
		{
			return Float4(
				_00 * v.x + _10 * v.y + _20 * v.z + _30 * v.w,
				_01 * v.x + _11 * v.y + _21 * v.z + _31 * v.w,
				_02 * v.x + _12 * v.y + _22 * v.z + _32 * v.w,
				_03 * v.x + _13 * v.y + _23 * v.z + _33 * v.w
			);
		}

		Float4 Float4x4::operator*(const Float4& v) const noexcept
		{
			return Mul(v);
		}

		Float4x4 Float4x4::operator*(float s) const noexcept
		{
			Float4x4 r;
			for(int i = 0; i < 16; i++)
				r.l[i] = l[i] * s;
			return r;
		}

		Float4x4 Float4x4::Scaling(const Float3& factors) noexcept
		{
			Float4x4 s = Identity;
			s._00 = factors.x;
			s._11 = factors.y;
			s._22 = factors.z;

			return s;
		}

		Float4x4 Float4x4::Translation(const Float3& offset) noexcept
		{
			Float4x4 t = Identity;
			t._30 = offset.x;
			t._31 = offset.y;
			t._32 = offset.z;
			return t;
		}

		Float4x4 Float4x4::Rotation(const Float3& axis, float angle) noexcept
		{
			Float4x4 r = Identity;

			float s = sin(angle);
			float c = cos(angle);
			float t = 1 - c;

			float axisLength = axis.Length();
			if(axisLength == 0.0f)
				return Identity;
			Float3 ax = axis / Float3{ axisLength, axisLength, axisLength };

			float& x = ax.x;
			float& y = ax.y;
			float& z = ax.z;

			r._00 = t * x*x + c;
			r._01 = t * y*x + s * z;
			r._02 = t * z*x - s * y;

			r._10 = t * x*y - s * z;
			r._11 = t * y*y + c;
			r._12 = t * z*y + s * x;

			r._20 = t * x*z + s * y;
			r._21 = t * y*z - s * x;
			r._22 = t * z*z + c;

			return r;
		}

		Float4x4 Float4x4::Reflection(const Float4& plane) noexcept
		{
			Float4 normalPlane = plane / plane.xyz.Length();

			return Float4x4(
				-2 * normalPlane.x * normalPlane.x + 1, -2 * normalPlane.y * normalPlane.x, -2 * normalPlane.z * normalPlane.x, 0,
				-2 * normalPlane.x * normalPlane.y, -2 * normalPlane.y * normalPlane.y + 1, -2 * normalPlane.z * normalPlane.y, 0,
				-2 * normalPlane.x * normalPlane.z, -2 * normalPlane.y * normalPlane.z, -2 * normalPlane.z * normalPlane.z + 1, 0,
				-2 * normalPlane.x * normalPlane.w, -2 * normalPlane.y * normalPlane.w, -2 * normalPlane.z * normalPlane.w, 1);
		}


		Float4x4 Float4x4::View(const Float3& eye, const Float3& ahead, const Float3& up) noexcept
		{
			Float3 zaxis = ahead.Normalize();
			Float3 xaxis = up.Cross(zaxis).Normalize();
			Float3 yaxis = zaxis.Cross(xaxis);

			return Float4x4(
				xaxis.x, yaxis.x, zaxis.x, 0,
				xaxis.y, yaxis.y, zaxis.y, 0,
				xaxis.z, yaxis.z, zaxis.z, 0,
				-xaxis.Dot(eye), -yaxis.Dot(eye), -zaxis.Dot(eye), 1);
		}

		Float4x4 Float4x4::Proj(float fovy, float aspect, float zn, float zf) noexcept
		{
			float yScale = 1.0f / ::tanf(fovy * 0.5f);
			float xScale = yScale / aspect;
			return Float4x4(
				xScale, 0.0f, 0.0f, 0.0f,
				0.0f, yScale, 0.0f, 0.0f,
				0.0f, 0.0f, zf / (zf - zn), 1,
				0.0f, 0.0f, -zn * zf / (zf - zn), 0);
		}

		Float4x4 Float4x4::Transpose() const noexcept
		{
			return Float4x4(
				_00, _10, _20, _30,
				_01, _11, _21, _31,
				_02, _12, _22, _32,
				_03, _13, _23, _33);
		}

		Float4x4 Float4x4::_Invert() const noexcept
		{
			float det;
			float d10, d20, d21, d31, d32, d03;
			Float4x4 inv;

			/* Inverse = adjoint / det. (See linear algebra texts.)*/

			/* pre-compute 2x2 dets for last two rows when computing */
			/* cofactors of first two rows. */
			d10 = (_02*_13 - _03 * _12);
			d20 = (_02*_23 - _03 * _22);
			d21 = (_12*_23 - _13 * _22);
			d31 = (_12*_33 - _13 * _32);
			d32 = (_22*_33 - _23 * _32);
			d03 = (_32*_03 - _33 * _02);

			inv.l[0] = (_11 * d32 - _21 * d31 + _31 * d21);
			inv.l[1] = -(_01 * d32 + _21 * d03 + _31 * d20);
			inv.l[2] = (_01 * d31 + _11 * d03 + _31 * d10);
			inv.l[3] = -(_01 * d21 - _11 * d20 + _21 * d10);

			/* Compute determinant as early as possible using these cofactors. */
			det = _00 * inv.l[0] + _10 * inv.l[1] + _20 * inv.l[2] + _30 * inv.l[3];

			/* Run singularity test. */
			if(det == 0.0) {
				return Identity;
			} else
			{
				float invDet = 1.0f / det;
				/* Compute rest of inverse. */
				inv.l[0] *= invDet;
				inv.l[1] *= invDet;
				inv.l[2] *= invDet;
				inv.l[3] *= invDet;

				inv.l[4] = -(_10 * d32 - _20 * d31 + _30 * d21) * invDet;
				inv.l[5] = (_00 * d32 + _20 * d03 + _30 * d20) * invDet;
				inv.l[6] = -(_00 * d31 + _10 * d03 + _30 * d10) * invDet;
				inv.l[7] = (_00 * d21 - _10 * d20 + _20 * d10) * invDet;

				/* Pre-compute 2x2 dets for first two rows when computing */
				/* cofactors of last two rows. */
				d10 = _00 * _11 - _01 * _10;
				d20 = _00 * _21 - _01 * _20;
				d21 = _10 * _21 - _11 * _20;
				d31 = _10 * _31 - _11 * _30;
				d32 = _20 * _31 - _21 * _30;
				d03 = _30 * _01 - _31 * _00;

				inv.l[8] = (_13 * d32 - _23 * d31 + _33 * d21) * invDet;
				inv.l[9] = -(_03 * d32 + _23 * d03 + _33 * d20) * invDet;
				inv.l[10] = (_03 * d31 + _13 * d03 + _33 * d10) * invDet;
				inv.l[11] = -(_03 * d21 - _13 * d20 + _23 * d10) * invDet;
				inv.l[12] = -(_12 * d32 - _22 * d31 + _32 * d21) * invDet;
				inv.l[13] = (_02 * d32 + _22 * d03 + _32 * d20) * invDet;
				inv.l[14] = -(_02 * d31 + _12 * d03 + _32 * d10) * invDet;
				inv.l[15] = (_02 * d21 - _12 * d20 + _22 * d10) * invDet;

				return inv;
			}
		}

		Float4x4 Float4x4::Invert() const noexcept
		{
			float det;

			if(_03 != 0.0f || _13 != 0.0f || _23 != 0.0f || _33 != 1.0f)
			{
				return _Invert();
			}

			Float4x4 inv;

			/* Inverse = adjoint / det. */
			inv.l[0] = _11 * _22 - _21 * _12;
			inv.l[1] = _21 * _02 - _01 * _22;
			inv.l[2] = _01 * _12 - _11 * _02;

			/* Compute determinant as early as possible using these cofactors. */
			det = _00 * inv.l[0] + _10 * inv.l[1] + _20 * inv.l[2];

			/* Run singularity test. */
			if(det == 0.0f)
			{
				/* printf("invert_Float4x4: Warning: Singular Float4x4.\n"); */
				return Identity;
			} else
			{
				float d10, d20, d21, d31, d32, d03;
				float im00, im10, im20, im30;

				det = 1.0f / det;

				/* Compute rest of inverse. */
				inv.l[0] *= det;
				inv.l[1] *= det;
				inv.l[2] *= det;
				inv.l[3] = 0.0f;

				im00 = _00 * det;
				im10 = _10 * det;
				im20 = _20 * det;
				im30 = _30 * det;
				inv.l[4] = im20 * _12 - im10 * _22;
				inv.l[5] = im00 * _22 - im20 * _02;
				inv.l[6] = im10 * _02 - im00 * _12;
				inv.l[7] = 0.0f;

				/* Pre-compute 2x2 dets for first two rows when computing */
				/* cofactors of last two rows. */
				d10 = im00 * _11 - _01 * im10;
				d20 = im00 * _21 - _01 * im20;
				d21 = im10 * _21 - _11 * im20;
				d31 = im10 * _31 - _11 * im30;
				d32 = im20 * _31 - _21 * im30;
				d03 = im30 * _01 - _31 * im00;

				inv.l[8] = d21;
				inv.l[9] = -d20;
				inv.l[10] = d10;
				inv.l[11] = 0.0f;

				inv.l[12] = -(_12 * d32 - _22 * d31 + _32 * d21);
				inv.l[13] = (_02 * d32 + _22 * d03 + _32 * d20);
				inv.l[14] = -(_02 * d31 + _12 * d03 + _32 * d10);
				inv.l[15] = 1.0f;

				return inv;
			}
		}

	}
}


