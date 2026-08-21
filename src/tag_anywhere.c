#include "modding.h"
#include "ultra64.h"

typedef struct floatPos
{
	/* 0x000 */ f32 xPos;
	/* 0x004 */ f32 yPos;
	/* 0x008 */ f32 zPos;
} floatPos;

typedef struct actorData
{
	/* 0x000 */ s8 unk_00[0x58];
	/* 0x058 */ s32 actorType;
	/* 0x05C */ s8 unk_5C[0x7C - 0x5C];
	/* 0x07C */ f32 xPos;
	/* 0x080 */ f32 yPos;
	/* 0x084 */ f32 zPos;
	/* 0x088 */ s8 unk_80[0xB8 - 0x88];
	/* 0x0B8 */ f32 hSpeed;
	/* 0x0BC */ s8 unk_BC[0x154 - 0xBC];
	/* 0x154 */ s8 control_state;
	/* 0x155 */ s8 control_state_progress;
	/* 0x156 */ s8 unk_156[0x180 - 0x156];
	/* 0x180 */ void *tied_character_spawner;
} actorData;

typedef struct cameraData
{
	/* 0x000 */ s8 unk_00[0x7C];
	/* 0x07C */ f32 xPos;
	/* 0x080 */ f32 yPos;
	/* 0x084 */ f32 zPos;
	/* 0x088 */ s8 unk_88[0x15F - 0x88];
	/* 0x15F */ s8 facing_angle;
	/* 0x160 */ s8 unk_160[0x1FC - 0x160];
	/* 0x1FC */ f32 viewportX;
	/* 0x200 */ f32 viewportY;
	/* 0x204 */ f32 viewportZ;
	/* 0x208 */ s8 unk_208[0x22A - 0x208];
	/* 0x22A */ s16 viewportRotation;
	/* 0x22C */ s8 unk_22C[0x26B - 0x22C];
	/* 0x26B */ s8 camera_state;
} cameraData;

typedef struct bone_array
{
	/* 0x000 */ s8 unk_00[0x58];
	/* 0x058 */ s16 xPos;
	/* 0x05A */ s16 yPos;
	/* 0x05C */ s16 zPos;
} bone_array;

typedef struct rendering_params
{
	/* 0x000 */ s8 unk_00[0x14];
	/* 0x014 */ bone_array *bone_array1;
	/* 0x018 */ bone_array *bone_array2;
} rendering_params;

typedef struct playerData
{
	/* 0x000 */ s8 unk_00[0x4];
	/* 0x004 */ rendering_params *rendering_param_pointer;
	/* 0x008 */ s8 unk_08[0x58 - 0x8];
	/* 0x058 */ s32 characterID; // 02 is dk, 03 is diddy, 04 is lanky, etc
	/* 0x05C */ s8 unk_5C[0x60 - 0x5C];
	/* 0x060 */ s32 obj_props_bitfield;
	/* 0x064 */ s8 unk_64[0x6A - 0x64];
	/* 0x06A */ s16 grounded_bitfield;
	/* 0x06C */ s16 unk_bitfield;
	/* 0x06E */ s8 unk_6E[0x7C - 0x6E];
	/* 0x07C */ f32 xPos;
	/* 0x080 */ f32 yPos;
	/* 0x084 */ f32 zPos;
	/* 0x088 */ s8 unk_88[0xA4 - 0x88];
	/* 0x0A4 */ f32 floor;
	/* 0x0A8 */ s8 unk_A8[0xB8 - 0xA8];
	/* 0x0B8 */ f32 hSpeed;
	/* 0x0BC */ s8 unk_BC[0x4];
	/* 0x0C0 */ f32 yVelocity;
	/* 0x0C4 */ f32 yAccel;
	/* 0x0C8 */ s8 unk_C4[0xE6 - 0xC8];
	/* 0x0E6 */ s16 facing_angle;
	/* 0x0E8 */ s16 skew_angle;
	/* 0x0EA */ s8 unk_EA[0xEE - 0xEA];
	/* 0x0EE */ s16 next_facing_angle;
	/* 0x0F0 */ s8 unk_F0[0x110 - 0xF0];
	/* 0x110 */ s8 touching_object;
	/* 0x111 */ s8 unk_111[0x128 - 0x111];
	/* 0x128 */ s16 strong_kong_value;
	/* 0x12A */ s8 unk_12A[2];
	/* 0x12C */ s16 chunk;
	/* 0x12E */ s8 unk_12E[0x13C - 0x12E];
	/* 0x13C */ void *collision_queue_pointer;
	/* 0x140 */ s8 unk_140[0x147 - 0x140];
	/* 0x147 */ s8 hand_state;
	/* 0x148 */ s8 unk_148[0x154 - 0x148];
	/* 0x154 */ s8 control_state;
	/* 0x155 */ s8 control_state_progress;
	/* 0x156 */ s8 unk_156[0x18A - 0x156];
	/* 0x18A */ s16 moving_angle;
	/* 0x18C */ s8 unk_18C[0x1B8 - 0x18C];
	/* 0x1B8 */ f32 velocity_cap;
	/* 0x1BC */ s8 unk_1BC[0x1D0 - 0x1BC];
	/* 0x1D0 */ s16 ostand_value;
	/* 0x1D2 */ s8 unk_1D2[0x208 - 0x1D2];
	/* 0x208 */ actorData *vehicle_actor_pointer;
	/* 0x20C */ s8 was_gun_out;
	/* 0x20D */ s8 unk_20D[0x23C - 0x20D];
	/* 0x23C */ s16 unk_rocketbarrel_value1;
	/* 0x23E */ s16 unk_rocketbarrel_value2;
	/* 0x240 */ s8 unk_240[0x284 - 0x240];
	/* 0x284 */ cameraData *camera_pointer;
	/* 0x288 */ s8 unk_288[0x323 - 0x288];
	/* 0x323 */ s8 unk_rocketbarrel_value3;
	/* 0x324 */ s8 unk_324[0x328 - 0x324];
	/* 0x328 */ actorData *krool_timer_pointer;
	/* 0x32C */ actorData *held_actor;
	/* 0x330 */ s8 unk_330[0x36F - 0x330];
	/* 0x36F */ s8 new_kong;
	/* 0x370 */ s32 strong_kong_ostand_bitfield;
} playerData; // size 0x630

typedef struct TextOverlay
{
	/* 0x000 */ s8 unk_00[0x84];
	/* 0x004 */ // u16
	/* 0x006 */ // u16
	/* 0x008 */ // u8
	/* 0x009 */ // u8
	/* 0x054 */ // layer ID?
	/* 0x084 */ f32 style;
	/* 0x088 */ s8 unk_88[0x15F - 0x88];
	/* 0x15F */ s8 opacity;
	/* 0x160 */ s8 unk_160[0x0A];
	/* 0x16A */ u8 red;
	/* 0x16B */ u8 green;
	/* 0x16C */ u8 blue;
	/* 0x16D */ s8 unk_16D[0x0B];
	/* 0x178 */ char *string;
} TextOverlay;

typedef struct Screen
{
	/* 0x000 */ void *TextArray;
	/* 0x004 */ const int *FunctionArray;
	/* 0x005 */ s8 ArrayItems;
	/* 0x006 */ s8 ParentScreen;
	/* 0x007 */ s8 ParentPosition;
} Screen;

typedef const struct MapWarp
{
	/* 0x000 */ const u8 *maps;
	/* 0x004 */ const u8 *exits;
	/* 0x008 */ s8 screen;
} MapWarp;

typedef struct Controller
{
	/* 0x000 */ s16 Buttons;
	/* 0x002 */ s8 stickX;
	/* 0x003 */ s8 stickY;
} Controller;

typedef struct InventoryBase
{
	/* 0x000 */ s16 StandardAmmo;
	/* 0x002 */ s16 HomingAmmo;
	/* 0x004 */ s16 Oranges;
	/* 0x006 */ s16 Crystals;
	/* 0x008 */ s16 Film;
	/* 0x00A */ s8 unk0A;
	/* 0x00B */ s8 Health;
	/* 0x00C */ s8 Melons;
} InventoryBase;

typedef struct PosState
{
	/* 0x000 */ f32 xCamera;
	/* 0x004 */ f32 yCamera;
	/* 0x008 */ f32 zCamera;
	/* 0x00C */ f32 yVelocity;
	/* 0x010 */ f32 yAccel;
	/* 0x014 */ f32 hVelocity;
	/* 0x018 */ f32 yFloor;
	/* 0x01C */ s16 xStored1;
	/* 0x01E */ s16 yStored1;
	/* 0x020 */ s16 zStored1;
	/* 0x022 */ s16 xStored2;
	/* 0x024 */ s16 yStored2;
	/* 0x026 */ s16 zStored2;
	/* 0x028 */ s16 facing_angle;
	/* 0x02A */ s16 skew_angle;
	/* 0x02C */ f32 xPos;
	/* 0x030 */ f32 yPos;
	/* 0x034 */ f32 zPos;
	/* 0x038 */ s8 control_state;
	/* 0x039 */ s8 control_state_progress;
	/* 0x03A */ s8 map;
	/* 0x03B */ s8 bone_array_counter;
	/* 0x03C */ s16 cameraRotation;
	/* 0x03E */ s8 cameraState;
} PosState;

typedef struct TimerInfo
{
	/* 0x000 */ u32 Start;
	/* 0x004 */ u32 Timer;
	/* 0x008 */ s8 Mode;
	/* 0x009 */ s8 StartMode;
	/* 0x00A */ s8 PauseMode;
	/* 0x00B */ s8 FinishMode;
	/* 0x00C */ u32 Reduction;
	/* 0x010 */ u32 TimerPostReduction;
} TimerInfo;

typedef struct AutowalkData
{
	/* 0x000 */ s8 unk_00[0x12];
	/* 0x012 */ s16 xPos;
	/* 0x014 */ s8 unk_14[0x2];
	/* 0x016 */ s16 zPos;
} AutowalkData;

typedef struct RGB
{
	/* 0x000 */ u8 red;
	/* 0x001 */ u8 green;
	/* 0x002 */ u8 blue;
} RGB;

typedef struct KongBase
{
	/* 0x000 */ s8 special_moves;
	/* 0x001 */ s8 simian_slam;
	/* 0x002 */ s8 weapon_bitfield;
	/* 0x003 */ s8 ammo_belt;
	/* 0x004 */ s8 instrument_bitfield;
	/* 0x005 */ s8 unk_05[0x2];
	/* 0x007 */ s8 coins;
	/* 0x008 */ s16 instrument_energy;
	/* 0x00A */ s16 cb_count[0xE];
	/* 0x026 */ s16 tns_cb_count[0xE];
	/* 0x042 */ s16 gb_count[0xE];
} KongBase;

