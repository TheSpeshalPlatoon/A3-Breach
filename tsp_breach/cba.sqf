["tsp_cba_breach", "CHECKBOX", ["Enable Breaching", "Enable/disable door/wall breaching."],	"TSP Breach", true, true] call CBA_fnc_addSetting;
["tsp_cba_breach_auto", "SLIDER", ["Auto Fuse Time", "Time to detonation for auto fuse"], ["TSP Breach", ""], [0, 15, 5], true] call CBA_fnc_addSetting;

["tsp_cba_breach_ace", "CHECKBOX", ["Enable ACE Interaction", "Enable/disable ACE interaction on doors."], ["TSP Breach", "Interaction"], true] call CBA_fnc_addSetting;
["tsp_cba_breach_vanilla", "CHECKBOX", ["Disable Vanilla Interaction", "Enable/disable vanilla scroll wheel interaction on doors."], ["TSP Breach", "Interaction"], false] call CBA_fnc_addSetting;
["tsp_cba_breach_break", "CHECKBOX", ["Break Locks", "Enable/disable lock breaking on breach."], ["TSP Breach", "Interaction"], true] call CBA_fnc_addSetting;

["tsp_cba_breach_lock_house", "SLIDER", ["Lock Chance (House)", "Chance house will be selected to be locked."], ["TSP Breach", "Auto Locking"], [0, 1, 0.25], true] call CBA_fnc_addSetting;
["tsp_cba_breach_lock_door", "SLIDER", ["Lock Chance (Door)", "Chance door will be selected to be locked."], ["TSP Breach", "Auto Locking"], [0, 1, 0.75], true] call CBA_fnc_addSetting;
["tsp_cba_breach_lock_blacklist", "EDITBOX", ["Lock Blacklist", "Array of houses that should not be locked randomly. Use this setVariable ['breach_blacklist',true] for specific buildings."], ["TSP Breach", "Auto Locking"], '[]', true, {tsp_cba_breach_lock_blacklist = call compile tsp_cba_breach_lock_blacklist}] call CBA_fnc_addSetting;

["tsp_cba_breach_paperclip", "EDITBOX", ["Paperclip Chances", "Chances of picking doors. [Glass, Civil, Military, Reinforced]"], ["TSP Breach", "Lock Picking"], '[0,0.5,0.25,0.15]', true, {tsp_cba_breach_paperclip = call compile tsp_cba_breach_paperclip}] call CBA_fnc_addSetting;
["tsp_cba_breach_lockpick", "EDITBOX", ["Lockpick Chances", "Chances of picking doors. [Glass, Civil, Military, Reinforced]"], ["TSP Breach", "Lock Picking"], '[0,0.75,0.5,0.05]', true, {tsp_cba_breach_lockpick = call compile tsp_cba_breach_lockpick}] call CBA_fnc_addSetting;
["tsp_cba_breach_picking_time", "SLIDER", ["Picking Duration", "Duration of picking doors. There is some randomness."], ["TSP Breach", "Lock Picking"], [0, 120, 20], true] call CBA_fnc_addSetting;

["tsp_cba_breach_ammo", "EDITBOX", ["Breaching Ammo", "Array containing ammo that should be effective at opening doors, like shotgun shells."],	["TSP Breach", "Ballistic Breaching"], '[
	"B_12Gauge_Slug_NoCartridge","B_12Gauge_Pellets_Submunition",
	"rhs_ammo_12g_slug","rhs_ammo_12g_00buckshot","rhs_ammo_m576_buckshot",
	"UK3CB_BAF_B_12Gauge_Slug","UK3CB_BAF_B_12Gauge_Pellets",
	"CUP_12Gauge_Slug","CUP_B_12Gauge_Pellets","CUP_B_12Gauge_74Slug",
	"CUP_12Gauge_Pellets_Submunition_No0_Buck","CUP_12Gauge_Pellets_Submunition_No00_Buck",
	"ACE_12Gauge_Pellets_Submunition_No0_Buck","HLC_12G_Buck"
]', true, {tsp_cba_breach_ammo = call compile tsp_cba_breach_ammo}] call CBA_fnc_addSetting;
["tsp_cba_breach_ammo_multiplier", "SLIDER", ["Ammo Multiplier", "Effectiveness of non-breaching ammo multiplier."], ["TSP Breach", "Ballistic Breaching"], [0, 10, 1], true] call CBA_fnc_addSetting;

