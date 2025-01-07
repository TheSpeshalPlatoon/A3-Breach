class CfgPatches {
	class tsp_breach_cup {
		requiredAddons[] = {"rhsusf_main", "ace_compat_cup_weapons_explosives"};
        skipWhenMissingDependencies = 1;
        weapons[] = {};
        units[] = {};
	};
};

class CfgMagazines {
	class CUP_TimeBomb_M;
	class CUP_Mine_M;
	class CUP_PipeBomb_M: CUP_TimeBomb_M {
		class ACE_Triggers {
			SupportedTriggers[] = {"Timer", "Command", "MK16_Transmitter", "DeadmanSwitch", "Cellphone", "Shock", "ShockShort"};
			class Shock {FuseTime = 2;}; class ShockShort {FuseTime = 1;};
		};
	};
	class CUP_IED_V1_M: CUP_Mine_M {
		class ACE_Triggers {
			SupportedTriggers[] = {"Timer", "Cellphone", "PressurePlate", "Command", "MK16_Transmitter", "DeadmanSwitch", "Shock", "ShockShort"};
			class Shock {FuseTime = 2;}; class ShockShort {FuseTime = 1;};
		};
	};
	class CUP_IED_V3_M: CUP_IED_V1_M {
		class ACE_Triggers {
			SupportedTriggers[] = {"Timer", "Cellphone", "PressurePlate", "Command", "MK16_Transmitter", "DeadmanSwitch", "Shock", "ShockShort"};
			class Shock {FuseTime = 2;}; class ShockShort {FuseTime = 1;};
		};
	};
	class CUP_IED_V4_M: CUP_IED_V1_M {
		class ACE_Triggers {
			SupportedTriggers[] = {"Timer", "Cellphone", "PressurePlate", "Command", "MK16_Transmitter", "DeadmanSwitch", "Shock", "ShockShort"};
			class Shock {FuseTime = 2;}; class ShockShort {FuseTime = 1;};
		};
	};
};