class CfgPatches {
	class tsp_breach_rhsgref {
		requiredAddons[] = {"rhsgref_main", "ace_explosives", "ace_compat_rhs_gref3_explosives"};
        skipWhenMissingDependencies = 1;
        weapons[] = {};
        units[] = {};
	};
};

class CfgMagazines {
	class DemoCharge_Remote_Mag;
	class rhs_charge_M2tet_x2_mag: DemoCharge_Remote_Mag {
		class ACE_Triggers {
			SupportedTriggers[] = {"Timer", "Command", "MK16_Transmitter", "DeadmanSwitch", "Shock30", "Shock15", "Shock5"};
			class Shock {FuseTime = 3;}; class ShockShort {FuseTime = 1;};
		};
	};
};