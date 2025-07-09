#pragma once
#include "CommandTable.h"
#include "ParamInfos.h"
#include "GameForms.h"
#include "GameObjects.h"

DEFINE_CMD_ALT_COND_PLUGIN(GetYAFEVersion, , , 0, NULL);
DEFINE_COMMAND_PLUGIN(GetValueAlt, 0, kParams_OneOptionalObjectID);
DEFINE_COMMAND_PLUGIN(SetValueAlt, 0, kParams_OneObjectID_OneInt);