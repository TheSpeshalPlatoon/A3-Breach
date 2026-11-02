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

	class HandGrenade;
	class rhs_mag_plamyam: HandGrenade {displayNameShort = "Plamya-M"; ammo = "rhs_ammo_plamyam"; flashbang = "sleep 2; [_this#0, _this#1] spawn tsp_fnc_flashbang";}; 
	class rhs_mag_zarya2: HandGrenade {displayNameShort = "Zarya-2"; ammo = "rhs_ammo_zarya2"; flashbang = "sleep 2; [_this#0, _this#1] spawn tsp_fnc_flashbang";}; 
};
class CfgAmmo {
    class SmokeShell;
    class rhs_ammo_plamyam: SmokeShell {model = "\rhsafrf\addons\rhs_weapons\grenades\throw\acc_plamyaM"; explosionTime = 2.3; timeToLive = 60; grenadeFireSound[] = {}; grenadeBurningSound[] = {}; aiAmmoUsageFlags = "64"; effectsSmoke = "";};
    class rhs_ammo_zarya2: rhs_ammo_plamyam {model = "\rhsafrf\addons\rhs_weapons\grenades\throw\acc_zarya";};
};