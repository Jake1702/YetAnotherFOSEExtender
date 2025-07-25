#pragma once

/**** base opcodes
 *	
 *	10	begin
 *	11	end
 *	12	short		int
 *	13	long
 *	14	float
 *	15	set
 *	16	if
 *	17	else
 *	18	elseif
 *	19	endif
 *	1A	while_DEPRECATED
 *	1B	endwhile_DEPRECATED
 *	1C	.			(dot operator)
 *	1D	scriptname	scn
 *	1E	return
 *	1F	reference	ref
 *	
 ***/

class TESObjectREFR;
class Script;
struct ScriptEventList;
struct ScriptLineBuffer;
struct ScriptBuffer;
struct PluginInfo;

enum ParamType
{
	kParamType_String =					0x00,
	kParamType_Integer =				0x01,
	kParamType_Float =					0x02,
	kParamType_ObjectID =		0x03,	// GetItemCount				TESForm *, must pass IsInventoryObjectType check
	kParamType_ObjectRef =				0x04,	// Activate					TESObjectREFR *
	kParamType_ActorValue =				0x05,	// ModActorValue			not in switch
	kParamType_Actor =					0x06,	// ToggleAI					TESObjectREFR *, must pass IsActor
	kParamType_SpellItem =				0x07,	// AddSpell					TESForm *, must be either SpellItem or book
	kParamType_Axis =					0x08,	// Rotate					not in switch (X Y Z, passed as char)
	kParamType_Cell =					0x09,	// GetInCell				TESObjectCELL *, must pass sub_4C0780
	kParamType_AnimationGroup =			0x0A,	// PlayGroup				not in switch
	kParamType_MagicItem =				0x0B,	// Cast						MagicItem *
	kParamType_Sound =					0x0C,	// Sound					TESForm *, kFormType_Sound
	kParamType_Topic =					0x0D,	// Say						TESForm *, kFormType_Dialog
	kParamType_Quest =					0x0E,	// ShowQuestVars			TESForm *, kFormType_Quest
	kParamType_Race =					0x0F,	// GetIsRace				TESForm *, kFormType_Race
	kParamType_Class =					0x10,	// GetIsClass				TESForm *, kFormType_Class
	kParamType_Faction =				0x11,	// Faction					TESForm *, kFormType_Faction
	kParamType_Sex =					0x12,	// GetIsSex					not in switch
	kParamType_Global =					0x13,	// GetGlobalValue			TESForm *, kFormType_Global
	kParamType_Furniture =				0x14,	// IsCurrentFurnitureObj	TESForm *, kFormType_Furniture
	kParamType_TESObject =				0x15,	// PlaceAtMe				TESObject *
	kParamType_VariableName =			0x16,	// GetQuestVariable			not in switch
	kParamType_QuestStage =				0x17,	// SetStage					handled like integer
	kParamType_MapMarker =				0x18,	// ShowMap					TESObjectREFR *, base form must be dword_AF36F8
	kParamType_ActorBase =				0x19,	// SetEssential				TESActorBase *
	kParamType_Container =				0x1A,	// RemoveMe					TESObjectREFR *, must pass TESObjectREFR_GetContainer
	kParamType_WorldSpace =				0x1B,	// CenterOnWorld			TESWorldSpace *
	kParamType_CrimeType =				0x1C,	// GetCrimeKnown			not in switch
	kParamType_AIPackage =				0x1D,	// GetIsCurrentPackage		TESPackage *
	kParamType_CombatStyle =			0x1E,	// SetCombatStyle			TESCombatStyle *
	kParamType_MagicEffect =			0x1F,	// HasMagicEffect			EffectSetting *
	kParamType_FormType =				0x20,	// GetIsUsedItemType		FormType (not all types supported)
	kParamType_WeatherID =				0x21,	// GetIsCurrentWeather		TESForm *, kFormType_Weather
	kParamType_NPC =					0x22,	// unused
	kParamType_Owner =					0x23,	// IsOwner					TESForm *, kFormType_NPC or kFormType_Faction
	kParamType_EffectShader =			0x24,	// PlayMagicShaderVisuals		TESForm *, kFormType_EffectShader
	kParamType_FormList	=				0x25,	// IsInList
	kParamType_MenuIcon =				0x26,	// unused
	kParamType_Perk =					0x27,	// Add Perk	
	kParamType_Note =					0x28,	// Add Note
	kParamType_Double =					0x2C,	// 
	kParamType_MiscellaneousStat =		0x29,	// ModPCMiscStat
	kParamType_IdleForm =				0x30,	// IsLastIdlePlayed
	kParamType_Message =				0x31,	// ShowTutorialMenu
	kParamType_InvObjOrFormList =		0x32,	// AddItem
	kParamType_Alignment =				0x33,	// GetIsAlignment
	kParamType_EquipType =				0x34,	// GetIsUsedEquipType
	kParamType_NonInvObjOrFormList =	0x35,	// GetIsUsedItem
	kParamType_Music =					0x36,	// PlayMusic
	kParamType_CriticalStage =			0x37,	// SetCriticalStage

