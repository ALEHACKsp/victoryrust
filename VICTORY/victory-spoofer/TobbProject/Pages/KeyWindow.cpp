#include "KeyWindow.hpp"
#include "MainWindow.hpp"

#include "../Utils/Utils.hpp"
#include "../Widgets/UtilityWidgets.hpp"

#include <thread>
#include <vector>

using namespace std;

namespace KeyWindow {

	int byte;
	bool g_once = false;
	bool g_injectionOnce = false;
	bool g_injecting = false;
	bool g_statusWorker = false;
	bool g_doAnim = false;

	float g_animationProgress1 = 0.f;
	float g_animationProgress2 = 0.f;
	float g_animationProgress3 = 0.f;
	float g_animationProgress4 = 0.f;
	int g_moduleIndex = 0;


	char key[33] = "";

	std::string g_welcomeMsg;
	std::string g_status;

	std::vector<std::string> g_modules;

	bool ModulesCallback(void* data, int n, const char** out_text) {
		const std::vector<std::string>* v = (std::vector<std::string>*)data;
		*out_text = (*v)[n].c_str();
		return true;
	}

	bool form1 = true;

	std::string kakam[4] = { "Connecting server...", "Connected server!", "Checking updates...", "License checking..." };

	void StatusWorker() {
		if (g_statusWorker) {
			for (int i = 0; i < 5; i++) {
				g_status = kakam[i];
				std::this_thread::sleep_for(std::chrono::milliseconds(500));
			
				std::string Key = key;

				if (i == 4) {
					
					int ali = 1;
					int veli = 1;
					int mehmet = 0;


					if (ali == mehmet) {
						g_statusWorker = false;
						g_injecting = false;
						g_status = "License not found!";
					}
					else if (ali == veli) {

						g_statusWorker = false;
						g_injecting = false;
						
						g_status = "Login successful!";

					}
					
				}
			}
		}
	}