typedef struct ISGFadeoutData
{
	/* 0x000 */ s32 FadeoutTime;
	/* 0x004 */ s8 FadeoutMap;
	/* 0x005 */ s8 unk_05[0x3];
} ISGFadeoutData;

typedef struct GiantKoshaData
{
	/* 0x000 */ s16 timer;
} GiantKoshaData;

typedef struct SwapObjectData
{
	/* 0x000 */ s8 unk_00[0x210];
	/* 0x210 */ floatPos cameraPositions[4];
	/* 0x240 */ s8 unk_21C[0x29C - 0x240];
	/* 0x29C */ s16 action_type;
	/* 0x29E */ s8 unk_29E[0x2C0 - 0x29E];
	/* 0x2C0 */ s8 size; // 0 = Mini Monkey, 1 = normal, 2 = Hunky Chunky
} SwapObjectData;

typedef struct sandstormData
{
	/* 0x000 */ s8 unk_00[0x54];
	/* 0x054 */ s8 sandstorm_active;
} sandstormData;

typedef struct snagData
{
	/* 0x000 */ s8 unk_00[0x48];
	/* 0x048 */ s8 reset;
	/* 0x049 */ s8 unk_49[0x54 - 0x49];
	/* 0x054 */ s8 check;
	/* 0x055 */ s8 unk_55[0x60 - 0x55];
	/* 0x060 */ s8 state;
	/* 0x061 */ s8 unk_61[0x9B - 0x61];
	/* 0x09B */ s8 resettrigger;
} snagData;

typedef struct ModelTwoData
{
	/* 0x000 */ s8 unk_00[0x7C];
	/* 0x07C */ void *behaviour_pointer;
	/* 0x080 */ s8 unk_80[0x84 - 0x80];
	/* 0x084 */ s16 object_type;
	/* 0x086 */ s8 unk_86[0x4];
	/* 0x08A */ s16 object_id;
	/* 0x08C */ s8 unk_8C[0x4];
} ModelTwoData;

typedef struct WarpInfo
{
	/* 0x000 */ s16 xPos;
	/* 0x002 */ s16 yPos;
	/* 0x004 */ s16 zPos;
	/* 0x006 */ u8 facing_angle; // (val / 255) * 4096
	/* 0x007 */ u8 camera_angle; // (player + 0x284)->0x15F
	/* 0x008 */ s8 will_autowalk;
	/* 0x009 */ s8 spawn_at_origin;
} WarpInfo;

typedef struct flagMenuData
{
	/* 0x000 */ const short *flagArray;
	/* 0x004 */ const char *flagTypeArray;
	/* 0x008 */ const int *flagText;
	/* 0x00C */ s8 screenIndex;
	/* 0x00D */ s8 flagCount;
} flagMenuData;

typedef struct cutsceneInfo
{
	/* 0x000 */ s8 csdata[0xC];
} cutsceneInfo;

typedef struct cutsceneType
{
	/* 0x000 */ s8 unk_00[0xD0];
	/* 0x0D0 */ cutsceneInfo *cutscene_databank;
} cutsceneType;

typedef struct spriteDisplay
{
	/* 0x000 */ s32 disappear;
	/* 0x004 */ s8 unk_04[0x11];
	/* 0x015 */ s8 unk_15;
} spriteDisplay;

typedef struct spriteControl
{
	/* 0x000 */ f32 movement_style;
	/* 0x004 */ f32 pointer_offset_0x15;
	/* 0x008 */ f32 xPos;
	/* 0x00C */ f32 yPos;
	/* 0x010 */ f32 scale;
	/* 0x014 */ f32 unk_14;
	/* 0x018 */ s32 unk_18;
	/* 0x01C */ s32 unk_1C;
} spriteControl;

typedef struct otherSpriteControl
{
	/* 0x000 */ s8 unk_000[0x28];
	/* 0x028 */ u8 left_stretch;
	/* 0x029 */ u8 right_stretch;
	/* 0x02A */ u8 up_stretch;
	/* 0x02B */ u8 down_stretch;
	/* 0x02C */ s8 unk_02C[0x340 - 0x2C];
	/* 0x340 */ f32 xPos;
	/* 0x344 */ f32 yPos;
	/* 0x348 */ s8 unk_348[8];
	/* 0x350 */ s8 gif_update_frequency;
	/* 0x351 */ s8 unk_351[0xB];
	/* 0x35C */ spriteControl *gif_control_pointer;
	/* 0x360 */ f32 xScale;
	/* 0x364 */ f32 yScale;
	/* 0x368 */ s8 unk_368[0x2];
	/* 0x36A */ s8 transparency1;
	/* 0x36B */ s8 transparency2;
	/* 0x36C */ s8 transparency3;
	/* 0x36D */ s8 transparency4;
	/* 0x36E */ s8 unk_36E[0x384 - 0x36E];
	/* 0x384 */ void *some_pointer;
} otherSpriteControl;

typedef struct submapInfo
{
	/* 0x000 */ s8 in_submap;
	/* 0x001 */ s8 unk_01;
	/* 0x003 */ s16 transition_properties_bitfield;
	/* 0x004 */ s8 unk_04[0x12 - 4];
	/* 0x012 */ s16 parent_map;
	/* 0x014 */ s8 parent_exit;
} submapInfo;

typedef struct MinigameController
{
	/* 0x000 */ s8 unk_00[0x1C5];
	/* 0X000 */ s8 hit_count;
} MinigameController;

typedef struct SpawnerInfo
{
	/* 0x000 */ u8 enemy_value;
	/* 0x001 */ s8 unk_01[0x14 - 0x1];
	/* 0x014 */ s8 respawnTimerInit;
	/* 0x015 */ s8 unk_15[0x18 - 0x15];
	/* 0x018 */ void *tied_actor;
	/* 0x01C */ s8 unk_1C[0x42 - 0x1C];
	/* 0x042 */ s8 spawn_state;
	/* 0x043 */ s8 unk_43[0x48 - 0x43];
} SpawnerInfo;

typedef struct pppanicController
{
	/* 0x000 */ s8 unk_00[0x1B1];
	/* 0x1B1 */ s8 hit_count1;
	/* 0x1B2 */ s8 unk_1B2;
	/* 0x1B3 */ s8 hit_count2;
} pppanicController;

typedef struct krazykkcontroller
{
	/* 0x000 */ s8 unk_00[0x1BD];
	/* 0x1BD */ s8 hit_count1;
	/* 0x1BE */ s8 unk_1BE;
	/* 0x1BF */ s8 hit_count2;
} krazykkcontroller;

typedef struct slotArray
{
	/* 0x000 */ s8 unk_10[0x16];
	/* 0x016 */ s16 hit_count;
} slotArray;

typedef struct bbbanditcontroller
{
	/* 0x000 */ s8 unk_00[0x11C];
	/* 0x11C */ actorData *slot_pointer;
	/* 0x120 */ s8 unk_120[0x154 - 0x120];
	/* 0x154 */ s8 control_state;
	/* 0x155 */ s8 unk_155[0x174 - 0x155];
	/* 0x174 */ slotArray *handle_pointer;
} bbbanditcontroller;

typedef struct bbbashcontroller
{
	/* 0x000 */ s8 unk_00[0x1A1];
	/* 0x1A1 */ s8 hit_count;
} bbbashcontroller;

typedef struct kkoshcontroller
{
	/* 0x000 */ s8 unk_00[0x1CB];
	/* 0x1CB */ s8 hit_count;
} kkoshcontroller;

typedef struct sseekcontroller
{
	/* 0x000 */ s8 unk_00[0x19F];
	/* 0x19F */ s8 hit_count;
} sseekcontroller;

typedef struct SpawnerArray
{
	/* 0x000 */ SpawnerInfo SpawnerData[120];
} SpawnerArray;

typedef struct SpawnerMasterInfo
{
	/* 0x000 */ s16 count;
	/* 0x002 */ s8 unk_02[2];
	/* 0x004 */ SpawnerArray *array;
} SpawnerMasterInfo;

typedef struct filestateInfo
{
	/* 0x000 */ s8 perm_flags[0x140];
	/* 0x140 */ s8 moves_base[0x1E0];
	/* 0x320 */ s8 inventory[0x10];
	/* 0x330 */ s8 temp_flags[0x10];
} filestateInfo;

typedef struct loadedActorArr
{
	/* 0x000 */ actorData *actor;
	/* 0x004 */ s32 unk_04;
} loadedActorArr;

typedef struct actorSpawnerData
{
	/* 0x000 */ s8 unk_00[4];
	/* 0x004 */ floatPos positions;
	/* 0x010 */ s8 unk_10[0x44 - 0x10];
	/* 0x044 */ void *tied_actor;
	/* 0x048 */ s8 unk_48[0x5A - 0x58];
	/* 0x05A */ s16 id;
	/* 0x05C */ s8 unk_5C[0x64 - 0x5C];
	/* 0x064 */ void *previous_spawner;
	/* 0x068 */ void *next_spawner;
} actorSpawnerData;

/*
// TODO: This needs to be a char, not an int
enum HUDState {
	Invisible,
	Appearing,
	Visible,
	Disappearing,
};
*/

typedef struct HUDDisplay
{
	/* 0x000 */ void *actual_count_pointer;
	/* 0x004 */ s16 hud_count;
	/* 0x006 */ s8 freeze_timer;
	/* 0x007 */ s8 counter_timer;
	/* 0x008 */ u32 screen_x;
	/* 0x00C */ u32 screen_y;
	/* 0x010 */ s8 unk_10[0x20 - 0x10];
	/* 0x020 */ u32 hud_state;
	/* 0x024 */ s32 unk_24;
	/* 0x028 */ void *counter_pointer;
	/* 0x02C */ s32 unk_2c;
} HUDDisplay;

