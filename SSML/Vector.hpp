#pragma once

#include <nmmintrin.h>

namespace SSML {
	struct VECTOR2D {
		union {
			struct {
				float x;
				float y;
			};
			struct {
				float u;
				float v;
			};
			struct {
				float r;
				float g;
			};
		};

		VECTOR2D operator*(const VECTOR2D& other) {
			VECTOR2D v;
			v.x = this->x * other.x;
			v.y = this->y * other.y;
			return v;
		}

		VECTOR2D() {}
		VECTOR2D(float x, float y) : x(x), y(y) {}
		VECTOR2D(float* float2dArray) : x(float2dArray[0]), y(float2dArray[1]) {}
	};

	struct VECTOR3D {
		union {
			struct {
				float x;
				float y;
				float z;
			};
			struct {
				float u;
				float v;
				float w;
			};
			struct {
				float r;
				float g;
				float b;
			};
		};

		VECTOR3D operator*(const VECTOR3D& other) {
			VECTOR3D v;
			v.x = this->x * other.x;
			v.y = this->y * other.y;
			v.z = this->z * other.z;
			return v;
		}

		VECTOR3D() {}
		VECTOR3D(float x, float y, float z) : x(x), y(y), z(z) {}
		VECTOR3D(float* float3dArray) : x(float3dArray[0]), y(float3dArray[1]), z(float3dArray[2]) {}
	};

	struct VECTOR4D {
		union {
			struct {
				float x;
				float y;
				float z;
				float w;
			};
			struct {
				float r;
				float g;
				float b;
				float a;
			};
		};

		VECTOR4D operator*(const VECTOR4D& other) {
			VECTOR4D v;
			v.x = this->x * other.x;
			v.y = this->y * other.y;
			v.z = this->z * other.z;
			v.w = this->w * other.w;
			return v;
		}

		operator float*() const { return (float*)this; }
		
		VECTOR4D() {}
		VECTOR4D(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
		VECTOR4D(float* float4dArray) : x(float4dArray[0]), y(float4dArray[1]), z(float4dArray[2]), w(float4dArray[3]) {}
	};

	struct XMMVECTOR {
		__m128 m_Data;
	
		XMMVECTOR() = default;
		~XMMVECTOR() = default;

		XMMVECTOR(const VECTOR2D& vector) {
			float m4d[4];
			m4d[0] = vector.x;
			m4d[1] = vector.y;
			m4d[2] = 0.0f;
			m4d[3] = 0.0f;
			m_Data = _mm_loadu_ps(m4d);
		}

		XMMVECTOR(const VECTOR3D& vector) {
			float m4d[4];
			m4d[0] = vector.x;
			m4d[1] = vector.y;
			m4d[2] = vector.z;
			m4d[3] = 0.0f;
			m_Data = _mm_loadu_ps(m4d);
		}

		XMMVECTOR(float* uFloatArray) {
			m_Data = _mm_loadu_ps(uFloatArray);
		}

		XMMVECTOR(const VECTOR4D& vector) {
			m_Data = _mm_loadu_ps(vector);
		}

		XMMVECTOR(__m128 other) {
			m_Data = other;
		}

		operator __m128() const { return m_Data; }

		XMMVECTOR operator*(const XMMVECTOR& other) {
			return _mm_mul_ps(m_Data, other.m_Data);
		}

		XMMVECTOR operator/(const XMMVECTOR& other) {
			return _mm_div_ps(m_Data, other.m_Data);
		}

		XMMVECTOR operator+(const XMMVECTOR& other) {
			return _mm_add_ps(m_Data, other.m_Data);
		}

		XMMVECTOR operator-(const XMMVECTOR& other) {
			return _mm_sub_ps(m_Data, other.m_Data);;
		}

		static XMMVECTOR VectorDot(const XMMVECTOR& vec1, const XMMVECTOR& vec2) {
			constexpr int mask = 0xFF;
			return _mm_dp_ps(vec1.m_Data, vec2.m_Data, mask);
		}

		operator VECTOR2D() const {
			float floatArray[4];
			_mm_storeu_ps(floatArray, m_Data);
			return { floatArray[0], floatArray[1] };
		}

		operator VECTOR3D() const {
			float floatArray[4];
			_mm_storeu_ps(floatArray, m_Data);
			return { floatArray[0], floatArray[1], floatArray[2] };
		}

		operator VECTOR4D() const {
			float floatArray[4];
			_mm_storeu_ps(floatArray, m_Data);
			return { floatArray[0], floatArray[1], floatArray[2], floatArray[3] };
		}

		void GetXYZW(float* outFloatArray) const {
			_mm_store_ps(outFloatArray, m_Data);
		}

		float GetVectorAsOne() const {
			float result[4];
			_mm_store_ps1(result, m_Data);
			return result[0];
		}
	};
}

