class CfgPatches {
	class tsp_breach_shock {
		requiredAddons[] = {"cba_common", "tsp_breach", "ace_interaction", "ace_explosives"};
        weapons[] = {"tsp_breach_shock"};
        units[] = {};
	};
};

//-- FUNCTIONS
class Extended_PreInit_EventHandlers {class tsp_breach_shock_cba {init = "[] call compileScript ['\tsp_breach_shock\cba.sqf']";};};
class Extended_PostInit_EventHandlers {class tsp_breach_shock_init {init = "['CBA_settingsInitialized', {[] spawn compileScript ['\tsp_breach_shock\init.sqf']}] call CBA_fnc_addEventHandler;";};};

//-- SOUNDS
class CfgSounds {class tsp_breach_fuse {name = "tsp_breach_fuse"; sound[] = {"tsp_breach_shock\snd\fuse.ogg", 2, 2, 30}; titles[] = {0, ""};};};

//-- ROPE 
class CfgVehicles {class Rope; class shock_wire: Rope {model = "\tsp_breach_shock\wire.p3d"; segmentType = "shock_wire_segment";};};
class CfgNonAIVehicles {class RopeSegment; class shock_wire_segment: RopeSegment {model = "\tsp_breach_shock\wire.p3d";};};

//-- ITEMS
class CfgWeapons {
    class ACE_Clacker;
    class tsp_breach_shock: ACE_Clacker {
        displayName = "Shock Tube";
        picture = "\tsp_breach_shock\gui\ui.paa";
        model = "\tsp_breach_shock\shock.p3d";
        ACE_Explosives_Range = 999;
        ACE_Explosives_triggerType = "Shock";
    };
};

class ACE_Triggers {
    class Shock {
        displayName = "Shock Tube (30M)";
        isAttachable = 1;
        onPlace = "[_this#0, _this#1, _this#2, _this#3, _this#4, 30] spawn tsp_fnc_breach_shock_wire; _this call ace_explosives_fnc_AddClacker; false";
        picture = "\tsp_breach_shock\gui\ui.paa";
        requires[] = {"tsp_breach_shock"};
    };
    class ShockShort: Shock {
        displayName = "Shock Tube (15M)";
        onPlace = "[_this#0, _this#1, _this#2, _this#3, _this#4, 15] spawn tsp_fnc_breach_shock_wire; _this call ace_explosives_fnc_AddClacker; false";
    };
};

class CfgMagazines {    
    class CA_Magazine;
	class ATMine_Range_Mag;
    class SatchelCharge_Remote_Mag;
	class DemoCharge_Remote_Mag; 
    class ClaymoreDirectionalMine_Remote_Mag: CA_Magazine {class ACE_Triggers {SupportedTriggers[] = {"Timer", "Command", "MK16_Transmitter", "Shock", "ShockShort"}; class Shock {FuseTime = 2;}; class ShockShort {FuseTime = 1;};};};
    class DemoCharge_Remote_Mag: SatchelCharge_Remote_Mag {class ACE_Triggers {SupportedTriggers[] = {"Timer", "Command", "MK16_Transmitter", "Shock", "ShockShort"}; class Shock {FuseTime = 2;}; class ShockShort {FuseTime = 1;};};};
	class SatchelCharge_Remote_Mag: CA_Magazine	{class ACE_Triggers {SupportedTriggers[] = {"Timer", "Command", "MK16_Transmitter", "DeadmanSwitch", "Shock", "ShockShort"}; class Shock {FuseTime = 2;}; class ShockShort {FuseTime = 1;};};};
	class SLAMDirectionalMine_Wire_Mag: ATMine_Range_Mag {class ACE_Triggers {SupportedTriggers[] = {"IRSensor", "PressurePlate", "Command", "Timer", "MK16_Transmitter", "Shock", "ShockShort"}; class Shock {FuseTime = 2;}; class ShockShort {FuseTime = 1;};};};
	class IEDUrbanSmall_Remote_Mag: DemoCharge_Remote_Mag {class ACE_Triggers {SupportedTriggers[] = {"Cellphone", "PressurePlate", "Command", "DeadmanSwitch", "Shock", "ShockShort"}; class Shock {FuseTime = 2;}; class ShockShort {FuseTime = 1;};};};
	class IEDUrbanBig_Remote_Mag: DemoCharge_Remote_Mag	{class ACE_Triggers {SupportedTriggers[] = {"Cellphone", "PressurePlate", "Command", "DeadmanSwitch", "Shock", "ShockShort"}; class Shock {FuseTime = 2;}; class ShockShort {FuseTime = 1;};};};
};