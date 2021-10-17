#include "widgets.hpp"
#include "..\utils\utils.hpp"

#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui_internal.h"

static ImVector<ImRect> s_GroupPanelLabelStack;

const char* const KeyNames[] = {
"  Unknown",
	"m1",
	"m2",
	"cancel",
	"mB",
	"m3",
	"m4",
	"Unknown",
	"back",
	"tab",
	"Unknown",
	"Unknown",
	"CLEAR",
	"RETURN",
	"Unknown",
	"Unknown",
	"SHIFT",
	"CTRL",
	"MENU",
	"PAUSE",
	"CAPITAL",
	"KANA",
	"Unknown",
	"JUNJA",
	"FINAL",
	"KANJI",
	"Unknown",
	"ESCAPE",
	"CONVERT",
	"NONCONVERT",
	"ACCEPT",
	"MODECHANGE",
	"SPACE",
	"PRIOR",
	"NEXT",
	"END",
	"HOME",
	"left",
	"up",
	"right",
	"down",
	"SELECT",
	"PRINT",
	"EXECUTE",
	"SNAPSHOT",
	"ins",
	"DELETE",
	"HELP",
	"0",
	"1",
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",
	"8",
	"9",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"a",
	"b",
	"c",
	"d",
	"e",
	"f",
	"g",
	"h",
	"i",
	"j",
	"k",
	"l",
	"m",
	"n",
	"o",
	"p",
	"q",
	"r",
	"s",
	"t",
	"u",
	"v",
	"w",
	"x",
	"y",
	"x",
	"lwin",
	"RWIN",
	"APPS",
	"Unknown",
	"SLEEP",
	"n0",
	"n1",
	"n2",
	"n3",
	"n4",
	"n5",
	"n6",
	"n7",
	"n8",
	"n9",
	"*",
	"+",
	"|",
	"-",
	".",
	"/",
	"f1",
	"f2",
	"f3",
	"f4",
	"f5",
	"f6",
	"f7",
	"f8",
	"f9",
	"f10",
	"f11",
	"f12",
	"f13",
	"f14",
	"f15",
	"f16",
	"f17",
	"f18",
	"f19",
	"f20",
	"f21",
	"f22",
	"f23",
	"f24",
	"  Unknown",
	"  Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"n-lock",
	"SCROLL",
	"VK_OEM_NEC_EQUAL",
	"VK_OEM_FJ_MASSHOU",
	"VK_OEM_FJ_TOUROKU",
	"VK_OEM_FJ_LOYA",
	"VK_OEM_FJ_ROYA",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"LSHIFT",
	"RSHIFT",
	"LCONTROL",
	"RCONTROL",
	"LMENU",
	"RMENU"
};

namespace ImGui {
	bool Hotkey(const char* label, int* k, const ImVec2& size_arg) {
		ImGuiWindow* window = ImGui::GetCurrentWindow();
		if (window->SkipItems)
			return false;

		ImGuiContext& g = *GImGui;
		ImGuiIO& io = g.IO;
		const ImGuiStyle& style = g.Style;

		const ImGuiID id = window->GetID(label);
		const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);
		ImVec2 size = ImGui::CalcItemSize(size_arg, ImGui::CalcItemWidth(), label_size.y + style.FramePadding.y * 2.0f);

		//const ImRect frame_bb(window->DC.CursorPos + ImVec2(label_size.x + style.ItemInnerSpacing.x, 0.0f), window->DC.CursorPos + size);
		const ImRect frame_bb(window->DC.CursorPos + ImVec2(0.0f, 0.0f), window->DC.CursorPos + size);
		const ImRect frame_bb_border(window->DC.CursorPos + ImVec2(10, 10), window->DC.CursorPos + size);

		const ImRect total_bb(window->DC.CursorPos, frame_bb.Max);

		ImGui::ItemSize(total_bb, style.FramePadding.y);
		if (!ImGui::ItemAdd(total_bb, id))
			return false;

		const bool focus_requested = ImGui::FocusableItemRegister(window, g.ActiveId == id);

		const bool hovered = ImGui::ItemHoverable(frame_bb, id);

		if (hovered) {
			ImGui::SetHoveredID(id);
			g.MouseCursor = ImGuiMouseCursor_TextInput;
		}

		const bool user_clicked = hovered && io.MouseClicked[0];

