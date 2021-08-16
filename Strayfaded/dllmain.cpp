#include "include.h"

void* d3d9Device[119];
BYTE EndSceneBytes[7]{ 0 };
tEndScene oEndScene = nullptr;
LPDIRECT3DDEVICE9 pDevice = nullptr;
WNDPROC oWndProc;

Engine E;
Entity EntityController;
Localplayer PlayerController;

void InitImGui(LPDIRECT3DDEVICE9 pDevice)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
    ImGui::StyleColorsDark();
    ImGui_ImplWin32_Init(window);
    ImGui_ImplDX9_Init(pDevice);

    SetupStyles();
}

struct GlowEntry
{
    int32_t m_nNextFreeSlot; //0x0000
    uint32_t pEntity; //0x0004
    float R; //0x0008
    float G; //0x000C
    float B; //0x0010
    float A; //0x0014
    char pad_0018[4]; //0x0018
    float flUnk; //0x001C
    float flBloom; //0x0020
    float localplayeriszeropoint3; //0x0024
    bool m_bRenderWhenOccluded; //0x0028
    bool m_bRenderWhenUnoccluded; //0x0029
    bool m_bFullBloomRender; //0x002A
    char pad_002B[1]; //0x002B
    int32_t m_nFullBloomStencilTestValue; //0x002C
    int32_t iUnk; //0x0030
    int32_t m_nSplitScreenSlot; //0x0034
}; //Size: 0x0038

bool init = false;
bool ShowMenu = false;
bool drawWaterMark = true;

bool show_aiming = false;
bool show_skin = false;
bool show_misc = false;
bool show_visuals = false;
bool show_colors = false;


