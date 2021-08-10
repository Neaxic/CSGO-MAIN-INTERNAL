#include "include.h"

DWORD Localplayer::Get() {
	return *(DWORD*)(Global_GameModule + dwLocalPlayer);
}
bool Localplayer::Exsists() {
	if (*(DWORD*)(Global_GameModule + dwLocalPlayer)) {
		return true;
	}
	return false;
}

int Localplayer::GetHealth() {
	DWORD Player = Get();
	if (Player)
		return *(int*)(Player + m_iHealth);
	return -1;
}

int Localplayer::GetTeam() {
	DWORD Player = Get();
	if (Player)
		return *(int*)(Player + m_iTeamNum);
	return -1;
}

int Localplayer::Crosshair() {
	DWORD Player = Get();
	if (Player)
		return *(int*)(Player + m_iCrosshairId);
	return -1;
}

int Localplayer::DefaultFOV() {
	DWORD Player = Get();
	if (Player)
		return *(int*)(Player + m_iDefaultFOV);
	return 80;
}

void Localplayer::ChangeFOV(int FOV) {
	DWORD Player = Get();
	if (Player) {
		*(DWORD*)(Player + m_iDefaultFOV) = FOV;
	}
}

void Localplayer::EnableThirdPerson() {
	DWORD Player = Get();
	if (Player) {
		*(int*)(Player + m_iObserverMode) = 1;
	}
}

void Localplayer::DisableThirdPerson() {
	DWORD Player = Get();
	if (Player) {
		*(int*)(Player + m_iObserverMode) = 0;
	}
}

void Localplayer::ForceJump() {
	*(DWORD*)(Global_GameModule + dwForceJump) = 6;
}

void Localplayer::ForceAttack() {
	*(int*)(Global_GameModule + dwForceAttack) = 5;
}

void Localplayer::StopAttack() {
	*(int*)(Global_GameModule + dwForceAttack) = 4;
}

void Localplayer::NoFlash() {
	DWORD Player = Get();
	if (Player) {
		*(float*)(Player + m_flFlashMaxAlpha) = 0;
	}
}

void Localplayer::YesFlash() {
	DWORD Player = Get();
	if (Player) {
		*(float*)(Player + m_flFlashMaxAlpha) = 1;
	}
}

Vector3 Localplayer::GetLocation() {
	DWORD Player = Get();
	if (Player)
		return *(Vector3*)(Player + m_vecOrigin);
	return {0,0,0};
}

Vector3 Localplayer::GetBonePosition(int Bone) {
	DWORD Player = Get();
	if (Player) {
		uintptr_t BoneMatrixBase = *(uintptr_t*)(Player + m_dwBoneMatrix);
		BoneMatrix BoneMat = *(BoneMatrix*)(BoneMatrixBase + sizeof(Bone) * Bone);
		Vector3 Location = { BoneMat.x, BoneMat.y, BoneMat.z };
		return Location;
	}
	return { 0, 0, 0 };
}
Vector2 Localplayer::GetBonePositionScreen(int Bone) {
	DWORD Player = Get();
	if (Player) {
		uintptr_t BoneMatrixBase = *(uintptr_t*)(Player + m_dwBoneMatrix);
		BoneMatrix BoneMat = *(BoneMatrix*)(BoneMatrixBase + sizeof(Bone) * Bone);
		Vector3 Location = { BoneMat.x, BoneMat.y, BoneMat.z };

		float Matrix[16];
		Vector2 Out;
		memcpy(&Matrix, (PBYTE*)(Global_GameModule + dwViewMatrix), sizeof(Matrix));
	
		if (WorldToScreen(Location, Out, Matrix)) {
			return Out;
		}
	}
	return { 0, 0 };
}