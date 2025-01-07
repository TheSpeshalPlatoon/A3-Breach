class CfgPatches {
	class tsp_flashbang {
		requiredAddons[] = {"cba_common", "A3_Weapons_F","A3_Modules_F_Misc"};
		units[] = {"tsp_core"};
	};
};

//-- FUNCTIONS
class Extended_PreInit_EventHandlers {class tsp_flashbang_cba {init = "[] call compileScript ['\tsp_flashbang\cba.sqf']";}; class tsp_flashbang_functions {init = "[] call compileScript ['\tsp_flashbang\functions.sqf']";};}; 
class Extended_PostInit_EventHandlers {class tsp_flashbang_init {init = "['ace_firedPlayer', {_code = getText (configFile >> 'CfgMagazines' >> (_this#5) >> 'flashbang'); if (_code != '') exitWith {[_unit, (_this#6)] spawn (compile _code)}}] call CBA_fnc_addEventHandler";};};

//-- FLASHBANGS
class CfgMagazines {
	class HandGrenade;
	class tsp_flashbang_fakels: HandGrenade {
		scope = 2;
		scopeArsenal = 2;
		scopeCurator = 2;
		flashbang = "sleep 2; [_this#0, _this#1] spawn tsp_fnc_flashbang";
        displayname = "Fakel-S Stun Grenade";
        descriptionShort = "The Fakel-S is a Russian flashbang.";
        displayNameShort = "Fakel-S";
        model = "tsp_flashbang\fakel_s.p3d";
        picture = "\tsp_flashbang\gui\fakel.paa";
        ammo = "tsp_flashbang_fakels_ammo";
        mass = 2;
    };
    class tsp_flashbang_cts: tsp_flashbang_fakels {
		flashbang = "sleep 1.5; for '_i' from 1 to 9 do {[_this#0, _this#1, _i in [0,4,9]] spawn tsp_fnc_flashbang; sleep ((random 1) min 0.25 max 0.2)}";
        displayname = "CTS 9-Bang";
        descriptionShort = "The CTS 9-Bang is a flashbang that will go off 9 times, greatly improving it's effectiveness.";
        displayNameShort = "9-Bang";
        model = "tsp_flashbang\cts.p3d";
        picture = "\tsp_flashbang\gui\cts.paa";
        ammo = "tsp_flashbang_cts_ammo";
    };
    class tsp_flashbang_cts2: tsp_flashbang_fakels {
		flashbang = "sleep 1.5; for '_i' from 1 to 2 do {[_this#0, _this#1] spawn tsp_fnc_flashbang; sleep ((random 1) min 0.25 max 0.2)}";
        displayname = "CTS 2-Bang";
        descriptionShort = "The CTS 2-Bang is a flashbang that will go off 2 times.";
        displayNameShort = "2-Bang";
        model = "tsp_flashbang\cts.p3d";
        picture = "\tsp_flashbang\gui\cts.paa";
        ammo = "tsp_flashbang_cts_ammo";
    };
    class tsp_flashbang_cts99: tsp_flashbang_cts {
		flashbang = "sleep 1.5; for '_i' from 1 to 99 do {[_this#0, _this#1] spawn tsp_fnc_flashbang; sleep ((random 1) min 0.25 max 0.2)}";
        displayname = "CTS 99-Bang";
        descriptionShort = "The forbidden banger.";
        displayNameShort = "99-Bang";
    };
    class tsp_flashbang_m84: tsp_flashbang_fakels {
        displayname = "M84 Stun Grenade";
        descriptionShort = "The M84 is the currently-issued stun grenade of the United States Armed Forces.";
        displayNameShort = "M84";
        model = "tsp_flashbang\m84.p3d";
        picture = "\tsp_flashbang\gui\m84.paa";
        ammo = "tsp_flashbang_m84_ammo";
    };
};
class CfgAmmo {
    class SmokeShell;
    class tsp_flashbang_fakels_ammo: SmokeShell {model = "tsp_flashbang\fakel_s.p3d"; explosionTime = 2.3; timeToLive = 60; grenadeFireSound[] = {}; grenadeBurningSound[] = {}; aiAmmoUsageFlags = "64"; effectsSmoke = "";};
    class tsp_flashbang_cts_ammo: tsp_flashbang_fakels_ammo {model = "tsp_flashbang\cts.p3d";};
    class tsp_flashbang_m84_ammo: tsp_flashbang_fakels_ammo {model = "tsp_flashbang\m84.p3d";};
};
class CfgWeapons {
    class GrenadeLauncher;
    class Throw: GrenadeLauncher {
        muzzles[] += {"tsp_flashbang_fakelMuzzle","tsp_flashbang_ctsMuzzle","tsp_flashbang_cts2Muzzle","tsp_flashbang_cts99Muzzle", "tsp_flashbang_m84Muzzle"};
        class ThrowMuzzle;
        class tsp_flashbang_fakelMuzzle: ThrowMuzzle {magazines[] = {"tsp_flashbang_fakels"};};
        class tsp_flashbang_ctsMuzzle: ThrowMuzzle {magazines[] = {"tsp_flashbang_cts"};};
        class tsp_flashbang_cts2Muzzle: ThrowMuzzle {magazines[] = {"tsp_flashbang_cts2"};};
        class tsp_flashbang_cts99Muzzle: ThrowMuzzle {magazines[] = {"tsp_flashbang_cts99"};};
        class tsp_flashbang_m84Muzzle: ThrowMuzzle {magazines[] = {"tsp_flashbang_m84"};};
    };
};