// Functions
extern void setFlag(s32 flagIndex, s32 value, s8 flagType);
extern s32 isFlagSet(s32 flagIndex, s8 flagType);
extern void *dk_malloc(s32 size);
extern void dk_free(void *mallocPtr);
extern void playSound(s16 soundIndex, s32 volume, f32 unk1, f32 pitch, s32 unk3, s32 unk4);
extern void initiateTransition(s32 map, s32 exit);
extern s32 *getFlagBlockAddress(s8 flagType);
extern s32 isAddressActor(void *address);
extern s32 getTimestamp();
extern void dmaFileTransfer(s32 romStart, s32 romEnd, s32 ramStart);
extern void deleteActor(void *actor);
extern s32 spawnActor(s32 actorID, s32 actorBehaviour);
extern void spawnTextOverlay(s32 style, s32 x, s32 y, s8 *string, s32 timer1, s32 timer2, u8 effect, u8 speed);
extern f32 dk_sqrt(f32 __x);
extern void dk_strFormat(s8 *destination, s8 *source, ...);
extern void dk_multiply(f64 val1, f64 val2, s32 unk1, s32 unk2);
extern f64 convertTimestamp(f64 unk0, f64 unk1, u32 unk2, u32 unk3);
extern void resetMap();
extern void prepKongColoring();
extern void *dk_memcpy(void *_dest, void *_src, s32 size);
extern void SaveToGlobal();
extern s32 DetectGameOver();
extern s32 DetectAdventure();
extern void displaySprite(void *control_pointer, void *sprite, s32 x, s32 y, s32 scale, s32 gif_updatefrequency, s32 movement_style);
extern void alterSize(void *object, s32 size);
extern void unkSizeFunction(void *object);
extern void spawnRocketbarrel(void *object, s32 unk);
extern void playSong(s32 songIndex);
extern void playCutscene(void *actor, s32 cutscene_index, s32 cutscene_type);
extern void setHUDItemAsInfinite(s32 item_index, s32 player_index, s8 isInfinite);
extern void copyFromROM(s32 rom_start, void *write_Location, void *file_size_location, s32 unk1, s32 unk2, s32 unk3, s32 unk4);
extern s32 getActorSpawnerID(void *actor);
extern void textOverlayCode(void);
extern void func_global_asm_805FBC5C(void);
extern void func_global_asm_805FBE04(void);
extern void func_global_asm_805FE7FC(void);
extern void func_global_asm_805FC2B0(void);
extern void func_global_asm_8070A934(s32 nextMap, s32 nextExit);
extern void func_arcade_80024000(void);
extern void func_jetpac_80024000(void);
extern void func_global_asm_80600B10(void);
extern void func_global_asm_8066AF40(void);
extern void func_global_asm_80610268(s32 value);
extern void func_global_asm_80600674(void);
extern void func_global_asm_80658CCC(void);
extern void func_global_asm_80700BF4(void);
extern void func_global_asm_80611730(void);
extern void raiseException(s32 type, s32 arg1, s32 arg2, s32 arg3);
extern void func_global_asm_806C8E58(s16 kong_actor_index); // tagKong
extern void func_global_asm_806CFF9C(void *player);	// clearTagSlide
extern void func_global_asm_806F12FC(void *actor); // removeGorillaGone
extern void func_global_asm_80602B60(s32 song, u8 unk0); // cancelMusic
extern void playAnimation(void *player, s32 anim_index);
extern void func_global_asm_80614D90(void *actor); // handleAnimation
extern u8 func_global_asm_805FF0C8(void); // hasTurnedInEnoughCBs
extern u8 getLevelIndex(u8 map, u8 lobby_is_isles); // getWorld

// Vanilla data
extern f32 TransitionSpeed;
extern s8 CutsceneWillPlay;
extern s8 KRoolRound;
extern KongBase D_global_asm_807FC950[6];
extern s32 PlayerOneColor;
extern s8 Mode;
extern s8 global_properties_bitfield;
extern s32 current_map;
extern s32 DestMap;
extern s32 DestExit;
extern u16 D_global_asm_8076A172;
extern s8 story_skip;
extern s8 HelmTimerShown;
extern s8 TempFlagBlock[0x10];
extern submapInfo SubmapData;
extern s8 HelmTimerPaused;
extern s32 LagBoost;
extern s32 FrameLag;
extern s32 FrameReal;
extern s32 RNG;
extern s8 LogosDestMap;
extern s8 LogosDestMode;
extern s8 Gamemode;
extern void *ObjectModel2Pointer; // TODO: Object model 2 struct array
extern s32 ObjectModel2Timer;
extern s32 ObjectModel2Count;
extern s32 ObjectModel2Count_Dupe;
extern f32 D_global_asm_807444BC;
extern s32 D_global_asm_80744460;
extern s32 D_global_asm_807444F8;
extern s32 D_global_asm_80744504;
extern s16 D_global_asm_807476F4;
extern s16 D_global_asm_807476F0;
extern s32 D_global_asm_8074682C;
extern s32 D_global_asm_807444F0;
extern s8 is_cutscene_active;
extern s32 next_map;
extern s32 next_exit;
extern s32 D_global_asm_80767CC0;
extern s32 D_global_asm_8076A070;
extern OSMesgQueue D_global_asm_8076A110;
extern u8 D_global_asm_8076A0B1;
extern s8 D_global_asm_8076A0B2;
extern cutsceneType *CutsceneTypePointer;
extern s16 PreviousCameraState;
extern s16 CurrentCameraState;
extern s16 CameraStateChangeTimer;
extern AutowalkData *AutowalkPointer;
extern s8 is_autowalking;
extern WarpInfo PositionWarpInfo;
extern s16 PositionWarpBitfield;
extern f32 PositionFloatWarps[3];
extern u16 PositionFacingAngle;
extern s8 ChimpyCam;
extern s8 ScreenRatio;
extern actorData *CurrentActorPointer;
extern u8 D_global_asm_807FBB34[]; // LoadedActorCount is byte [1] (0x807FBB35)
extern loadedActorArr D_global_asm_807FB930[64]; // LoadedActorArray
extern SpawnerMasterInfo SpawnerMasterData;
extern void *ActorSpawnerArrayPointer;
extern RGB MenuSkyTopRGB;
extern RGB MenuSkyRGB;
extern actorData *actor_list[];
extern s16 actor_count;
extern s16 ButtonsEnabledBitfield;
extern s8 JoystickEnabledX;
extern s8 JoystickEnabledY;
extern u16 D_global_asm_807ECD58; // p1HeldButtons (held controller buttons; ControllerInput)
extern Controller newly_pressed_input_copy;
extern playerData *gPlayerPointer;
extern SwapObjectData *character_change_array;
extern s8 current_character_index;
extern cameraData *Camera;
extern s8 ISGActive;
extern u32 ISGTimestampMajor; // TODO: libultra type (OSTime)
extern u32 ISGTimestampMinor;
extern s8 ISGPreviousFadeout;
extern u32 CurrentTimestampMajor; // TODO: libultra type (OSTime)
extern u32 CurrentTimestampMinor;
extern ISGFadeoutData ISGFadeoutArray[];
extern InventoryBase D_global_asm_807FCC40;
extern u8 D_global_asm_807FD798; // ModelTwoTouchCount
extern s16 ModelTwoTouchArray[4];
extern s8 TransitionProgress;
extern Controller BackgroundHeldInput;
extern u32 PauseTimestampMajor; // TODO: libultra type (OSTime)
extern u32 PauseTimestampMinor;
extern u32 HelmStartTimestampMajor; // TODO: libultra type (OSTime)
extern u32 HelmStartTimestampMinor;
extern s32 HelmStartTime;
extern s16 p1PressedButtons; // TODO: libultra type
extern s16 p1HeldButtons;	 // TODO: libultra type
extern s8 player_count;
extern s32 *sprite_table[0xAF];
extern s8 sprite_translucency;
extern s32 *bbbandit_array[4];
extern s8 StoredDamage;
extern void *ActorSpawnerPointer;
extern f32 D_global_asm_807FD888;
extern HUDDisplay *D_global_asm_80754280;
extern u8 D_global_asm_807F059C[];
extern u32 gStackCanary;
extern void *D_global_asm_807655E0;

// Hack data

enum textTable
{
	terminate, // 0x00
	nothing_01,
	nothing_02,
	nothing_03,
	nothing_04,
	nothing_05,
	nothing_06,
	nothing_07,
	nothing_08,
	nothing_09,
	nothing_0A,
	nothing_0B,
	nothing_0C,
	nothing_0D,
	nothing_0E,
	nothing_0F,
	nothing_10,
	nothing_11,
	nothing_12,
	nothing_13,
	nothing_14,
	nothing_15,
	nothing_16,
	nothing_17,
	nothing_18,
	nothing_19,
	nothing_1A,
	nothing_1B,
	nothing_1C,
	nothing_1D,
	nothing_1E,
	nothing_1F,
	space,			  // 0x20
	exclamationPoint, // 0x21
	nothing_22,		  // 0x22
	nothing_23,		  // 0x23
	nothing_24,		  // 0x24
	percentSign,	  // 0x25
	ampersand,		  // 0x26
	apostrophe,		  // 0x27
	nothing_28,		  // 0x28
	nothing_29,		  // 0x29
	nothing_2A,		  // 0x2A
	nothing_2B,		  // 0x2B
	bigComma,		  // 0x2C
	hypen,			  // 0x2D
	smallComma,		  // 0x2E
	nothing_2F,		  // 0x2F
	zero,			  // 0x30
	one,			  // 0x31
	two,			  // 0x32
	three,			  // 0x33
	four,			  // 0x34
	five,			  // 0x35
	six,			  // 0x36
	seven,			  // 0x37
	eight,			  // 0x38
	nine,			  // 0x39
	colon,			  // 0x3A
	nothing_3B,		  // 0x3B
	nothing_3C,		  // 0x3C
	nothing_3D,		  // 0x3D
	nothing_3E,		  // 0x3E
	questionMark,	  // 0x3F
	nothing_40,		  // 0x40
	A,				  // 0x41 start of normal ascii
	B,				  // 0x42
	C,				  // 0x43
	D,				  // 0x44
	E,				  // 0x45
	F,				  // 0x46
	G,				  // 0x47
	H,				  // 0x48
	I,				  // 0x49
	J,				  // 0x4A
	K,				  // 0x4B
	L,				  // 0x4C
	M,				  // 0x4D
	N,				  // 0x4E
	O,				  // 0x4F
	P,				  // 0x50
	Q,				  // 0x51
	R,				  // 0x52
	S,				  // 0x53
	T,				  // 0x54
	U,				  // 0x55
	V,				  // 0x56
	W,				  // 0x57
	X,				  // 0x58
	Y,				  // 0x59
	Z,				  // 0x5A
	nothing_5B,		  // 0x5B
	nothing_5C,		  // 0x5C
	nothing_5D,		  // 0x5D
	nothing_5E,		  // 0x5E
	nothing_5F,		  // 0x5F
	nothing_60,		  // 0x60
	nothing_61,		  // 0x61
	buttonB_62,		  // 0x62
	buttonCopyright,  // 0x63
	nothing_64,		  // 0x64
	buttonCRight,	  // 0x65
	nothing_66,		  // 0x66
	buttonStart,	  // 0x67
	nothing_68,		  // 0x68
	nothing_69,		  // 0x69
	nothing_6A,		  // 0x6A
	nothing_6B,		  // 0x6B
	buttonL,		  // 0x6C
	nothing_6D,		  // 0x6D
	buttonCUp,		  // 0x6E
	infinity,		  // 0x6F
	nothing_70,		  // 0x70
	buttonA,		  // 0x71
	buttonR,		  // 0x72
	buttonCDown,	  // 0x73
	nothing_74,		  // 0x74
	nothing_75,		  // 0x75
	nothing_76,		  // 0x76
	buttonCLeft,	  // 0x77
	nothing_78,		  // 0x78
	nothing_79,		  // 0x79
	buttonZ			  // 0x7A
};

