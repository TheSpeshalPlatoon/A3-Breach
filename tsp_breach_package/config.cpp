class CfgPatches {
	class tsp_breach_package {
		requiredAddons[] = {"cba_common", "tsp_breach"};
		units[] = {};
	};
};

class CfgMagazines {
    class SLAMDirectionalMine_Wire_Mag;
    class tsp_breach_package_mag: SLAMDirectionalMine_Wire_Mag {
        displayName = "Packaged Charge"; picture = "\tsp_breach_package\gui\ui.paa"; descriptionShort = "package style breaching charge, used for walls and reinforced doors. Has a high potential to be lethal.";  //ACTUAL DESC
        model = "tsp_breach_package\package_mag.p3d"; ammo = "tsp_breach_package_ammo"; mass = 20; ace_explosives_setupObject = "tsp_breach_package_place";
		class ACE_Triggers {SupportedTriggers[] = {"Timer", "Command", "MK16_Transmitter", "Shock30", "Shock15", "Shock5"};class Shock30 {FuseTime = 3;}; class Shock15 {FuseTime = 3;}; class Shock5 {FuseTime = 3;};};
    };
};

class CfgAmmo {
    class ClaymoreDirectionalMine_Remote_Ammo;
    class tsp_breach_package_ammo: ClaymoreDirectionalMine_Remote_Ammo {
        model = "tsp_breach_package\package_ammo.p3d"; mineModelDisabled = "\tsp_breach_package\package_ammo.p3d"; hit = 100; indirectHit = 70; indirectHitRange = 5; explosionAngle = 120;
        defaultMagazine = "tsp_breach_package_mag"; ace_explosives_magazine = "tsp_breach_package_mag"; ace_explosives_explosive = "tsp_breach_package_ammo";
        soundHit[] = {"A3\Sounds_F\arsenal\explosives\mines\Explosion_claymore",0.1,0,100};  //-- Lower it so it doesnt trigger ACE hearing
    };
};

class CfgVehicles {
    class ACE_Explosives_Place_SLAM;
    class tsp_breach_package_place: ACE_Explosives_Place_SLAM {ammo = "tsp_breach_package_ammo"; model = "tsp_breach_package\package_ammo.p3d"; class EventHandlers {init = "[_this#0,-1,[1,1,1,1,1],1] spawn tsp_fnc_breach_explosive";};};
};

class CfgWeapons {
	class Default;
	class Put: Default {
		muzzles[] += {"tsp_breach_package_muzzle"};
		class PutMuzzle: Default {};
		class tsp_breach_package_muzzle: PutMuzzle {magazines[] = {"tsp_breach_package_mag"};};
	};
};
