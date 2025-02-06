class CfgPatches {
	class tsp_breach_rhssaf {
		requiredAddons[] = {"rhssaf_main", "ace_explosives", "ace_compat_rhs_saf3_explosives"};
        skipWhenMissingDependencies = 1;
        weapons[] = {};
        units[] = {};
	};
};

class CfgMagazines {
	class CA_Magazine;
	class rhssaf_mine_mrud_a_mag;
	class rhssaf_tm100_mag: CA_Magazine	{
		class ACE_Triggers {
			SupportedTriggers[] = {"Timer", "Command", "MK16_Transmitter", "DeadmanSwitch", "Shock", "ShockShort"};
			class Shock {FuseTime = 2;}; class ShockShort {FuseTime = 1;};
		};
	};
	class rhssaf_mine_mrud_d_mag: rhssaf_mine_mrud_a_mag {
		class ACE_Triggers {
			SupportedTriggers[] = {"Command", "MK16_Transmitter", "Shock", "ShockShort"};
			class Shock {FuseTime = 2;}; class ShockShort {FuseTime = 1;};
		};
	};
};