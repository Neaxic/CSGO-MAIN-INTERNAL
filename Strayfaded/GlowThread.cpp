#include "include.h"

DWORD WINAPI GlowThread(HMODULE hMod) {
	Localplayer L;
    Entity EntityController;
	while (!GetAsyncKeyState(UNINJECT_KB)) {
		if (L.Exsists() && Settings.EnableGlow) {
			uintptr_t GlowObj = *(uintptr_t*)(Global_GameModule + dwGlowObjectManager);

			for (int i = 0; i < 64; i++) {
				uintptr_t Entity = *(uintptr_t*)((Global_GameModule + dwEntityList) + i * 0x10);

				if (Entity != NULL) {
					int EntityTeam = *(int*)(Entity + m_iTeamNum);
					int GlowIndex = *(int*)(Entity + m_iGlowIndex);
					
					if (L.GetTeam() != EntityTeam) {
						*(float*)(GlowObj + ((GlowIndex * 0x38) + 0x8)) = Settings.EnemyGlowColor.Value.x;
						*(float*)(GlowObj + ((GlowIndex * 0x38) + 0xC)) = Settings.EnemyGlowColor.Value.y;
						*(float*)(GlowObj + ((GlowIndex * 0x38) + 0x10)) = Settings.EnemyGlowColor.Value.z;
						*(float*)(GlowObj + ((GlowIndex * 0x38) + 0x14)) = Settings.EnemyGlowColor.Value.w;
					}
					else {
						*(float*)(GlowObj + ((GlowIndex * 0x38) + 0x8)) = Settings.FriendlyGlowColor.Value.x;
						*(float*)(GlowObj + ((GlowIndex * 0x38) + 0xC)) = Settings.FriendlyGlowColor.Value.y;
						*(float*)(GlowObj + ((GlowIndex * 0x38) + 0x10)) = Settings.FriendlyGlowColor.Value.z;
						*(float*)(GlowObj + ((GlowIndex * 0x38) + 0x14)) = Settings.FriendlyGlowColor.Value.w;
					}
					*(bool*)(GlowObj + ((GlowIndex * 0x38) + 0x28)) = true;
					*(bool*)(GlowObj + ((GlowIndex * 0x38) + 0x29)) = false;
					}
			}
		
		
		}

        
		Sleep(3);
	}
	FreeLibraryAndExitThread(hMod, 0);
}