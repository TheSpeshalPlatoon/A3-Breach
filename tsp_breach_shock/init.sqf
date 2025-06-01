tsp_fnc_breach_shock_wire = {
	params ["_unit", "_explosive", "_magazine", "_fuzeTime", "_triggerItem", "_length"];
	if (!isNil "tsp_fnc_animate_clacker") then {[_unit, "", "tsp_animate_shock_loop_wnon", "\tsp_breach_shock\shock.p3d", "leftHand", [0.02,0,0], [0,0,-100], {!("shock" in gestureState playa)}, false] spawn tsp_fnc_gesture_item};
	_helper_ammo = "tsp_shock_helper" createVehicle [0,0,0]; _helper_ammo enableSimulation false; _helper_ammo allowDamage false; 
	if ("attach" in (_explosive selectionNames "MEMORY")) then {_helper_ammo attachTo [_explosive, [0,0,0], "attach"]} else {_helper_ammo attachTo [_explosive, [0,0,0]]}; detach _helper_ammo;
	_helper_unit = "tsp_shock_helper" createVehicle [0,0,0]; _helper_unit allowDamage false; _helper_unit setPos (getPos _unit);
	_helper_unit setVariable ["rope", ropeCreate [_helper_unit, [0,0,0], _helper_ammo, [0,0,0], _length, ["", [0,0,-1]], ["", [0,0,-1]], "shock_wire"], true];
	while {sleep 0.1; alive _unit && _explosive isNotEqualTo objNull} do {
		if ("shock_out" in gestureState _unit) exitWith {detach _helper_unit};
		if (_unit distance _explosive < (_length-3) && isNull attachedTo _helper_unit) then {_helper_unit attachTo [_unit, [0,0,0], "leftHand"]};
		if (_unit distance _explosive > (_length-2) && !isNull attachedTo _helper_unit) then {detach _helper_unit};
	}; 
	waitUntil {!alive _unit || _explosive isEqualTo objNull};
	_helper_ammo enableSimulation true; _helper_ammo setVelocityModelSpace [0,-3,0]; detach _helper_unit;
	sleep tsp_cba_breach_shock; {deleteVehicle _x} forEach [_helper_ammo, _helper_unit]; 
};

tsp_fnc_breach_shock_wave = {
	params ["_unit", "_explosive", "_magazine", "_fuzeTime", "_triggerItem", ["_helpers", attachedObjects (_this#0) select {typeOf _x == "tsp_shock_helper"}]];
	if (count _helpers == 0) exitWith {}; _rope = (_helpers#0) getVariable "rope";
	_source = "Land_HelipadEmpty_F" createVehicle [0,0,0]; 
	_source say3D "tsp_breach_fuse";
	{
		if (_forEachIndex % 2 == 0) then {continue}; 
		_source setPosASL (getPosASL _x);
		_light = "#lightpoint" createVehicle (getPos _x);
		_light setLightColor [1,0.7,0.7]; 
		_light setLightAmbient [1,0.7,0.7]; 
		_light setLightBrightness 0.05; 
		_light setLightDayLight true;
		_light setLightUseFlare true; 
		_light setLightFlareSize 10; 
		_light setLightFlareMaxDistance 5;
		_light spawn {sleep 0.1; deleteVehicle _this}; 
		sleep 0.01;
	} forEach ropeSegments _rope;
	sleep 0.1; deleteVehicle _source;
};

waitUntil {sleep 5; !(isNull (findDisplay 46))};  //-- Idk why this is needed but it is
[{_this remoteExec ["tsp_fnc_breach_shock_wave", 0]; true}] call ace_explosives_fnc_addDetonateHandler;