#pragma once

#ifndef UTILITY_WIDGETS_HPP
#define UTILITY_WIDGETS_CPP

#include "../Utils/Utils.hpp"

namespace ImGui {
    void BufferingBar(const char* label, float value, const ImVec2& pos, const ImVec2& size_arg, const ImU32& bg_col, const ImU32& fg_col);
    void Spinner(const char* label, const ImVec2& pos, float radius, int thickness, const ImU32& color);
}

#endif // !UTILITY_WIDGETS_HPP
