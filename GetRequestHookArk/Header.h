#define _CRT_SECURE_NO_WARNINGS

#pragma once

#include <API/Ark/Ark.h>
#include <string>
#include <nlohmann/json.hpp>
#include <iostream>
#include <fstream>

std::string PluginName = "GetRequestHookArk";

using json = nlohmann::json;
json config = nullptr;
std::wstring DllPath() {
	TCHAR buffer[MAX_PATH] = { 0 };
	GetModuleFileName(NULL, buffer, MAX_PATH);
	std::wstring::size_type pos = std::wstring(buffer).find_last_of(L"\\/");
	auto startPath = std::wstring(buffer).substr(0, pos);
	return startPath + fmt::format(L"\\ArkApi\\Plugins\\{}\\", PluginName);
}

void loadConfig() {
	try {
		std::ifstream file(FString(DllPath()).ToString() + "config.json");
		file >> config;
	}
	catch (std::exception& e) {
		Log::GetLog()->info("Error loading config: {}", e.what());
	}
}