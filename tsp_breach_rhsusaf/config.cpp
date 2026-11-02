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
			SupportedTriggers[] = {"Timer", "Command", "MK16_Transmitter", "DeadmanSwitch", "Shock30", "Shock15", "Shock5"};
			class Shock {FuseTime = 3;}; class ShockShort {FuseTime = 1;};
		};
	};

	class HandGrenade;
	class rhs_mag_mk84: HandGrenade {displayNameShort = "MK-84"; ammo = "rhs_ammo_m84"; flashbang = "sleep 1.5; [_this#0, _this#1] spawn tsp_fnc_flashbang";}; 
};
class CfgAmmo {
    class SmokeShell;
    class rhs_ammo_m84: SmokeShell {model = "\rhsusf\addons\rhsusf_weapons\grenades_thrown\m84\m84_flash"; explosionTime = 2.3; timeToLive = 60; grenadeFireSound[] = {}; grenadeBurningSound[] = {}; aiAmmoUsageFlags = "64"; effectsSmoke = "";};
    class rhs_ammo_mk3a2: rhs_ammo_m84 {model = "\rhsusf\addons\rhsusf_weapons\grenades_thrown\mk3a2\mk3a2";};
    class rhs_grenade_mkiiia1_ammo: rhs_ammo_m84 {model = "\rhsgref\addons\rhsgref_weapons2\grenades\US\thrown\mk_iii_proj";};
};