#define NULL 0

// SFX Index
#define SFX_Banana 0x2A0
#define SFX_Okay 0x23C
#define SFX_UhOh 0x150
#define SFX_Bell 0x1F
#define SFX_KLumsy 0x31C
#define SFX_Wrong 0x98
#define SFX_Potion 0x214
#define SFX_AmmoPickup 0x157
#define SFX_Coin 0x1D1
#define SFX_BeepHigh 116
#define SFX_BeepLow 117
#define SFX_FeedMe 601
#define SFX_Bounce 458
#define SFX_TimerTock 143
#define SFX_ChunkyFallTooFar 197
#define SFX_Fire 234
#define SFX_MatchingSound 171
#define SFX_CameraPull 441
#define SFX_Quack 170
#define SFX_TagWarp 612
#define SFX_TakeWarp 230
#define SFX_Splat 22
#define SFX_Burp 530

// Other
#define MysteryWriteOffset 0x29C
#define CurrentCharacter 0x36C
#define MovesBaseSize 0x1D8

extern void setPermanentFlag(s16 flagIndex);
extern void setGlobalFlag(s16 flagIndex);
extern void setTemporaryFlag(s16 flagIndex);
extern void *findActorWithType(s32 search_actor_type);

extern s32 inTransform(void);
extern s32 canTagAnywhere(void);
extern s32 getTagAnywhereKong(s32 direction);
extern void tagAnywhere(void);

void setPermanentFlag(s16 flagIndex)
{
	setFlag(flagIndex, 1, 0);
}

void setGlobalFlag(s16 flagIndex)
{
	setFlag(flagIndex, 1, 1);
}

void setTemporaryFlag(s16 flagIndex)
{
	setFlag(flagIndex, 1, 2);
}

void *findActorWithType(s32 search_actor_type)
{
	for (s32 i = 0; i < actor_count; i++)
	{
		actorData *_actor_ = (actorData *)actor_list[i];
		if (_actor_->actorType == search_actor_type)
		{
			return _actor_;
		}
	}
	return 0;
}

typedef struct map_bitfield
{
	unsigned char test_map : 1;
	unsigned char funkys_store : 1;
	unsigned char dk_arcade : 1;
	unsigned char k_rool_barrel_lankys_maze : 1;
	unsigned char jungle_japes_mountain : 1;
	unsigned char crankys_lab : 1;
	unsigned char jungle_japes_minecart : 1;
	unsigned char jungle_japes : 1;
	unsigned char jungle_japes_army_dillo : 1;
	unsigned char jetpac : 1;
	unsigned char kremling_kosh_very_easy : 1;
	unsigned char stealthy_snoop_normal_no_logo : 1;
	unsigned char jungle_japes_shell : 1;
	unsigned char jungle_japes_lankys_cave : 1;
	unsigned char angry_aztec_beetle_race : 1;
	unsigned char snides_hq : 1;
	unsigned char angry_aztec_tinys_temple : 1;
	unsigned char hideout_helm : 1;
	unsigned char teetering_turtle_trouble_very_easy : 1;
	unsigned char angry_aztec_five_door_temple_dk : 1;
	unsigned char angry_aztec_llama_temple : 1;
	unsigned char angry_aztec_five_door_temple_diddy : 1;
	unsigned char angry_aztec_five_door_temple_tiny : 1;
	unsigned char angry_aztec_five_door_temple_lanky : 1;
	unsigned char angry_aztec_five_door_temple_chunky : 1;
	unsigned char candys_music_shop : 1;
	unsigned char frantic_factory : 1;
	unsigned char frantic_factory_car_race : 1;
	unsigned char hideout_helm_level_intros_game_over : 1;
	unsigned char frantic_factory_power_shed : 1;
	unsigned char gloomy_galleon : 1;
	unsigned char gloomy_galleon_k_rools_ship : 1;
	unsigned char batty_barrel_bandit_very_easy : 1;
	unsigned char jungle_japes_chunkys_cave : 1;
	unsigned char dk_isles_overworld : 1;
	unsigned char k_rool_barrel_dks_target_game : 1;
	unsigned char frantic_factory_crusher_room : 1;
	unsigned char jungle_japes_barrel_blast : 1;
	unsigned char angry_aztec : 1;
	unsigned char gloomy_galleon_seal_race : 1;
	unsigned char nintendo_logo : 1;
	unsigned char angry_aztec_barrel_blast : 1;
	unsigned char troff_n_scoff : 1;
	unsigned char gloomy_galleon_shipwreck_diddy_lanky_chunky : 1;
	unsigned char gloomy_galleon_treasure_chest : 1;
	unsigned char gloomy_galleon_mermaid : 1;
	unsigned char gloomy_galleon_shipwreck_dk_tiny : 1;
	unsigned char gloomy_galleon_shipwreck_lanky_tiny : 1;
	unsigned char fungi_forest : 1;
	unsigned char gloomy_galleon_lighthouse : 1;
	unsigned char k_rool_barrel_tinys_mushroom_game : 1;
	unsigned char gloomy_galleon_mechanical_fish : 1;
	unsigned char fungi_forest_ant_hill : 1;
	unsigned char battle_arena_beaver_brawl : 1;
	unsigned char gloomy_galleon_barrel_blast : 1;
	unsigned char fungi_forest_minecart : 1;
	unsigned char fungi_forest_diddys_barn : 1;
	unsigned char fungi_forest_diddys_attic : 1;
	unsigned char fungi_forest_lankys_attic : 1;
	unsigned char fungi_forest_dks_barn : 1;
	unsigned char fungi_forest_spider : 1;
	unsigned char fungi_forest_front_part_of_mill : 1;
	unsigned char fungi_forest_rear_part_of_mill : 1;
	unsigned char fungi_forest_mushroom_puzzle : 1;
	unsigned char fungi_forest_giant_mushroom : 1;
	unsigned char stealthy_snoop_normal : 1;
	unsigned char mad_maze_maul_hard : 1;
	unsigned char stash_snatch_normal : 1;
	unsigned char mad_maze_maul_easy : 1;
	unsigned char mad_maze_maul_normal : 1;
	unsigned char fungi_forest_mushroom_leap : 1;
	unsigned char fungi_forest_shooting_game : 1;
	unsigned char crystal_caves : 1;
	unsigned char battle_arena_kritter_karnage : 1;
	unsigned char stash_snatch_easy : 1;
	unsigned char stash_snatch_hard : 1;
	unsigned char dk_rap : 1;
	unsigned char minecart_mayhem_easy : 1;
	unsigned char busy_barrel_barrage_easy : 1;
	unsigned char busy_barrel_barrage_normal : 1;
	unsigned char main_menu : 1;
	unsigned char title_screen_not_for_resale_version : 1;
	unsigned char crystal_caves_beetle_race : 1;
	unsigned char fungi_forest_dogadon : 1;
	unsigned char crystal_caves_igloo_tiny : 1;
	unsigned char crystal_caves_igloo_lanky : 1;
	unsigned char crystal_caves_igloo_dk : 1;
	unsigned char creepy_castle : 1;
	unsigned char creepy_castle_ballroom : 1;
	unsigned char crystal_caves_rotating_room : 1;
	unsigned char crystal_caves_shack_chunky : 1;
	unsigned char crystal_caves_shack_dk : 1;
	unsigned char crystal_caves_shack_diddy_middle_part : 1;
	unsigned char crystal_caves_shack_tiny : 1;
	unsigned char crystal_caves_lankys_hut : 1;
	unsigned char crystal_caves_igloo_chunky : 1;
	unsigned char splish_splash_salvage_normal : 1;
	unsigned char k_lumsy : 1;
	unsigned char crystal_caves_ice_castle : 1;
	unsigned char speedy_swing_sortie_easy : 1;
	unsigned char crystal_caves_igloo_diddy : 1;
	unsigned char krazy_kong_klamour_easy : 1;
	unsigned char big_bug_bash_very_easy : 1;
	unsigned char searchlight_seek_very_easy : 1;
	unsigned char beaver_bother_easy : 1;
	unsigned char creepy_castle_tower : 1;
	unsigned char creepy_castle_minecart : 1;
	unsigned char kong_battle_battle_arena : 1;
	unsigned char creepy_castle_crypt_lanky_tiny : 1;
	unsigned char kong_battle_arena_1 : 1;
	unsigned char frantic_factory_barrel_blast : 1;
	unsigned char gloomy_galleon_pufftoss : 1;
	unsigned char creepy_castle_crypt_dk_diddy_chunky : 1;
	unsigned char creepy_castle_museum : 1;
	unsigned char creepy_castle_library : 1;
	unsigned char kremling_kosh_easy : 1;
	unsigned char kremling_kosh_normal : 1;
	unsigned char kremling_kosh_hard : 1;
	unsigned char teetering_turtle_trouble_easy : 1;
	unsigned char teetering_turtle_trouble_normal : 1;
	unsigned char teetering_turtle_trouble_hard : 1;
	unsigned char batty_barrel_bandit_easy : 1;
	unsigned char batty_barrel_bandit_normal : 1;
	unsigned char batty_barrel_bandit_hard : 1;
	unsigned char mad_maze_maul_insane : 1;
	unsigned char stash_snatch_insane : 1;
	unsigned char stealthy_snoop_very_easy : 1;
	unsigned char stealthy_snoop_easy : 1;
	unsigned char stealthy_snoop_hard : 1;
	unsigned char minecart_mayhem_normal : 1;
	unsigned char minecart_mayhem_hard : 1;
	unsigned char busy_barrel_barrage_hard : 1;
	unsigned char splish_splash_salvage_hard : 1;
	unsigned char splish_splash_salvage_easy : 1;
	unsigned char speedy_swing_sortie_normal : 1;
	unsigned char speedy_swing_sortie_hard : 1;
	unsigned char beaver_bother_normal : 1;
	unsigned char beaver_bother_hard : 1;
	unsigned char searchlight_seek_easy : 1;
	unsigned char searchlight_seek_normal : 1;
	unsigned char searchlight_seek_hard : 1;
	unsigned char krazy_kong_klamour_normal : 1;
	unsigned char krazy_kong_klamour_hard : 1;
	unsigned char krazy_kong_klamour_insane : 1;
	unsigned char peril_path_panic_very_easy : 1;
	unsigned char peril_path_panic_easy : 1;
	unsigned char peril_path_panic_normal : 1;
	unsigned char peril_path_panic_hard : 1;
	unsigned char big_bug_bash_easy : 1;
	unsigned char big_bug_bash_normal : 1;
	unsigned char big_bug_bash_hard : 1;
	unsigned char creepy_castle_dungeon : 1;
	unsigned char hideout_helm_intro_story : 1;
	unsigned char dk_isles_dk_theatre : 1;
	unsigned char frantic_factory_mad_jack : 1;
	unsigned char battle_arena_arena_ambush : 1;
	unsigned char battle_arena_more_kritter_karnage : 1;
	unsigned char battle_arena_forest_fracas : 1;
	unsigned char battle_arena_bish_bash_brawl : 1;
	unsigned char battle_arena_kamikaze_kremlings : 1;
	unsigned char battle_arena_plinth_panic : 1;
	unsigned char battle_arena_pinnacle_palaver : 1;
	unsigned char battle_arena_shockwave_showdown : 1;
	unsigned char creepy_castle_basement : 1;
	unsigned char creepy_castle_tree : 1;
	unsigned char k_rool_barrel_diddys_kremling_game : 1;
	unsigned char creepy_castle_chunkys_toolshed : 1;
	unsigned char creepy_castle_trash_can : 1;
	unsigned char creepy_castle_greenhouse : 1;
	unsigned char jungle_japes_lobby : 1;
	unsigned char hideout_helm_lobby : 1;
	unsigned char dks_house : 1;
	unsigned char rock_intro_story : 1;
	unsigned char angry_aztec_lobby : 1;
	unsigned char gloomy_galleon_lobby : 1;
	unsigned char frantic_factory_lobby : 1;
	unsigned char training_grounds : 1;
	unsigned char dive_barrel : 1;
	unsigned char fungi_forest_lobby : 1;
	unsigned char gloomy_galleon_submarine : 1;
	unsigned char orange_barrel : 1;
	unsigned char barrel_barrel : 1;
	unsigned char vine_barrel : 1;
	unsigned char creepy_castle_crypt : 1;
	unsigned char enguarde_arena : 1;
	unsigned char creepy_castle_car_race : 1;
	unsigned char crystal_caves_barrel_blast : 1;
	unsigned char creepy_castle_barrel_blast : 1;
	unsigned char fungi_forest_barrel_blast : 1;
	unsigned char fairy_island : 1;
	unsigned char kong_battle_arena_2 : 1;
	unsigned char rambi_arena : 1;
	unsigned char kong_battle_arena_3 : 1;
	unsigned char creepy_castle_lobby : 1;
	unsigned char crystal_caves_lobby : 1;
	unsigned char dk_isles_snides_room : 1;
	unsigned char crystal_caves_army_dillo : 1;
	unsigned char angry_aztec_dogadon : 1;
	unsigned char training_grounds_end_sequence : 1;
	unsigned char creepy_castle_king_kut_out : 1;
	unsigned char crystal_caves_shack_diddy_upper_part : 1;
	unsigned char k_rool_barrel_diddys_rocketbarrel_game : 1;
	unsigned char k_rool_barrel_lankys_shooting_game : 1;
	unsigned char k_rool_fight_dk_phase : 1;
	unsigned char k_rool_fight_diddy_phase : 1;
	unsigned char k_rool_fight_lanky_phase : 1;
	unsigned char k_rool_fight_tiny_phase : 1;
	unsigned char k_rool_fight_chunky_phase : 1;
	unsigned char bloopers_ending : 1;
	unsigned char k_rool_barrel_chunkys_hidden_kremling_game : 1;
	unsigned char k_rool_barrel_tinys_pony_tail_twirl_game : 1;
	unsigned char k_rool_barrel_chunkys_shooting_game : 1;
	unsigned char k_rool_barrel_dks_rambi_game : 1;
	unsigned char k_lumsy_ending : 1;
	unsigned char k_rools_shoe : 1;
	unsigned char k_rools_arena : 1;
} map_bitfield;

