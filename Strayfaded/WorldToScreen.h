#include "include.h"

struct BoneMatrix {
	byte pad1[12];
	float x;
	byte pad2[12];
	float y;
	byte pad3[12];
	float z;
};

bool WorldToScreen(Vector3 pos, Vector2& screen, float Matrix[16]);