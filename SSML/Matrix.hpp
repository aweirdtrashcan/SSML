#pragma once

#include "Vector.hpp"

namespace SSML {
	struct alignas(64) MATRIX {
		VECTOR4D m_Data[4];

		MATRIX(float a00, float a01, float a02, float a03,
			   float b00, float b01, float b02, float b03,
			   float c00, float c01, float c02, float c03,
			   float d00, float d01, float d02, float d03) 
		{
			m_Data[0] = { a00, a01, a02, a03 };
			m_Data[1] = { b00, b01, b02, b03 };
			m_Data[2] = { c00, c01, c02, c03 };
			m_Data[3] = { d00, d01, d02, d03 };
		}

		MATRIX(const float* pArray) {
			memcpy(&this->m_Data, pArray, sizeof(VECTOR4D) * 4);
		}

		MATRIX() {}

		static MATRIX Identity() {
			return {
				1.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 1.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f
			};
		}

		void SetRowA(float* float4Array) {
			m_Data[0] = float4Array;
		}
		
		void SetRowA(const VECTOR4D& vector) {
			m_Data[0] = vector;
		}

		void SetRowB(float* float4Array) {
			m_Data[1] = float4Array;
		}

		void SetRowB(const VECTOR4D& vector) {
			m_Data[1] = vector;
		}

		void SetRowC(float* float4Array) {
			m_Data[2] = float4Array;
		}

		void SetRowC(const VECTOR4D& vector) {
			m_Data[2] = vector;
		}

		void SetRowD(float* float4Array) {
			m_Data[3] = float4Array;
		}

		void SetRowD(const VECTOR4D& vector) {
			m_Data[3] = vector;
		}

		float* GetAsArray() const {
			return (float*)this->m_Data;
		}
	};

	struct alignas(64) XMMMATRIX {
		XMMVECTOR m_Data[4];

		XMMMATRIX(const MATRIX& matrix) {
			m_Data[0] = matrix.m_Data[0];
			m_Data[1] = matrix.m_Data[1];
			m_Data[2] = matrix.m_Data[2];
			m_Data[3] = matrix.m_Data[3];
		}

		XMMMATRIX(const float* pArray) {
			m_Data[0] = _mm_load_ps(&pArray[0]);
			m_Data[1] = _mm_load_ps(&pArray[4]);
			m_Data[2] = _mm_load_ps(&pArray[8]);
			m_Data[3] = _mm_load_ps(&pArray[12]);
		}

		XMMMATRIX() {}

		XMMMATRIX operator*(const XMMMATRIX& other) {
			XMMMATRIX matrix;

			matrix.m_Data[0] = _mm_mul_ps(_mm_shuffle_ps(m_Data[0], m_Data[0], 0x0), other.m_Data[0].m_Data);
			matrix.m_Data[0] = _mm_add_ps(matrix.m_Data[0], _mm_mul_ps(_mm_shuffle_ps(m_Data[0], m_Data[0], _MM_SHUFFLE(1, 1, 1, 1)), other.m_Data[1].m_Data));
			matrix.m_Data[0] = _mm_add_ps(matrix.m_Data[0], _mm_mul_ps(_mm_shuffle_ps(m_Data[0], m_Data[0], _MM_SHUFFLE(2, 2, 2, 2)), other.m_Data[2].m_Data));
			matrix.m_Data[0] = _mm_add_ps(matrix.m_Data[0], _mm_mul_ps(_mm_shuffle_ps(m_Data[0], m_Data[0], _MM_SHUFFLE(3, 3, 3, 3)), other.m_Data[3].m_Data));

			matrix.m_Data[1] = _mm_mul_ps(_mm_shuffle_ps(m_Data[1], m_Data[1], 0), other.m_Data[0].m_Data);
			matrix.m_Data[1] = _mm_add_ps(matrix.m_Data[1], _mm_mul_ps(_mm_shuffle_ps(m_Data[1], m_Data[1], _MM_SHUFFLE(1, 1, 1, 1)), other.m_Data[1].m_Data));
			matrix.m_Data[1] = _mm_add_ps(matrix.m_Data[1], _mm_mul_ps(_mm_shuffle_ps(m_Data[1], m_Data[1], _MM_SHUFFLE(2, 2, 2, 2)), other.m_Data[2].m_Data));
			matrix.m_Data[1] = _mm_add_ps(matrix.m_Data[1], _mm_mul_ps(_mm_shuffle_ps(m_Data[1], m_Data[1], _MM_SHUFFLE(3, 3, 3, 3)), other.m_Data[3].m_Data));
	
			matrix.m_Data[2] = _mm_mul_ps(_mm_shuffle_ps(m_Data[2], m_Data[2], 0), other.m_Data[0].m_Data);
			matrix.m_Data[2] = _mm_add_ps(matrix.m_Data[2], _mm_mul_ps(_mm_shuffle_ps(m_Data[2], m_Data[2], _MM_SHUFFLE(1, 1, 1, 1)), other.m_Data[1].m_Data));
			matrix.m_Data[2] = _mm_add_ps(matrix.m_Data[2], _mm_mul_ps(_mm_shuffle_ps(m_Data[2], m_Data[2], _MM_SHUFFLE(2, 2, 2, 2)), other.m_Data[2].m_Data));
			matrix.m_Data[2] = _mm_add_ps(matrix.m_Data[2], _mm_mul_ps(_mm_shuffle_ps(m_Data[2], m_Data[2], _MM_SHUFFLE(3, 3, 3, 3)), other.m_Data[3].m_Data));

			matrix.m_Data[3] = _mm_mul_ps(_mm_shuffle_ps(m_Data[3], m_Data[3], 0), other.m_Data[0].m_Data);
			matrix.m_Data[3] = _mm_add_ps(matrix.m_Data[3], _mm_mul_ps(_mm_shuffle_ps(m_Data[3], m_Data[3], _MM_SHUFFLE(1, 1, 1, 1)), other.m_Data[1].m_Data));
			matrix.m_Data[3] = _mm_add_ps(matrix.m_Data[3], _mm_mul_ps(_mm_shuffle_ps(m_Data[3], m_Data[3], _MM_SHUFFLE(2, 2, 2, 2)), other.m_Data[2].m_Data));
			matrix.m_Data[3] = _mm_add_ps(matrix.m_Data[3], _mm_mul_ps(_mm_shuffle_ps(m_Data[3], m_Data[3], _MM_SHUFFLE(3, 3, 3, 3)), other.m_Data[3].m_Data));

			return matrix;
		}