typedef struct movement_bitfield
{
	unsigned char null_state : 1;
	unsigned char idle_enemy : 1;
	unsigned char first_person_camera : 1;
	unsigned char first_person_camera_water : 1;
	unsigned char fairy_camera : 1;
	unsigned char fairy_camera_water : 1;
	unsigned char locked_bonus_barrel_0x6 : 1;
	unsigned char minecart_idle : 1;
	unsigned char minecart_crouch : 1;
	unsigned char minecart_jump : 1;
	unsigned char minecart_left : 1;
	unsigned char minecart_right : 1;
	unsigned char idle : 1;
	unsigned char walking : 1;
	unsigned char skidding : 1;
	unsigned char sliding_beetle_race : 1;
	unsigned char sliding_beetle_race_left : 1;
	unsigned char sliding_beetle_race_right : 1;
	unsigned char sliding_beetle_race_forward : 1;
	unsigned char sliding_beetle_race_back : 1;
	unsigned char jumping_beetle_race : 1;
	unsigned char slipping : 1;
	unsigned char slipping_helm_slope : 1;
	unsigned char jumping : 1;
	unsigned char baboon_blast_pad : 1;
	unsigned char bouncing_mushroom : 1;
	unsigned char double_jump : 1;
	unsigned char simian_spring : 1;
	unsigned char simian_slam : 1;
	unsigned char long_jumping : 1;
	unsigned char falling : 1;
	unsigned char falling_gun : 1;
	unsigned char falling_or_splat : 1;
	unsigned char falling_beetle_race : 1;
	unsigned char pony_tail_twirl : 1;
	unsigned char attacking_enemy : 1;
	unsigned char primate_punch : 1;
	unsigned char attacking_enemy_0x25 : 1;
	unsigned char ground_attack : 1;
	unsigned char attacking_enemy_0x27 : 1;
	unsigned char ground_attack_final : 1;
	unsigned char moving_ground_attack : 1;
	unsigned char aerial_attack : 1;
	unsigned char rolling : 1;
	unsigned char throwing_orange : 1;
	unsigned char shockwave : 1;
	unsigned char chimpy_charge : 1;
	unsigned char charging_rambi : 1;
	unsigned char bouncing : 1;
	unsigned char damaged : 1;
	unsigned char stunlocked_kasplat : 1;
	unsigned char damaged_mad_jack : 1;
	unsigned char unknown_0x34 : 1;
	unsigned char damaged_klump_knockback : 1;
	unsigned char death : 1;
	unsigned char damaged_underwater : 1;
	unsigned char damaged_vehicle : 1;
	unsigned char shrinking : 1;
	unsigned char unknown_0x3a : 1;
	unsigned char death_dogadon : 1;
	unsigned char crouching : 1;
	unsigned char uncrouching : 1;
	unsigned char backflip : 1;
	unsigned char entering_orangstand : 1;
	unsigned char orangstand : 1;
	unsigned char jumping_orangstand : 1;
	unsigned char barrel_tag_barrel : 1;
	unsigned char barrel_underwater : 1;
	unsigned char baboon_blast_shot : 1;
	unsigned char cannon_shot : 1;
	unsigned char pushing_object : 1;
	unsigned char picking_up_object : 1;
	unsigned char idle_carrying_object : 1;
	unsigned char walking_carrying_object : 1;
	unsigned char dropping_object : 1;
	unsigned char throwing_object : 1;
	unsigned char jumping_carrying_object : 1;
	unsigned char throwing_object_air : 1;
	unsigned char surface_swimming : 1;
	unsigned char underwater : 1;
	unsigned char leaving_water : 1;
	unsigned char jumping_water : 1;
	unsigned char bananaporter : 1;
	unsigned char monkeyport : 1;
	unsigned char bananaport_multiplayer : 1;
	unsigned char unknown_0x55 : 1;
	unsigned char locked_funky_and_candy : 1;
	unsigned char swinging_on_vine : 1;
	unsigned char leaving_vine : 1;
	unsigned char climbing_tree : 1;
	unsigned char leaving_tree : 1;
	unsigned char grabbed_ledge : 1;
	unsigned char pulling_up_on_ledge : 1;
	unsigned char idle_gun : 1;
	unsigned char walking_gun : 1;
	unsigned char putting_away_gun : 1;
	unsigned char pulling_out_gun : 1;
	unsigned char jumping_gun : 1;
	unsigned char aiming_gun : 1;
	unsigned char rocketbarrel : 1;
	unsigned char taking_photo : 1;
	unsigned char taking_photo_underwater : 1;
	unsigned char damaged_tnt_barrels : 1;
	unsigned char instrument : 1;
	unsigned char unknown_0x68 : 1;
	unsigned char car_race : 1;
	unsigned char learning_gun : 1;
	unsigned char locked_bonus_barrel_0x6b : 1;
	unsigned char feeding_tns : 1;
	unsigned char boat : 1;
	unsigned char baboon_balloon : 1;
	unsigned char updraft : 1;
	unsigned char gb_dance : 1;
	unsigned char key_dance : 1;
	unsigned char crown_dance : 1;
	unsigned char loss_dance : 1;
	unsigned char victory_dance : 1;
	unsigned char vehicle_castle_car_race : 1;
	unsigned char entering_battle_crown : 1;
	unsigned char locked_cutscenes : 1;
	unsigned char gorilla_grab : 1;
	unsigned char learning_move : 1;
	unsigned char locked_car_race_loss : 1;
	unsigned char locked_beetle_race_loss : 1;
	unsigned char trapped : 1;
	unsigned char klaptrap_kong : 1;
	unsigned char surface_swimming_enguarde : 1;
	unsigned char underwater_enguarde : 1;
	unsigned char attacking_enguarde_surface : 1;
	unsigned char attacking_enguarde : 1;
	unsigned char leaving_water_enguarde : 1;
	unsigned char fairy_refill : 1;
	unsigned char unknown_0x84 : 1;
	unsigned char main_menu : 1;
	unsigned char entering_main_menu : 1;
	unsigned char entering_portal : 1;
	unsigned char exiting_portal : 1;
} movement_bitfield;

