#include "include.h"

DWORD WINAPI BhopThread(HMODULE hMod) {
	Localplayer L;
	while (!GetAsyncKeyState(UNINJECT_KB)) {
		if (L.Exsists() && Settings.EnableBhop){
			DWORD flag = *(BYTE*)(L.Get() + m_fFlags);
			if (GetAsyncKeyState(VK_SPACE) && flag & (1 << 0)) {
				L.ForceJump();
			}
		}
		if (Settings.EnableNoFlash) {
			if (L.Exsists()) {
				L.NoFlash();
			}
		}
		else if (!Settings.EnableNoFlash) {
			if (L.Exsists()) {
				L.YesFlash();
			}
		}
	}
	FreeLibraryAndExitThread(hMod, 0);
}