#include "MainWindow.hpp"

#include "../Utils/Utils.hpp"
#include "../Widgets/UtilityWidgets.hpp"


#include <thread>
#include <vector>




//#include "Spoofer\encrypt\xor.h"


#include "../Spoofer/hwid.h"
#include "../Spoofer/spoof/spoof.h"
#include "../Spoofer/spoof/caches.h"

extern "C" {
#include "../Spoofer/spoof/cleaner/clean.h"

}
template< typename ... Args >
std::string stringer(Args const& ... args)
{
	std::ostringstream stream;
	using List = int[];
	(void)List {
		0, ((void)(stream << args), 0) ...
	};
	return stream.str();
}


void spoof() {


}

using namespace std;

namespace MainWindow {
	bool g_once = false;
	bool g_injectionOnce = false;
	bool g_injecting = false;
	bool g_statusWorker = false;
	bool g_doAnim = false;
	bool g_loginAnim = false;
	bool durumkontrol = false;

	float g_animationProgress1 = 0.f;
	float g_animationProgress2 = 0.f;
	float g_animationProgress3 = 0.f;
	float g_animationProgress4 = 0.f;
	int g_moduleIndex = 0;

	int m_product;
	int s_product;

	std::string m_string = "";
	std::string s_string = "";

	std::string g_welcomeMsg;
	std::string g_status;



	bool loginQuery = true;

	std::vector<std::string> g_modules;

	bool ModulesCallback(void* data, int n, const char** out_text) {
		const std::vector<std::string>* v = (std::vector<std::string>*)data;
		*out_text = (*v)[n].c_str();
		return true;
	}

	std::string Texts[6] = { "Cleaning game traces", "Deleting AC history", "HardClean Opinion ", "Cleaning Registry", "Checking Last ID's", "Done You Ready to go!" };

	void StatusWorker() {

		ProcessKiller(); VanguardDrivers();  DriverLoad(); 
		for (int i = 0; i < 6; i++) {

			g_status = Texts[i];
			std::this_thread::sleep_for(std::chrono::milliseconds(2000));

	//		
			if (i == 1)
			{
				std::thread st1(GayMacChanger);
				st1.detach();
			}

			if (i == 2)

			{
			
				

			}

			if (i == 3)
			{
			
				const int spoofopt = MessageBoxA(0, _xor_("Would you like to use Hard Cleaner?").c_str(), (_xor_("Victory Spoofer").c_str()), MB_YESNO);
				switch (spoofopt)
				{

				case IDYES:
					printf(_xor_("\n   [+] Spoofing\n").c_str());
					
					HardCleann();
					printf(_xor_("   [+] Spoofed!").c_str());
					Sleep(1000);
					system(_xor_("cls").c_str());

				case IDNO:
					printf(_xor_("\n   [!] Spoofing Skipped").c_str());
					Sleep(1500);
			}
				Sleep(3000);


			}
			if (i == 4) {
			
			
			}
			if (i == 5) {
				/* ney */
				
				g_statusWorker = false;
				g_injecting = false;
			
				g_status = "Done!";
				std::this_thread::sleep_for(std::chrono::milliseconds(1000));

				/* load driver here */
				
			}
		}
	}
	

	void Test() {
		if (loginQuery) {
			loginQuery = false;
			
		}

		if (m_product == 1) {
			m_string = "Rust Script";
		}
		else {
			m_string = "";
		}

		if (s_product == 1) {
			s_string = "Hwid Spoofer";
		}
		else {
			s_string = "";
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

		if (g_animationProgress3 <= 0.99999f && (g_status.find("Done") != std::string::npos)) {
			g_animationProgress3 = (g_animationProgress3 + static_cast<float>(0.025f * (1.0f - g_animationProgress3)));
		}

		if (g_animationProgress3 >= 0.99999f) {	
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

			if (g_pLogoTexture) {
				auto fnImageWrapper = [&](void* texture, ImVec2 pos, ImVec2 size)->void {
					ImGui::GetBackgroundDrawList()->AddImage(texture, pos, ImVec2(pos.x + size.x, pos.y + size.y),
						ImVec2(0, 0), ImVec2(1, 1), ImColor(255, 255, 255, int(255 * g_animationProgress1)));
				};

				fnImageWrapper(g_pLogoTexture, ImVec2(100, (-40) + (95 * g_animationProgress1)), ImVec2(200, 40));
			}

			if (!g_once) {
				g_once = true;
				g_welcomeMsg = "Welcome, Please select process " + std::string( "" );
			}

			auto tSize = ImGui::CalcTextSize(g_welcomeMsg.c_str());
			float tCX = (wSize.x - tSize.x) / 2;
			ImGui::GetBackgroundDrawList()->AddText({ tCX, 115 }, ImColor(192, 192, 192, int(255 * g_animationProgress1)), g_welcomeMsg.c_str());

			if (!g_loginAnim) {
				g_loginAnim = true;
				std::thread(Test).detach();
			} 
			else if (g_injecting) {

				if (!g_injectionOnce) {
					g_injectionOnce = true;
					g_statusWorker = true;
					std::thread(StatusWorker).detach();
				}

				float sCX = (wSize.x - 100) / 2;
				ImGui::Spinner("test", { sCX + 10, 165 - (50 * g_animationProgress2) }, 40, 1.f, ImColor(255, 18, 117, int(255 * g_animationProgress2)));
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

				ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, { 8 , 4 });
				auto vPos2 = ImGui::GetCursorScreenPos();

				const char* items[] = {"", "EyePremium Spoofer - PUBLIC" ,""  };

				static const char* current_item = items[1];

				if (ImGui::BeginCombo("##combo", current_item))
				{
					for (int n = 0; n < IM_ARRAYSIZE(items); n++)
					{
						std::string convert = items[n];
						if (!convert.empty()) {
							bool is_selected = (current_item == items[n]);
							if (ImGui::Selectable(items[n], is_selected)) {
								current_item = items[n];
								if (is_selected) {
									ImGui::SetItemDefaultFocus();
								}
							}
						}
					}
					ImGui::EndCombo();
				}

				ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 20);

				if (ImGui::Button("Load", { flWidth, 25 })) {
					if (g_moduleIndex > -1) {
						g_injectionOnce = false;
						g_injecting = true;
					}
				}

				ImGui::GetBackgroundDrawList()->AddRect(ImVec2(vPos2.x - 1, vPos2.y - 1), ImVec2(vPos2.x + (flWidth + 1), vPos2.y + 26), ImColor(60, 60, 60, int(255 * g_animationProgress1)), 0.f, 15, 1.f);

				ImGui::End();
				ImGui::PopStyleVar(3);
			}


			tSize = ImGui::CalcTextSize(g_status.c_str());
			tCX = (wSize.x - tSize.x) / 2;
			ImGui::GetBackgroundDrawList()->AddText({ tCX, (100 - ((50 * g_animationProgress2) - (80 * (g_animationProgress3)))) + (300 * g_animationProgress4) },
				ImColor(192, 192, 192, int((255 * g_animationProgress2) * (1.0f - g_animationProgress4))), g_status.c_str());

			if (g_animationProgress4 >= 0.95f) {
				exit(1);
			}
			ImGui::PopFont();
		}
		ImGui::PopStyleVar();
	}
}