#include "CommandTable.h"

bool Cmd_Default_Parse(UInt32 numParams, ParamInfo * paramInfo, ScriptLineBuffer * lineBuf, ScriptBuffer * scriptBuf)
{
	return g_defaultParseCommand(numParams, paramInfo, lineBuf, scriptBuf);
}

#if RUNTIME

static const Cmd_Parse g_defaultParseCommand = (Cmd_Parse)0x0051AF10;

#else

static const Cmd_Parse g_defaultParseCommand = (Cmd_Parse)0x005C01F0;

#endif