#include "include.h"


bool WorldToScreen(Vector3 pos, Vector2& screen, float Matrix[16]){
	int width = GetSystemMetrics(SM_CXSCREEN);
	int height = GetSystemMetrics(SM_CYSCREEN);

	Vector4 ClipCoords;
	ClipCoords.x = pos.x * Matrix[0] + pos.y * Matrix[1] + pos.z * Matrix[2] + Matrix[3];
	ClipCoords.y = pos.x * Matrix[4] + pos.y * Matrix[5] + pos.z * Matrix[6] + Matrix[7];
	ClipCoords.z = pos.x * Matrix[8] + pos.y * Matrix[9] + pos.z * Matrix[10] + Matrix[11];
	ClipCoords.w = pos.x * Matrix[12] + pos.y * Matrix[13] + pos.z * Matrix[14] + Matrix[15];

	if (ClipCoords.w < 0.f) {
		return false;
	}

	Vector3 NDC;
	NDC.x = ClipCoords.x / ClipCoords.w;
	NDC.y = ClipCoords.y / ClipCoords.w;
	NDC.z = ClipCoords.z / ClipCoords.w;

	screen.x = (width / 2 * NDC.x) + (NDC.x + width / 2);
	screen.y = -(height / 2 * NDC.y) + (NDC.y + height / 2);
	return true;
}