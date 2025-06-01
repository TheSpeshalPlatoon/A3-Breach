class CfgPatches {
	class tsp_breach_linear {
		requiredAddons[] = {"cba_common", "tsp_breach"};
		units[] = {};
	};
};

class CfgMagazines {
    class SLAMDirectionalMine_Wire_Mag;
    class tsp_breach_linear_mag: SLAMDirectionalMine_Wire_Mag {
        displayName = "Linear Charge"; picture = "\tsp_breach_linear\gui\ui.paa"; descriptionShort = "Linear style breaching charge, used for regular/military/reinforced doors.";
        model = "tsp_breach_linear\linear_mag.p3d"; ammo = "tsp_breach_linear_ammo"; mass = 5; ace_explosives_setupObject = "tsp_breach_linear_place";
		class ACE_Triggers {SupportedTriggers[] = {"Timer", "Command", "MK16_Transmitter", "Shock30", "Shock15", "Shock5"};class Shock30 {FuseTime = 3;}; class Shock15 {FuseTime = 3;}; class Shock5 {FuseTime = 3;};};
    };
    class tsp_breach_linear_auto_mag: tsp_breach_linear_mag {displayName = "Linear Charge (Auto-Fuse)"; ace_explosives_setupObject = "tsp_breach_linear_auto_place"; class ACE_Triggers {SupportedTriggers[] = {};};};
};

class CfgAmmo {
    class ClaymoreDirectionalMine_Remote_Ammo;
    class tsp_breach_linear_ammo: ClaymoreDirectionalMine_Remote_Ammo {
        model = "tsp_breach_linear\linear_ammo.p3d"; mineModelDisabled = "\tsp_breach_linear\linear_ammo.p3d";
        hit = 10; indirectHit = 5; indirectHitRange = 1; explosionAngle = 90;
        defaultMagazine = "tsp_breach_linear_mag"; ace_explosives_magazine = "tsp_breach_linear_mag"; ace_explosives_explosive = "tsp_breach_linear_ammo";
        SoundSetExplosion[] = {"tsp_breach_exp","ClaymoreMine_Tail_SoundSet","Explosion_Debris_SoundSet"}; 
        soundHit[] = {"A3\Sounds_F\arsenal\explosives\mines\Explosion_claymore",0.1,0,100};  //-- Lower it so it doesnt trigger ACE hearing
    };
};

class CfgVehicles {
    class ACE_Explosives_Place_SLAM;
    class tsp_breach_linear_place: ACE_Explosives_Place_SLAM {ammo = "tsp_breach_linear_ammo"; model = "tsp_breach_linear\linear_ammo.p3d"; class EventHandlers {init = "[_this#0,-1,[1,1,1,1,0],0.1,0.4] spawn tsp_fnc_breach_explosive";};};
    class tsp_breach_linear_auto_place: tsp_breach_linear_place {class EventHandlers {init = "[_this#0,tsp_cba_breach_auto,[1,1,1,0.5,0],0.1,0.4] spawn tsp_fnc_breach_explosive";};};
};

class CfgWeapons {
	class Default;
	class Put: Default {
		muzzles[] += {"tsp_breach_linear_muzzle"};
		class PutMuzzle: Default {};
		class tsp_breach_linear_muzzle: PutMuzzle {magazines[] = {"tsp_breach_linear_mag","tsp_breach_linear_auto_mag"};};
	};
};