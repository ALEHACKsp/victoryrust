#pragma once
#include <string>

class program
{
public:
	static std::tuple<std::string, std::string, std::string> login(std::string key, std::string userid, std::string pid, std::string programname, std::string skey);



};