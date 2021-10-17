#pragma once
#include <Windows.h>
#include <string>
static std::string Expire;
class CAuth {
public:
	bool Login();

};
extern CAuth* Auth;