static const map_bitfield banned_map_btf = {
	// Whether a tag is banned on a given map. Each property is a boolean.
	.test_map = 0,
	.funkys_store = 1,					 // Reason: Shop
	.dk_arcade = 1,						 // Reason: Locked Movement
	.k_rool_barrel_lankys_maze = 0,
	.jungle_japes_mountain = 0,
	.crankys_lab = 1,					 // Reason: Shop
	.jungle_japes_minecart = 1,			 // Reason: Locked Movement
	.jungle_japes = 0,
	.jungle_japes_army_dillo = 1,		 // Reason: Boss Map
	.jetpac = 1,						 // Reason: Locked Movement
	.kremling_kosh_very_easy = 1,		 // Reason: Locked Movement
	.stealthy_snoop_normal_no_logo = 0,
	.jungle_japes_shell = 0,
	.jungle_japes_lankys_cave = 0,
	.angry_aztec_beetle_race = 0,		 // Reason: Locked Movement
	.snides_hq = 1,						 // Reason: Shop
	.angry_aztec_tinys_temple = 0,
	.hideout_helm = 0,
	.teetering_turtle_trouble_very_easy = 1, // Reason: Locked Movement
	.angry_aztec_five_door_temple_dk = 0,
	.angry_aztec_llama_temple = 0,
	.angry_aztec_five_door_temple_diddy = 0,
	.angry_aztec_five_door_temple_tiny = 0,
	.angry_aztec_five_door_temple_lanky = 0,
	.angry_aztec_five_door_temple_chunky = 0,
	.candys_music_shop = 1,				 // Reason: Shop
	.frantic_factory = 0,
	.frantic_factory_car_race = 1,		 // Reason: Locked Movement
	.hideout_helm_level_intros_game_over = 1, // Reason: Cutscene Map
	.frantic_factory_power_shed = 0,
	.gloomy_galleon = 0,
	.gloomy_galleon_k_rools_ship = 0,
	.batty_barrel_bandit_very_easy = 1,	 // Reason: Locked Movement
	.jungle_japes_chunkys_cave = 0,
	.dk_isles_overworld = 0,
	.k_rool_barrel_dks_target_game = 0,
	.frantic_factory_crusher_room = 0,
	.jungle_japes_barrel_blast = 1,		 // Reason: BBlast Course
	.angry_aztec = 0,
	.gloomy_galleon_seal_race = 1,		 // Reason: Locked Movement
	.nintendo_logo = 1,					 // Reason: Cutscene Map
	.angry_aztec_barrel_blast = 1,		 // Reason: BBlast Course
	.troff_n_scoff = 0,
	.gloomy_galleon_shipwreck_diddy_lanky_chunky = 0,
	.gloomy_galleon_treasure_chest = 0,
	.gloomy_galleon_mermaid = 0,
	.gloomy_galleon_shipwreck_dk_tiny = 0,
	.gloomy_galleon_shipwreck_lanky_tiny = 0,
	.fungi_forest = 0,
	.gloomy_galleon_lighthouse = 0,
	.k_rool_barrel_tinys_mushroom_game = 0,
	.gloomy_galleon_mechanical_fish = 0,
	.fungi_forest_ant_hill = 0,
	.battle_arena_beaver_brawl = 0,
	.gloomy_galleon_barrel_blast = 1,	 // Reason: BBlast Course
	.fungi_forest_minecart = 1,			 // Reason: Locked Movement
	.fungi_forest_diddys_barn = 0,
	.fungi_forest_diddys_attic = 0,
	.fungi_forest_lankys_attic = 0,
	.fungi_forest_dks_barn = 0,
	.fungi_forest_spider = 0,
	.fungi_forest_front_part_of_mill = 0,
	.fungi_forest_rear_part_of_mill = 0,
	.fungi_forest_mushroom_puzzle = 0,
	.fungi_forest_giant_mushroom = 0,
	.stealthy_snoop_normal = 0,
	.mad_maze_maul_hard = 0,
	.stash_snatch_normal = 0,
	.mad_maze_maul_easy = 0,
	.mad_maze_maul_normal = 0,
	.fungi_forest_mushroom_leap = 0,
	.fungi_forest_shooting_game = 0,
	.crystal_caves = 0,
	.battle_arena_kritter_karnage = 0,
	.stash_snatch_easy = 0,
	.stash_snatch_hard = 0,
	.dk_rap = 1,						 // Reason: Cutscene Map
	.minecart_mayhem_easy = 1,			 // Reason: Locked Movement
	.busy_barrel_barrage_easy = 1,		 // Reason: Locked Movement
	.busy_barrel_barrage_normal = 1,	 // Reason: Locked Movement
	.main_menu = 1,						 // Reason: Locked Movement
	.title_screen_not_for_resale_version = 1, // Reason: Cutscene Map
	.crystal_caves_beetle_race = 0,		 // Reason: Locked Movement
	.fungi_forest_dogadon = 1,			 // Reason: Boss Map
	.crystal_caves_igloo_tiny = 0,
	.crystal_caves_igloo_lanky = 0,
	.crystal_caves_igloo_dk = 0,
	.creepy_castle = 0,
	.creepy_castle_ballroom = 0,
	.crystal_caves_rotating_room = 0,
	.crystal_caves_shack_chunky = 0,
	.crystal_caves_shack_dk = 0,
	.crystal_caves_shack_diddy_middle_part = 0,
	.crystal_caves_shack_tiny = 0,
	.crystal_caves_lankys_hut = 0,
	.crystal_caves_igloo_chunky = 0,
	.splish_splash_salvage_normal = 0,
	.k_lumsy = 0,
	.crystal_caves_ice_castle = 0,
	.speedy_swing_sortie_easy = 0,
	.crystal_caves_igloo_diddy = 0,
	.krazy_kong_klamour_easy = 1,		 // Reason: Locked Movement
	.big_bug_bash_very_easy = 1,		 // Reason: Locked Movement
	.searchlight_seek_very_easy = 1,	 // Reason: Locked Movement
	.beaver_bother_easy = 1,			 // Reason: Locked Movement
	.creepy_castle_tower = 0,
	.creepy_castle_minecart = 0,
	.kong_battle_battle_arena = 1,		 // Reason: Multiplayer Map
	.creepy_castle_crypt_lanky_tiny = 0,
	.kong_battle_arena_1 = 1,			 // Reason: Multiplayer Map
	.frantic_factory_barrel_blast = 1,	 // Reason: BBlast Course
	.gloomy_galleon_pufftoss = 1,		 // Reason: Boss Map
	.creepy_castle_crypt_dk_diddy_chunky = 0,
	.creepy_castle_museum = 0,
	.creepy_castle_library = 0,
	.kremling_kosh_easy = 1,			 // Reason: Locked Movement
	.kremling_kosh_normal = 1,			 // Reason: Locked Movement
	.kremling_kosh_hard = 1,			 // Reason: Locked Movement
	.teetering_turtle_trouble_easy = 1,	 // Reason: Locked Movement
	.teetering_turtle_trouble_normal = 1, // Reason: Locked Movement
	.teetering_turtle_trouble_hard = 1,	 // Reason: Locked Movement
	.batty_barrel_bandit_easy = 1,		 // Reason: Locked Movement
	.batty_barrel_bandit_normal = 1,	 // Reason: Locked Movement
	.batty_barrel_bandit_hard = 1,		 // Reason: Locked Movement
	.mad_maze_maul_insane = 0,
	.stash_snatch_insane = 0,
	.stealthy_snoop_very_easy = 0,
	.stealthy_snoop_easy = 0,
	.stealthy_snoop_hard = 0,
	.minecart_mayhem_normal = 1,		 // Reason: Locked Movement
	.minecart_mayhem_hard = 1,			 // Reason: Locked Movement
	.busy_barrel_barrage_hard = 1,		 // Reason: Locked Movement
	.splish_splash_salvage_hard = 0,
	.splish_splash_salvage_easy = 0,
	.speedy_swing_sortie_normal = 0,
	.speedy_swing_sortie_hard = 0,
	.beaver_bother_normal = 1,			 // Reason: Locked Movement
	.beaver_bother_hard = 1,			 // Reason: Locked Movement
	.searchlight_seek_easy = 1,			 // Reason: Locked Movement
	.searchlight_seek_normal = 1,		 // Reason: Locked Movement
	.searchlight_seek_hard = 1,			 // Reason: Locked Movement
	.krazy_kong_klamour_normal = 1,		 // Reason: Locked Movement
	.krazy_kong_klamour_hard = 1,		 // Reason: Locked Movement
	.krazy_kong_klamour_insane = 1,		 // Reason: Locked Movement
	.peril_path_panic_very_easy = 1,	 // Reason: Locked Movement
	.peril_path_panic_easy = 1,			 // Reason: Locked Movement
	.peril_path_panic_normal = 1,		 // Reason: Locked Movement
	.peril_path_panic_hard = 1,			 // Reason: Locked Movement
	.big_bug_bash_easy = 1,				 // Reason: Locked Movement
	.big_bug_bash_normal = 1,			 // Reason: Locked Movement
	.big_bug_bash_hard = 1,				 // Reason: Locked Movement
	.creepy_castle_dungeon = 0,
	.hideout_helm_intro_story = 1,		 // Reason: Cutscene Map
	.dk_isles_dk_theatre = 1,			 // Reason: Cutscene Map
	.frantic_factory_mad_jack = 1,		 // Reason: Boss Map
	.battle_arena_arena_ambush = 0,
	.battle_arena_more_kritter_karnage = 0,
	.battle_arena_forest_fracas = 0,
	.battle_arena_bish_bash_brawl = 0,
	.battle_arena_kamikaze_kremlings = 0,
	.battle_arena_plinth_panic = 0,
	.battle_arena_pinnacle_palaver = 0,
	.battle_arena_shockwave_showdown = 0,
	.creepy_castle_basement = 0,
	.creepy_castle_tree = 0,
	.k_rool_barrel_diddys_kremling_game = 0,
	.creepy_castle_chunkys_toolshed = 0,
	.creepy_castle_trash_can = 0,
	.creepy_castle_greenhouse = 0,
	.jungle_japes_lobby = 0,
	.hideout_helm_lobby = 0,
	.dks_house = 0,
	.rock_intro_story = 1,				 // Reason: Cutscene Map
	.angry_aztec_lobby = 0,
	.gloomy_galleon_lobby = 0,
	.frantic_factory_lobby = 0,
	.training_grounds = 0,
	.dive_barrel = 0,
	.fungi_forest_lobby = 0,
	.gloomy_galleon_submarine = 0,
	.orange_barrel = 0,
	.barrel_barrel = 0,
	.vine_barrel = 0,
	.creepy_castle_crypt = 0,
	.enguarde_arena = 1,				 // Reason: Enguarde-Only Room
	.creepy_castle_car_race = 0,
	.crystal_caves_barrel_blast = 1,	 // Reason: BBlast Course
	.creepy_castle_barrel_blast = 1,	 // Reason: BBlast Course
	.fungi_forest_barrel_blast = 1,		 // Reason: BBlast Course
	.fairy_island = 0,
	.kong_battle_arena_2 = 1,			 // Reason: Multiplayer Map
	.rambi_arena = 1,					 // Reason: Rambi-Only Room
	.kong_battle_arena_3 = 1,			 // Reason: Multiplayer Map
	.creepy_castle_lobby = 0,
	.crystal_caves_lobby = 0,
	.dk_isles_snides_room = 0,
	.crystal_caves_army_dillo = 1,		 // Reason: Boss Map
	.angry_aztec_dogadon = 1,			 // Reason: Boss Map
	.training_grounds_end_sequence = 1,	 // Reason: Cutscene Map
	.creepy_castle_king_kut_out = 1,	 // Reason: Boss Map
	.crystal_caves_shack_diddy_upper_part = 0,
	.k_rool_barrel_diddys_rocketbarrel_game = 0,
	.k_rool_barrel_lankys_shooting_game = 0,
	.k_rool_fight_dk_phase = 1,			 // Reason: Boss Map
	.k_rool_fight_diddy_phase = 1,		 // Reason: Boss Map
	.k_rool_fight_lanky_phase = 1,		 // Reason: Boss Map
	.k_rool_fight_tiny_phase = 1,		 // Reason: Boss Map
	.k_rool_fight_chunky_phase = 1,		 // Reason: Boss Map
	.bloopers_ending = 1,				 // Reason: Cutscene Map
	.k_rool_barrel_chunkys_hidden_kremling_game = 0,
	.k_rool_barrel_tinys_pony_tail_twirl_game = 0,
	.k_rool_barrel_chunkys_shooting_game = 0,
	.k_rool_barrel_dks_rambi_game = 1,	 // Reason: Rambi-Only Room
	.k_lumsy_ending = 1,				 // Reason: Cutscene Map
	.k_rools_shoe = 1,					 // Reason: Boss Map
	.k_rools_arena = 1,					 // Reason: Cutscene Map
};

