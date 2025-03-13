tsp_fnc_breach_doors = {  //-- Get doors in radius
	params ["_center", ["_actionRadius", 7], ["_houseRadius", 25], ["_doors", []]];
	{  //-- For all houses in radius 
		_house = _x;
		{  //-- For all door useractions in house
			[_x, getText (configOf _house >> "UserActions" >> _x >> "actionNamedSel"), getText (configOf _house >> "UserActions" >> _x >> "position")] params ["_class", "_actionNamedSel", "_position", "_actualPos"];
			if (_position != "") then {_actualPos = _house modelToWorldWorld (_house selectionPosition [_position, "Memory", "AveragePoint"])};  //-- Use position by default
			if (_actionNamedSel != "") then {_actualPos = _house modelToWorldWorld (_house selectionPosition [_actionNamedSel, "Geometry", "AveragePoint"])};  //-- Use actionNamedSel if available
			if (count (_doors select {_x#3 distance _actualPos < 1}) > 0) then {continue};  //-- If there is already a similar point in _doors, then this is probably the same door
			if (_center distance _actualPos > _actionRadius) then {continue};  //-- If too far away from _center
			if (_actionNamedSel == "") then {_actionNamedSel = _position};  //-- If _actionNamedSel undefined, try to use _position as name
			_doors pushBack [_house, _class, _actionNamedSel, _actualPos];
		} forEach (((configfile >> "CfgVehicles" >> typeOf _house >> "UserActions") call BIS_fnc_getCfgSubClasses) select {["door", _x] call BIS_fnc_inString}); 
	} forEach (nearestObjects [ASLtoAGL _center, ["Static"], _houseRadius]);
	tsp_doors = _doors; _doors
};

//[getPosASL player, 3] call tsp_fnc_breach_doors;

//{
//	_x params ["_house", "_class", "_action", "_pos"];
//	_helper = "Sign_Arrow_F" createVehicleLocal [0,0,0]; _helper setPosASL _pos;
//} forEach (([getPosASL player] call tsp_fnc_breach_doors));

//{  //-- For all door useractions in house
//	_helper = "Sign_Arrow_F" createVehicleLocal [0,0,0]; 
//	_helper setPosASL (cursorObject modelToWorldWorld (cursorObject selectionPosition [getText (configOf cursorObject >> "UserActions" >> _x >> "actionNamedSel"), "Geometry", "AveragePoint"]));
//} forEach (((configfile >> "CfgVehicles" >> typeOf cursorObject >> "UserActions") call BIS_fnc_getCfgSubClasses) select {["door", _x] call BIS_fnc_inString}); 

tsp_fnc_breach_data = {  //-- Get ALL the door data
	params ["_house", "_door"];
	_id = [_door, "0123456789"] call BIS_fnc_filterString;
	_pos = _house modelToWorldWorld (_house selectionPosition _door);  //-- Actual door selection pos
	_animName = "NO"; {if ((_x find "door" != -1 || _x find "Door" != -1) && _x find _id != -1 && _x find "_handle" == -1) exitWith {_animName = _x}} forEach animationNames _house;
	_animPhase = _house animationPhase _animName;
	_locked = _house getVariable ["bis_disabled_Door_" + _id, 0];
	_triggerName = "NO"; {if (_x find "trigger" != -1 && _x find "door" != -1 && _id isEqualTo ([_x, "0123456789"] call BIS_fnc_filterString)) exitWith {_triggerName = _x}} forEach (_house selectionNames "MEMORY");
	_triggerPos = _house modelToWorldWorld (_house selectionPosition [_triggerName, "Memory"]); if (ASLtoAGL _triggerPos distance _house < 1) then {_triggerPos = _pos};
	_handleName = "NO";{if (_x find "handle" != -1 && _id isEqualTo ([_x, "0123456789"] call BIS_fnc_filterString)) exitWith {_handleName = _x}} forEach (_house selectionNames "MEMORY");
	_handlePos = _house modelToWorldWorld (_house selectionPosition [_handleName, "Memory"]); if (ASLtoAGL _handlePos distance _house < 1 || _animPhase == 1) then {_handlePos = _triggerPos};
	_hingeName = "NO";{if (_x find "axis" != -1 && _id isEqualTo ([_x, "0123456789"] call BIS_fnc_filterString)) exitWith {_hingeName = _x}} forEach (_house selectionNames "MEMORY");
	_hingePos = _house modelToWorldWorld (_house selectionPosition [_hingeName, "Memory"]); if (ASLtoAGL _hingePos distance _house < 1) then {_hingePos = _handlePos};
	[_id, _house, _door, _pos, _animName, _animPhase, _locked, _triggerName, _triggerPos, _handleName, _handlePos, _hingeName, _hingePos]
};

tsp_fnc_breach_push = {  //-- Check if door is push or pull, only used by melee
	params ["_unit", "_data"]; _data params ["_id","_house","_door","_pos","_animName","_animPhase","_locked","_triggerName","_triggerPos","_handleName","_handlePos","_hingeName","_hingePos"];
	_initialPosition = _house modelToWorld (_house selectionPosition [_door, "ViewGeometry", "AveragePoint"]);	//-- AveragePoint to get center of door selection
	_house animate [_animName, 1 + -_animPhase]; sleep 0.15;
	_finalPosition = _house modelToWorld (_house selectionPosition [_door, "ViewGeometry", "AveragePoint"]);  //-- AveragePoint to get center of door selection
	_house animate [_animName, _animPhase];  //-- Reset to original state
	if (_unit distance _initialPosition < _unit distance _finalPosition) then {true} else {false};
};

tsp_fnc_breach_effectiveness = {  //-- Select effectiveness based on house type
	params ["_house", "_damage"]; _damage params ["_glass", "_civil", "_military", "_reinforced", "_wall"];
	if (typeOf _house in tsp_cba_breach_military) exitWith {_military};
	if (typeOf _house in tsp_cba_breach_reinforced) exitWith {_reinforced};
	_civil
};

tsp_fnc_breach_adjust = {  //-- Manipulate doors
	params ["_data", ["_amount", -1], ["_lock", -1]];  //-- "_amount" can be -1 (nothing), 0 - 1 (closed - open) // "_lock" can be -1 (nothing), 0 (unlocked), 1 (locked), 3 (break)
	_data params ["_id", "_house", "_door", "_pos", "_animName", "_animPhase", "_locked", "_triggerName", "_triggerPos", "_handleName", "_handlePos", "_hingeName", "_hingePos"];
	if (_amount != -1) then {{_house animate [_animName regexReplace [_x#0, _x#1], _amount]} forEach [["a_rot","b_rot"],["b_rot","a_rot"],["a_rot","_rot"],["b_rot","_rot"]]};  //-- Double doors
	if (_amount != -1) then {{_house animateSource [(_animName + _x), _amount]} forEach ["_noSound_source", "_sound_source"]};  //-- Sahara
	if (_lock == 0) then {_house setVariable [("bis_disabled_Door_" + _id), 0, true]; playSound3D ["tsp_breach\snd\unlock.ogg", _pos, false, _pos, 4, 1, 50]};  //-- Unlock	
	if (_lock == 1) then {_house setVariable [("bis_disabled_Door_" + _id), 1, true]; playSound3D ["tsp_breach\snd\lock.ogg", _pos, false, _pos, 4, 1, 50]};   //-- Lock
	if (_lock == 3 && _locked != 3) then {_house setVariable [("bis_disabled_Door_" + _id), if (tsp_cba_breach_break) then {3} else {0}, true]};  //-- Break and not broken
	if (_lock == 3 && _locked != 3) then {playSound3D ["tsp_breach\snd\destroy.ogg", _pos, false, _pos, 1, 1, 50]};  //-- Break and not broken
	if (_lock == 3) then {_smoke = "#particlesource" createVehicle ASLtoATL _handlePos; _smoke setParticleClass "ImpactSmoke"; _smoke setDropInterval 0.1; sleep 0.2; deleteVehicle _smoke};  //-- Break
};

tsp_fnc_breach_interact = {  //-- Add ACE actions
	params ["_unit"]; {deleteVehicle _x} forEach (missionNameSpace getVariable ["tsp_breach_allActionsHelpers",[]]); tsp_breach_allActionsHelpers = [];  //-- Delete all old helpers on opening menu
	{  //-- For all door actions in radius
		_x params ["_house", "_class", "_name", "_actionPos"]; 
		([_house, _name] call tsp_fnc_breach_data) params ["_id","_house","_door","_pos","_animName","_animPhase","_locked","_triggerName","_triggerPos","_handleName","_handlePos","_hingeName","_hingePos"];
		_helper = "ACE_LogicDummy" createVehicleLocal [0,0,0]; tsp_breach_allActionsHelpers pushBack _helper;  //-- Create helper object, ace_marker_flags_red // ACE_LogicDummy // Sign_Arrow_F
		_helper setPosASL (if (_handlePos distance _actionPos < 1) then {_handlePos} else {_actionPos});
		[_helper, 0, [], ["door", "Door", "", {true}, {true}, {}, [], {[0,0,0]}, 2.5] call ace_interact_menu_fnc_createAction] call ace_interact_menu_fnc_addActionToObject;  //-- Add main action to "_helper"
		_helper setVariable ["data", [_house, _name] call tsp_fnc_breach_data];
		{
			_x params ["_name", "_image", "_code", "_condition"]; [(str _code) trim ["{}",0], (str _condition) trim ["{}", 0]] params ["_code", "_condition"];
			_params = "_data = (_this#0) getVariable 'data'; _data params ['_id','_house','_door','_pos','_animName','_animPhase','_locked','_triggerName','_triggerPos','_handleName','_handlePos','_hingeName','_hingePos'];";
			[_helper, 0, ["door"], [_id, _name, _image, compile (_params + _code), compile (_params + _condition), {}, _helper, [0,0,0], 2.5] call ace_interact_menu_fnc_createAction] call ace_interact_menu_fnc_addActionToObject;
		} forEach [
			["Open","\tsp_breach\gui\open.paa",{[_data,1] call tsp_fnc_breach_adjust; if !(isNil 'tsp_fnc_animate_tactical') then {[playa,'door'] call tsp_fnc_animate_tactical};},{_animPhase < 0.9 && _locked != 1}],
			["Close","\tsp_breach\gui\close.paa",{[_data,0] call tsp_fnc_breach_adjust; if !(isNil 'tsp_fnc_animate_tactical') then {[playa,'door'] call tsp_fnc_animate_tactical};},{_animPhase > 0.1 && _locked != 1}],
			["Knock","\tsp_breach\gui\knock.paa",{playSound3D ["tsp_breach\snd\knock.ogg", _pos, false, _pos, 5, 1, 10]; [playa, "", "tsp_breach_knock", "tsp_common_stop", true, true, true] spawn tsp_fnc_gesture_play},{_animPhase == 0}],
			["Unlock","\tsp_breach\gui\unlock.paa",{[_data,-1,0] call tsp_fnc_breach_adjust; if !(isNil 'tsp_fnc_animate_tactical') then {[playa,'door'] call tsp_fnc_animate_tactical};},{_locked == 1 && _animPhase == 0 && (([eyePos playa, playa] call tsp_fnc_outsideness) < ([eyePos playa vectorAdd (vectorDir playa vectorMultiply 2), playa] call tsp_fnc_outsideness))}], 
			["Lock","\tsp_breach\gui\lock.paa",{[_data,-1,1] call tsp_fnc_breach_adjust; if !(isNil 'tsp_fnc_animate_tactical') then {[playa,'door'] call tsp_fnc_animate_tactical};},{_locked == 0 && _animPhase == 0}], 
			["Use Paperclip","\tsp_breach\gui\paperclip.paa",{[playa,_data,0.75,"tsp_paperclip",tsp_cba_breach_paperclip] spawn tsp_fnc_breach_pick},{_locked == 1 && _animPhase == 0 && "tsp_paperclip" in (items playa)}], 
			["Use Lockpick","\tsp_breach\gui\lockpick.paa",{[playa,_data,0,"tsp_lockpick",tsp_cba_breach_lockpick] spawn tsp_fnc_breach_pick},{_locked == 1 && _animPhase == 0 && "tsp_lockpick" in (items playa)}]
		];
	} forEach ([getPosASL _unit] call tsp_fnc_breach_doors);
};

tsp_fnc_breach_lock = {  //-- Lock random doors in radius
	params [["_pos", [0,0,0]], ["_radius", 999999], ["_houseChance", tsp_cba_breach_lock_house], ["_doorChance", tsp_cba_breach_lock_door], ["_lock", 1], ["_types", ["BUILDING", "HOUSE", "CHURCH", "CHAPEL", "BUNKER", "FORTRESS", "VIEW-TOWER", "LIGHTHOUSE", "FUELSTATION", "HOSPITAL", "TOURISM"]]];
	{  //-- For all buildings in radius
		if !(random 1 < _houseChance) then {continue};  //--  Skip
		if (_x getVariable ["breach_blacklist", false] || (typeOf _x) in tsp_cba_breach_lock_blacklist) then {continue};  //--  Skip
		for "_i" from 0 to (count (configfile >> "CfgVehicles" >> typeOf _x >> "UserActions")) do {if (random 1 <= _doorChance) then {_x setVariable [format ["bis_disabled_Door_%1", _i], _lock, true]}};
	} forEach (nearestTerrainObjects [_pos, _types, _radius] + nearestObjects [_pos, _types, _radius]);
};

tsp_fnc_breach_explosive = {
	params ["_charge", ["_fuse", -1], ["_damage", [1,1,1,0.2,0]], ["_floor", -1], ["_swing", 1], ["_push", 0.02]];  //["_glass", "_civil", "_military", "_reinforced", "_wall"];
	[getPosASL _charge, typeOf _charge, getText (configFile >> "CfgVehicles" >> (typeOf _charge) >> "ammo")] params ["_pos", "_class", "_ammoClass"];  //-- Save these cause we can't get em later
	if (!local _charge || !tsp_cba_breach || _charge getVariable ["vis", false]) exitWith {};

	//-- Iffy sticky instersecty uh
	[_pos vectorAdd ([vectorDir _charge, 0, 2] call BIS_fnc_rotateVector3D vectorMultiply 0.7), _pos vectorAdd ([vectorDir _charge, 0, 2] call BIS_fnc_rotateVector3D vectorMultiply -0.7)] params ["_start", "_end"];
	((lineIntersectsSurfaces [_start, _end, _charge, player, true, 1, "GEOM"])#0) params ["_intersectPos", "_normal", "_object"]; if (isNil "_object") exitWith {};  //-- If no house/wall found
	
	//-- Position charge and handle auto fuse
	_charge setPosASL (_intersectPos vectorAdd (vectorDir _charge vectorMultiply _push)); _charge enableSimulation false; _charge setVectorDir _normal; _dir = [vectorDir _charge, vectorUp _charge];
	if (_floor != -1) then {_charge setPosASL (getPosASL _charge vectorAdd [0,0,-([_charge] call tsp_fnc_height) + _floor])};
	if (_fuse > -1) then {[_charge, getPosATL _charge, getDir _charge, getText (configFile >> "CfgAmmo" >> _ammoClass >> "defaultMagazine"), "Timer", [_fuse], _charge] call ace_explosives_fnc_placeExplosive};
	
	//-- Wait til armed
	_visual = createVehicle [_class, [0,0,0], [], 0, "CAN_COLLIDE"]; _visual setVariable ["vis", true]; 
	[_visual, _visual] call ace_common_fnc_claim; _visual enableSimulation false; _visual attachTo [_charge, [0,0,0]];  //-- Removes ACE actions
	while {sleep 0.01; _charge isNotEqualTo objNull} do {if (count (lineIntersectsSurfaces [_start, _end, _charge, player, true, 1, "GEOM"]) < 1) then {_charge enableSimulation true}};
	
	//-- Handle ammo
	_ammo = (allMissionObjects _ammoClass) select {_x distance2D _pos < 2}; if (count _ammo == 0) exitWith {deleteVehicle _visual}; _ammo = _ammo#0; 
	[_ammo, true] remoteExec ["hideObjectGlobal", 2];

	//-- Wait til explosion
	while {sleep 0.1; _ammo isNotEqualTo objNull} do {if (count (lineIntersectsSurfaces [_start, _end, _ammo, _visual, true, 1, "GEOM"]) < 1) then {_visual enableSimulation true; _ammo attachTo [_visual]}};
	[_visual, true] remoteExec ["hideObjectGlobal", 2];  //-- Cause we might sleep below before deleting _visual

	{  //-- Doors
		_x params ["_house", "_class", "_name", "_pos"];
		if (random 1 <= [_house, _damage] call tsp_fnc_breach_effectiveness) then {[[_house, _name] call tsp_fnc_breach_data, _swing, 3] spawn tsp_fnc_breach_adjust};
	} forEach ([getPosASL _visual, 2] call tsp_fnc_breach_doors);

	//-- Walls
	((lineIntersectsSurfaces [_end, _start, _charge, _visual, true, 1, "GEOM"])#0) params ["_intersectPos", "_normal", "_wall"];
	if (random 1 < (_damage#4) && !isNil "_wall") then {  //-- If wall found and successful breach
		_near = (nearestTerrainObjects [_wall, ["WALL", "FENCE"], 1]) + (nearestObjects [_object, ["WALL", "FENCE"], 1]);
		_wrecks = tsp_cba_breach_walls select {_x#0 in str _wall || _x#1 == typeOf _wall};
		if !(_wall in _near || ["wall", typeOf _wall] call BIS_fnc_inString || ["fence", typeOf _wall] call BIS_fnc_inString || ["wall", getText (configFile >> "CfgVehicles" >> typeOf _wall >> "displayName")] call BIS_fnc_inString) exitWith {};
		if (count _wrecks > 0) exitWith {
			_wreck = createVehicle [_wrecks#0#2, getPos _wall, [], 0, "CAN_COLLIDE"]; _wreck setDir (getDir _wall); 
			_wreck setVehiclePosition [_wall, [], 0, "CAN_COLLIDE"]; [_wall, true] remoteExec ["hideObjectGlobal",2]};
		_wall setDamage 1; _vector = vectorDir _wall; sleep 0.1;
		if (typeOf _wall == "" && vectorDir _wall isEqualTo _vector) then {  //-- For terrain objects that refuse to die
			_physics = createVehicle ["tsp_breach_wall", getPos _wall, [], 0, "CAN_COLLIDE"]; _physics setDir (getDir _wall); hideObjectGlobal _wall;
			(createSimpleObject [(getModelInfo _wall)#1, getPos _wall]) attachTo [_physics, [0,0,0]]; _physics setVelocity (_visual vectorModelToWorld [0,-3,-2]);
		};
	};

	{  //-- Glass
		if (getAllHitPointsDamage _x isEqualTo []) then {continue};
		[_x, (getAllHitPointsDamage _x)#1, (getAllHitPointsDamage _x)#2] params ["_house", "_selections", "_damage"];
		{  //-- For all selections
			[_x, _house modelToWorld (_house selectionPosition _x)] params ["_selection", "_selectionPos"];
			if (_selectionPos distance _pos > 7 || _damage#_forEachIndex == 1 || !("glass" in _selection || "window" in _selection)) then {continue};  //-- Skip
			[_house, [_selection, 1]] remoteExec ["setHit", 0]; playSound3D [format ["A3\Sounds_F\arsenal\sfx\bullet_hits\glass_0%1.wss", (floor random 8) + 1], _selectionPos, false, AGLtoASL _selectionPos, 3, 1, 25];
		} forEach _selections;
	} forEach (nearestObjects [getPosASL _visual, ["BUILDING", "HOUSE", "CHURCH", "CHAPEL", "BUNKER", "FORTRESS", "VIEW-TOWER", "LIGHTHOUSE", "FUELSTATION", "HOSPITAL", "TOURISM"], 20]);

	//-- Flash
	if (tsp_cba_breach_stun && _damage#2 > 0.5) then {_visual setPosASL _end; [playa, _visual, false, false, tsp_cba_flashbang_distance*0.7, 1] call tsp_fnc_flashbang};

	deleteVehicle _visual;
};

tsp_fnc_breach_pick = {
	params ["_unit", "_data", "_deleteChance", "_item", "_damage"]; _data params ["_id","_house","_door","_pos","_animName","_animPhase","_locked","_triggerName","_triggerPos","_handleName","_handlePos","_hingeName","_hingePos"];
	_effectiveness = [_house, _damage] call tsp_fnc_breach_effectiveness;    //-- Get effectiveness
	if (_unit getUnitTrait "Engineer") then {_effectiveness = _effectiveness + 0.75};  //-- This is the lock picking lawyer ~
	if (random 1 <= _deleteChance) then {_unit removeItem _item};      //-- Delete item
	[tsp_cba_breach_picking_time, [_unit, _data, _effectiveness], {  //-- ACE progress bar
		(_this#0) params ["_unit", "_data", "_effectiveness"]; _unit switchMove "AmovPknlMstpSnonWnonDnon";
		if (random 1 <= _effectiveness) then {[_data, -1, 0] call tsp_fnc_breach_adjust; ["Picking", "Success"] spawn tsp_fnc_hint} else {["Picking", "Failed"] spawn tsp_fnc_hint};	
	}, {player switchMove "AmovPknlMstpSnonWnonDnon";}, "Picking...", {if !("fixing" in animationState player) then {player disableAI "ANIM"; player playMoveNow "Acts_CarFixingWheel"}; true}] call ace_common_fnc_progressBar;
};

tsp_fnc_breach_gun = {
	params ["_unit", "_ammo"];
	(([cursorObject, "GEOM"] intersect [positionCameraToWorld [0,0,0], positionCameraToWorld [0,0,3]])#0) params ["_selection"]; if (isNil "_selection") exitWith {}; if !("door" in _selection) exitWith {};
	_effectiveness = if (_ammo in tsp_cba_breach_ammo) then {1} else {(((getNumber (configFile >> "CfgAmmo" >> _ammo >> "hit")) min 50)/50)*tsp_cba_breach_ammo_multiplier};  //-- Cap at 50 and divide by 50 to get 0-1 value	
	_data = [cursorObject, _selection] call tsp_fnc_breach_data; 
	_data params ["_id", "_house", "_door", "_pos", "_animName", "_animPhase", "_locked", "_triggerName", "_triggerPos", "_handleName", "_handlePos", "_hingeName", "_hingePos"];
	if (_locked != 3 && _animPhase == 0 && random 1 <= [cursorObject, [0,_effectiveness,_effectiveness/2,_effectiveness/10,0]] call tsp_fnc_breach_effectiveness) then {[_data, 0.2, 3] spawn tsp_fnc_breach_adjust};
};

tsp_fnc_breach_melee = {
	params ["_unit", "_environmentDamage"];	
	(([cursorObject, "GEOM"] intersect [positionCameraToWorld [0,0,0], positionCameraToWorld [0,0,3]])#0) params [["_selection", ""]]; if (isNil "_selection") exitWith {}; if !("door" in _selection) exitWith {};
	_data = [cursorObject, _selection] call tsp_fnc_breach_data; _data params ["_id","_house","_door","_pos","_animName","_animPhase","_locked","_triggerName","_triggerPos","_handleName","_handlePos","_hingeName","_hingePos"];
	_push = [_unit, _data] call tsp_fnc_breach_push;
	if (_animPhase != 0 || _locked == 3) then {[_data, if (_push) then {1} else {0}] spawn tsp_fnc_breach_adjust};
	if (_animPhase != 0 || _locked == 3) exitWith {playSound3D ["tsp_breach\snd\fail.ogg", _pos, false, _pos, 2, 1, 40]};  //-- If door is open (0.01-1: open, 0: closed) or lock broken, we just want to swing it around
	if (random 1 < [_house, _environmentDamage] call tsp_fnc_breach_effectiveness) exitWith {[_data, if (_push) then {1} else {0.15}, 3] spawn tsp_fnc_breach_adjust};
	playSound3D ["tsp_breach\snd\fail.ogg", _pos, false, _pos, 2, 1, 40];
};