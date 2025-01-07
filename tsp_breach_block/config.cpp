class CfgPatches {
	class tsp_breach_block {
		requiredAddons[] = {"cba_common", "tsp_breach"};
		units[] = {};
	};
};

class CfgMagazines {
    class SLAMDirectionalMine_Wire_Mag;
    class tsp_breach_block_mag: SLAMDirectionalMine_Wire_Mag {
        displayName = "Breaching Block"; picture = "\tsp_breach_block\gui\ui.paa"; descriptionShort = "C4 block breaching charge, used for regular/military/reinforced doors.";
        model = "tsp_breach_block\block_mag.p3d"; ammo = "tsp_breach_block_ammo"; mass = 10; ace_explosives_setupObject = "tsp_breach_block_place";
		class ACE_Triggers {SupportedTriggers[] = {"Timer", "Command", "MK16_Transmitter", "Shock", "ShockShort"}; class Shock {FuseTime = 2;}; class ShockShort {FuseTime = 1;};};
    };
    class tsp_breach_block_auto_mag: tsp_breach_block_mag {displayName = "Breaching Block (Auto-Fuse)"; ace_explosives_setupObject = "tsp_breach_block_auto_place"; class ACE_Triggers {SupportedTriggers[] = {};};};
};

class CfgAmmo {
    class ClaymoreDirectionalMine_Remote_Ammo;
    class tsp_breach_block_ammo: ClaymoreDirectionalMine_Remote_Ammo {
        model = "tsp_breach_block\block_ammo.p3d"; mineModelDisabled = "\tsp_breach_block\block_ammo.p3d"; hit = 10; indirectHit = 5; indirectHitRange = 1; explosionAngle = 90;
        defaultMagazine = "tsp_breach_block_mag"; ace_explosives_magazine = "tsp_breach_block_mag"; ace_explosives_explosive = "tsp_breach_block_ammo";
        SoundSetExplosion[] = {"tsp_breach_exp","ClaymoreMine_Tail_SoundSet","Explosion_Debris_SoundSet"}; 
        soundHit[] = {"A3\Sounds_F\arsenal\explosives\mines\Explosion_claymore",0.1,0,100};  //-- Lower it so it doesnt trigger ACE hearing
    };
};

class CfgVehicles {
    class SLAMDirectionalMine;
    class ACE_Explosives_Place_SLAM;
    class tsp_breach_block_place: ACE_Explosives_Place_SLAM {ammo = "tsp_breach_block_ammo"; model = "tsp_breach_block\block_ammo.p3d"; class EventHandlers {init = "[_this#0] spawn tsp_fnc_breach_explosive";};};
    class tsp_breach_block_auto_place: tsp_breach_block_place {class EventHandlers {init = "[_this#0,tsp_cba_breach_auto] spawn tsp_fnc_breach_explosive";};};
};

class CfgWeapons {
	class Default;
	class Put: Default {
		muzzles[] += {"tsp_breach_block_muzzle"};
		class PutMuzzle: Default {};
		class tsp_breach_block_muzzle: PutMuzzle {magazines[] = {"tsp_breach_block_mag","tsp_breach_block_auto_mag"};};
	};
};