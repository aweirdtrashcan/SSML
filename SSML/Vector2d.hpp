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
	};

	struct alignas(16) XMMVECTOR {
		__m128 m_Data;
	
		XMMVECTOR() = default;
		~XMMVECTOR() = default;

		XMMVECTOR(const VECTOR2D& vector) {
			float m4d[4];
			m4d[0] = vector.r;
			m4d[1] = vector.g;
			m4d[2] = 0.0f;
			m4d[3] = 0.0f;
			m_Data = _mm_load_ps(m4d);
		}

		XMMVECTOR(__m128 d) {
			m_Data = d;
		}

		XMMVECTOR operator*(const XMMVECTOR other) {
			return _mm_mul_ps(this->m_Data, other.m_Data);
		}

		void GetFloatArray(float* out_float_array) {
			_mm_store_ps(out_float_array, m_Data);
		}
	};
}

