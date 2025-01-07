tsp_fnc_breach_silhouette_stick = {
    params ["_unit", "_range", "_explosive", "_fuzeTime", "_triggerItem"];
    if !('silhouette' in typeOf _explosive || "door" in typeOf _explosive) exitWith {};
    _stick = 'tsp_breach_silhouette_stick' createVehicle [0,0,0]; 
    sleep (_fuzeTime-0.1); _stick attachTo [_explosive, [0, 0, -0.2]];  //-- Attach before its blown up
    [_stick, true] remoteExec ["hideObjectGlobal", 2];  //-- So that it doesnt block intersect
    sleep 0.2; 
    [_stick, false] remoteExec ["hideObjectGlobal", 2];
    detach _stick; _stick setVelocityModelSpace [0,-15,0]; _stick addTorque [0,20,0];
};

[{_this spawn tsp_fnc_breach_silhouette_stick; true}] call ace_explosives_fnc_addDetonateHandler;