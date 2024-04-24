#include <iostream>

#include "Vector2d.hpp"

#include <chrono>

int main() {
	SSML::VECTOR2D v = { 3.5984f, 4.3890f };
	SSML::XMMVECTOR xmv = v;

	auto n0 = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < 30000; i++)
		SSML::VECTOR2D v1 = v * v;
	auto end0 = std::chrono::high_resolution_clock::now();

	auto n1 = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < 30000; i++) SSML::XMMVECTOR xmv1 = xmv * xmv;
	auto end1 = std::chrono::high_resolution_clock::now();

	auto start0 = std::chrono::time_point_cast<std::chrono::microseconds>(n0).time_since_epoch().count();
	auto mend0 = std::chrono::time_point_cast<std::chrono::microseconds>(end0).time_since_epoch().count();

	auto start1 = std::chrono::time_point_cast<std::chrono::microseconds>(n1).time_since_epoch().count();
	auto mend1 = std::chrono::time_point_cast<std::chrono::microseconds>(end1).time_since_epoch().count();

	auto duration0 = mend0 - start0;
	auto duration1 = mend1 - start1;

	double percentage = ((double)duration0 / (double)duration1) * 100 - 100;

	std::cout << "Non SIMD took " << duration0 << " time\n";
	std::cout << "SIMD took " << duration1 << " time\n";
	std::cout << "SIMD was " << percentage << "% faster than non SIMD\n";

	//std::cout << v1.x << " | " << v1.y << "\n";

	//float fa[4];
	//xmv1.GetFloatArray(fa);

	//std::cout << fa[0] << " | " << fa[1] << "\n";
}