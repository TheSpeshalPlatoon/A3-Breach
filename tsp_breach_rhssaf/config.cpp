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
			SupportedTriggers[] = {"Timer", "Command", "MK16_Transmitter", "DeadmanSwitch", "Shock30", "Shock15", "Shock5"};
			class Shock {FuseTime = 3;}; class ShockShort {FuseTime = 1;};
		};
	};
	class rhssaf_mine_mrud_d_mag: rhssaf_mine_mrud_a_mag {
		class ACE_Triggers {
			SupportedTriggers[] = {"Command", "MK16_Transmitter", "Shock30", "Shock15", "Shock5"};
			class Shock {FuseTime = 3;}; class ShockShort {FuseTime = 1;};
		};
	};
	class HandGrenade;
	class rhssaf_mag_rshb_p98: HandGrenade {displayNameShort = "RShB P98"; ammo = "rhssaf_ammo_rshb_p98"; flashbang = "sleep 1.5; [_this#0, _this#1] spawn tsp_fnc_flashbang";}; 
};
class CfgAmmo {
    class SmokeShell;
    class rhssaf_ammo_rshb_p98: SmokeShell {model = "\rhssaf\addons\rhssaf_m_explosives\grenades\thrown\rshb_p98\rhssaf_rshb_p98_throw"; explosionTime = 2.3; timeToLive = 60; grenadeFireSound[] = {}; grenadeBurningSound[] = {}; aiAmmoUsageFlags = "64"; effectsSmoke = "";};
};