	// added for dlc (1.1)
	kParamType_LeveledOrBaseChar =		0x38,	// AddNPCToLeveledList
	kParamType_LeveledOrBaseCreature =	0x39,	// AddCreatureToLeveledList
	kParamType_LeveledChar =			0x3A,	// AddNPCToLeveledList
	kParamType_LeveledCreature =		0x3B,	// AddCreatureToLeveledList
	kParamType_LeveledItem =			0x3C,	// AddItemToLeveledList
	kParamType_AnyForm =				0x3D,	// AddFormToFormList
};


enum CommandReturnType : UInt8
{
	kRetnType_Default,
	kRetnType_Form,
	kRetnType_String,

	kRetnType_Max
};

struct ParamInfo
{
	const char	* typeStr;
	UInt32		typeID;		// ParamType
	UInt32		isOptional;	// do other bits do things?
};

#define COMMAND_ARGS		ParamInfo * paramInfo, UInt8* scriptData, TESObjectREFR* thisObj, TESObjectREFR* containingObj, Script* scriptObj, ScriptEventList* eventList, double * result, UInt32 * opcodeOffsetPtr
#define PASS_COMMAND_ARGS	paramInfo, scriptData, thisObj, containingObj, scriptObj, eventList, result, opcodeOffsetPtr
#define EXTRACT_ARGS		paramInfo, scriptData, opcodeOffsetPtr, thisObj, containingObj, scriptObj, eventList
//args passed to EVAL version of command (arg1 and arg2 types vary based on ParamInfo)
#define COMMAND_ARGS_EVAL	TESObjectREFR * thisObj, void * arg1, void * arg2, double * result
#define PASS_CMD_ARGS_EVAL	thisObj, arg1, arg2, result
#define EXTRACT_ARGS_EX		paramInfo, scriptData, opcodeOffsetPtr, scriptObj, eventList
#define PASS_FMTSTR_ARGS	paramInfo, scriptData, opcodeOffsetPtr, scriptObj, eventList

//Macro to make CommandInfo definitions a bit less tedious

