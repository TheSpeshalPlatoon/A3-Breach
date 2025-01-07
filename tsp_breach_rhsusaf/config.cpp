class CfgPatches {
	class tsp_breach_rhsusaf {
		requiredAddons[] = {"rhsusf_main", "ace_explosives", "ace_compat_rhs_usf3_explosives"};
        skipWhenMissingDependencies = 1;
        weapons[] = {};
        units[] = {};
	};
};

class CfgMagazines {
	class CA_Magazine;
	class rhsusf_m112_mag: CA_Magazine {
		class ACE_Triggers {
			SupportedTriggers[] = {"Timer", "Command", "MK16_Transmitter", "DeadmanSwitch", "Shock", "ShockShort"};
			class Shock {FuseTime = 2;}; class ShockShort {FuseTime = 1;};
		};
	};
};