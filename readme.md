[Licensing, bug reporting and contact information.](https://github.com/TheSpeshalPlatoon) 

This addon relies on components from tsp_core which can be found in the [Core Repository](https://github.com/TheSpeshalPlatoon/A3-Core).

[<img style="width:15px" src="https://core.thespeshalplatoon.com/img/steam_small.png"> Breach](https://steamcommunity.com/sharedfiles/filedetails/?id=3283645995)  

## 📕 Content
This mod adds various door/wall breaching to the game as well as flashbangs.
- Shock Tube Detonator
- Flashbangs (Fakel, M84, M84S, 9-Bang, 2-Bang)
- Lock Picking (Lock Pick Kit, Paperclips)
- Breaching with Melee (Kicking, Sledge, etc - Requires [Melee](https://steamcommunity.com/sharedfiles/filedetails/?id=3283652320))
- Breaching with Firearms (All weapons, configured to use prefer slugs from RHS by default)
- Automatic Door Locking (Configurable in CBA Settings)
- Door Interactions with ACE Menu (Locking/Unlocking/Knocking)
- Door Tiers based on Structure class (Civilian, Military, Reinforced)
- Breaching Charges (Smallest to Largest)  
↳ Lock Popper (Auto Fuse, Rated for: Civilian Doors) 
↳ Dip Charge (Auto Fuse, Rated for: Military Doors)   
↳ Block Charge (Auto Fuse, Rated for: Military Doors)  
↳ Linear Charge (Rated for: Reinforced Doors)  
↳ Stick Charge (Rated for: Reinforced Doors, has Custom Equip Animation)  
↳ Packaged Charge (Auto Fuse, Rated for: Reinforced Doors & Walls)  
↳ Silhouette Charge (Rated for: Reinforced Doors & Walls)

## 🔥 Compatibility
✔️ If loaded with [Melee](https://steamcommunity.com/sharedfiles/filedetails/?id=3283652320), you will be able to breach doors using melee weapons or kicking.  
✔️ [PHEN Door kick!](https://steamcommunity.com/sharedfiles/filedetails/?id=3284809188) adds compatibility with [Improved Melee System](https://steamcommunity.com/sharedfiles/filedetails/?id=2291129343).  
✔️ Works with [CUP Terrains](https://steamcommunity.com/workshop/filedetails/?id=583496184) buildings.  
⚠️ Tested with [MBG Killhouses](https://steamcommunity.com/workshop/filedetails/?id=962938144), works but doors cannot be locked.  
⚠️ Tested with [JBAD](https://steamcommunity.com/workshop/filedetails/?id=520618345) buildings, works but most doors cannot be locked.  
❌ Likely not compatible with other mods that have similar features.  
❌ Not compatible with older versions of this mod.  

## 📝 Scriptadoodle
```cpp
_house setVariable ["bis_disabled_Door_1", 1, true];  //-- Lock door 1
_house setVariable ["unbreachable_1", true, true];  //-- Make door 1 unbreachable

//-- Disable different actions on a house
_house setVariable ["breach_blacklist_explosive", true];
_house setVariable ["breach_blacklist_melee", true];
_house setVariable ["breach_blacklist_pick", true];
_house setVariable ["breach_blacklist_gun", true]; 
_house setVariable ["breach_blacklist_lock", true];
```