void APIENTRY hkEndScene(LPDIRECT3DDEVICE9 o_pDevice)
{

    
    if (GetAsyncKeyState(MENU_KB) & 1)
    {
        ShowMenu = !ShowMenu;
    }
    if (!pDevice)
    {
        pDevice = o_pDevice;
    }
    if (!init)
    {
        InitImGui(pDevice);
        init = true;

        D3DXCreateFont(pDevice, 17, 0, FW_BOLD, 0, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, TEXT("Arial"), &Settings.m_font);

    }

    ImGui_ImplDX9_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();
    ImGui::StyleColorsClassic();
    //ImGui::SetNextWindowPos(ImVec2(25, 25));
    ShowWatermark(&drawWaterMark, "SICKOMODE X1.5", ImVec4(255, 0, 0, 255));

    ImGui::SetNextWindowSize(ImVec2(265, 400));
    
    //DrawFilledRect(0, 0, 20, 10, D3DCOLOR_ARGB(255, 255, 255, 255));
    if(ShowMenu) {
        ImGui::Begin("SICKOMODE MAINMENU");
        ImGui::Text("DIRECTX9 INTERNAL HOOK | ANDRE#0420");
        ImGui::Separator();
        ImGui::Spacing();
        ImGui::Checkbox("Option -> RAGE", &show_aiming);
        ImGui::Checkbox("Option -> LEGIT", &show_visuals);
        ImGui::Checkbox("Option -> VISUALS", &show_visuals);
        ImGui::Checkbox("Option -> SKIN CHANGER", &show_skin);
        ImGui::Checkbox("Option -> MISC", &show_misc);
        ImGui::Separator();
        ImGui::Spacing();
        ImGui::Text("LAST UPDATE: 20-07-2021");
        ImGui::End();

        if (show_aiming) {
            ImGui::Begin("SICKOMODE RAGE OPTIONS");
            ImGui::Text("DIRECTX9 INTERNAL HOOK | ANDRE#0420");
            ImGui::Separator();
            ImGui::Spacing();
            if (ImGui::Checkbox("TriggerBot", &Settings.EnableTrigger)) {
                ImGui::SliderInt("Trigger delay", &Settings.TriggerDelay, 0, 250);
            }
            ImGui::End();
        }

        if (show_visuals) {
            ImGui::SetNextWindowSize(ImVec2(700, 400));
            ImGui::Begin("SICKOMODE VISUALS OPTIONS");
            ImGui::Text("DIRECTX9 INTERNAL HOOK | ANDRE#0420");
            ImGui::Separator();
            ImGui::Spacing();

            ImGui::BeginChild("Tracer", ImVec2(350, 350));
            ImGui::Text("Tracer Settings");
            ImGui::Checkbox2("Enable Tracers", &Settings.EnableTrace);
            ImGui::Checkbox2("Enable Glow", &Settings.EnableGlow);
            ImGui::Checkbox2("Enable CornorESP", &Settings.EnableConoredESP);
            if (Settings.EnableConoredESP) {
                ImGui::SliderFloat("Coverage", &Settings.CorneredCoverage, 0.00f, 1.00f);
            }
            if (Settings.EnableTrace) {
                ImGui::Checkbox2("Enable Team Tracers", &Settings.TraceTemmates);
                ImGui::Checkbox2("Enable CustomTacerBone", &Settings.EnableCustomTracerBone);

                ImGui::SliderInt("Thickness", &Settings.TracerThickness, 1, 10);
                if (Settings.EnableCustomTracerBone) {
                    ImGui::SliderInt("Tracer Bone", &Settings.TracerBone, 0, 100);

                    if (ImGui::Button("Center")) {
                        Settings.TracerBone = 0;
                    }
                    if (ImGui::Button("Head")) {
                        Settings.TracerBone = 8;
                    }
                    if (ImGui::Button("Bottom")) {
                        Settings.TracerBone = 1;
                    }
                }

                ImGui::Spacing();

                ImGui::Text("Tracer Starting Point:");
                if (ImGui::Button("Bottom Center")) {
                    Settings.TraceFromFeet = false;
                }
                ImGui::SameLine();
                if (ImGui::Button("Player Feet")) {
                    Settings.TraceFromFeet = true;
                }
            }
            ImGui::EndChild();
            
            
            ImGui::SameLine();


            ImGui::BeginChild("BoundingBox", ImVec2(350, 350));
            ImGui::Text("Bounding Box Settings");
            ImGui::Checkbox("Charms", &Settings.EnableCharms);
            ImGui::Checkbox("Player Info", &Settings.EnablePlayerInfo);
            ImGui::Checkbox("Global Antialiasing", &Settings.Global_Antialias);
            if (Settings.EnableCharms) {
                ImGui::ColorEdit3("Friendly", Settings.CharmsColor);
                ImGui::ColorEdit3("Enemies", Settings.CharmsColor);
            }
            
            ImGui::Separator();

            ImGui::Checkbox("BoundingBoxes", &Settings.EnableBoundingBoxes);
            if (Settings.EnableBoundingBoxes) {
                ImGui::SliderInt("Thickness", &Settings.BoundingBoxisThickness, 1, 10);
                ImGui::SliderFloat("Box Width", &Settings.BoundingBoxesWidth, 0.01f, 1.0f);
            }

            ImGui::EndChild();

            ImGui::Spacing();
            ImGui::Text("LAST UPDATE: 20-07-2021");

            ImGui::End();
        }

        if (show_skin) {
            ImGui::Begin("SICKOMODE SKIN OPTIONS");
            ImGui::Text("DIRECTX9 INTERNAL HOOK | ANDRE#0420");
            ImGui::Separator();
            ImGui::Spacing();
            ImGui::End();
        }

        if (show_misc) {
            ImGui::Begin("SICKOMODE MISC OPTIONS");
            ImGui::Text("DIRECTX9 INTERNAL HOOK | ANDRE#0420");
            ImGui::Separator();
            ImGui::Spacing();
            ImGui::Checkbox("Bhop", &Settings.EnableBhop);
            ImGui::Checkbox("FOV", &Settings.EnableFOV);
            ImGui::Checkbox("NoFlash", &Settings.EnableNoFlash);
            ImGui::Checkbox("Radar ESP", &Settings.EnableRadar);
            ImGui::Checkbox("ThirdPerson", &Settings.EnableThirdPerson);
            ImGui::Checkbox("Edit Colors", &show_colors);
            ImGui::Separator();
            if (Settings.EnableFOV) {
                ImGui::SliderInt("FOV", &Settings.ValueFOV, -180, 180);
            }
            ImGui::End();
        }


        if (show_colors) {
            ImGui::SetNextWindowSize(ImVec2(700, 800));
            ImGui::Begin("SICKOMODE COLOR OPTIONS");
            ImGui::Text("DIRECTX9 INTERNAL HOOK | ANDRE#0420");
            ImGui::Separator();
            ImGui::Spacing();

            ImGui::Button("prefix1");
            ImGui::SameLine();
            ImGui::Button("prefix2");
            ImGui::SameLine();
            ImGui::Button("prefix3");
            ImGui::SameLine();
            ImGui::Button("prefix4");

            ImGui::Separator();
            ImGui::Spacing();

            ImGui::BeginChild("Snaplines", ImVec2(350, 350));
            ImGui::Text("Snaplines");
            ImGui::ColorEdit4("Enemy Color", (float*)(&Settings.EnemyTracerColor));
            ImGui::ColorEdit4("Friendly Color", (float*)(&Settings.FriendlyTracerColor));
            ImGui::EndChild();
            
            ImGui::SameLine();

            ImGui::BeginChild("Bounding Boxes", ImVec2(350, 350));
            ImGui::Text("Bounding Boxes");
            ImGui::ColorEdit4("Friendly", (float*)&Settings.FriendlyBoxColor);
            ImGui::ColorEdit4("Enemies", (float*)&Settings.EnemyBoxColor);
            ImGui::EndChild();

            ImGui::BeginChild("Glow", ImVec2(350, 350));
            ImGui::Text("Glow");
            ImGui::ColorEdit4("Enemy Color", (float*)(&Settings.EnemyGlowColor));
            ImGui::ColorEdit4("Friendly Color", (float*)(&Settings.FriendlyGlowColor));
            ImGui::EndChild();

            ImGui::SameLine();

            ImGui::BeginChild("Charms", ImVec2(350, 350));
            ImGui::Text("Charms");
            ImGui::ColorEdit4("Enemy Color", (float*)(&Settings.EnemyTracerColor));
            ImGui::ColorEdit4("Friendly Color", (float*)(&Settings.FriendlyTracerColor));
            ImGui::EndChild();

            ImGui::Separator();
            ImGui::End();
        }

    }

    ImGui::EndFrame();
    ImGui::Render();
    ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());

    windowWidth = GetSystemMetrics(SM_CXSCREEN);
    windowHeight = GetSystemMetrics(SM_CYSCREEN);
    
    if (Settings.EnableTrace || Settings.EnableBoundingBoxes) {
        if (PlayerController.Exsists()) {
            Vector2 StartLocation = { windowWidth / 2, windowHeight };
            if (Settings.TraceFromFeet) {
                StartLocation = PlayerController.GetBonePositionScreen(1);
            }

            Vector2 EndLocation;
            for (int i = 1; i < 32; i++) {
                uintptr_t Entity = *(uintptr_t*)(Global_GameModule + dwEntityList + (i * 0x10));
                if (Entity != NULL) {
                    int EntityHealth = EntityController.GetHealth(Entity);
                    if (EntityHealth > 0 && EntityHealth < 101) {
                        EndLocation = EntityController.GetBonePositionScreen(Entity, Settings.TracerBone);

                        //Box
                        Vector3 BaseLocation = EntityController.GetLocation(Entity);
                        Vector3 HeadLocation = EntityController.GetBonePosition(Entity, 96);
                        HeadLocation.z += 15;

                        Vector2 Head;
                        Vector2 Base;
                        float Matrix[16];
                        memcpy(&Matrix, (PBYTE*)(Global_GameModule + dwViewMatrix), sizeof(Matrix));
                        WorldToScreen(HeadLocation, Head, Matrix);
                        WorldToScreen(BaseLocation, Base, Matrix);

                        if (EndLocation.x != 0 && EndLocation.y != 0) {
                            D3DCOLOR TracerColor;
                            D3DCOLOR BoxColor;

                            int Height = Head.Distance(Base);
                            int PlayerTeam = PlayerController.GetTeam();
                            int EntityTeam = EntityController.GetTeam(Entity);
                            int EntityArmor = EntityController.GetArmor(Entity);
                            int EntityRank = EntityController.GetRank(Entity);
                            DWORD EntityName = EntityController.GetName(Entity);
                            bool dormant = EntityController.GetDormant(Entity);

                            
                            if (PlayerTeam != EntityTeam) {
                                TracerColor = ImColor_D3D(Settings.EnemyTracerColor);
                                BoxColor = ImColor_D3D(Settings.EnemyBoxColor);
                                if (Settings.EnableTrace) {
                                    DrawLine(
                                        StartLocation.x,
                                        StartLocation.y,
                                        EndLocation.x,
                                        EndLocation.y,
                                        Settings.TracerThickness,
                                        Settings.Global_Antialias,
                                        TracerColor
                                    );
                                }

                                if (Settings.EnablePlayerInfo) {
                                    DrawHealthText(
                                        Settings.m_font,
                                        (Base.x + (Height * Settings.BoundingBoxesWidth) / 2) + 5,
                                        Base.y - Height - 5,
                                        EntityHealth,
                                        EntityArmor
                                        );
                                }
                                
                                if (Settings.EnableBoundingBoxes) {
                                    DrawBoundingBox(
                                        Base.x,
                                        Base.y,
                                        Height * Settings.BoundingBoxesWidth,
                                        Height,
                                        Settings.BoundingBoxisThickness,
                                        Settings.Global_Antialias,
                                        BoxColor
                                    );

                                   
                                    DrawHealthBar(
                                        Base.x,
                                        Base.y,
                                        Height * Settings.BoundingBoxesWidth,
                                        Height,
                                        Settings.BoundingBoxisThickness,
                                        Settings.Global_Antialias,
                                        EntityHealth,
                                        EntityArmor
                                    );
                                }

                                if (Settings.EnableConoredESP) {
                                    DrawCorneredBox(
                                        Base.x,
                                        Base.y,
                                        Height * Settings.BoundingBoxesWidth,
                                        Height,
                                        Settings.BoundingBoxisThickness,
                                        Settings.CorneredCoverage / 2,
                                        Settings.Global_Antialias,
                                        BoxColor
                                    );
                                }
                            }
                            else if (PlayerTeam == EntityTeam) {
                                if (PlayerController.Get() != Entity) {
                                    TracerColor = ImColor_D3D(Settings.FriendlyTracerColor);
                                    BoxColor = ImColor_D3D(Settings.FriendlyBoxColor);
                                    if (Settings.EnableTrace) {
                                        DrawLine(
                                            StartLocation.x,
                                            StartLocation.y,
                                            EndLocation.x,
                                            EndLocation.y,
                                            Settings.TracerThickness,
                                            Settings.Global_Antialias,
                                            TracerColor
                                        );
                                    }
                                    if (Settings.EnableBoundingBoxes) {
                                        DrawBoundingBox(
                                            Base.x,
                                            Base.y,
                                            Height * Settings.BoundingBoxesWidth,
                                            Height,
                                            Settings.BoundingBoxisThickness,
                                            Settings.Global_Antialias,
                                            BoxColor
                                        );

                                        DrawHealthBar(
                                            Base.x,
                                            Base.y,
                                            Height * Settings.BoundingBoxesWidth,
                                            Height,
                                            Settings.BoundingBoxisThickness,
                                            Settings.Global_Antialias,
                                            EntityHealth,
                                            EntityArmor
                                        );
                                    }

                                    if (Settings.EnablePlayerInfo) {
                                        DrawHealthText(
                                            Settings.m_font,
                                            (Base.x + (Height * Settings.BoundingBoxesWidth) / 2) + 5,
                                            Base.y - Height - 5,
                                            EntityHealth,
                                            EntityArmor
                                        );
                                    }

                                    if (Settings.EnableConoredESP) {
                                        DrawCorneredBox(
                                            Base.x,
                                            Base.y,
                                            Height * Settings.BoundingBoxesWidth,
                                            Height,
                                            Settings.BoundingBoxisThickness,
                                            Settings.CorneredCoverage / 2,
                                            Settings.Global_Antialias,
                                            BoxColor
                                        );
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    

    oEndScene(pDevice);
}

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

    if (true && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
        return true;
    return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}
BOOL CALLBACK EnumWindowsCallback(HWND handle, LPARAM lParam)
{
    DWORD wndProcId;
    GetWindowThreadProcessId(handle, &wndProcId);

    if (GetCurrentProcessId() != wndProcId)
        return TRUE;
    window = handle;
    return FALSE;
}
HWND GetProcess()
{
    window = NULL;
    EnumWindows(EnumWindowsCallback, NULL);
    return window;
}

DWORD WINAPI MainThread(HMODULE hMod)
{
    // Hook
    if (GetD3D9Device(d3d9Device, sizeof(d3d9Device)))
    {
        memcpy(EndSceneBytes, (char*)d3d9Device[42], 7);
        oEndScene = (tEndScene)TrampHook((char*)d3d9Device[42], (char*)hkEndScene, 7);
    }
    window = GetProcess();
    oWndProc = (WNDPROC)SetWindowLongPtr(window, -4, (LONG_PTR)WndProc);

    // Loop
    while (!GetAsyncKeyState(UNINJECT_KB))
    {

    }

    // Unhook
    Patch((BYTE*)d3d9Device[42], EndSceneBytes, 7);
    FreeLibraryAndExitThread(hMod, 0);
}

BOOL __stdcall StartThread(HMODULE hModule, LPTHREAD_START_ROUTINE StartAddress)
{
    return CloseHandle(CreateThread(0, 0, (LPTHREAD_START_ROUTINE)StartAddress, hModule, 0, 0));
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        E.Init();
        StartThread(hModule, (LPTHREAD_START_ROUTINE)MainThread);
        StartThread(hModule, (LPTHREAD_START_ROUTINE)BhopThread);
        StartThread(hModule, (LPTHREAD_START_ROUTINE)TriggerThread);
        StartThread(hModule, (LPTHREAD_START_ROUTINE)FOVThread);
        StartThread(hModule, (LPTHREAD_START_ROUTINE)ThirdPersonThread);
        StartThread(hModule, (LPTHREAD_START_ROUTINE)GlowThread);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}