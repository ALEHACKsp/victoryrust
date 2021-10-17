#pragma once
#include <vector>
#include <Windows.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <iomanip>
#include <string>

class Scenes {
public:
	void Login();
	void Cheat();
};

inline std::unique_ptr<Scenes> m_Scenes;