tsp_fnc_flashbang = {
	params ["_thrower", "_flash", ["_smoke", true], ["_effects", true], ["_distance", tsp_cba_flashbang_distance], ["_volume", tsp_cba_flashbang_volume], ["_sound", "tsp_flashbang\snd\bang.ogg"]];
	_flash addTorque [(random 20)-10, (random 20)-10, (random 20)-10]; _flash setVelocityModelSpace [(random 8)-4, (random 8)-4, random 4];  //-- Fly
	[_flash, _smoke, _effects, _effects, _effects] remoteExec ["tsp_fnc_flashbang_effects", 0];  //-- Global effects
	playSound3D [_sound, _flash, false, getPosASL _flash, _volume, (random 1) min 1.3 max 0.7, 250];  //-- Sound
	{  //-- Victims
		_amount = (1-((_x distance _flash)/_distance))*tsp_cba_flashbang_intensity;         //-- Calculate _amount based on distance from flash (0-1)
		if (side _x == side _thrower) then {_amount = _amount*tsp_cba_flashbang_friends};  //-- Reduce effects for friends
		[_x, _amount] remoteExec [if (isPlayer _x) then {"tsp_fnc_flashbang_player"} else {"tsp_fnc_flashbang_ai"}, _x];
	} forEach (allUnits select {(_x distance _flash < _distance/10) || (_x distance _flash < _distance && [_flash, "VIEW"] checkVisibility [eyePos _x, eyePos _flash] > 0)});
};

tsp_fnc_flashbang_effects = {  //-- Particle effects, global
	params ["_flash", ["_smokeFX", true], ["_sparksFX", true], ["_fireFX", true], ["_lightFX", true]];
	_smoke = "#particleSource" createVehicleLocal [0,0,0]; if (tsp_cba_flashbang_smoke && _smokeFX) then {_smoke attachto [_flash, [0,0,0]]}; _smoke setParticleClass "ScudSmoke2";  //-- Smoke
	_sparks = "#particleSource" createVehicleLocal [0,0,0];	if (tsp_cba_flashbang_sparks && _sparksFX) then {_sparks attachto [_flash, [0,0,0]]}; _sparks setParticleClass "FireSparksSmall";    //-- Sparks    
	_fire = "#particleSource" createVehicleLocal [0,0,0]; if (tsp_cba_flashbang_fire && _fireFX) then {_fire attachto [_flash, [0,0,0]]}; _fire setParticleClass "ScudFire";                    //-- Fire   	
	_light = "#lightpoint" createVehicleLocal (getPos _flash); _light setLightColor [1,0.8,0.5]; _light setLightAmbient [1,0.8,0.5];
	_light setLightUseFlare true; _light setLightFlareSize tsp_cba_flashbang_brightness; _light setLightFlareMaxDistance tsp_cba_flashbang_brightness;
	if (_lightFX) then {_light setLightBrightness tsp_cba_flashbang_brightness; _light setLightDayLight true};
	sleep 0.1; deleteVehicle _sparks; sleep 0.1; deleteVehicle _fire; deleteVehicle _light; sleep 0.1; deleteVehicle _smoke;
};

tsp_fnc_flashbang_player = {  //-- Screen effects
	params ["_unit", "_amount", ["_volume", soundVolume]];
	if (_unit getVariable ["flashed", false]) exitWith {}; _unit setVariable ["flashed", true];	
	_blur = ppEffectCreate ["DynamicBlur", 600]; _blur ppEffectEnable true; _blur ppEffectAdjust [50*_amount]; _blur ppEffectCommit 0.1;
	if (_volume == 1) then {0.1 fadeSound (1-_amount); sleep 0.1; (5*_amount) fadeSound _volume};
	sleep 0.1; _blur ppEffectAdjust [0]; _blur ppEffectCommit (8*_amount);
	_unit setVariable ["flashed", false];
};

tsp_fnc_flashbang_ai = {
	params ["_unit", "_amount"];

	if (_unit getVariable ["flashed", false] || _unit getVariable ["ACE_isUnconscious", false]) exitWith {}; _unit setVariable ["flashed", true];
	_unit disableAI "ANIM"; _unit disableAI "MOVE";	_unit setMimic (selectRandom ["dead", "unconscious"]);

	if (random 1 < tsp_cba_flashbang_spray) then {_unit spawn {for "_i" from 1 to (round (random 10)) do {_this forceWeaponFire [currentWeapon _this, "Single"]; sleep ((random 1) max 0.2)}}};

	switch true do {
		case (random 1 < tsp_cba_flashbang_surrender): {[_unit, true] call ACE_captives_fnc_setSurrendered; sleep 0.5; [_unit, currentWeapon _unit] call tsp_fnc_throw};  //-- Surrender
		case (currentWeapon _unit == ""): {_unit playMoveNow "ApanPknlMstpSnonWnonDnon"};  //-- Unarmed
		case (currentWeapon _unit == handgunWeapon _unit): {_unit playMoveNow (selectRandom ["Acts_Flashes_Recovery_1", "Acts_Flashes_Recovery_2"])};  //-- Pistol
		case (currentWeapon _unit == primaryWeapon _unit): {_unit playMoveNow (selectRandom ["Acts_Shocked_1_Loop", "Acts_Shocked_3", "Acts_Shocked_4_Loop", "Acts_Ambient_Rifle_Drop"]); sleep (_amount*5); if (alive _unit) then {_unit playMoveNow "amovpercmstpsraswrfldnon"}};  //-- Rifle
	};

	_unit enableAI "ANIM"; _unit enableAI "MOVE"; _unit setMimic "default";	sleep 3; _unit setVariable ["flashed", false];
};

//case (currentWeapon _unit == ""): {_unit playMoveNow "ApanPknlMstpSnonWnonDnon"};  //-- Unarmed
//case (currentWeapon _unit == primaryWeapon _unit && _amount > 0.9): {_unit playMoveNow "Acts_Stunned_Unconscious"; sleep 5};  //-- Rifle super