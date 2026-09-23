#include "modding.h"
#include "ultra64.h"
#include "enums.h"
#include "common_structs.h"
#include "tag_anywhere.h"

typedef struct {
    Actor* unk0;
    s32 unk4;
} GlobalASMStruct53;

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
void func_global_asm_806C8E58(s16 kong_actor_index); // tagKong
void func_global_asm_806CFF9C(void *player);	// clearTagSlide
void func_global_asm_806F12FC(void *actor); // removeGorillaGone
void func_global_asm_80602B60(s32 song, u8 unk0); // cancelMusic
void playAnimation(void *player, s32 anim_index);
void func_global_asm_80614D90(void *actor); // handleAnimation
u8 func_global_asm_805FF0C8(void); // hasTurnedInEnoughCBs
u8 getLevelIndex(u8 map, u8 lobby_is_isles); // getWorld
u8 isFlagSet(s16 flagIndex, u8 flagType);

// Vanilla data
extern PlayerProgress D_global_asm_807FC950[4];
extern s8 Mode;
extern u32 global_properties_bitfield;
extern Maps current_map;
extern s8 is_cutscene_active;
extern u8 D_global_asm_8076A0B1;
extern u16 D_global_asm_807FBB34;
extern GlobalASMStruct53 D_global_asm_807FB930[64]; // LoadedActorArray
extern u16 D_global_asm_807ECD58; // p1HeldButtons (held controller buttons; ControllerInput)
extern Actor *gPlayerPointer;
extern CharacterChange *character_change_array;
extern s8 current_character_index;
extern u8 D_global_asm_807FD798; // ModelTwoTouchCount
extern f32 D_global_asm_807FD888;
extern HUDDisplay *D_global_asm_80754280;
extern const map_bitfield banned_map_btf;
extern const movement_bitfield banned_movement_btf;

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
u8 tag_countdown = 0;
u8 item_cooldown = 0;
u8 can_tag_anywhere = FALSE;
u8 can_tag_left = FALSE;
u8 can_tag_right = FALSE;
const u8 important_huds[] = {0, 1};
u8 important_huds_changed[] = {0, 0};
s8 grab_lock_timer = -1;
u8 tag_locked = FALSE;
u8 action_tag_lock = FALSE;

u8 inTransform(void) {
	// Is the player mid-transformation? (blocks tagging)
	if (gPlayerPointer) {
		// 0x10 - Strong Kong, 0x20 - Orangstand Sprint
		if (gPlayerPointer->PaaD->unk1F0 & 0x30) {
			return TRUE;
		}
		// Rocketbarrel
		if (gPlayerPointer->control_state == 0x63) {
			return TRUE;
		}
	}
	if (character_change_array) {
		// 0 = Mini Monkey, 2 = Hunky Chunky (1 = normal size)
		return character_change_array->unk2C0 != 1;
	}
	return FALSE;
}

u8 canTagAnywhere(void) {
	s32 i;

	// Note: only called from tagAnywhere() once gPlayerPointer is known non-null.
	if (gPlayerPointer->PaaD->unk1F0 & 0x100) return 0; // Seasick
	if (gPlayerPointer->collision_queue_pointer) return 0;
	if (D_global_asm_807FD888 > 15.0f) return 0; // LZ fadeout in progress - can cause inconsistent graphical crashes
	if (inTransform()) return 0;
	if (is_cutscene_active) return 0;
	if (D_global_asm_807FD798 > 0) return 0; // ModelTwoTouchCount
	if ((tag_locked) || (action_tag_lock)) return 0;
	if (current_map == MAP_TROFF_N_SCOFF) {
		if (D_global_asm_8076A0B1 & 0x10) return 0;
		if (func_global_asm_805FF0C8()) {
			// hasTurnedInEnoughCBs
			if (gPlayerPointer->z_position < 560.0f) {
				// Too close to boss door
				return 0;
			}
		}
	}
	for (i = 0; i < D_global_asm_807FBB34; i++) {
		if (D_global_asm_807FB930[i].unk0) {
			switch (D_global_asm_807FB930[i].unk0->unk58) {
				case ACTOR_PROJECTILE_COCONUTS:
				case ACTOR_PROJECTILE_PEANUT:
				case ACTOR_PROJECTILE_GRAPE:
				case ACTOR_PROJECTILE_PINEAPPLE:
					return 0;
				case ACTOR_PROJECTILE_FEATHER:
					if (D_global_asm_807FB930[i].unk0->control_state == 0) {
						return 0;
					}
					break;
				default:
					break;
			}
		}
	}
	// In tag barrel / paused
	if (global_properties_bitfield & 2) return 0;
	if (tag_countdown != 0) return 0;
	if (item_cooldown != 0) return 0;
	s32 offset = current_map >> 3;
	s32 check = current_map % 8;
	if (banned_map_btf.as_bytes[offset] & (0x80 >> check)) {
		return 0;
	}
	s32 control_state = gPlayerPointer->control_state;
	offset = control_state >> 3;
	check = control_state % 8;
	if (banned_movement_btf.as_bytes[offset] & (0x80 >> check)) {
		return 0;
	}
	return 1;
}

