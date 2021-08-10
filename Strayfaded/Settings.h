#include "include.h"

inline D3DCOLOR ImColor_D3D(ImColor Input) {
	return D3DCOLOR_RGBA(
		(int)(Input.Value.x * 255.0f),
		(int)(Input.Value.y * 255.0f),
		(int)(Input.Value.z * 255.0f),
		(int)(Input.Value.w * 255.0f),
	);
}

class USettings {
public:
	LPD3DXFONT m_font = NULL;

	bool EnableBhop = false;

	bool EnableTrigger = false;
	int TriggerDelay;

	bool EnableCharms = false;
	float CharmsColor[3];

	bool EnableNoFlash = false;
	bool EnableRadar = false;

	bool EnableConoredESP = false;
	float CorneredCoverage = 0.0f;

	bool EnableNoZoom = false;

	bool EnableGlow = false;
	ImColor EnemyGlowColor = { 0.2f, 0.0f, 2.0f, 1.0f };
	ImColor FriendlyGlowColor = { 0.2f, 1.0f, 2.0f, 1.0f };

	bool EnablePlayerInfo = false;

	bool EnableTrace = false;
	bool TraceTemmates = false;
	bool EnableCustomTracerBone = false;
	bool TraceFromFeet = false;
	int TracerBone = 0;
	int TracerThickness = 1;
	ImColor EnemyTracerColor = { 0.2f, 0.0f, 2.0f, 1.0f };
	ImColor FriendlyTracerColor = { 0.2f, 1.0f, 2.0f, 1.0f };

	bool EnableBoundingBoxes = false;
	float BoundingBoxesWidth = 0.5f;
	int BoundingBoxisThickness = 1;
	ImColor EnemyBoxColor = { 0.2f, 0.0f, 2.0f, 1.0f };
	ImColor FriendlyBoxColor = { 0.2f, 1.0f, 2.0f, 1.0f };

	bool EnableFOV = false;
	int ValueFOV = 90;

	bool EnableThirdPerson = false;
	bool Global_Antialias = true;
};