static const movement_bitfield banned_movement_btf = {
	// Whether a tag is banned during a given control state. Each property is a boolean.
	.null_state = 0,
	.idle_enemy = 0,
	.first_person_camera = 0,
	.first_person_camera_water = 0,
	.fairy_camera = 1,			 // Reason: HUD
	.fairy_camera_water = 1,	 // Reason: HUD
	.locked_bonus_barrel_0x6 = 1, // Reason: Locked Movement
	.minecart_idle = 0,
	.minecart_crouch = 0,
	.minecart_jump = 0,
	.minecart_left = 0,
	.minecart_right = 0,
	.idle = 0,
	.walking = 0,
	.skidding = 0,
	.sliding_beetle_race = 1,
	.sliding_beetle_race_left = 1,
	.sliding_beetle_race_right = 1,
	.sliding_beetle_race_forward = 1,
	.sliding_beetle_race_back = 1,
	.jumping_beetle_race = 1,
	.slipping = 1,				 // Reason: Visual
	.slipping_helm_slope = 1,	 // Reason: Visual
	.jumping = 0,
	.baboon_blast_pad = 1,		 // Reason: Visual
	.bouncing_mushroom = 0,
	.double_jump = 0,
	.simian_spring = 1,			 // Reason: Visual
	.simian_slam = 0,
	.long_jumping = 0,
	.falling = 0,
	.falling_gun = 0,
	.falling_or_splat = 1,		 // Reason: Cheese
	.falling_beetle_race = 0,
	.pony_tail_twirl = 0,
	.attacking_enemy = 0,
	.primate_punch = 0,
	.attacking_enemy_0x25 = 0,
	.ground_attack = 0,
	.attacking_enemy_0x27 = 0,
	.ground_attack_final = 0,
	.moving_ground_attack = 0,
	.aerial_attack = 0,
	.rolling = 0,
	.throwing_orange = 0,
	.shockwave = 1,				 // Reason: Crash
	.chimpy_charge = 1,			 // Reason: Visual
	.charging_rambi = 0,
	.bouncing = 0,
	.damaged = 1,				 // Reason: Glitch
	.stunlocked_kasplat = 1,	 // Reason: Crash
	.damaged_mad_jack = 1,		 // Reason: Crash
	.unknown_0x34 = 0,
	.damaged_klump_knockback = 1, // Reason: Glitch
	.death = 1,					 // Reason: Glitch
	.damaged_underwater = 1,	 // Reason: Glitch
	.damaged_vehicle = 1,		 // Reason: Glitch
	.shrinking = 1,				 // Reason: Glitch
	.unknown_0x3a = 0,
	.death_dogadon = 0,
	.crouching = 0,
	.uncrouching = 0,
	.backflip = 0,
	.entering_orangstand = 0,
	.orangstand = 0,
	.jumping_orangstand = 0,
	.barrel_tag_barrel = 1,		 // Reason: Locked Movement
	.barrel_underwater = 1,		 // Reason: Locked Movement
	.baboon_blast_shot = 1,		 // Reason: Locked Movement
	.cannon_shot = 1,			 // Reason: Locked Movement
	.pushing_object = 0,
	.picking_up_object = 0,
	.idle_carrying_object = 0,
	.walking_carrying_object = 0,
	.dropping_object = 0,
	.throwing_object = 0,
	.jumping_carrying_object = 0,
	.throwing_object_air = 0,
	.surface_swimming = 0,
	.underwater = 0,
	.leaving_water = 0,
	.jumping_water = 0,
	.bananaporter = 1,			 // Reason: Locked Movement
	.monkeyport = 1,			 // Reason: Locked Movement
	.bananaport_multiplayer = 1, // Reason: Glitch
	.unknown_0x55 = 0,
	.locked_funky_and_candy = 1, // Reason: Locked Movement
	.swinging_on_vine = 1,		 // Reason: Crash
	.leaving_vine = 1,			 // Reason: Crash
	.climbing_tree = 1,			 // Reason: Crash
	.leaving_tree = 1,			 // Reason: Crash
	.grabbed_ledge = 1,			 // Reason: Crash
	.pulling_up_on_ledge = 1,	 // Reason: Crash
	.idle_gun = 0,
	.walking_gun = 0,
	.putting_away_gun = 0,
	.pulling_out_gun = 0,
	.jumping_gun = 0,
	.aiming_gun = 0,
	.rocketbarrel = 1,			 // Reason: Glitch
	.taking_photo = 1,			 // Reason: Glitch
	.taking_photo_underwater = 1, // Reason: Glitch
	.damaged_tnt_barrels = 0,
	.instrument = 1,			 // Reason: Glitch
	.unknown_0x68 = 0,
	.car_race = 1,				 // Reason: Locked Movement
	.learning_gun = 1,			 // Reason: Locked Movement
	.locked_bonus_barrel_0x6b = 1, // Reason: Locked Movement
	.feeding_tns = 1,			 // Reason: Locked Movement
	.boat = 1,					 // Reason: Locked Movement
	.baboon_balloon = 1,		 // Reason: Visual
	.updraft = 1,				 // Reason: Visual
	.gb_dance = 1,				 // Reason: Locked Movement
	.key_dance = 1,				 // Reason: Locked Movement
	.crown_dance = 1,			 // Reason: Locked Movement
	.loss_dance = 1,			 // Reason: Locked Movement
	.victory_dance = 1,			 // Reason: Locked Movement
	.vehicle_castle_car_race = 0,
	.entering_battle_crown = 0,
	.locked_cutscenes = 0,
	.gorilla_grab = 1,			 // Reason: Locked Movement
	.learning_move = 1,			 // Reason: Locked Movement
	.locked_car_race_loss = 1,	 // Reason: Locked Movement
	.locked_beetle_race_loss = 1, // Reason: Locked Movement
	.trapped = 1,				 // Reason: Locked Movement
	.klaptrap_kong = 1,			 // Reason: Glitch
	.surface_swimming_enguarde = 0,
	.underwater_enguarde = 0,
	.attacking_enguarde_surface = 0,
	.attacking_enguarde = 0,
	.leaving_water_enguarde = 0,
	.fairy_refill = 1,			 // Reason: Locked Movement
	.unknown_0x84 = 0,
	.main_menu = 0,
	.entering_main_menu = 0,
	.entering_portal = 1,		 // Reason: Locked Movement
	.exiting_portal = 1,		 // Reason: Locked Movement
};

static const u16 kong_unlocked_flags[] = {
	385, // Kong Unlocked: DK
	6,	 // Kong Unlocked: Diddy
	70,	 // Kong Unlocked: Lanky
	66,	 // Kong Unlocked: Tiny
	117, // Kong Unlocked: Chunky
};

#define TAG_ANYWHERE_KONG_LIMIT 5 // Number of kongs in the tag loop

// Tag cooldown / HUD-freeze bookkeeping. Self-contained: driven entirely by
// tagAnywhere() each frame.
static unsigned char tag_countdown = 0;
static char can_tag_anywhere = 0;
static char can_tag_left = 0;
static char can_tag_right = 0;
static const unsigned char important_huds[] = {0, 1};
static unsigned char important_huds_changed[] = {0, 0};
static char grab_lock_timer = 0; // TODO: Figure this out
static char tag_locked = 0;