s32 getTagAnywhereKong(s32 direction) {
	s32 i;
	s32 next_character;
	u8 reached_limit;
	u8 pass;

	// Get the next unlocked kong in the tag loop in the given direction
	next_character = current_character_index + direction;
	if (next_character < 0) {
		next_character = TAG_ANYWHERE_KONG_LIMIT - 1;
	} else if (next_character >= TAG_ANYWHERE_KONG_LIMIT) {
		next_character = 0;
	}
	i = 0;
	reached_limit = FALSE;
	while (i < TAG_ANYWHERE_KONG_LIMIT) {
		pass = FALSE;
		if (isFlagSet(kong_unlocked_flags[next_character], 0)) {
			pass = TRUE;
		}
		if (pass) {
			break;
		} else {
			if ((i + 1) == TAG_ANYWHERE_KONG_LIMIT) {
				reached_limit = 1;
				return current_character_index;
			} else {
				next_character += direction;
				if (next_character < 0) {
					next_character = TAG_ANYWHERE_KONG_LIMIT - 1;
				} else if (next_character >= TAG_ANYWHERE_KONG_LIMIT) {
					next_character = 0;
				}
			}
		}
		i++;
	}
	if (reached_limit) {
		return current_character_index;
	}
	return next_character;
}

void changeKong(s32 next_character) {
	u32 i;
	s32 hud_st;
	u8 old_control_state;

	if (((D_global_asm_807FC950[0].character_progress[next_character].weapon & 1) == 0) || (gPlayerPointer->PaaD->unk8C == 0)) {
		gPlayerPointer->unk146 = 1;
		gPlayerPointer->PaaD->unk8C = 0;
		// Without this, tags to and from Diddy mess up
		if (next_character == 1) {
			gPlayerPointer->unk146 = 0;
		}
	} else {
		gPlayerPointer->unk146 = 2;
		gPlayerPointer->PaaD->unk8C = 1;
		// Without this, tags to and from Diddy mess up
		if (next_character == 1) {
			gPlayerPointer->unk146 = 3;
		}
	}
	// Freeze the HUD so counters don't pop in for a few frames after a tag
	if (current_map == MAP_TROFF_N_SCOFF) {
		if (!func_global_asm_805FF0C8()) {
			// hasTurnedInEnoughCBs
			tag_countdown = 3;
			D_global_asm_80754280[0].freeze_timer = 1;
			D_global_asm_80754280[0].counter_timer = 0;
			D_global_asm_80754280[0].hud_state = 0;
		}
	} else {
		for (i = 0; i < sizeof(important_huds); i++) {
			important_huds_changed[i] = 0;
			if (D_global_asm_80754280) {
				hud_st = D_global_asm_80754280[important_huds[i]].hud_state;
				if ((hud_st == 1) || (hud_st == 2)) {
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
	if (gPlayerPointer->PaaD->unk1F0 & 0x40) {
		func_global_asm_80602B60(0x6C, 0); // cancelMusic
		gPlayerPointer->object_properties_bitfield |= 0x8000;
		func_global_asm_806F12FC(gPlayerPointer); // removeGorillaGone
	}
	// Perform the tag
	old_control_state = gPlayerPointer->control_state;
	grab_lock_timer = 0; // inactive without the grab-lock hook
	func_global_asm_806C8E58(next_character + 2); // tagKong
	func_global_asm_806CFF9C(gPlayerPointer);	  // clearTagSlide
	if (old_control_state == 0x4F) {
		// Fix the underwater tag memes
		gPlayerPointer->y_velocity = 0.0f;
		playAnimation(gPlayerPointer, 0x37);
		func_global_asm_80614D90(gPlayerPointer); // handleAnimation
		gPlayerPointer->control_state = old_control_state;
		gPlayerPointer->control_state_progress = 4;
	}
	gPlayerPointer->PaaD->unk1EE = next_character + 2;
}

void tagAnywhere(void) {
	s32 world;
	u32 i;
	s32 change;
	s32 next_character;

	if (!gPlayerPointer) return;
	if (tag_countdown > 0) {
		tag_countdown--;
	}
	if (current_map == MAP_TROFF_N_SCOFF) {
		if (tag_countdown == 2) {
			D_global_asm_80754280[0].hud_state = 1;
			if (gPlayerPointer->control_state == 108) {
				world = getLevelIndex(current_map, 0);
				if (D_global_asm_807FC950[0].character_progress[current_character_index].coloured_bananas[world] > 0) {
					D_global_asm_80754280[0].hud_state = 0;
				}
			}
		} else if (tag_countdown == 1) {
			if (gPlayerPointer->control_state == 108) {
				world = getLevelIndex(current_map, 0);
				if (D_global_asm_807FC950[0].character_progress[current_character_index].coloured_bananas[world] > 0) {
					D_global_asm_80754280[0].hud_state = 1;
				}
			}
		}
	} else {
		if (tag_countdown == 2) {
			for (i = 0; i < sizeof(important_huds); i++) {
				if (important_huds_changed[i]) {
					D_global_asm_80754280[important_huds[i]].hud_state = 0;
				}
			}
		} else if (tag_countdown == 1) {
			for (i = 0; i < sizeof(important_huds); i++) {
				if (important_huds_changed[i])
				{
					D_global_asm_80754280[important_huds[i]].hud_state = 1;
				}
			}
		}
	}
	can_tag_anywhere = canTagAnywhere();
	// Input buffering
	if (current_character_index < TAG_ANYWHERE_KONG_LIMIT) {
		change = 0;

		if (D_global_asm_807ECD58 & L_JPAD) {
			if (can_tag_left) {
				change--;
			}
		} else {
			can_tag_left = TRUE;
		}

		if (D_global_asm_807ECD58 & R_JPAD) {
			if (can_tag_right) {
				change++;
			}
		} else {
			can_tag_right = TRUE;
		}

		if (!can_tag_anywhere) {
			return;
		}

		if (change != 0) {
			can_tag_left = FALSE;
			can_tag_right = FALSE;

			next_character = getTagAnywhereKong(change);
			if (next_character != current_character_index) {
				// Fix hand state
				changeKong(next_character);
			}
		}
	}
}


RECOMP_CALLBACK("*", dk64recomp_every_frame) void tag_anywhere(void) {
	if ((is_cutscene_active != 6) && (is_cutscene_active != 3) && (is_cutscene_active != 4) && (is_cutscene_active != 5)) {
		tagAnywhere();
		if ((global_properties_bitfield & 2) == 0) {
			if (grab_lock_timer >= 0) {
				grab_lock_timer++;
				if (grab_lock_timer > 10) {
					grab_lock_timer = -1;
				}
			}
			if (item_cooldown > 0) {
				item_cooldown--;
			}
		}
	}
}

RECOMP_EXPORT char get_tag_locked(void) {
	return tag_locked;
}

RECOMP_EXPORT void set_tag_locked(u8 locked) {
	tag_locked = locked;
}