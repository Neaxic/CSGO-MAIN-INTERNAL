#include "include.h"

bool Engine::Init() {
	Global_GameModule = GameModule();
	Global_EngineModule = EngineModule();
	if (Global_GameModule && Global_EngineModule) {
		return true;
	}
	return false;
}

DWORD Engine::GameModule() {
	return (DWORD)GetModuleHandleA("client.dll");
}

DWORD Engine::EngineModule() {
	return (DWORD)GetModuleHandleA("engine.dll");
}