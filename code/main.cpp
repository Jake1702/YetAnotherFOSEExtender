#include "PluginAPI.h"
#include "CommandTable.h"
#include "main.h"
#include "functions.h"
#include "patches.h"
#include "fose_version.h"

#define REG_CMD(name) fose->RegisterCommand(&kCommandInfo_##name)

IDebugLog		g_log("YetAnotherFOSEExtender.log");

PluginHandle	g_pluginHandle = kPluginHandle_Invalid;

int g_version = 69;

char* s_strArgBuffer;
char* s_strValBuffer;

CommandInfo* cmd_IsKeyPressed = nullptr;
FOSECommandTableInterface* cmdTableInterface = nullptr;

extern "C" {

bool FOSEPlugin_Query(const FOSEInterface * fose, PluginInfo * info)
{

	info->infoVersion = PluginInfo::kInfoVersion;
	info->name = "Yet Another FOSE Extender";
	info->version = g_version;
	// version checks
	if (fose->isNogore)
	{
		_ERROR("German No-Gore version is not supported");
		return false;
	}
	if(fose->foseVersion < 0x1030020)
	{
		MessageBoxA(nullptr, "Yet Another FOSE Extender requires FOSE version v1.3b2.\n\nInstalled version is too old.", "Yet Another FOSE Extender", 0);
		_ERROR("FOSE 1.3b2 is required for Yet Another FOSE Extender. Your version is %08X", fose->foseVersion);
		return false;
	}

	if(!fose->isEditor && fose->runtimeVersion != FALLOUT_VERSION_1_7)
	{
		_ERROR("incorrect runtime version (got %08X need %08X)", fose->runtimeVersion, FALLOUT_VERSION_1_7);
		return false;
	}

	
	return true;
}


bool FOSEPlugin_Load(const FOSEInterface * fose)
{
	fose->SetOpcodeBase(0x3800);
	g_pluginHandle = fose->GetPluginHandle();
	REG_CMD(GetYAFEVersion);
	REG_CMD(GetValueAlt);
	REG_CMD(SetValueAlt);
	REG_CMD(GetBit);
	REG_CMD(SetBit);
	REG_CMD(ClearBit);
	s_strArgBuffer = (char*)malloc(0x4000);
	s_strValBuffer = (char*)malloc(0x10000);


	cmdTableInterface = (FOSECommandTableInterface*)fose->QueryInterface(kInterface_CommandTable);
	if (cmdTableInterface) {

		cmd_IsKeyPressed = cmdTableInterface->GetByOpcode(0x143A);
	}
	return true;
}

};
