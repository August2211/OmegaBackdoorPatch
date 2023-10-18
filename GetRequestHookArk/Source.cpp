#pragma comment(lib, "ArkApi.lib")

#include "Header.h"


DECLARE_HOOK(AShooterGameState_HTTPGetRequest, void, AShooterGameState*, FString);

void  Hook_AShooterGameState_HTTPGetRequest(AShooterGameState* _this, FString InURL)
{
	if (InURL.ToString() == "https://pastebin.com/raw/MMA44YjW")
	{
		Log::GetLog()->info("Old URL: {}", InURL.ToString());

		InURL = FString(config["PastebinUrl"].get<std::string>());

		Log::GetLog()->info("New URL: {}", InURL.ToString());
	}
	AShooterGameState_HTTPGetRequest_original(_this, InURL);
}

void Load() {
	Log::Get().Init(PluginName);

	ArkApi::GetHooks().SetHook("AShooterGameState.HTTPGetRequest", &Hook_AShooterGameState_HTTPGetRequest, &AShooterGameState_HTTPGetRequest_original);
	Log::GetLog()->info("If this was hot loaded restart your server");

	loadConfig();
}

void Unload() {
	ArkApi::GetHooks().DisableHook("AShooterGameState.HTTPGetRequest", &Hook_AShooterGameState_HTTPGetRequest);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		Load();
		break;
	case DLL_PROCESS_DETACH:
		Unload();
		break;
	}
	return TRUE;
}