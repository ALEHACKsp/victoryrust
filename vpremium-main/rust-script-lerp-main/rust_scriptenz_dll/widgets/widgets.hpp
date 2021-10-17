#pragma once

#ifndef WIDGETS_HPP
#define WIDGETS_HPP

#include "../pch/pch.h"

namespace ImGui {
	bool Hotkey(const char* label, int* k, const ImVec2& size_arg = {});
	bool BeginGroupBox(const char* label, const ImVec2& size = { 200.f, 200.f });
	void EndGroupBox();
	bool BetterCombo(const char* label, const char* preview_text, int* current_item, const char* const items[], int items_count);
}

#endif // !WIDGETS_HPP
