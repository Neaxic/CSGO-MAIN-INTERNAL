#include "include.h"

void ShowWatermark(bool* OpenWindow, const char* text, ImVec4 Color) {
	const float Distance = 10.0f;
	static int cornor = 0;
	ImGuiIO& io = ImGui::GetIO();
	ImGuiWindowFlags WindowFlags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav;
	//ImGui::fustFont()


	if (io.MousePos.x < 300.0f && io.MousePos.y < 100) {
		if (cornor != -1) {
			WindowFlags |= ImGuiWindowFlags_NoMove;
			ImVec2 WindowPosPivot = ImVec2((cornor & 1) ? 1.0f : 0.f, (cornor & 2) ? 1.0f : 0.0f);
			ImVec2 WindowPos = ImVec2((cornor & 1) ? io.DisplaySize.x - Distance : Distance, (cornor & 2) ? io.DisplaySize.y - Distance : Distance);
			ImGui::SetNextWindowPos(WindowPos, ImGuiCond_Always, WindowPosPivot);
		}
		if (ImGui::Begin("Watermark", OpenWindow, WindowFlags)) {
			//ImGui::PushFont()
			ImGui::TextColored(Color, text);
			//ImGui::PopFont();
			ImGui::End();
		}
	}
	else {
		if (cornor != -1) {
			WindowFlags |= ImGuiWindowFlags_NoMove;
			ImVec2 WindowPosPivot = ImVec2((cornor & 1) ? 1.0f : 0.f, (cornor & 2) ? 1.0f : 0.0f);
			ImVec2 WindowPos = ImVec2((cornor & 1) ? io.DisplaySize.x - Distance : Distance, (cornor & 2) ? io.DisplaySize.y - Distance : Distance);
			ImGui::SetNextWindowPos(WindowPos, ImGuiCond_Always, WindowPosPivot);
		}
		if (ImGui::Begin("Watermark", OpenWindow, WindowFlags)) {
			//ImGui::PushFont()
			ImGui::TextColored(Color, text);
			//ImGui::PopFont();
			ImGui::End();
		}
	}
}



