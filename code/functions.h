#pragma once
#include "CommandTable.h"
#include "ParamInfos.h"
#include "GameForms.h"
#include "GameObjects.h"

DEFINE_CMD_ALT_COND_PLUGIN(GetYAFEVersion, , , 0, NULL);
DEFINE_COMMAND_PLUGIN(GetValueAlt, 0, kParams_OneOptionalObjectID);
DEFINE_COMMAND_PLUGIN(SetValueAlt, 0, kParams_OneObjectID_OneInt);
DEFINE_COMMAND(GetBit, Gets a single bit specified by lsb-first index, 0, 2, kParams_TwoInts);
DEFINE_COMMAND(SetBit, Sets a single bit specified by lsb-first index, 0, 3, kParams_TwoInts_OneOptionalInt);
DEFINE_COMMAND(ClearBit, Clear a single bit specified by lsb-first index, 0, 2, kParams_TwoInts);