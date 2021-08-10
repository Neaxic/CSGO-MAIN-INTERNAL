#include "include.h"

DWORD WINAPI TriggerThread(HMODULE hMod) {
	Localplayer L;
	Entity E;

	while (!GetAsyncKeyState(UNINJECT_KB)) {

		int CrossHairID = L.Crosshair();
		int Localteam = L.GetTeam();
		int LocalHealth = L.GetHealth();

		if (L.Exsists()) {
			if (CrossHairID > 0 && CrossHairID < 64) {
				DWORD Entity = E.Get(CrossHairID - 1);
				int EntityTeam = E.GetTeam(Entity);
				int EntityHealth = E.GetHealth(Entity);

				if (EntityTeam != Localteam && Settings.EnableTrigger) {
					if (EntityHealth > 0 && EntityHealth < 101) {
						if (LocalHealth > 0) {
							Sleep(Settings.TriggerDelay);
							L.ForceAttack();
							Sleep(20);
							L.StopAttack();
						}
					}
				}
			}
		}
		Sleep(3);
	}
	FreeLibraryAndExitThread(hMod, 0);
}