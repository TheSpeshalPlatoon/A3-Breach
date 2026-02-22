class CfgPatches {class tsp_breach_volume {requiredAddons[] = {"cba_common", "tsp_breach"}; units[] = {};};};

class CfgSoundShaders {
    class GrenadeHe_closeExp_SoundShader;
    class tsp_breach_exp: GrenadeHe_closeExp_SoundShader {volume = 1;};
    class tsp_breach_exp_small: GrenadeHe_closeExp_SoundShader {volume = 1;};
    class tsp_breach_exp_triple: GrenadeHe_closeExp_SoundShader {volume = 1;};
    class tsp_breach_exp_claymore: GrenadeHe_closeExp_SoundShader {volume = 1;};
};