#define DEFINE_CMD_FULL(name, altName, description, refRequired, numParams, paramInfo, parser) \
	extern bool Cmd_ ## name ## _Execute(COMMAND_ARGS); \
	static CommandInfo (kCommandInfo_ ## name) = { \
	#name, \
	#altName, \
	0, \
	#description, \
	refRequired, \
	numParams, \
	paramInfo, \
	HANDLER(Cmd_ ## name ## _Execute), \
	parser, \
	NULL, \
	0 \
	};

#define DEFINE_CMD_ALT(name, altName, description, refRequired, numParams, paramInfo) \
	DEFINE_CMD_FULL(name, altName, description, refRequired, numParams, paramInfo, Cmd_Default_Parse)	

#define DEFINE_CMD_ALT_EXP(name, altName, description, refRequired, paramInfo) \
	DEFINE_CMD_FULL(name, altName, description, refRequired, (sizeof(paramInfo) / sizeof(ParamInfo)), paramInfo, Cmd_Expression_Parse)	

#define DEFINE_COMMAND(name, description, refRequired, numParams, paramInfo) \
	DEFINE_CMD_FULL(name, , description, refRequired, numParams, paramInfo, Cmd_Default_Parse)	

#define DEFINE_CMD(name, description, refRequired, paramInfo) \
	DEFINE_COMMAND(name, description, refRequired, (sizeof(paramInfo) / sizeof(ParamInfo)), paramInfo)

#define DEFINE_COMMAND_EXP(name, description, refRequired, paramInfo) \
	DEFINE_CMD_ALT_EXP(name, , description, refRequired, paramInfo)	

#define DEFINE_COMMAND_ALT_PLUGIN(name, altName, description, refRequired, numParams, paramInfo) \
	DEFINE_CMD_FULL(name, altName, description, refRequired, numParams, paramInfo, NULL)

// for commands which can be used as conditionals
#define DEFINE_CMD_ALT_COND_ANY(name, altName, description, refRequired, paramInfo, parser) \
	extern bool Cmd_ ## name ## _Execute(COMMAND_ARGS); \
	extern bool Cmd_ ## name ## _Eval(COMMAND_ARGS_EVAL); \
	static CommandInfo (kCommandInfo_ ## name) = { \
	#name,	\
	#altName,		\
	0,		\
	#description,	\
	refRequired,	\
	(sizeof(paramInfo) / sizeof(ParamInfo)),	\
	paramInfo,	\
	HANDLER(Cmd_ ## name ## _Execute),	\
	parser,	\
	HANDLER_EVAL(Cmd_ ## name ## _Eval),	\
	1	\
	};

#define DEFINE_CMD_ALT_COND(name, altName, description, refRequired, paramInfo) \
	DEFINE_CMD_ALT_COND_ANY(name, altName, description, refRequired, paramInfo, Cmd_Default_Parse)

#define DEFINE_CMD_ALT_COND_PLUGIN(name, altName, description, refRequired, paramInfo) \
	DEFINE_CMD_ALT_COND_ANY(name, altName, description, refRequired, paramInfo, NULL)

#define DEFINE_CMD_COND(name, description, refRequired, paramInfo) \
	DEFINE_CMD_ALT_COND(name, , description, refRequired, paramInfo)


#define DEFINE_COMMAND_PLUGIN(name, refRequired, paramInfo) \
	extern bool Cmd_##name##_Execute(COMMAND_ARGS); \
	static CommandInfo kCommandInfo_##name = { \
	#name, \
	nullptr, \
	0, \
	nullptr, \
	refRequired, \
	sizeof(paramInfo) / sizeof(ParamInfo), \
	paramInfo, \
	Cmd_##name##_Execute, \
	nullptr, \
	nullptr, \
	0 \
	};
typedef bool (* Cmd_Execute)(COMMAND_ARGS);
bool Cmd_Default_Execute(COMMAND_ARGS);

typedef bool (* Cmd_Parse)(UInt32 numParams, ParamInfo * paramInfo, ScriptLineBuffer * lineBuf, ScriptBuffer * scriptBuf);
bool Cmd_Default_Parse(UInt32 numParams, ParamInfo * paramInfo, ScriptLineBuffer * lineBuf, ScriptBuffer * scriptBuf);

typedef bool (* Cmd_Eval)(COMMAND_ARGS_EVAL);
bool Cmd_Default_Eval(COMMAND_ARGS_EVAL);

#ifdef RUNTIME
#define HANDLER(x)	x
#define HANDLER_EVAL(x)	x
#else
#define HANDLER(x)	Cmd_Default_Execute
#define HANDLER_EVAL(x)	Cmd_Default_Eval
#endif

// unk3 args:
// TESObjectREFR * thisObj
// TESForm * param
// TESForm * param2
// double * result

struct CommandInfo
{
	const char	* longName;		// 00
	const char	* shortName;	// 04
	UInt32		opcode;			// 08
	const char	* helpText;		// 0C
	UInt16		needsParent;	// 10
	UInt16		numParams;		// 12
	ParamInfo	* params;		// 14

	// handlers
	Cmd_Execute	execute;		// 18
	Cmd_Parse	parse;			// 1C
	Cmd_Eval	eval;			// 20 - smaller version of Cmd_Execute with arg extracted already, used for dialog condition evaluation

	UInt32		flags;			// 24
	
	void	DumpFunctionDef() const;
	void	DumpDocs() const;
};

const UInt32 kFoseOpCodeStart	= 0x1400;
const UInt32 kFoseOpCodeTest	= 0x2000;

struct CommandMetadata
{
	CommandMetadata() :parentPlugin(kFoseOpCodeStart), returnType(kRetnType_Default) { }

	UInt32				parentPlugin;
	CommandReturnType	returnType;
};

extern const Cmd_Parse g_defaultParseCommand;