		if (focus_requested || user_clicked) {
			if (g.ActiveId != id) {
				// Start edition
				memset(io.MouseDown, 0, sizeof(io.MouseDown));
				memset(io.KeysDown, 0, sizeof(io.KeysDown));
				*k = 0;
			}
			ImGui::SetActiveID(id, window);
			ImGui::FocusWindow(window);
		}
		else if (io.MouseClicked[0]) {
			// Release focus when we click outside
			if (g.ActiveId == id)
				ImGui::ClearActiveID();
		}

		bool value_changed = false;
		int key = *k;

		if (g.ActiveId == id) {
			for (auto i = 0; i < 5; i++) {
				if (io.MouseDown[i]) {
					switch (i) {
					case 0:
						key = VK_LBUTTON;
						break;
					case 1:
						key = VK_RBUTTON;
						break;
					case 2:
						key = VK_MBUTTON;
						break;
					case 3:
						key = VK_XBUTTON1;
						break;
					case 4:
						key = VK_XBUTTON2;
						break;
					}
					value_changed = true;
					ImGui::ClearActiveID();
				}
			}
			if (!value_changed) {
				for (auto i = VK_BACK; i <= VK_RMENU; i++) {
					if (io.KeysDown[i]) {
						key = i;
						value_changed = true;
						ImGui::ClearActiveID();
					}
				}
			}

			if (IsKeyPressedMap(ImGuiKey_Escape)) {
				*k = 0;
				ImGui::ClearActiveID();
			}
			else {
				*k = key;
			}
		}

		// Render
		// Select which buffer we are going to display. When ImGuiInputTextFlags_NoLiveEdit is Set 'buf' might still be the old value. We Set buf to NULL to prevent accidental usage from now on.

		char buf_display[64] = " .. ";

		ImGui::RenderFrame(frame_bb.Min, frame_bb.Max, ImGui::GetColorU32(ImVec4(0.20f, 0.25f, 0.30f, 1.0f)), true, style.FrameRounding);
		const auto colA = ImGui::GetColorU32(ImGui::GetStyleColorVec4(ImGuiCol_Button));
		const auto colB = ImGui::GetColorU32(ImGui::GetStyleColorVec4(ImGuiCol_ButtonHovered));


		window->DrawList->AddRectFilledMultiColor(frame_bb.Min, frame_bb.Max, colA, colA, colB, colB);
		const auto colBorder = ImGui::GetColorU32(ImGui::GetStyleColorVec4(ImGuiCol_Border));
		window->DrawList->AddRect(frame_bb.Min, frame_bb.Max, colBorder, 0.f, 15, 0);
		window->DrawList->AddRect(frame_bb.Min, frame_bb.Max, colBorder, 0.f, 15, 1.1f);


		if (*k != 0 && g.ActiveId != id) {
			strcpy_s(buf_display, KeyNames[*k]);
		}
		else if (g.ActiveId == id) {
			strcpy_s(buf_display, " [] ");
		}

		const ImRect clip_rect(frame_bb.Min.x, frame_bb.Min.y, frame_bb.Min.x + size.x, frame_bb.Min.y + size.y); // Not using frame_bb.Max because we have adjusted size
		ImVec2 render_pos = frame_bb.Min + style.FramePadding;
		ImGui::RenderTextClipped(frame_bb.Min + style.FramePadding, frame_bb.Max - style.FramePadding, buf_display, NULL, NULL, { 0.f, 0.4f }, &clip_rect);

		if (label_size.x > 0)
			// 	ImGui::RenderText(ImVec2(total_bb.Max.x + style.ItemInnerSpacing.x, frame_bb.Min.y + style.FramePadding.y), label);