[
	"tsp_cba_breach_walls", "EDITBOX",
	["Wall Destruction Classnames", "Array containing main model and destruct model for cooler looking breaches. [p3d,type,wreck]"],
	["TSP Breach", "Classification"], '[
		["AHHH", "Land_BrickWall_04_l_5m_F","Land_BrickWall_04_l_5m_d_F"],
		["AHHH", "Land_BrickWall_03_l_5m_v2_F","Land_BrickWall_03_l_5m_v2_d_F"],
		["AHHH", "Land_BrickWall_03_l_5m_v1_F","Land_BrickWall_03_l_5m_v2_d_F"],
		["AHHH", "Land_BrickWall_02_l_5m_F","Land_BrickWall_02_l_5m_d_F"],
		["AHHH", "Land_BrickWall_01_l_5m_F","Land_BrickWall_01_l_5m_d_F"],
		["AHHH", "Land_Stone_8m_F","Land_Stone_8mD_F"],
		["AHHH", "Land_WallCity_01_8m_yellow_F","Land_WallCity_01_8m_dmg_yellow_F"],
		["AHHH", "Land_City_8m_F","Land_City_8mD_F"],
		["AHHH", "Land_WallCity_01_8m_whiteblue_F","Land_WallCity_01_8m_dmg_whiteblue_F"],
		["AHHH", "Land_WallCity_01_8m_blue_F","Land_WallCity_01_8m_dmg_blue_F"],
		["AHHH", "Land_WallCity_01_8m_grey_F","Land_WallCity_01_8m_dmg_grey_F"],
		["AHHH", "Land_WallCity_01_8m_pink_F","Land_WallCity_01_8m_dmg_pink_F"],
		["AHHH", "Land_SilageWall_01_l_5m_F","Land_SilageWall_01_l_d_F"],
		["AHHH", "Land_ConcreteWall_02_m_8m_F","Land_ConcreteWall_02_m_d_F"],
		["AHHH", "Land_ConcreteWall_01_m_4m_F","Land_ConcreteWall_01_m_d_F"],
		["AHHH", "Land_ConcreteWall_01_m_8m_F","Land_ConcreteWall_01_m_d_F"],
		["AHHH", "Land_PipeFence_01_m_8m_F","Land_PipeFence_01_m_d_F"],
		["AHHH", "Land_City2_8m_F","Land_City2_8mD_F"],
		["AHHH", "Land_Wall_IndCnc_4_F","Land_Wall_IndCnc_End_2_F"],
		["AHHH", "Land_CamoConcreteWall_01_l_4m_v1_F","Land_CamoConcreteWall_01_l_end_v1_F"],
		["AHHH", "Land_Mil_WallBig_4m_F","Land_Mil_WallBig_4m_damaged_center_F"],
		["mil_wallbig_4m_battered_f", "Land_Mil_WallBig_4m_battered_F","Land_Mil_WallBig_4m_damaged_right_F"],
		["AHHH", "Land_Mil_WallBig_Corner_F","Land_Mil_WallBig_debris_F"],
		["AHHH", "Land_Mil_WallBig_corner_battered_F","Land_Mil_WallBig_debris_F"]
	]', true, {tsp_cba_breach_walls = call compile tsp_cba_breach_walls}
] call CBA_fnc_addSetting;

[
	"tsp_cba_breach_military", "EDITBOX",
	["Military Classnames", "Array containing house classnames that should be considered when as military doors."],
	["TSP Breach", "Classification"], '[
		"Land_Budova4_in",
		"Land_Budova4",
		"Barrack2",
		"Land_Barrack2",
		"Land_MilOffices_V1_F",
		"Land_Mil_Barracks_L_EP1",
		"Land_Barrack2_EP1",
		"Land_Mil_Barracks_EP1",
		"Land_Mil_Barracks_no_interior_EP1_CUP",
		"Land_Mil_Barracks_i_EP1",
		"Land_Mil_Barracks_L",
		"Land_Mil_Barracks_no_interior_CUP",
		"Land_Mil_Barracks_i",
		"Land_Mil_Barracks",
		"Land_GuardHouse_02_F",
		"Land_Mil_Guardhouse_EP1",
		"Land_Mil_Guardhouse",
		"Land_Mil_Guardhouse_no_interior_CUP",
		"Land_GuardHouse_02_grey_F",
		"Land_Barracks_03_F",
		"Land_Barracks_05_F",
		"Land_Barracks_02_F",
		"Land_Barracks_04_F",
		"Land_ControlTower_02_F",
		"Land_Mil_Guardhouse_no_interior_EP1_CUP",
		"Land_Radar_01_HQ_F",
		"Land_i_Barracks_V2_F",
		"Land_i_Barracks_V1_F",
		"Land_u_Barracks_V2_F",
		"Land_Barracks_06_F",
		"Land_Mil_House_dam_EP1",
		"Land_Barracks_01_grey_F",
		"Land_Barracks_01_dilapidated_F",
		"Land_Mil_House_EP1",
		"Land_Army_hut2_int",
		"Land_Barracks_01_camo_F",
		"Land_Army_hut_int",
		"Land_Army_hut3_long",
		"Land_Army_hut2",
		"Land_Army_hut3_long_int"
	]', true, {tsp_cba_breach_military = call compile tsp_cba_breach_military}
] call CBA_fnc_addSetting;

[
	"tsp_cba_breach_reinforced", "EDITBOX",
	["Reinforced Classnames", "Array containing house classnames that should be considered when as reinforced doors."],
	["TSP Breach", "Classification"], '[
		"Land_Ammostore2",
		"Land_Garaz_s_tankem",
		"Land_Garaz_bez_tanku",
		"Land_Cargo_House_V4_F",
		"Land_Cargo_Tower_V1_F",
		"Land_Cargo_HQ_V4_F",
		"Land_Cargo_Tower_V1_No4_F",
		"Land_Cargo_Tower_V1_No5_F",
		"Land_Cargo_Tower_V1_No7_F",
		"Land_Cargo_Tower_V4_F",
		"Land_Cargo_Tower_V1_No2_F",
		"Land_Cargo_Tower_V2_F",
		"Land_Cargo_Tower_V3_F",
		"Land_Cargo_Tower_V1_No1_F",
		"Land_Cargo_Tower_V1_No3_F",
		"Land_Cargo_HQ_V2_F",
		"Land_Medevac_HQ_V1_F",
		"Land_Cargo_HQ_V1_F",
		"Land_Cargo_House_V2_F",
		"Land_Medevac_house_V1_F",
		"Land_Cargo_Tower_V1_No6_F",
		"Land_Cargo_House_V1_F",
		"Land_Cargo_HQ_V3_F",
		"Land_Cargo_House_V3_F"
	]', true, {tsp_cba_breach_reinforced = call compile tsp_cba_breach_reinforced}
] call CBA_fnc_addSetting;