#include "include.h"

DWORD WINAPI ThirdPersonThread(HMODULE hMod) {
	Localplayer L;
	while (!GetAsyncKeyState(UNINJECT_KB)) {
		if (L.Exsists() && Settings.EnableThirdPerson) {
			L.EnableThirdPerson();
		}
		else {
			L.DisableThirdPerson();
		}
	}
	FreeLibraryAndExitThread(hMod, 0);
}