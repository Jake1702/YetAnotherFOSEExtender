#include "functions.h"
#include <string>
#include <unordered_map>
#include "CommandTable.h"
#include "GameAPI.h"
#include "GameEffects.h"
#include "GameObjects.h"
#include "GameRTTI.h"
#include "GameExtraData.h"
#include "SafeWrite.h"
#include "GameMenus.h"

extern int g_version;

extern char* s_strArgBuffer;
extern char* s_strValBuffer;

extern std::unordered_map<UInt32, char*> markerIconMap;

extern CommandInfo* cmd_IsKeyPressed;

extern TESClimate* s_forcedClimate;

static bool timePatched = false;

const UInt32 kMsgIconsPathAddr[] = { 0xDC0C38, 0xDC0C78, 0xDC5544, 0xDCE658, 0xDD9148, 0xDE3790, 0xDF3278 };

TESObjectREFR* s_tempPosMarker;

bool Cmd_GetYAFEVersion_Execute(COMMAND_ARGS) {
	*result = g_version;
	if (IsConsoleMode()) {
		Console_Print("GetYAFEVersion >> %.f", *result);
	}
	return true;
}

bool Cmd_GetYAFEVersion_Eval(COMMAND_ARGS_EVAL) {
	*result = g_version;
	return true;
}

bool Cmd_GetValueAlt_Execute(COMMAND_ARGS) {
	TESForm* form = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &form) && (form || (thisObj && (form = thisObj->baseForm) && kInventoryType[form->typeID])))
		*result = (int)form->GetItemValue();
	return true;
}

bool Cmd_SetValueAlt_Execute(COMMAND_ARGS)
{
	TESForm *form;
	UInt32 newVal;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &form, &newVal))
		if (TESValueForm *valForm = DYNAMIC_CAST(form, TESForm, TESValueForm))
		{
			valForm->value = newVal;
			//form->MarkModified(2);
		}
		else if IS_ID(form, AlchemyItem)
			((AlchemyItem*)form)->value = newVal;
	return true;
}

bool Cmd_GetBit_Execute(COMMAND_ARGS)
{
	*result = 0;

	UInt32	data = 0;
	UInt32	idx = 0;

	if(!ExtractArgs(EXTRACT_ARGS, &data, &idx))
		return true;

	*result = (data & (1 << idx)) >> idx;

	return true;
}

bool Cmd_SetBit_Execute(COMMAND_ARGS)
{
	*result = 0;

	UInt32	data = 0;
	UInt32	idx = 0;
	UInt32	doSet = 1;	// default value

	if(!ExtractArgs(EXTRACT_ARGS, &data, &idx, &doSet))
		return true;

	if(doSet)
		data |= (1 << idx);
	else
		data &= ~(1 << idx);

	*result = data;

	return true;
}

bool Cmd_ClearBit_Execute(COMMAND_ARGS)
{
	*result = 0;

	UInt32	data = 0;
	UInt32	idx = 0;

	if(!ExtractArgs(EXTRACT_ARGS, &data, &idx))
		return true;

	data &= ~(1 << idx);

	*result = data;

	return true;
}