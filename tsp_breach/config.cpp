class CfgPatches {
	class tsp_breach {
		requiredAddons[] = {"cba_common", "ace_explosives"};
		units[] = {};
	};
};

//-- FUNCTIONS
class Extended_PreInit_EventHandlers {class tsp_breach_cba {init = "[] call compileScript ['\tsp_breach\cba.sqf']";}; class tsp_breach_functions {init = "[] call compileScript ['\tsp_breach\functions.sqf']";};};
class Extended_PostInit_EventHandlers {class tsp_breach_init {init = "['CBA_settingsInitialized', {[] spawn compileScript ['\tsp_breach\init.sqf']}] call CBA_fnc_addEventHandler;";};};

//-- FAKE WALL
class CfgVehicles {class Items_base_F; class tsp_breach_wall: Items_base_F {scope = 2; displayName = "Fake Wall"; model = "tsp_breach\wall.p3d";};};

//-- ITEMS
class CfgWeapons {
	class CBA_MiscItem;
	class CBA_MiscItem_ItemInfo;
	class tsp_paperclip: CBA_MiscItem {
		scope = 2;
		displayName = "Paperclip";
		picture = "\tsp_breach\gui\paperclip.paa";
		model = "tsp_breach\paperclip.p3d";
		class ItemInfo: CBA_MiscItem_ItemInfo {mass = 1; type = 302;};
    };
	class tsp_lockpick: tsp_paperclip {
		displayName = "Lock Pick Kit";
		picture = "\tsp_breach\gui\lockpick.paa";
		model = "tsp_breach\lockpick.p3d";
		class ItemInfo: ItemInfo {mass = 10;};
    };
};

//-- SOUNDS
class CfgSoundShaders {
    class GrenadeHe_closeExp_SoundShader;
    class tsp_breach_exp: GrenadeHe_closeExp_SoundShader {samples[] = {{"\tsp_breach\snd\exp1.ogg",1},{"\tsp_breach\snd\exp2.ogg",1}}; volume = 2;};
    class tsp_breach_exp_small: GrenadeHe_closeExp_SoundShader {samples[] = {{"\tsp_breach\snd\exp_small.ogg",1}}; volume = 1;};
    class tsp_breach_exp_triple: GrenadeHe_closeExp_SoundShader {samples[] = {{"\tsp_breach\snd\exp_triple.ogg",1}}; volume = 1.5;};
    class tsp_breach_exp_claymore: GrenadeHe_closeExp_SoundShader {samples[] = {{"\A3\Sounds_F\arsenal\explosives\mines\Explosion_claymore",1}}; volume = 2;};
};
class CfgSoundSets {
    class GrenadeHe_Exp_SoundSet;
    class tsp_breach_exp: GrenadeHe_Exp_SoundSet {soundShaders[] = {"tsp_breach_exp","tsp_breach_exp_claymore"};};
    class tsp_breach_exp_triple: GrenadeHe_Exp_SoundSet {soundShaders[] = {"tsp_breach_exp_triple","tsp_breach_exp_claymore"};};
    class tsp_breach_exp_small: GrenadeHe_Exp_SoundSet {soundShaders[] = {"tsp_breach_exp_small"};};
};

//-- ANIMATIONS
class CfgMovesBasic {class default; class DefaultDie; class ManActions {tsp_breach_knock[] = {"tsp_breach_knock", "Gesture"};};};
class CfgGesturesMale {
	skeletonName = "OFP2_ManSkeleton";
	class Default {};
	class States {
		class GestureNo;
		class tsp_breach_knock: GestureNo {
			mask = "leftArm"; 
			file = "tsp_breach\gestures\knock.rtm"; 
			speed = 1.5; 
			interpolationSpeed = 3; 
			leftHandIKCurve[] = {0,1,0.05,0,0.95,0,1,1}; 
			rightHandIKCurve[] = {1}; 
			disableWeapons = false;
		};
	};
	class BlendAnims {
		leftArm[] = {
            "LeftShoulder", 1, "LeftArm", 1, "LeftArmRoll", 1, "LeftForeArm", 1, "LeftForeArmRoll", 1, "LeftHand", 1, 
            "LeftHandThumb1", 1, "LeftHandThumb2", 1, "LeftHandThumb3", 1,
            "LeftHandIndex1", 1, "LeftHandIndex2", 1, "LeftHandIndex3", 1, 
            "LeftHandMiddle1", 1, "LeftHandMiddle2", 1, "LeftHandMiddle3", 1, 
            "LeftHandRing", 1, "LeftHandRing1", 1, "LeftHandRing2", 1, "LeftHandRing3", 1, 
            "LeftHandPinky1", 1, "LeftHandPinky2", 1, "LeftHandPinky3", 1
		};
	};
};