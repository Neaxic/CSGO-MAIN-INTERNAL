#include "include.h"

class Entity {
public:
	DWORD Get(int Index);

	int GetHealth(DWORD Entity);
	int GetTeam(DWORD Entity);
	int GetArmor(DWORD Entity);
	bool GetDormant(DWORD Entity);
	int GetRank(DWORD Entity);
	DWORD GetName(DWORD Entity);

	Vector3 GetLocation(DWORD Entity);
	Vector3 GetBonePosition(DWORD Entity, int Bone);
	Vector2 GetBonePositionScreen(DWORD Entity, int Bone);
};