s32 inTransform(void)
{
	// Is the player mid-transformation? (blocks tagging)
	if (gPlayerPointer)
	{
		// 0x10 - Strong Kong, 0x20 - Orangstand Sprint
		if (gPlayerPointer->strong_kong_ostand_bitfield & 0x30)
		{
			return 1;
		}
		// Rocketbarrel
		if (gPlayerPointer->control_state == 0x63)
		{
			return 1;
		}
	}
	if (character_change_array)
	{
		// 0 = Mini Monkey, 2 = Hunky Chunky (1 = normal size)
		return character_change_array->size != 1;
	}
	return 0;
}

s32 canTagAnywhere(void)
{
	// Note: only called from tagAnywhere() once gPlayerPointer is known non-null.
	if (gPlayerPointer->strong_kong_ostand_bitfield & 0x100)
	{
		// Seasick
		return 0;
	}
	if (gPlayerPointer->collision_queue_pointer)
	{
		return 0;
	}
	if (D_global_asm_807FD888 > 15.0f)
	{
		// LZ fadeout in progress - can cause inconsistent graphical crashes
		return 0;
	}
	if (inTransform())
	{
		return 0;
	}
	if (is_cutscene_active)
	{
		return 0;
	}
	if (D_global_asm_807FD798 > 0) // ModelTwoTouchCount
	{
		return 0;
	}
	if (tag_locked)
	{
		return 0;
	}
	if (current_map == 42) // Troff 'n' Scoff
	{
		if (D_global_asm_8076A0B1 & 0x10) // MapState
		{
			return 0;
		}
		if (func_global_asm_805FF0C8()) // hasTurnedInEnoughCBs
		{
			if (gPlayerPointer->zPos < 560.0f)
			{
				// Too close to boss door
				return 0;
			}
		}
	}
	for (s32 i = 0; i < D_global_asm_807FBB34[1]; i++) // LoadedActorCount @ 0x807FBB35
	{
		if (D_global_asm_807FB930[i].actor)
		{
			s32 tested_type = D_global_asm_807FB930[i].actor->actorType;
			if (tested_type == 48) // Coconut
			{
				return 0;
			}
			else if (tested_type == 36) // Peanut
			{
				return 0;
			}
			else if (tested_type == 42) // Grape
			{
				return 0;
			}
			else if (tested_type == 43) // Feather
			{
				if (D_global_asm_807FB930[i].actor->control_state == 0)
				{
					return 0;
				}
			}
			else if (tested_type == 38) // Pineapple
			{
				return 0;
			}
		}
	}
	// In tag barrel / paused
	if (global_properties_bitfield & 2)
	{
		return 0;
	}
	if (tag_countdown != 0)
	{
		return 0;
	}
	s32 offset = current_map >> 3;
	s32 check = current_map % 8;
	if (*(unsigned char *)((unsigned char *)(&banned_map_btf) + offset) & (0x80 >> check))
	{
		return 0;
	}
	s32 control_state = gPlayerPointer->control_state;
	offset = control_state >> 3;
	check = control_state % 8;
	if (*(unsigned char *)((unsigned char *)(&banned_movement_btf) + offset) & (0x80 >> check))
	{
		return 0;
	}
	return 1;
}

s32 getTagAnywhereKong(s32 direction)
{
	// Get the next unlocked kong in the tag loop in the given direction
	s32 next_character = current_character_index + direction;
	if (next_character < 0)
	{
		next_character = TAG_ANYWHERE_KONG_LIMIT - 1;
	}
	else if (next_character >= TAG_ANYWHERE_KONG_LIMIT)
	{
		next_character = 0;
	}
	s32 i = 0;
	s32 reached_limit = 0;
	while (i < TAG_ANYWHERE_KONG_LIMIT)
	{
		s32 pass = 0;
		if (isFlagSet(kong_unlocked_flags[next_character], 0))
		{
			pass = 1;
		}
		if (pass)
		{
			break;
		}
		else
		{
			if ((i + 1) == TAG_ANYWHERE_KONG_LIMIT)
			{
				reached_limit = 1;
				return current_character_index;
			}
			else
			{
				next_character = next_character + direction;
				if (next_character < 0)
				{
					next_character = TAG_ANYWHERE_KONG_LIMIT - 1;
				}
				else if (next_character >= TAG_ANYWHERE_KONG_LIMIT)
				{
					next_character = 0;
				}
			}
		}
		i++;
	}
	if (reached_limit)
	{
		return current_character_index;
	}
	else
	{
		return next_character;
	}
}

void tagAnywhere(void)
{
	if (gPlayerPointer)
	{
		if (tag_countdown > 0)
		{
			tag_countdown -= 1;
		}
		if (current_map == 42) // Troff 'n' Scoff
		{
			if (tag_countdown == 2)
			{
				D_global_asm_80754280[0].hud_state = 1;
				if (gPlayerPointer->control_state == 108)
				{
					s32 world = getLevelIndex(current_map, 0);
					if (D_global_asm_807FC950[current_character_index].cb_count[world] > 0)
					{
						D_global_asm_80754280[0].hud_state = 0;
					}
				}
			}
			else if (tag_countdown == 1)
			{
				if (gPlayerPointer->control_state == 108)
				{
					s32 world = getLevelIndex(current_map, 0);
					if (D_global_asm_807FC950[current_character_index].cb_count[world] > 0)
					{
						D_global_asm_80754280[0].hud_state = 1;
					}
				}
			}
		}
		else
		{
			if (tag_countdown == 2)
			{
				for (s32 i = 0; i < sizeof(important_huds); i++)
				{
					if (important_huds_changed[i])
					{
						D_global_asm_80754280[important_huds[i]].hud_state = 0;
					}
				}
			}
			else if (tag_countdown == 1)
			{
				for (s32 i = 0; i < sizeof(important_huds); i++)
				{
					if (important_huds_changed[i])
					{
						D_global_asm_80754280[important_huds[i]].hud_state = 1;
					}
				}
			}
		}
		s32 can_ta = canTagAnywhere();
		can_tag_anywhere = can_ta;
		// Input buffering
		if (current_character_index < TAG_ANYWHERE_KONG_LIMIT)
		{
			s32 change = 0;

			if (D_global_asm_807ECD58 & L_JPAD) // p1HeldButtons d_left
			{
				if (can_tag_left)
				{
					change -= 1;
				}
			}
			else
			{
				can_tag_left = 1;
			}

			if (D_global_asm_807ECD58 & R_JPAD) // p1HeldButtons d_right
			{
				if (can_tag_right)
				{
					change += 1;
				}
			}
			else
			{
				can_tag_right = 1;
			}
			if (!can_ta)
			{
				return;
			}

			if (change != 0)
			{
				can_tag_left = 0;
				can_tag_right = 0;

				s32 next_character = getTagAnywhereKong(change);
				if (next_character != current_character_index)
				{
					// Fix hand state
					if (((D_global_asm_807FC950[next_character].weapon_bitfield & 1) == 0) || (gPlayerPointer->was_gun_out == 0))
					{
						gPlayerPointer->hand_state = 1;
						gPlayerPointer->was_gun_out = 0;
						// Without this, tags to and from Diddy mess up
						if (next_character == 1)
						{
							gPlayerPointer->hand_state = 0;
						}
					}
					else
					{
						gPlayerPointer->hand_state = 2;
						gPlayerPointer->was_gun_out = 1;
						// Without this, tags to and from Diddy mess up
						if (next_character == 1)
						{
							gPlayerPointer->hand_state = 3;
						}
					}
					// Freeze the HUD so counters don't pop in for a few frames after a tag
					if (current_map == 42)
					{
						if (!func_global_asm_805FF0C8()) // hasTurnedInEnoughCBs
						{
							tag_countdown = 3;
							D_global_asm_80754280[0].freeze_timer = 1;
							D_global_asm_80754280[0].counter_timer = 0;
							D_global_asm_80754280[0].hud_state = 0;
						}
					}
					else
					{
						for (s32 i = 0; i < sizeof(important_huds); i++)
						{
							important_huds_changed[i] = 0;
							if (D_global_asm_80754280)
							{
								s32 hud_st = D_global_asm_80754280[important_huds[i]].hud_state;
								if ((hud_st == 1) || (hud_st == 2))
								{
									tag_countdown = 3;
									D_global_asm_80754280[important_huds[i]].freeze_timer = 0;
									D_global_asm_80754280[important_huds[i]].counter_timer = 0;
									D_global_asm_80754280[important_huds[i]].hud_state = 0;
									important_huds_changed[i] = 1;
								}
							}
						}
					}
					// Cancel Gorilla Gone
					if (gPlayerPointer->strong_kong_ostand_bitfield & 0x40)
					{
						func_global_asm_80602B60(0x6C, 0); // cancelMusic
						gPlayerPointer->obj_props_bitfield |= 0x8000;
						func_global_asm_806F12FC(gPlayerPointer); // removeGorillaGone
					}
					// Perform the tag
					s32 old_control_state = gPlayerPointer->control_state;
					grab_lock_timer = 0; // inactive without the grab-lock hook
					func_global_asm_806C8E58(next_character + 2); // tagKong
					func_global_asm_806CFF9C(gPlayerPointer);	  // clearTagSlide
					if (old_control_state == 0x4F)
					{
						// Fix the underwater tag memes
						gPlayerPointer->yVelocity = 0.0f;
						playAnimation(gPlayerPointer, 0x37);
						func_global_asm_80614D90(gPlayerPointer); // handleAnimation
						gPlayerPointer->control_state = old_control_state;
						gPlayerPointer->control_state_progress = 4;
					}
					gPlayerPointer->new_kong = next_character + 2;
				}
			}
		}
	}
}

void cFuncLoop(void)
{
	// Enable stack trace upon crash
	*(s8 *)(0x807563B4) = 1;
	*(s32 *)(0x80731F78) = 0;

	// Set Arcade High Scores
	*(u32 *)(0x807467EC) = 999950;
	*(u32 *)(0x807467F0) = 999950;
	*(u32 *)(0x807467F4) = 999950;
	*(u32 *)(0x807467F8) = 999950;
	*(u32 *)(0x807467FC) = 999950;

	// Unlock Mystery Menu
	if (!isFlagSet(0, 1))
	{
		for (s32 i = 0; i < 35; i++)
		{
			setFlag(i, 1, 1);
		}
	}

	tagAnywhere();
}


RECOMP_CALLBACK("*", dk64recomp_every_frame) void tag_anywhere(void) {
	if ((is_cutscene_active != 6) && (is_cutscene_active != 3) && (is_cutscene_active != 4) && (is_cutscene_active != 5)) {
		cFuncLoop();
	}
}