#include <iostream>

#include "Matrix.hpp"

#include <chrono>

void vec_test();

int main() {

	SSML::MATRIX identity0 = {
		1.0, 2.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 5.0f,
		2.0f, 3.0f, 4.0f, 7.0f,
		3.0f, 4.0f, 1.0f, 6.0
	};

	SSML::MATRIX identity1 = {
		2.0f, 5.0f, 1.0f, 4.0f,
		6.0f, 7.0f, 3.0f, 2.0f,
		1.0f, 8.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f
	};

	SSML::XMMMATRIX xmmIdentity0 = identity0;
	SSML::XMMMATRIX xmmIdentity1 = identity1;

	SSML::XMMMATRIX xmmIdentity2 = xmmIdentity0 * xmmIdentity1;
}

void vec_test() {
	for (int i = 0; i < 33904; i++) {
		SSML::VECTOR4D v = { 3.5984f, 4.3890f, 3.3904f, 8.6632f };
		SSML::XMMVECTOR xmv = v;

		SSML::XMMVECTOR xmv1;
		SSML::VECTOR4D v1;

		auto n0 = std::chrono::high_resolution_clock::now();
		for (int i = 0; i < 300000; i++)
			v1 = v * v;
		auto end0 = std::chrono::high_resolution_clock::now();

		auto n1 = std::chrono::high_resolution_clock::now();
		for (int i = 0; i < 300000; i++)
			xmv1 = xmv * xmv;
		auto end1 = std::chrono::high_resolution_clock::now();

		auto start0 = std::chrono::time_point_cast<std::chrono::microseconds>(n0).time_since_epoch().count();
		auto mend0 = std::chrono::time_point_cast<std::chrono::microseconds>(end0).time_since_epoch().count();

		auto start1 = std::chrono::time_point_cast<std::chrono::microseconds>(n1).time_since_epoch().count();
		auto mend1 = std::chrono::time_point_cast<std::chrono::microseconds>(end1).time_since_epoch().count();

		auto duration0 = mend0 - start0;
		auto duration1 = mend1 - start1;

		double percentage = ((double)duration0 / (double)duration1) * 100 - 100;

		system("cls");
		std::cout << "Non SIMD took " << duration0 << " time\n";
		std::cout << "SIMD took " << duration1 << " time\n";
		std::cout << "SIMD was " << percentage << "% faster than non SIMD\n";

		//std::cout << v1.x << " | " << v1.y << "\n";

		//float fa[4];
		//xmv1.GetFloatArray(fa);

		//std::cout << fa[0] << " | " << fa[1] << "\n";
	}
}