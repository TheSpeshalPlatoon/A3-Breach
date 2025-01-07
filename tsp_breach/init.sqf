if (!tsp_cba_breach) exitWith {};
player addEventHandler ["FiredMan", {params ["_unit", "_weapon", "_muzzle", "_mode", "_ammo"]; [_unit, _ammo] spawn tsp_fnc_breach_gun}];
["ace_interactMenuOpened", {params ["_type"]; if (tsp_cba_breach_ace && _type == 0) then {[playa] spawn tsp_fnc_breach_interact}}] call CBA_fnc_addEventHandler;
["if (['door', _this#4] call BIS_fnc_inString && tsp_cba_breach_vanilla) then {hint 'Vanilla Door Actions are Disabled'; _returnVar = true};"] spawn tsp_fnc_scroll;  //-- Vanilla actions
if (isServer && !is3DEN) then {[] call tsp_fnc_breach_lock};