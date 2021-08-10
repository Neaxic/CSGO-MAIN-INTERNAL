#include "include.h"

struct Vector2 {
	float x, y;

	float Distance(Vector2 Input) {
		return sqrt(pow(x - Input.x, 2) + pow(y - Input.y, 2));
	}
};

struct Vector3 {
	float x, y, z;

	Vector3 operator+(Vector3 D) {
		return { x + D.x, y + D.y, z + D.z };
	}
	Vector3 operator-(Vector3 D) {
		return { x - D.x, y - D.y, z - D.z };
	}
	Vector3 operator*(Vector3 D) {
		return { x * D.x, y * D.y, z * D.z };
	}
	Vector3 operator/(Vector3 D) {
		return { x / D.x, y / D.y, z / D.z };
	}


	void Normalize() {
		while(y < -180) {
			y = 179.99;
		}
		while (y > 180) {
			y = -179.99;
		}
		while (x < -89) {
			y = -89;
		}
		while (x > 89) {
			y = 89;
		}
		z = 0;
	}
};

struct Vector4 {
	float x, y, z, w;
};