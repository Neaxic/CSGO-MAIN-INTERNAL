#include "include.h"

class Localplayer {
public:
	DWORD Get();
	bool Exsists();
	void ForceJump();

	int GetHealth();
	int Crosshair();
	int GetTeam();
	int DefaultFOV();

	void ForceAttack();
	void StopAttack();
	void ChangeFOV(int FOV);

	void NoFlash();
	void YesFlash();

	void EnableThirdPerson();
	void DisableThirdPerson();

	Vector3 GetLocation();
	Vector3 GetBonePosition(int Bone);
	Vector2 GetBonePositionScreen(int Bone);
};