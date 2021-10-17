#pragma once 

#include <Windows.h>
#include <iostream>
#include <cstdint>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <chrono>
#include <unordered_map>
#include <thread>
#include <array>
#include <functional>
#include <fstream>
#include <filesystem>
#include <ShlObj.h>


#include "../vec2/vec2.h"

#ifndef _DEBUG
#define DEVMSG(...) printf(__VA_ARGS__)
#else
#define DEVMSG(...)
#endif

#undef Callback

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include <d3d9.h>
#include <d3dx9tex.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#include <imgui.h>
#include <imgui_impl_dx9.h>
#include <imgui_impl_win32.h>

using Callback = std::function<void()>;

#include "../utils/utils.hpp"
