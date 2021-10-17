#include "LoadingWindow.hpp"

#include "../Utils/Utils.hpp"
#include "../Widgets/UtilityWidgets.hpp"
#include "../Pages/MainWindow.hpp"
#include "../Pages/KeyWindow.hpp"
#include <thread>

namespace LoadingWindow {

	bool g_statusWorker = false;
	bool g_once = false;
	float g_animationProgress = 0.f;
	std::string g_status = "";
	bool form1 = true;

	int g_fadeAnim = 10;
	int g_spinnerFade = 30;
	int r = 255;
	int g = 0;
	int b = 0;

	void StatusWorker() {
		const char* statusText[3] = { "Checking for updates", "Checking license", "The Nulled is being prepared" };
		for (int i = 0; i < 3; i++) {
			g_status = statusText[i];
			std::this_thread::sleep_for(std::chrono::milliseconds(1500));
			if (i == 2) {
				std::this_thread::sleep_for(std::chrono::milliseconds(1500));
				form1 = false;
			}
		}
	}

	void Render() {
		if (form1) {

			#pragma region RGB

			if (r >= 255 && g >= 0 && b == 0) {
				g++;
			}
			if (r <= 255 && g >= 255 && b == 0) {
				r--;
			}
			if (r == 0 && g >= 255 && b >= 0) {
				b++;
			}
			if (r == 0 && g <= 255 && b >= 255) {
				g--;
			}
			if (r >= 0 && g == 0 && b == 255) {
				r++;
			}
			if (r >= 255 && g == 0 && b <= 255) {
				b--;
			}

			#pragma endregion

			if (g_fadeAnim <= 255) {
				g_fadeAnim++;
				std::this_thread::sleep_for(std::chrono::milliseconds(20));
			}

			if (g_fadeAnim <= 180 && g_spinnerFade >= 0) {
				g_spinnerFade++;
			}

			if (g_animationProgress <= 1.0f) {
				g_animationProgress = (g_animationProgress + static_cast<float>(0.05f * (1.0f - g_animationProgress)));
			}

			auto wSize = Utils::GetWindowSize();
			ImGui::GetBackgroundDrawList()->AddRectFilled({ 0, 0 }, wSize, ImColor(30, 30, 30, 255));
			ImGui::GetBackgroundDrawList()->AddRect({ 0, 0 }, wSize, ImColor(255, 18, 117, g_fadeAnim), 0.f, 15, 1.f);

			ImGui::PushFont(g_fontSm);
			auto tSize = ImGui::CalcTextSize(g_status.c_str());
			float tCX = (wSize.x - tSize.x) / 2;
			ImGui::GetBackgroundDrawList()->AddText({ tCX, 70 }, ImColor(255, 246, 222, int(255 * g_animationProgress)), g_status.c_str());
			ImGui::PopFont();

			float sCX = (wSize.x - 100) / 2;
			ImGui::Spinner("test", { sCX + 10, 135 }, 40, 1.f, ImColor(r, g, b, int(g_spinnerFade * g_animationProgress)));

			if (!g_once) {
				g_statusWorker = true;
				g_once = true;
				std::thread(StatusWorker).detach();
			}

			ImGui::PushFont(g_fontMd);
			auto sSize = ImGui::CalcTextSize(g_status.c_str());
			float statusCX = (wSize.x - sSize.x) / 2;
			ImGui::GetBackgroundDrawList()->AddText({ statusCX, 300 }, ImColor(192, 192, 192, int(255 * g_animationProgress)), g_status.c_str());
			ImGui::PopFont();
		}
		else {
			KeyWindow::Render();
		}
	}
}