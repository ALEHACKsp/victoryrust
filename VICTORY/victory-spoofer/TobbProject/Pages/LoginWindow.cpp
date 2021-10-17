#include "LoginWindow.hpp"

#include "../Utils/Utils.hpp"
#include "../Widgets/UtilityWidgets.hpp"

#include <thread>

namespace LoginWindow {
	bool g_statusWorker = false;
	bool g_once = false;
	float g_animationProgress = 0.f;
	std::string g_status = "";

	void StatusWorker() {
		while (g_statusWorker) {
			g_status = std::string(NULL);
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
		}
	}

	void LoginWorker() {
		if (true) {
			g_statusWorker = false;
			g_loggedIn = true;
			g_status = "Welcome " + std::string(NULL);
		}

		else {
			Utils::Shout("Login failed", "infinity", true);
		}
	}

	void Render() {
		if (g_animationProgress <= 1.0f) {
			g_animationProgress = (g_animationProgress + static_cast<float>(0.05f * (1.0f - g_animationProgress)));
		}

		auto wSize = Utils::GetWindowSize();
		ImGui::GetBackgroundDrawList()->AddRectFilled({ 0, 0 }, wSize, ImColor(30, 30, 30, 255));
		ImGui::GetBackgroundDrawList()->AddRect({ 0, 0 }, wSize, ImColor(0, 150, 255, 255), 0.f, 15, 2.f);

		//ImGui::PushFont(g_fontLg);
		auto tSize = ImGui::CalcTextSize("Please wait...");
		float tCX = (wSize.x - tSize.x) / 2;
		ImGui::GetBackgroundDrawList()->AddText({ tCX, 50 }, ImColor(0, 150, 255, int(255 * g_animationProgress)), "Please wait...");
		//ImGui::PopFont();

		float sCX = (wSize.x - 100) / 2;
		ImGui::Spinner("test", { sCX, 150 }, 50, 2.f, ImColor(0, 150, 255, int(255 * g_animationProgress)));

		if (!g_once) {
			g_statusWorker = true;
			g_once = true;
			//std::thread(LoginWorker).detach();
			//std::thread(StatusWorker).detach();
		}

		//ImGui::PushFont(g_fontMd);
		auto sSize = ImGui::CalcTextSize(g_status.c_str());
		float statusCX = (wSize.x - sSize.x) / 2;
		ImGui::GetBackgroundDrawList()->AddText({ statusCX, 300 }, ImColor(192, 192, 192, int(255 * g_animationProgress)), g_status.c_str());
		//ImGui::PopFont();
	}
}