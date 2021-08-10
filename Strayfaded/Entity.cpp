#include "include.h"

DWORD Entity::Get(int Index) {
	return *(DWORD*)(Global_GameModule + dwEntityList + (Index * 0x10));
}
int Entity::GetHealth(DWORD Entity) {
	return *(int*)(Entity + m_iHealth);
}
int Entity::GetArmor(DWORD Entity) {
	return *(int*)(Entity + m_ArmorValue);
}
int Entity::GetTeam(DWORD Entity) {
	return *(int*)(Entity + m_iTeamNum);
}
bool Entity::GetDormant(DWORD Entity) {
	return *(bool*)(Entity + m_bDormant);
}
int Entity::GetRank(DWORD Entity) {
	return *(int*)(Entity + m_iCompetitiveRanking);
}
DWORD Entity::GetName(DWORD Entity) {
	return *(DWORD*)(Entity + m_iAccountID);
}

Vector3 Entity::GetLocation(DWORD Entity) {
	return *(Vector3*)(Entity + m_vecOrigin);
}
Vector3 Entity::GetBonePosition(DWORD Entity, int Bone) {
		uintptr_t BoneMatrixBase = *(uintptr_t*)(Entity + m_dwBoneMatrix);
		BoneMatrix BoneMat = *(BoneMatrix*)(BoneMatrixBase + sizeof(Bone) * Bone);
		Vector3 Location = { BoneMat.x, BoneMat.y, BoneMat.z };
		return Location;
}
Vector2 Entity::GetBonePositionScreen(DWORD Entity, int Bone) {
		uintptr_t BoneMatrixBase = *(uintptr_t*)(Entity + m_dwBoneMatrix);
		BoneMatrix BoneMat = *(BoneMatrix*)(BoneMatrixBase + sizeof(Bone) * Bone);
		Vector3 Location = { BoneMat.x, BoneMat.y, BoneMat.z };

		float Matrix[16];
		Vector2 Out;
		memcpy(&Matrix, (PBYTE*)(Global_GameModule + dwViewMatrix), sizeof(Matrix));

		if (WorldToScreen(Location, Out, Matrix)) {
			return Out;
		}
		return { 0, 0 };
}