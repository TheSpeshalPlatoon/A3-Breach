class CfgPatches {
	class tsp_breach_silhouette {
		requiredAddons[] = {"cba_common", "tsp_breach"};
		units[] = {"tsp_breach_silhouette_twig", "tsp_breach_silhouette_stick"};
	};
};

//-- FUNCTIONS
class Extended_PostInit_EventHandlers {class tsp_breach_silhouette {init = "['CBA_settingsInitialized', {[] call compileScript ['\tsp_breach_silhouette\init.sqf']}] call CBA_fnc_addEventHandler;";};};

class CfgMagazines {
    class SLAMDirectionalMine_Wire_Mag;
    class tsp_breach_silhouette_mag: SLAMDirectionalMine_Wire_Mag {
        displayName = "Silhouette Charge"; picture = "\tsp_breach_silhouette\gui\ui.paa"; descriptionShort = "Works on walls and doors.";
        model = "tsp_breach_silhouette\silhouette_mag.p3d"; ammo = "tsp_breach_silhouette_ammo"; mass = 80; ace_explosives_setupObject = "tsp_breach_silhouette_place";
		class ACE_Triggers {SupportedTriggers[] = {"Timer", "Command", "MK16_Transmitter", "Shock", "ShockShort"}; class Shock {FuseTime = 2;}; class ShockShort {FuseTime = 1;};};
    };
};

class CfgAmmo {
    class ClaymoreDirectionalMine_Remote_Ammo;
    class tsp_breach_silhouette_ammo: ClaymoreDirectionalMine_Remote_Ammo {
        model = "tsp_breach_silhouette\silhouette_ammo.p3d"; mineModelDisabled = "\tsp_breach_silhouette\silhouette_ammo.p3d"; hit = 40; indirectHit = 40; indirectHitRange = 4; explosionAngle = 120;
        defaultMagazine = "tsp_breach_silhouette_mag"; ace_explosives_magazine = "tsp_breach_silhouette_mag"; ace_explosives_explosive = "tsp_breach_silhouette_ammo";
        SoundSetExplosion[] = {"tsp_breach_exp","ClaymoreMine_Tail_SoundSet","Explosion_Debris_SoundSet"}; 
        soundHit[] = {"A3\Sounds_F\arsenal\explosives\mines\Explosion_claymore",0.1,0,100};  //-- Lower it so it doesnt trigger ACE hearing
    };
};

class CfgVehicles {
    class SLAMDirectionalMine;
    class ACE_Explosives_Place_SLAM;
    class tsp_breach_silhouette_place: ACE_Explosives_Place_SLAM {
        ammo = "tsp_breach_silhouette_ammo"; model = "tsp_breach_silhouette\silhouette_ammo.p3d"; 
        class EventHandlers {init = "[_this#0,-1,[1,1,1,1,1],0,1,0.25] spawn tsp_fnc_breach_explosive";};
    };
	class Items_base_F; 
    class tsp_breach_silhouette_twig: Items_base_F {scope = 2; displayName = "Twig"; model = "tsp_breach_silhouette\twig.p3d";};
    class tsp_breach_silhouette_stick: tsp_breach_silhouette_twig {displayName = "Stick"; model = "tsp_breach_silhouette\stick.p3d";};
};

class CfgWeapons {
	class Default;
	class Put: Default {
		muzzles[] += {"tsp_breach_silhouette_muzzle"};
		class PutMuzzle: Default {};
		class tsp_breach_silhouette_muzzle: PutMuzzle {magazines[] = {"tsp_breach_silhouette_mag","tsp_breach_silhouette_auto_mag"};};
	};
};