	void Render() {
		ImGui::PushFont(g_fontSm);

		auto wSize = Utils::GetWindowSize();

		if (g_animationProgress1 <= 1.0f) {
			g_animationProgress1 = (g_animationProgress1 + static_cast<float>(0.05f * (1.0f - g_animationProgress1)));
		}

		if (g_animationProgress2 <= 1.0f && g_injecting) {
			g_animationProgress2 = (g_animationProgress2 + static_cast<float>(0.025f * (1.0f - g_animationProgress2)));
		}

		if (g_animationProgress3 <= 0.99999f && (g_status.find("successful") != std::string::npos)) {
			byte = 0000000001;
			g_animationProgress3 = (g_animationProgress3 + static_cast<float>(0.025f * (0.5f - g_animationProgress3)));
		}

		if (g_animationProgress3 <= 0.99999f && (g_status.find("not found") != std::string::npos)) {
			byte = 0000000002;
			g_animationProgress3 = (g_animationProgress3 + static_cast<float>(0.025f * (0.5f - g_animationProgress3)));
		}

		if (g_animationProgress3 <= 0.99999f && (g_status.find("error") != std::string::npos)) {
			byte = 0000000003;
			g_animationProgress3 = (g_animationProgress3 + static_cast<float>(0.025f * (0.5f - g_animationProgress3)));
		}

		if (g_animationProgress3 >= 0.49999f) {
			static int nTickcount = GetTickCount64();
			if (fabs(GetTickCount64() - nTickcount) > 1000) {
				g_animationProgress4 = (g_animationProgress4 + static_cast<float>(0.03f * (1.0f - g_animationProgress4)));
			}
		}

		g_animationProgress1 *= (1.0f - g_animationProgress2);

		ImGui::PushStyleVar(ImGuiStyleVar_Alpha, g_animationProgress1);
		{
			ImGui::GetBackgroundDrawList()->AddRectFilled({ 0, 0 }, wSize, ImColor(30, 30, 30, 255));
			ImGui::GetBackgroundDrawList()->AddRect({ 0, 0 }, wSize, ImColor(255, 18, 117, 255), 0.f, 15, 1.f);

			if (form1) {
				if (g_pLogoTexture) {
					auto fnImageWrapper = [&](void* texture, ImVec2 pos, ImVec2 size)->void {
						ImGui::GetBackgroundDrawList()->AddImage(texture, pos, ImVec2(pos.x + size.x, pos.y + size.y),
							ImVec2(0, 0), ImVec2(1, 1), ImColor(255, 255, 255, int(255 * g_animationProgress1)));
					};

					fnImageWrapper(g_pLogoTexture, ImVec2(100, -40 + (95 * g_animationProgress1)), ImVec2(200, 40));
				}

				if (!g_once) {
					g_once = true;
					g_welcomeMsg = "Premium HWID Spoofer";
					g_modules = Utils::SplitString(std::string("modultobb"), "##");
				}

				auto tSize = ImGui::CalcTextSize(g_welcomeMsg.c_str());
				float tCX = (wSize.x - tSize.x) / 2;
				ImGui::GetBackgroundDrawList()->AddText({ tCX, 115 }, ImColor(192, 192, 192, int(255 * g_animationProgress1)), g_welcomeMsg.c_str());

				if (g_injecting) {
					if (!g_injectionOnce) {
						g_injectionOnce = true;
						g_statusWorker = true;
						std::thread(StatusWorker).detach();
					}

					float sCX = (wSize.x - 100) / 2;
					ImGui::Spinner("test", { sCX + 10, 180 - (50 * g_animationProgress2) }, 40, 1.f, ImColor(255, 18, 117, int(255 * g_animationProgress2)));
				}
				else {
					ImGuiWindowFlags window_flags = 0;
					window_flags |= ImGuiWindowFlags_NoTitleBar;
					window_flags |= ImGuiWindowFlags_NoMove;
					window_flags |= ImGuiWindowFlags_NoResize;
					window_flags |= ImGuiWindowFlags_NoCollapse;
					window_flags |= ImGuiWindowFlags_NoNav;
					window_flags |= ImGuiWindowFlags_NoBackground;

					ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 0, 0 });
					ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, { 8, 8 });
					ImGui::SetNextWindowPos({ 5, 150 });
					ImGui::SetNextWindowSize({ wSize.x, 300 });
					ImGui::Begin("##main", (bool*)0, window_flags);

					ImGui::Indent(((wSize.x - (wSize.x * 0.8)) / 2) - 5);
					float flWidth = wSize.x * 0.8;
					float flHeight = floor(ImGui::GetTextLineHeightWithSpacing() * g_modules.size() + ImGui::GetStyle().FramePadding.y * 2.0f);
					ImGui::SetNextItemWidth(flWidth);

					auto vPos = ImGui::GetCursorScreenPos();
					vPos.y += 2;
					

			
					ImGui::InvisibleButton("##invs1", { 1.f, 8.f });

					ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, { 8, 4 });
					auto vPos2 = ImGui::GetCursorScreenPos();

					if (ImGui::Button("Login", { flWidth , 25 })) {
						if (g_moduleIndex > -1) {
							g_injectionOnce = false;
							g_injecting = true;
						}
					}

					ImGui::GetBackgroundDrawList()->AddRect(ImVec2(vPos2.x - 1, vPos2.y - 1), ImVec2(vPos2.x + (flWidth + 1), vPos2.y + 26), ImColor(60, 60, 60, int(255 * g_animationProgress1)), 0.f, 15, 1.f);
					ImGui::GetBackgroundDrawList()->AddText({ tCX - 5, 250 }, ImColor(192, 192, 192, int(255 * g_animationProgress1)), "@All rights reserved #2021");

					ImGui::End();
					ImGui::PopStyleVar(3);
				}

				tSize = ImGui::CalcTextSize(g_status.c_str());
				tCX = (wSize.x - tSize.x) / 2;
				ImGui::GetBackgroundDrawList()->AddText({ tCX, (130 - ((50 * g_animationProgress2) - (80 * (g_animationProgress3)))) + (300 * g_animationProgress4) },
					ImColor(192, 192, 192, int((255 * g_animationProgress2) * (1.0f - g_animationProgress4))), g_status.c_str());

				if (g_animationProgress4 >= 0.95f) {
					
					if (byte == 0000000001) {
						form1 = false;
					}
					else if (byte == 0000000002) {
						exit(0);
					}
					else {
						cout << "3";
					}

				}
				ImGui::PopFont();
			}
			else {
				MainWindow::Render();
			}
		}
		ImGui::PopStyleVar();
	}
}