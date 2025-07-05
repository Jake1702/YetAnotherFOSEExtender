#include "patches.h"
#include <unordered_map>
#include "havok.h"
#include "SafeWrite.h"
#include "GameSettings.h"

const char* GetPackageTypeName(char type) {
	switch (type) {
	case 0:
		return "Explore";
	case 1:
		return "Follow";
	case 2:
		return "Escort";
	case 3:
		return "Eat";
	case 4:
		return "Sleep";
	case 5:
		return "Wander";
	case 6:
		return "Travel";
	case 7:
		return "Accompany";
	case 8:
		return "Use Item At";
	case 9:
		return "Ambush";
	case 10:
		return "Flee Not Combat";
	case 11:
		return "Cast Magic";
	case 12:
		return "Sandbox";
	case 13:
		return "Patrol";
	case 14:
		return "Guard";
	case 15:
		return "Dialogue";
	case 16:
		return "Use Weapon";
	case 18:
		return "Combat";
	case 19:
		return "Combat Low";
	case 20:
		return "Activate";
	case 21:
		return "Alarm";
	case 22:
		return "Flee";
	case 23:
		return "Trespass";
	case 24:
		return "Spectator";
	case 25:
		return "React To Dead";
	case 26:
		return "Get Up";
	case 27:
		return "Do Nothing";
	case 28:
		return "In-Game Dialogue";
	case 29:
		return "Surface";
	case 30:
		return "Search For Attacker";
	case 31:
		return "Avoid Radiation";
	default:
		return "";
	}
	return "";
}

void WriteEditorPatches()
{
	SafeWriteBuf(0xD4A838, "GetYAFEVersion\0", 22);
}
