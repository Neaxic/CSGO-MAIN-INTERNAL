#include "include.h"


//FOV + RADAR

DWORD WINAPI FOVThread(HMODULE hMod) {
	Localplayer L;
	while (!GetAsyncKeyState(UNINJECT_KB)) {
		if (L.Exsists() && Settings.EnableFOV) {
			L.ChangeFOV(Settings.ValueFOV);
		}
		if (L.Exsists() && Settings.EnableRadar) {
			for (int i = 0; i < 64; i++) {
				DWORD Current = *(DWORD*)(Global_GameModule + dwEntityList + i * 0x10);
				if (Current) {
					*(bool*)(Current + m_bSpotted) = true;
				}
			}
		}
		if (L.Exsists() && Settings.EnableNoZoom) {
			
		}
	}
	FreeLibraryAndExitThread(hMod, 0);
}