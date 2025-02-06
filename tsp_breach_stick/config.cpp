class CfgPatches {
	class tsp_breach_stick {
		requiredAddons[] = {"cba_common", "tsp_breach"};
		units[] = {};
	};
};

//-- FUNCTIONS
class Extended_PostInit_EventHandlers {class tsp_breach_stick_init {init = "['CBA_settingsInitialized', {[] spawn compileScript ['\tsp_breach_stick\init.sqf']}] call CBA_fnc_addEventHandler;";};};  

class CfgMagazines {
    class SLAMDirectionalMine_Wire_Mag;
    class tsp_breach_stick_mag: SLAMDirectionalMine_Wire_Mag {
        displayName = "Stick Charge"; picture = "\tsp_breach_stick\gui\ui.paa"; descriptionShort = "Large breaching charge intended for doors, used for regular/military/reinforced doors.";
        model = "tsp_breach_stick\stick_mag.p3d"; ammo = "tsp_breach_stick_ammo"; mass = 10; ace_explosives_setupObject = "tsp_breach_stick_place";
		class ACE_Triggers {SupportedTriggers[] = {"Timer", "Command", "MK16_Transmitter", "Shock", "ShockShort"}; class Shock {FuseTime = 2;}; class ShockShort {FuseTime = 1;};};
    };
};

class CfgAmmo {
    class ClaymoreDirectionalMine_Remote_Ammo;
    class tsp_breach_stick_ammo: ClaymoreDirectionalMine_Remote_Ammo {
        model = "tsp_breach_stick\stick_ammo.p3d"; mineModelDisabled = "\tsp_breach_stick\stick_ammo.p3d";
        hit = 10; indirectHit = 5; indirectHitRange = 1; explosionAngle = 270;
        defaultMagazine = "tsp_breach_stick_mag"; ace_explosives_magazine = "tsp_breach_stick_mag"; ace_explosives_explosive = "tsp_breach_stick_ammo";
        SoundSetExplosion[] = {"tsp_breach_exp_triple","ClaymoreMine_Tail_SoundSet","Explosion_Debris_SoundSet"}; 
        soundHit[] = {"A3\Sounds_F\arsenal\explosives\mines\Explosion_claymore",0.1,0,100};  //-- Lower it so it doesnt trigger ACE hearing
    };
};

class CfgVehicles {
    class ACE_Explosives_Place_SLAM;
    class tsp_breach_stick_place: ACE_Explosives_Place_SLAM {ammo = "tsp_breach_stick_ammo"; model = "tsp_breach_stick\stick_ammo.p3d"; class EventHandlers {init = "[_this#0,-1,[1,1,1,1,0],0.1] spawn tsp_fnc_breach_explosive";};};
};

class CfgWeapons {
	class Default;
	class Put: Default {
		muzzles[] += {"tsp_breach_stick_muzzle"};
		class PutMuzzle: Default {};
		class tsp_breach_stick_muzzle: PutMuzzle {magazines[] = {"tsp_breach_stick_mag"};};
	};
};

//-- ANIMATIONS
class CfgMovesBasic {
    class default;
    class DefaultDie;
    class ManActions {
		tsp_breach_stick_wnon_in[] = {"tsp_breach_stick_wnon_in", "Gesture"};
		tsp_breach_stick_wnon_loop[] = {"tsp_breach_stick_wnon_loop", "Gesture"};
		tsp_breach_stick_wrfl_in[] = {"tsp_breach_stick_wrfl_in", "Gesture"};
		tsp_breach_stick_wrfl_loop[] = {"tsp_breach_stick_wrfl_loop", "Gesture"};
	};
};
class CfgGesturesMale {
	skeletonName = "OFP2_ManSkeleton";
	class Default {};
	class States {
		class GestureNo;
		class tsp_breach_stick_wnon_in: GestureNo {file = "tsp_breach_stick\anim\stick_in.rtm"; speed = 1.5; mask = "handsWeapon_pst"; showHandgun = false; interpolationSpeed = 3; leftHandIKCurve[] = {0,1,0.8,1,1,0}; rightHandIKCurve[] = {0,1,0.8,1,1,0};};
		class tsp_breach_stick_wnon_loop: tsp_breach_stick_wnon_in {file = "tsp_breach_stick\anim\stick_loop.rtm"; speed = 0.5; looped = true; leftHandIKCurve[] = {0}; rightHandIKCurve[] = {0};};
        class tsp_breach_stick_wrfl_in: tsp_breach_stick_wnon_in {mask = "handsWeapon"; leftHandIKCurve[] = {0}; rightHandIKCurve[] = {0};};
        class tsp_breach_stick_wrfl_loop: tsp_breach_stick_wnon_loop {mask = "handsWeapon";};
	};
	class BlendAnims {};
};