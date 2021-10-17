#include "src/core/graphics_api.hpp"
#include "src/widgets/widgets.hpp"
#include "Cheat.h"
#include <imgui_internal.h>


bool g_open = true;
bool g_toggledInput = false;
int g_key = 0;

bool WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	return true;
}

void InitUI() {
	ImGuiStyle& s = ImGui::GetStyle();
	s.WindowRounding = 0.f;
}

bool bDrawFov = false;

void MenuStyle() {

	ImGuiStyle* style = &ImGui::GetStyle();
	ImVec4* colors = ImGui::GetStyle().Colors;
	style->Alpha = 1.0f;               // Global alpha applies to everything in ImGui


	//style->AntiAliasedFill = true;
	//style->AntiAliasedLines = true;
	//

	colors[ImGuiCol_Text] = ImVec4(0.78f, 0.78f, 0.78f, 1.00f);
	colors[ImGuiCol_TextDisabled] = ImVec4(0.44f, 0.43f, 0.43f, 1.00f);

	colors[ImGuiCol_WindowBg] = ImColor(222, 76, 114, 255);
	colors[ImGuiCol_ChildBg] = ImVec4(0.12f, 0.12f, 0.15f, 1.00f);
	colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
	colors[ImGuiCol_Border] = ImVec4(0.09f, 0.08f, 0.08f, 1.00f);
	colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_FrameBg] = ImVec4(0.16f, 0.16f, 0.19f, 1.00f);
	colors[ImGuiCol_FrameBgHovered] = ImVec4(0.16f, 0.16f, 0.19f, 1.00f);
	colors[ImGuiCol_FrameBgActive] = ImVec4(0.09f, 0.08f, 0.08f, 1.00f);
	colors[ImGuiCol_TitleBg] = ImVec4(0.12f, 0.12f, 0.15f, 1.00f);
	colors[ImGuiCol_TitleBgActive] = ImVec4(0.12f, 0.12f, 0.15f, 1.00f);
	colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.12f, 0.12f, 0.15f, 0.51f);
	colors[ImGuiCol_MenuBarBg] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_ScrollbarBg] = ImVec4(0.48f, 0.07f, 0.20f, 0.35f);
	colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
	colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.18f, 0.22f, 0.25f, 1.00f);
	colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.09f, 0.21f, 0.31f, 1.00f);
	colors[ImGuiCol_CheckMark] = ImColor(222, 76, 114, 255);
	colors[ImGuiCol_SliderGrab] = ImColor(222, 76, 114, 255);
	colors[ImGuiCol_SliderGrabActive] = ImColor(222, 76, 114, 255);

	

	colors[ImGuiCol_ButtonActive] = ImVec4(0.48f, 0.07f, 0.20f, 0.35f);
	colors[ImGuiCol_Header] = ImVec4(0.20f, 0.25f, 0.29f, 0.55f);
	colors[ImGuiCol_HeaderHovered] = ImVec4(0.48f, 0.07f, 0.20f, 0.44f);
	colors[ImGuiCol_HeaderActive] = ImVec4(0.48f, 0.07f, 0.20f, 0.35f);
	colors[ImGuiCol_Separator] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
	colors[ImGuiCol_SeparatorHovered] = ImVec4(0.48f, 0.07f, 0.20f, 0.35f);
	colors[ImGuiCol_SeparatorActive] = ImVec4(0.48f, 0.07f, 0.20f, 0.35f);
	colors[ImGuiCol_ResizeGrip] = ImVec4(0.48f, 0.07f, 0.20f, 0.35f);
	colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.48f, 0.07f, 0.20f, 0.35f);
	colors[ImGuiCol_ResizeGripActive] = ImVec4(0.48f, 0.07f, 0.20f, 0.35f);
	colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
	colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
	colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
	colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
	colors[ImGuiCol_TextSelectedBg] = ImVec4(0.48f, 0.07f, 0.20f, 0.35f);
	colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
	//

    colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
	colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.06f, 0.06f, 0.94f);
	colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
	colors[ImGuiCol_Border] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
	colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_FrameBg] = ImVec4(0.16f, 0.29f, 0.48f, 0.54f);
	colors[ImGuiCol_FrameBgHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
	colors[ImGuiCol_FrameBgActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
	colors[ImGuiCol_TitleBg] = ImVec4(0.04f, 0.04f, 0.04f, 1.00f);
	colors[ImGuiCol_TitleBgActive] = ImVec4(0.16f, 0.29f, 0.48f, 1.00f);
	colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
	colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
	colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
	colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
	colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
	colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
	colors[ImGuiCol_CheckMark] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	colors[ImGuiCol_SliderGrab] = ImVec4(0.24f, 0.52f, 0.88f, 1.00f);
	colors[ImGuiCol_SliderGrabActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	colors[ImGuiCol_Button] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	colors[ImGuiCol_ButtonHovered] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	colors[ImGuiCol_ButtonActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	colors[ImGuiCol_Header] = ImVec4(0.26f, 0.59f, 0.98f, 0.31f);
	colors[ImGuiCol_HeaderHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
	colors[ImGuiCol_HeaderActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	colors[ImGuiCol_Separator] = colors[ImGuiCol_Border];
	colors[ImGuiCol_SeparatorHovered] = ImVec4(0.10f, 0.40f, 0.75f, 0.78f);
	colors[ImGuiCol_SeparatorActive] = ImVec4(0.10f, 0.40f, 0.75f, 1.00f);
	colors[ImGuiCol_ResizeGrip] = ImVec4(0.26f, 0.59f, 0.98f, 0.25f);
	colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
	colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
	colors[ImGuiCol_Tab] = ImLerp(colors[ImGuiCol_Header], colors[ImGuiCol_TitleBgActive], 0.80f);
	colors[ImGuiCol_TabHovered] = colors[ImGuiCol_HeaderHovered];
	colors[ImGuiCol_TabActive] = ImLerp(colors[ImGuiCol_HeaderActive], colors[ImGuiCol_TitleBgActive], 0.60f);
	colors[ImGuiCol_TabUnfocused] = ImLerp(colors[ImGuiCol_Tab], colors[ImGuiCol_TitleBg], 0.80f);
	colors[ImGuiCol_TabUnfocusedActive] = ImLerp(colors[ImGuiCol_TabActive], colors[ImGuiCol_TitleBg], 0.40f);
	colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
	colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
	colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
	colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
	colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
	colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
	colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
	colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
	colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);




	style->Alpha = 1.0f;               // Global alpha applies to everything in ImGui
	style->WindowPadding = ImVec2(5, 5);     // Padding within a window
	style->WindowMinSize = ImVec2(100, 100);   // Minimum window size
	style->WindowRounding = 4.0f;               // Radius of window corners rounding. Set to 0.0f to have rectangular windows
	style->WindowTitleAlign = ImVec2(0.0f, 0.5f); // Alignment for title bar text
	style->FramePadding = ImVec2(4, 2);// Padding within a framed rectangle (used by most widgets)
	style->FrameRounding = 0.0f;               // Radius of frame corners rounding. Set to 0.0f to have rectangular frames (used by most widgets).
	style->ItemSpacing = ImVec2(2, 4);       // Horizontal and vertical spacing between widgets/lines
	style->ItemInnerSpacing = ImVec2(4, 4);       // Horizontal and vertical spacing between within elements of a composed widget (e.g. a slider and its label)
	style->TouchExtraPadding = ImVec2(0, 0);       // Expand reactive bounding box for touch-based system where touch position is not accurate enough. Unfortunately we don't sort widgets so priority on overlap will always be given to the first widget. So don't grow this too much!
	style->IndentSpacing = 18.0f;              // Horizontal spacing when e.g. entering a tree node. Generally == (FontSize + FramePadding.x*2).
	style->ColumnsMinSpacing = 6.0f;               // Minimum horizontal spacing between two columns
	style->ScrollbarSize = 0.01f;              // Width of the vertical scrollbar, Height of the horizontal scrollbar
	style->ScrollbarRounding = 9.0f;               // Radius of grab corners rounding for scrollbar
	style->GrabMinSize = 10.0f;              // Minimum width/height of a grab box for slider/scrollbar
	style->GrabRounding = 0.0f;               // Radius of grabs corners rounding. Set to 0.0f to have rectangular slider grabs.
	style->ButtonTextAlign = ImVec2(0.5f, 0.5f); // Alignment of button text when button is larger than text.
	style->DisplayWindowPadding = ImVec2(22, 22);     // Window positions are clamped to be visible within the display area by at least this amount. Only covers regular windows.
	style->DisplaySafeAreaPadding = ImVec2(4, 4);       // If you cannot see the edge of your screen (e.g. on a TV) increase the safe area padding. Covers popups/tooltips as well regular windows.
	//style->AntiAliasedLines = true;               // Enable anti-aliasing on lines/borders. Disable if you are really short on CPU/GPU.
	style->CurveTessellationTol = 1.25f;              // Tessellation tolerance. Decrease for highly tessellated curves (higher quality, more polygons), increase to reduce quality.
	style->ChildBorderSize = 1.0f;
	style->PopupBorderSize = 1.0f;
	style->WindowBorderSize = 1.0f;
	//style->TabBorderSize = 1.0f;
	style->FrameBorderSize = 1.0f;
	style->ChildRounding = 0.0f;


}

int WindowPos = 1;
int currenttab = 1;
int CurrentWindow = 1;

bool ApplyFullBright = false;
void RenderUI() {


	if (bDrawFov) {
		//bura1
		//DrawCircleImGui(960, 540, Vars::Aim::Fov + 1, { 0, 246, 197, 240 }, 40);
		DrawCircleImGui(960, 540, Vars::Aim::Fov, { 222, 76, 114, 255 }, 40);

	}
	if (Vars::Aim::Crosshair) {
		DrawNewTextImGui(960, 540, { 255,255, 255, 25 }, ".");
	}
	DrawNewTextImGui(1815, 10, { 66, 150, 249, 255 }, "Eye");
	DrawNewTextImGui(1830, 10, { 255,255, 255, 255 }, "Legit");
	Vars::Aim::Crosshair = true;
	if (g_open) {
		MenuStyle();

		if (WindowPos == 1) {
			ImGui::SetNextWindowPos(ImVec2(400, 400));
			WindowPos++;
		}

		ImGuiStyle* style = &ImGui::GetStyle();
		ImVec4* colors = ImGui::GetStyle().Colors;


		ImGuiWindowFlags flags = ImGuiWindowFlags_NoTitleBar  /*| ImGuiWindowFlags_AlwaysAutoResize*/ | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar;
		//ImGui::ShowStyleEditor();
	//	ImGui::SetNextWindowSize(ImVec2(460, 310));
		ImGui::SetNextWindowSize(ImVec2(560, 360));
		ImGui::Begin("EyeRust", NULL, flags);
		ImVec2 WindowPos = ImGui::GetWindowPos();


		//DrawNewTextImGui(1810, 10, { 0, 246, 197, 240 }, "vanity");
		//DrawNewTextImGui(1845, 10, { 255, 255, 255, 255 }, "solutions");
		ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.0f);
		ImGui::BeginChild("Tabs", ImVec2(550, 350), true);

		if (CurrentWindow == 1) {
			colors[ImGuiCol_Button] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
		}
		
			CurrentWindow = 1;
		


		colors[ImGuiCol_Button] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);

		//41 41 49
		ImGui::SetNextWindowPos(ImVec2(WindowPos.x + 5, WindowPos.y + 40));
		//colors[ImGuiCol_Border] = ImColor(222, 76, 114, 255);
		colors[ImGuiCol_Border] = ImVec4(0.09f, 0.08f, 0.08f, 1.00f);
		ImGui::BeginChild("Features", ImVec2(550, 350), true);
		colors[ImGuiCol_Border] = ImVec4(0.09f, 0.08f, 0.08f, 1.00f);


		if (CurrentWindow == 1) {
			
			ImGui::Text(" ");
			
			

			colors[ImGuiCol_ChildBg] = ImVec4(0.16f, 0.16f, 0.19f, 1.00f);

			//PLAYER ESP CHILD
			ImGui::SetNextWindowPos(ImVec2(WindowPos.x + 12, WindowPos.y + 68));
			ImGui::BeginChild("", ImVec2(265, 281), true);
			//	//265 281
			ImGui::Checkbox("No Recoil", &Vars::Misc::no_recoil);
			ImGui::Checkbox("No Spread", &Vars::Misc::anti_spread);
			ImGui::Checkbox("Insta Eoka", &Vars::Misc::InstaEoka);
			ImGui::Checkbox("Instant Compound", &Vars::Misc::compound);
			ImGui::Checkbox("Force Full Auto", &Vars::Misc::force_auto);

			ImGui::EndChild();

			//WORLD ESP CHILD
			ImGui::SetNextWindowPos(ImVec2(WindowPos.x + 283, WindowPos.y + 68));

			ImGui::BeginChild("  ", ImVec2(265, 281), true);
			ImGui::Checkbox("enable spyderman", &Vars::Misc::spyderman);
			ImGui::Checkbox("gravity", &Vars::Misc::gravity);
			ImGui::SliderFloat("gravity ammount", &Vars::Misc::ggravity, 0, 3);

			ImGui::Checkbox("FakeAdmin", &Vars::Misc::FakeAdmin);
			ImGui::Text(" ");

			ImGui::SliderInt("Fov", &Vars::Visuals::FOV, 1, 150, "%1.0f");
			ImGui::Checkbox("ApplyFov", &Vars::Misc::ApplyFov);
			if (Vars::Misc::ApplyFov) {
				UINT64 GraphicsConvar = driver::read<UINT64>(Gbase + 0x3231F60);
				UINT64 CurrentGraphics = driver::read<UINT64>(GraphicsConvar + 0xB8);
				driver::write<float>(CurrentGraphics + 0x18, Vars::Visuals::FOV);
				Vars::Misc::ApplyFov = false;
			}

			ImGui::EndChild();
		}
		colors[ImGuiCol_ChildBg] = ImVec4(0.12f, 0.12f, 0.15f, 1.00f);




		ImGui::EndChild();
		ImGui::EndChild();
		ImGui::End();
		//ImColor(222, 76, 114, 255);
		//ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
		DrawNewTextImGui(WindowPos.x + 255, WindowPos.y + 50, { 66, 150, 249, 255 }, "Eye ");
		DrawNewTextImGui(WindowPos.x + 275, WindowPos.y + 50, { 255, 255, 255, 255 }, "Legit");

		DrawNewTextImGui(WindowPos.x + 240, WindowPos.y + 10, { 66, 150, 249, 255 }, "VICTORY");
		DrawNewTextImGui(WindowPos.x + 285, WindowPos.y + 10, { 255, 255, 255, 255 }, "PRODUCTS");
		ImGui::PopStyleVar();
	}

	// render other windows here that should be displayed regardless of menu being open or not

	DrawPlayersLol();

	//ImGui::Begin("overlay"); {

	//	if (!g_open) {
	//		auto pos = ImGui::GetWindowPos();
	//		auto size = ImGui::GetWindowSize();

	//		POINT mPos;
	//		GetCursorPos(&mPos);

	//		bool isHovering = mPos.x >= pos.x && mPos.y >= pos.y && mPos.x <= (pos.x + size.x) && mPos.y <= (pos.y + size.y);

	//		if (!g_toggledInput && isHovering) {
	//			GAPI::EnableInput();
	//			printf("enabled\n");
	//			g_toggledInput = true;
	//		}

	//		else if (g_toggledInput && !isHovering) {
	//			GAPI::DisableInput();
	//			printf("disabled\n");
	//			g_toggledInput = false;
	//		}

	//		ImGui::Text("pos:  { %f, %f }", pos.x, pos.y);
	//		ImGui::Text("size: { %f, %f }", size.x, size.y);
	//		ImGui::Text("mpos: { %i, %i }", mPos.x, mPos.y);
	//		ImGui::Text("is hovering: %i", isHovering);
	//	}

	//	ImGui::Hotkey("keybind 2", &g_key);
	//} ImGui::End();
}

void GameThread() {
	while (true) {
		printf("tick\n");

		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}
}
void InitOverlay() {
	AllocConsole();
	FILE* _dummy;
	freopen_s(&_dummy, "CONOUT$", "w", stdout);

	InitializeCheat();
	//std::thread([]() { GameThread(); }).detach();

	GAPI::MakeWindow(
		"VICTORY", // window title
		"c_hook_with_imgui", // window class
		WndProc,
		InitUI,
		RenderUI,
		&g_open
	);

	return;
}
