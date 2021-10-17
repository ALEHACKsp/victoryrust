#include "Utils.hpp"

namespace Utils {
	void Shout(std::string_view message, std::string_view title, bool exit) {
		MessageBoxA(0, message.data(), title.data(), MB_OK);

		if (exit) {
			std::exit(1);
		}
	}

	ImVec2 GetWindowSize() {
		RECT size = {};
		GetWindowRect(g_hwnd, &size);

		return { (float)(size.right - size.left), (float)(size.bottom - size.top) };
	}

	std::vector<std::string> SplitString(std::string str, std::string_view delimiter) {
		std::vector<std::string> tokens;

		size_t pos = 0;
		while ((pos = str.find(delimiter)) != std::string::npos) {
			tokens.push_back(str.substr(0, pos));
			str.erase(0, pos + delimiter.size());
		}
		tokens.push_back(str);

		return tokens;
	}
}