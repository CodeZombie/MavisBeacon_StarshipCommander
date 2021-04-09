#pragma once
#include "glm/glm.hpp"
#include "glm/ext.hpp"
class MathHelper {
public:
	inline static glm::vec3 getRandomDirectionVector() {
		float phi = getRandomRange(0.f, 2 * glm::pi<float>());
		float z = getRandomRange(-1, 1);
		float x = sqrt(1 - (z*z)) * cos(phi);
		float y = sqrt(1 - (z*z)) * sin(phi);
		return glm::vec3(x, y, z);
	}

	inline static float getRandomRange(float low, float high) {
		float randNormal = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		return low + (randNormal * (high - low));
	}

	inline static float lerp(float a, float b, float f){
		return a + f * (b - a);
	}

	inline static float smoothstep(float edge0, float edge1, float x) {
		x = clamp(x, 0.f, 1.f);
		float mu2 = (1.f - cos(x * 3.14159)) / 2.f;
		return (edge0 * (1.f - mu2) + edge1 * x);
	}

	inline static float clamp(float x, float lowerlimit, float upperlimit) {
		if (x < lowerlimit)
			x = lowerlimit;
		if (x > upperlimit)
			x = upperlimit;
		return x;
	}

};

