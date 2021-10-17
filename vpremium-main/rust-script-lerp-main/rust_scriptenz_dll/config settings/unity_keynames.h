#pragma once
#include "../pch/pch.h"

// translates unity key name to proper vkey
// ... yes i manually wrote this

static std::unordered_map<std::string, int> unity_key_to_vk = { 
{ "backspace", VK_BACK },
{ "delete", VK_DELETE },
{ "tab", VK_TAB },
{ "clear", VK_CLEAR },
{ "return", VK_RETURN },
{ "pause", VK_PAUSE },
{ "escape", VK_ESCAPE },
{ "space", VK_SPACE },
{ "keypad0", VK_NUMPAD0 },
{ "keypad1", VK_NUMPAD1 },
{ "keypad2", VK_NUMPAD2 },
{ "keypad3", VK_NUMPAD3 },
{ "keypad4", VK_NUMPAD4 },
{ "keypad5", VK_NUMPAD5 },
{ "keypad6", VK_NUMPAD6 },
{ "keypad7", VK_NUMPAD7 },
{ "keypad8", VK_NUMPAD8 },
{ "keypad9", VK_NUMPAD9 },
{ "uparrow", VK_UP },
{ "downarrow", VK_DOWN },
{ "rightarrow", VK_RIGHT },
{ "leftarrow", VK_LEFT },
{ "insert", VK_INSERT },
{ "home", VK_HOME },
{ "end", VK_END },
{ "pageup", VK_PRIOR },
{ "pagedown", VK_NEXT },
{ "f1", VK_F1 },
{ "f2", VK_F2 },
{ "f3", VK_F3 },
{ "f4", VK_F4 },
{ "f5", VK_F5 },
{ "f6", VK_F6 },
{ "f7", VK_F7 },
{ "f8", VK_F8 },
{ "f9", VK_F9 },
{ "f10", VK_F10 },
{ "f11", VK_F11 },
{ "f12", VK_F12 },
{ "f13", VK_F13 },
{ "f14", VK_F14 },
{ "f15", VK_F15 },
{ "quote", VK_OEM_7 },
{ "plus", VK_OEM_PLUS },
{ "comma", VK_OEM_COMMA },
{ "minus", VK_OEM_MINUS },
{ "period", VK_OEM_PERIOD },
{ "slash", VK_OEM_2 },
{ "colon", VK_OEM_1 },
{ "question", VK_OEM_2 },
{ "backslash", VK_OEM_5 },
{ "a", 'A' },
{ "b", 'B' },
{ "c", 'C' },
{ "d", 'D' },
{ "e", 'E' },
{ "f", 'F' },
{ "g", 'G' },
{ "h", 'H' },
{ "i", 'I' },
{ "j", 'J' },
{ "k", 'K' },
{ "l", 'L' },
{ "m", 'M' },
{ "n", 'N' },
{ "o", 'O' },
{ "p", 'P' },
{ "q", 'Q' },
{ "r", 'R' },
{ "s", 'S' },
{ "t", 'T' },
{ "u", 'U' },
{ "v", 'V' },
{ "w", 'W' },
{ "x", 'X' },
{ "y", 'Y' },
{ "z", 'Z' },
{ "pipe", VK_OEM_5 },
{ "tilde", 0 },
{ "numlock", VK_NUMLOCK },
{ "capslock", VK_CAPITAL },
{ "scrolllock", VK_SCROLL },
{ "rightshift", VK_RSHIFT },
{ "leftshift", VK_LSHIFT },
{ "rightcontrol", VK_RCONTROL },
{ "leftcontrol", VK_LCONTROL },
{ "rightalt", VK_RMENU },
{ "leftalt", VK_LMENU },
{ "altgr", 0 },
{ "help", VK_HELP },
{ "print", VK_PRINT },
{ "break", VK_CANCEL },
{ "mouse0", VK_LBUTTON },
{ "mouse1", VK_RBUTTON },
{ "mouse2", VK_MBUTTON },
{ "mouse3", VK_XBUTTON1 },
{ "mouse4", VK_XBUTTON2 }, };