		XMMMATRIX operator+(const XMMMATRIX& other) {
			XMMMATRIX matrix;

			matrix.m_Data[0] = m_Data[0] + other.m_Data[0];
			matrix.m_Data[1] = m_Data[1] + other.m_Data[1];
			matrix.m_Data[2] = m_Data[2] + other.m_Data[2];
			matrix.m_Data[3] = m_Data[3] + other.m_Data[3];

			return matrix;
		}

		XMMMATRIX operator-(const XMMMATRIX& other) {
			XMMMATRIX matrix;

			matrix.m_Data[0] = m_Data[0] - other.m_Data[0];
			matrix.m_Data[1] = m_Data[1] - other.m_Data[1];
			matrix.m_Data[2] = m_Data[2] - other.m_Data[2];
			matrix.m_Data[3] = m_Data[3] - other.m_Data[3];

			return matrix;
		}

		XMMMATRIX RotateX(float angle) {
			float matrixArray[16];

			matrixArray[0] = 1.0f;
			matrixArray[1] = 0.0f;
			matrixArray[2] = 0.0f;
			matrixArray[3] = 0.0f;

			matrixArray[4] = 0.0f;
			matrixArray[5] = cosf(angle);
			matrixArray[6] = -sinf(angle);
			matrixArray[7] = 0.0f;

			matrixArray[8] = 0.0f;
			matrixArray[9] = sinf(angle);
			matrixArray[10] = cosf(angle);
			matrixArray[11] = 0.0f;

			matrixArray[12] = 0.0f;
			matrixArray[13] = 0.0f;
			matrixArray[14] = 0.0f;
			matrixArray[15] = 1.0f;

			return (*this) * XMMMATRIX(matrixArray);
		}

		XMMMATRIX RotateY(float angle) {
			float matrixArray[16];

			matrixArray[0] = cosf(angle);
			matrixArray[1] = 0.0f;
			matrixArray[2] = sinf(angle);
			matrixArray[3] = 0.0f;

			matrixArray[4] = 0.0f;
			matrixArray[5] = 1.0f;
			matrixArray[6] = 0.0f;
			matrixArray[7] = 0.0f;

			matrixArray[8] = -sinf(angle);
			matrixArray[9] = 0.0f;
			matrixArray[10] = cosf(angle);
			matrixArray[11] = 0.0f;

			matrixArray[12] = 0.0f;
			matrixArray[13] = 0.0f;
			matrixArray[14] = 0.0f;
			matrixArray[15] = 1.0f;

			return (*this) * XMMMATRIX(matrixArray);
		}

		XMMMATRIX RotateZ(float angle) {
			float matrixArray[16];

			matrixArray[0] = cosf(angle);
			matrixArray[1] = -sinf(angle);
			matrixArray[2] = 0.0f;
			matrixArray[3] = 0.0f;

			matrixArray[4] = sinf(angle);
			matrixArray[5] = cosf(angle);
			matrixArray[6] = 0.0f;
			matrixArray[7] = 0.0f;

			matrixArray[8] = 0.0f;
			matrixArray[9] = 0.0f;
			matrixArray[10] = 1.0f;
			matrixArray[11] = 0.0f;

			matrixArray[12] = 0.0f;
			matrixArray[13] = 0.0f;
			matrixArray[14] = 0.0f;
			matrixArray[15] = 1.0f;

			return (*this) * XMMMATRIX(matrixArray);
		}
	};
}