			return value_changed;
	}

	bool BeginGroupBox(const char* label, const ImVec2& size) {
		bool ret = ImGui::BeginChild(label, size);
		if (ret) {
			ImGui::Indent(10.f);
			ImGui::SetCursorPosY(20.f);
		}

		return ret;
	}

	void EndGroupBox() {
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Unindent(10.f);

		auto drawList = ImGui::GetCurrentWindow()->DrawList;
		auto longLabel = ImGui::GetCurrentWindow()->Name;
		auto parsedLabel = Utils::SplitString(Utils::SplitString(longLabel, "/")[1], "_");
		auto label = parsedLabel[0].c_str();

		const auto pos = ImGui::GetWindowPos();
		const auto labelSize = ImGui::CalcTextSize(label);
		const auto min = pos + ImVec2(10.f, -(labelSize.y * 0.5f));
		const auto max = pos + labelSize + ImVec2(20.f, 0.f); // next extra x padding for some reason
		drawList->PushClipRect(min, max, false);
		drawList->AddText(min, ImColor(255, 255, 255), label);
		drawList->PopClipRect();

		ImGui::EndChild();
	}

	bool BetterCombo(const char* label, const char* preview_text, int* current_item, const char* const items[], int items_count) {

		ImGuiContext& g = *GImGui;
		const float word_building_delay = .5f; // after this many seconds, typing will make a new search

		preview_text = items[*current_item];

		// this is actually shared between all combos. It's kinda ok because there is
		// only one combo open at any given time, however it causes a problem where
		// if you open combo -> keyboard select (but no enter) and close, the 
		// keyboard_selected will stay as-is when re-opening the combo, or even others.
		static int keyboard_selected = -1;


		if (!BeginCombo(label, preview_text)) {
			if (ImGui::IsItemHovered()) {
				if (ImGui::IsKeyPressed(VK_UP))
					(*current_item)--;
				else if (ImGui::IsKeyPressed(VK_DOWN))
					(*current_item)++;

				if (*current_item < 0)
					*current_item = items_count - 1;
				else if (*current_item > items_count - 1)
					*current_item = 0;
			}

			return false;
		}

		GetIO().WantTextInput = true;
		static char word[64] = "";
		static float time_since_last_update = 0.0f;
		time_since_last_update += g.IO.DeltaTime;
		bool update_keyboard_match = false;
		for (int n = 0; n < g.IO.InputQueueCharacters.size() && g.IO.InputQueueCharacters[n]; n++) {
			if (unsigned int c = (unsigned int)g.IO.InputQueueCharacters[n]) {
				if (c == ' '
					|| (c >= '0' && c <= '9')
					|| (c >= 'A' && c <= 'Z')
					|| (c >= 'a' && c <= 'z')) {

					// build temporary word
					if (time_since_last_update < word_building_delay) { // append
						const size_t i = strnlen(word, 64);
						if (i + 1 < 64) {
							word[i] = static_cast<char>(c);
							word[i + 1] = '\0';
						}
					}
					else { // reset
						word[0] = static_cast<char>(c);
						word[1] = '\0';
					}
					time_since_last_update = 0.0f;
					update_keyboard_match = true;
				}
			}
		}

		// find best keyboard match
		int best = -1;
		bool keyboard_selected_now = false;
		if (update_keyboard_match) {
			for (int i = 0; i < items_count; ++i) {
				const char* item_text;
				item_text = items[i];

				int j = 0;
				while (word[j] && item_text[j] && tolower(item_text[j]) == tolower(word[j])) {
					++j;
				}
				if (best < j) {
					best = j;
					keyboard_selected = i;
					keyboard_selected_now = true;
				}
			}
		}

		if (IsKeyPressed(VK_RETURN) && keyboard_selected >= 0) {
			*current_item = keyboard_selected;
			keyboard_selected = -1;
			CloseCurrentPopup();
			EndCombo();
			return true;
		}
		if (IsKeyPressed(VK_UP) && keyboard_selected > 0) {
			--keyboard_selected;
			keyboard_selected_now = true;
		}
		if (IsKeyPressed(VK_DOWN) && keyboard_selected < items_count - 1) {
			++keyboard_selected;
			keyboard_selected_now = true;
		}

		// Display items
		bool value_changed = false;
		for (int i = 0; i < items_count; i++) {
			PushID((void*)(intptr_t)i);
			const bool item_selected = (i == *current_item);
			const bool item_keyboard_selected = (i == keyboard_selected);
			const char* item_text;
			item_text = items[i];

			if (Selectable(item_text, item_selected || item_keyboard_selected)) {
				value_changed = true;
				*current_item = i;
				keyboard_selected = -1;
			}
			if (item_selected && IsWindowAppearing()) {
				SetScrollHereY();
			}
			if (item_keyboard_selected && keyboard_selected_now) {
				SetScrollHereY();
			}
			PopID();
		}
		EndCombo();
		return value_changed;
	}
}