class CfgPatches {
	class tsp_breach_dip {
		requiredAddons[] = {"cba_common", "tsp_breach"};
		units[] = {};
	};
};

class CfgMagazines {
    class SLAMDirectionalMine_Wire_Mag;
    class tsp_breach_dip_mag: SLAMDirectionalMine_Wire_Mag {
        displayName = "Dip Charge"; picture = "\tsp_breach_dip\gui\ui.paa"; descriptionShort = "Breaching charge made out of a Zyn can, Spearmint flavoured.";
        model = "tsp_breach_dip\dip_mag.p3d"; ammo = "tsp_breach_dip_ammo"; mass = 5; ace_explosives_setupObject = "tsp_breach_dip_place";
		class ACE_Triggers {SupportedTriggers[] = {"Timer", "Command", "MK16_Transmitter", "Shock30", "Shock15", "Shock5"};class Shock30 {FuseTime = 3;}; class Shock15 {FuseTime = 3;}; class Shock5 {FuseTime = 3;};};
    };
    class tsp_breach_dip_auto_mag: tsp_breach_dip_mag {displayName = "Dip Charge (Auto-Fuse)"; ace_explosives_setupObject = "tsp_breach_dip_auto_place"; class ACE_Triggers {SupportedTriggers[] = {};};};
};

class CfgAmmo {
    class SLAMDirectionalMine_Wire_Ammo;
    class tsp_breach_dip_ammo: SLAMDirectionalMine_Wire_Ammo {
        model = "tsp_breach_dip\dip_ammo.p3d"; mineModelDisabled = "\tsp_breach_dip\dip_ammo.p3d"; hit = 2; indirectHit = 1; indirectHitRange = 1; explosionAngle = 40;
        defaultMagazine = "tsp_breach_dip_mag"; ace_explosives_magazine = "tsp_breach_dip_mag"; ace_explosives_explosive = "tsp_breach_dip_ammo";
        SoundSetExplosion[] = {"tsp_breach_exp_small"}; explosionEffects = "DipExplosionEffect";    
        soundHit[] = {"A3\Sounds_F\arsenal\explosives\mines\Explosion_claymore",0,0,0};  //-- Lower it so it doesnt trigger ACE hearing
        soundHit1[] = {"A3\Sounds_F\arsenal\explosives\mines\Explosion_claymore",0,0,0};  //-- Lower it so it doesnt trigger ACE hearing
    };
};

class CfgVehicles {
    class ACE_Explosives_Place_SLAM;
    class tsp_breach_dip_place: ACE_Explosives_Place_SLAM {ammo = "tsp_breach_dip_ammo"; model = "tsp_breach_dip\dip_ammo.p3d"; class EventHandlers {init = "[_this#0,-1,[0.1,1,1,0,0],0,-1,0.25] spawn tsp_fnc_breach_explosive";};};
    class tsp_breach_dip_auto_place: tsp_breach_dip_place {class EventHandlers {init = "[_this#0,tsp_cba_breach_auto,[0.1,1,1,0,0],0,-1,0.25] spawn tsp_fnc_breach_explosive";};};
};

class CfgWeapons {
	class Default;
	class Put: Default {
		muzzles[] += {"tsp_breach_dip_muzzle"};
		class PutMuzzle: Default {};
		class tsp_breach_dip_muzzle: PutMuzzle {magazines[] = {"tsp_breach_dip_mag", "tsp_breach_dip_auto_mag"};};
	};
};

class DipExplosionEffect {
    class sparks {intensity = 1; interval = 1; lifeTime = 0.5; position[] = {0,0,0}; simulation = "particles"; type = "AmmoExpSparks";};    
    class sparks2 {intensity = 1; interval = 1; lifeTime = 0.5; position[] = {0,0,0}; simulation = "particles"; type = "AirFireSparks";};
    class smoke {intensity = 2; interval = 1; lifeTime = 2; position[] = {0,0,0}; simulation = "particles"; type = "ImpactSmoke";};
};