//-- ANIMATIONS
class CfgMovesBasic;
class CfgMovesMaleSdr: CfgMovesBasic {
    class States {
		class CutSceneAnimationBaseZoZo;
		class Acts_Shocked_1_Loop: CutSceneAnimationBaseZoZo {
            interpolateFrom[] = {"aidlpercmstpsraswrfldnon", 1, "amovpercmstpsraswrfldnon", 1}; 
            interpolateTo[] = {"amovpercmstpsraswrfldnon", 1, "Unconscious", 0.02}; 
            interpolationSpeed = 1000;
            disableWeapons = 0;
            disableWeaponsLong = 0;
            weaponLowered = 0;
            weaponObstructed = 0;
        };
		class Acts_Shocked_3: CutSceneAnimationBaseZoZo { 
            interpolateFrom[] = {"aidlpercmstpsraswrfldnon", 1, "amovpercmstpsraswrfldnon", 1}; 
            interpolateTo[] = {"amovpercmstpsraswrfldnon", 1, "Unconscious", 0.02}; 
            interpolationSpeed = 1000;
            disableWeapons = 0;
            disableWeaponsLong = 0;
            weaponLowered = 0;
            weaponObstructed = 0;
        };
		class Acts_Shocked_4_Loop: CutSceneAnimationBaseZoZo {
            interpolateFrom[] = {"aidlpercmstpsraswrfldnon", 1, "amovpercmstpsraswrfldnon", 1}; 
            interpolateTo[] = {"amovpercmstpsraswrfldnon", 1, "Unconscious", 0.02}; 
            interpolationSpeed = 1000;
            disableWeapons = 0;
            disableWeaponsLong = 0;
            weaponLowered = 0;
            weaponObstructed = 0;
        };
        class Acts_Stunned_Unconscious: CutSceneAnimationBaseZoZo {
            interpolateFrom[] = {"aidlpercmstpsraswrfldnon", 1, "amovpercmstpsraswrfldnon", 1}; 
            interpolateTo[] = {"amovppnemstpsnonwnondnon", 1, "Unconscious", 0.02}; 
            interpolationSpeed = 100;
            disableWeapons = 0;
            disableWeaponsLong = 0;
            weaponLowered = 0;
            weaponObstructed = 0;
        };
        class Acts_Flashes_Recovery_1: CutSceneAnimationBaseZoZo {
            interpolateFrom[] = {"aidlpercmstpsraswrfldnon", 1, "amovpknlmstpsraswpstdnon", 1}; 
            interpolateTo[] = {"amovpercmstpsraswrfldnon", 1, "Unconscious", 0.02}; 
            interpolationSpeed = 10;
            disableWeapons = 0;
            disableWeaponsLong = 0;
            weaponLowered = 0;
            weaponObstructed = 0;
        };
        class Acts_Flashes_Recovery_2: Acts_Flashes_Recovery_1 {
            interpolateFrom[] = {"aidlpercmstpsraswrfldnon", 1, "amovpknlmstpsraswpstdnon", 1}; 
            interpolateTo[] = {"amovpercmstpsraswrfldnon", 1, "Unconscious", 0.02}; 
            interpolationSpeed = 10;
            disableWeapons = 0;
            disableWeaponsLong = 0;
            weaponLowered = 0;
            weaponObstructed = 0;
        };
        class Acts_Ambient_Rifle_Drop: CutSceneAnimationBaseZoZo {
            interpolateFrom[] = {"aidlpercmstpsraswrfldnon", 1,"amovpercmstpsraswrfldnon", 1}; 
            interpolateTo[] = {"amovpercmstpsraswrfldnon", 1, "Unconscious", 0.02}; 
            interpolationSpeed = 10;
            disableWeapons = 0;
            disableWeaponsLong = 0;
            weaponLowered = 0;
            weaponObstructed = 0;
        };
	};
};