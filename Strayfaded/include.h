#pragma once
#include <Windows.h>
#include <cstdint>
#include <string> //to_string

// Extra Config
#define MENU_KB VK_INSERT
#define UNINJECT_KB VK_DELETE

// DirectX
#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

// Imgui
#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx9.h"

#include "Styles.h"
#include "Watermark.h"

// Settings
#include "Settings.h"
USettings Settings;

// Hook/Drawing
#include "DirectX.h"
#include "Hook.h"
#include "Drawing.h"

//Offsets
#include "Offsets.h"

//Structs
#include "Vector.h"
#include "WorldToScreen.h"

// Global Vars
DWORD Global_GameModule;
DWORD Global_EngineModule;

// Classes
#include "Engine.h"
#include "Localplayer.h"
#include "Entitiy.h"

//Modules
#include "Bhop.h"
#include "Triggerbot.h"
#include "FOV.h"
#include "ThirdPerson.h"
#include "GlowThread.h"