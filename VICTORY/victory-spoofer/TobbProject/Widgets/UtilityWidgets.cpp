#include "UtilityWidgets.hpp"
#include "../ImGui/imgui_internal.h"

namespace ImGui {
    void BufferingBar(const char* label, float value, const ImVec2& pos, const ImVec2& size_arg, const ImU32& bg_col, const ImU32& fg_col) {
        ImGuiContext& g = *GImGui;
        ImVec2 size = size_arg;

        const ImRect bb(pos, ImVec2(pos.x + size.x, pos.y + size.y));
        //ItemSize(bb);

        const float circleStart = size.x * 0.7f;
        const float circleEnd = size.x;
        const float circleWidth = circleEnd - circleStart;

        ImGui::GetBackgroundDrawList()->AddRectFilled(bb.Min, ImVec2(pos.x + circleStart, bb.Max.y), bg_col);
        ImGui::GetBackgroundDrawList()->AddRectFilled(bb.Min, ImVec2(pos.x + circleStart * value, bb.Max.y), fg_col);

        const float t = g.Time;
        const float r = size.y / 2;
        const float speed = 1.5f;

        const float a = speed * 0;
        const float b = speed * 0.333f;
        const float c = speed * 0.666f;

        const float o1 = (circleWidth + r) * (t + a - speed * (int)((t + a) / speed)) / speed;
        const float o2 = (circleWidth + r) * (t + b - speed * (int)((t + b) / speed)) / speed;
        const float o3 = (circleWidth + r) * (t + c - speed * (int)((t + c) / speed)) / speed;

        ImGui::GetBackgroundDrawList()->AddCircleFilled(ImVec2(pos.x + circleEnd - o1, bb.Min.y + r), r, bg_col);
        ImGui::GetBackgroundDrawList()->AddCircleFilled(ImVec2(pos.x + circleEnd - o2, bb.Min.y + r), r, bg_col);
        ImGui::GetBackgroundDrawList()->AddCircleFilled(ImVec2(pos.x + circleEnd - o3, bb.Min.y + r), r, bg_col);
    }

    void Spinner(const char* label, const ImVec2& pos, float radius, int thickness, const ImU32& color) {
        ImGuiContext& g = *GImGui;

        ImVec2 size((radius) * 2, radius * 2);

        const ImRect bb(pos, ImVec2(pos.x + size.x, pos.y + size.y));

        ImGui::GetBackgroundDrawList()->PathClear();

        int num_segments = 30;
        int start = abs(ImSin(g.Time * 0.5f) * (num_segments - 5));

        const float a_min = IM_PI * 2.0f * ((float)start) / (float)num_segments;
        const float a_max = IM_PI * 2.0f * ((float)num_segments - 3) / (float)num_segments;

        const ImVec2 centre = ImVec2(pos.x + radius, pos.y + radius);

        for (int i = 0; i < num_segments; i++) {
            const float a = a_min + ((float)i / (float)num_segments) * (a_max - a_min);
            ImGui::GetBackgroundDrawList()->PathLineTo(ImVec2(centre.x + ImCos(a + g.Time * 8) * radius,
                centre.y + ImSin(a + g.Time * 8) * radius));
        }

        ImGui::GetBackgroundDrawList()->PathStroke(color, false, thickness);
    }
}