#pragma once
#define _CRT_NONSTDC_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE 



#include <iostream>
#include <string>
#include <Windows.h>
#include "xor.h"
#include <random>
#include <direct.h>

#include <sstream>

#include "Bytes.h"
#include "bytetofile.hpp"
#include "xor.h"

template< typename ... Args >
std::string mixer(Args const& ... args)
{
	std::ostringstream stream;
	using List = int[];
	(void)List {
		0, ((void)(stream << args), 0) ...
	};
	return stream.str();
}
std::string random_string(std::string::size_type length)
{
	static auto& chrs = "0123456789"
		"abcdefghijklmnopqrstuvwxyz"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	thread_local static std::mt19937 rg{ std::random_device{}() };
	thread_local static std::uniform_int_distribution<std::string::size_type> pick(0, sizeof(chrs) - 2);

	std::string s;

	s.reserve(length);

	while (length--)
		s += chrs[pick(rg)];

	return s;
}
inline bool FileExists(const std::string& name) {
	struct stat buffer;
	return (stat(name.c_str(), &buffer) == 0);
}



void DriverLoadIntel() {
	//std::string finalPath = mixer(getenv("localappdata"), _xor_("\\"), random_string(32));
	std::string finalPath = mixer("C:\\Windows\\Temp", _xor_("\\"), random_string(32));
	// Create random string folder
	_mkdir(finalPath.c_str());

	if (FileExists(finalPath)) {

		// Create mapper.exe
		std::string mapperRandomize = mixer(finalPath, _xor_("\\"), random_string(32), _xor_(".exe"));
		utils::CreateFileFromMemory(mapperRandomize, reinterpret_cast<const char*>(KdMapper), sizeof(KdMapper));
		// Create driver.sys
		std::string driverRandomize = mixer(finalPath, _xor_("\\"), random_string(32), _xor_(".sys"));
		utils::CreateFileFromMemory(driverRandomize, reinterpret_cast<const char*>(driversys), sizeof(driversys));

		// Checking created files
		if (FileExists(mapperRandomize)) {
			if (FileExists(driverRandomize)) {

				// Load driver
				std::string loadCommand = mixer(mapperRandomize, _xor_(" "), driverRandomize);
				system(loadCommand.c_str());

				// Delete gdrv,mapper,driver
				DeleteFile(mapperRandomize.c_str());

				DeleteFile(driverRandomize.c_str());
				DeleteFile(finalPath.c_str());

				DeleteFileW(LPCWSTR(mapperRandomize.c_str()));

				DeleteFileW(LPCWSTR(driverRandomize.c_str()));
				DeleteFileW(LPCWSTR(finalPath.c_str()));
			}
		}
	}
}

void DriverLoad() {
	//std::string finalPath = mixer(getenv("localappdata"), _xor_("\\"), random_string(32));
	std::string finalPath = mixer("C:\\Windows\\Temp", _xor_("\\"), random_string(32));
	// Create random string folder
	_mkdir(finalPath.c_str());

	if (FileExists(finalPath)) {
		// Create gdrv.sys
		std::string gdrvRandomize = mixer(finalPath, _xor_("\\"), random_string(32), _xor_(".sys"));
		utils::CreateFileFromMemory(gdrvRandomize, reinterpret_cast<const char*>(gdrvsys), sizeof(gdrvsys));
		// Create mapper.exe
		std::string mapperRandomize = mixer(finalPath, _xor_("\\"), random_string(32), _xor_(".exe"));
		utils::CreateFileFromMemory(mapperRandomize, reinterpret_cast<const char*>(mapper), sizeof(mapper));
		// Create driver.sys
		std::string driverRandomize = mixer(finalPath, _xor_("\\"), random_string(32), _xor_(".sys"));
		utils::CreateFileFromMemory(driverRandomize, reinterpret_cast<const char*>(driversys), sizeof(driversys));

		// Checking created files
		if (FileExists(gdrvRandomize)) {
			if (FileExists(mapperRandomize)) {
				if (FileExists(driverRandomize)) {

					// Load driver
					std::string loadCommand = mixer(mapperRandomize, _xor_(" "), gdrvRandomize, _xor_(" "), driverRandomize);
					system(loadCommand.c_str());

					// Delete gdrv,mapper,driver
					DeleteFile(mapperRandomize.c_str());
					DeleteFile(gdrvRandomize.c_str());
					DeleteFile(driverRandomize.c_str());
					DeleteFile(finalPath.c_str());

					DeleteFileW(LPCWSTR(mapperRandomize.c_str()));
					DeleteFileW(LPCWSTR(gdrvRandomize.c_str()));
					DeleteFileW(LPCWSTR(driverRandomize.c_str()));
					DeleteFileW(LPCWSTR(finalPath.c_str()));
				}
			}
		}
	}
}