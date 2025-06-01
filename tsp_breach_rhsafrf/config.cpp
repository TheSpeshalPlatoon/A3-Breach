class CfgPatches {
	class tsp_breach_rhsafrf {
		requiredAddons[] = {"rhs_main", "ace_explosives", "ace_compat_rhs_afrf3_explosives"};
        skipWhenMissingDependencies = 1;
        weapons[] = {};
        units[] = {};
	};
};

class CfgMagazines {
	class ATMine_Range_Mag;
	class rhs_mine_ozm72_a_mag;
	class rhs_ec75_mag: ATMine_Range_Mag {
		class ACE_Triggers {
			SupportedTriggers[] = {"Timer", "Command", "MK16_Transmitter", "DeadmanSwitch", "Shock30", "Shock15", "Shock5"};
			class Shock {FuseTime = 3;}; class ShockShort {FuseTime = 1;};
		};
	};
	class rhs_mine_ozm72_c_mag: rhs_mine_ozm72_a_mag {
		class ACE_Triggers {
			SupportedTriggers[] = {"Command", "MK16_Transmitter", "Shock30", "Shock15", "Shock5"};
			class Shock {FuseTime = 3;}; class ShockShort {FuseTime = 1;};
		};
	};
};