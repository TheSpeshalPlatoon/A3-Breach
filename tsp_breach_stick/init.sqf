tsp_fnc_breach_stick_anim = {
	params ["_unit"]; sleep 0.01; 
	if !(ace_explosives_pfeh_running) exitWith {};
	if !("stick" in ctrlModel (uiNamespace getVariable ["ace_explosives_virtualAmmoDisplay", displayNull]  displayCtrl 800851)) exitWith {};
	_weapon = if (currentWeapon _unit == primaryWeapon _unit && primaryWeapon _unit != "") then {"rifle_"} else {""};
	[_unit, "tsp_breach_stick_wnon_in", "tsp_breach_stick_wnon_loop", "tsp_common_stop", true, true] spawn tsp_fnc_gesture_play; sleep 0.2;
	_left = createSimpleObject ["\tsp_breach_stick\stick_left.p3d", [0,0,0]]; _left attachto [_unit, [0.03,0,0.03], "leftHand", true]; [_left, [80,10,80]] call BIS_fnc_setObjectRotation;
	_right = createSimpleObject ["\tsp_breach_stick\stick_right.p3d", [0,0,0]]; _right attachto [_unit, [-0.2,-0.13,0], "rightHand", true]; [_right, [-75,0,80]] call BIS_fnc_setObjectRotation;
	waitUntil {sleep 0.1; !ace_explosives_pfeh_running || !alive _unit || !("breach_stick" in gestureState _unit)};
	[_unit] call tsp_fnc_gesture_stop; 
	{deleteVehicle _x} forEach [_left, _right];
};

["ace_interactMenuClosed", {[player] spawn tsp_fnc_breach_stick_anim}] call CBA_fnc_addEventHandler; 