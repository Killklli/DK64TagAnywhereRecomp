#include "modding.h"
#include "ultra64.h"
#include "enums.h"
#include "common_structs.h"
#include "tag_anywhere.h"

typedef struct {
    u8 unk0;
    u8 unk1;
    u8 unk2;
    u8 unk3;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    s16 unk10;
    s16 unk12;
    s16 unk14;
    s16 unk16;
    s8 unk18;
    s8 unk19;
    s8 unk1A;
    s8 unk1B;
} Struct807FDCC0_unk34;

typedef struct Struct807FDCC0 Struct807FDCC0;

struct Struct807FDCC0 {
    Actor *unk0; // Used
    u8 unk4; // Used
    u8 unk5;
    u8 unk6;
    u8 unk7;
    f32 unk8;
    f32 unkC;
    s32 unk10;
    f32 unk14;
    u8 unk18;
    s8 unk19;
    s8 unk1A;
    s8 unk1B;
    f32 unk1C;
    f32 unk20;
    f32 unk24;
    f32 unk28;
    f32 unk2C;
    s8 unk30;
    u8 unk31;
    s8 unk32;
    s8 unk33;
    Struct807FDCC0_unk34 *unk34;
    Struct807FDCC0 *next;
};

typedef struct Struct807FD610 {
    s32 unk0; // Timer that ticks up once per frame
    f32 unk4; // Probably float
    f32 unk8; // Probably float
    f32 unkC; // Probably float
    f32 unk10[4];
    s16 unk20[4];
    s16 unk28; // Used
    u16 unk2A; // Used, controller button bitfield
    u16 unk2C; // Used, controller button bitfield
    s8 unk2E; // Used
    s8 unk2F; // Used
    u8 unk30; // Used
    u8 unk31;
    s16 unk32;
} Struct807FD610;

extern Struct807FD610 D_global_asm_807FD610[];
extern f32 D_global_asm_80753E10[];
extern s16 D_global_asm_80753E00[];
extern s32 D_global_asm_807FBB64;
extern s32 D_global_asm_807FBB68;
extern Actor *gCurrentActorPointer;
extern Actor *gCurrentPlayer;
extern PlayerAdditionalActorData *extra_player_info_pointer;
extern Maps current_map;
extern Struct807FDCC0 *D_global_asm_807FDCC0;
extern s16 D_global_asm_807FD584;
extern u8 cc_player_index;
extern CharacterProgress *D_global_asm_807FD568;
extern u32 object_timer;
extern u8 D_global_asm_807FBE08;
extern u8 D_global_asm_807FBC55;
s32 func_global_asm_806725A0(Actor *arg0, s16 arg1);
u8 func_global_asm_806CFC90(Actor *arg0, f32 *arg1, u8 arg2, f32 arg3);
void func_global_asm_80666AC4(s16 *arg0, s16 *arg1);
u8 func_global_asm_80666AEC(void);
u8 setAction(s16 actionIndex, Actor *actor, u8 playerIndex);
u8 func_global_asm_8072F4A8(Actor *arg0, u8 arg1, f32 *arg2, f32 *arg3, f32 *arg4);
u8 func_global_asm_8072F59C(void *arg0, Struct807FDCC0 *arg1, f32 *arg2, u8 *arg3);
void func_global_asm_8072FCC4(void *arg0, s32 arg1, f32 arg2, f32 *arg3);
f32 func_global_asm_8072FA14(Actor *arg0, PlayerAdditionalActorData *arg1, Struct807FDCC0 *arg2, u8 arg3);
s32 func_global_asm_806E5488(Actor *arg0);
void changeCollectableCount(s32 HUDItemIndex, u8 playerIndex, s16 amount);
void func_global_asm_806F8BC4(s32 HUDItemIndex, u8 arg1, s32 arg2);
u16 func_global_asm_806F8AD4(u8 arg0, u8 playerIndex);
u8 func_global_asm_806E560C(Actor *arg0);
s32 func_global_asm_806E527C(void);
s32 func_global_asm_806E5488(Actor *arg0);
u8 func_global_asm_8066F250(Actor *arg0, s16 *arg1, s16 *arg2, u8 *arg3);
int func_global_asm_80714608(s32 arg0);
float sqrtf(float);

extern s8 grab_lock_timer;
extern u8 action_tag_lock;
extern u8 item_cooldown;

u8 isGrabLocked(void) {
    if ((grab_lock_timer >= 0) && (grab_lock_timer < 2)) {
        return TRUE;
    }
    return FALSE;
}

// Ledge Grab
RECOMP_PATCH void func_global_asm_806CF9CC(void) {
    f32 sp3C;
    u8 sp3B;
    u8 sp3A;
    s16 sp38;
    s16 sp36;
    u8 sp35;
    u8 var_v1;
    u8 var_t0;
    u8 temp_v1;
    u8 temp_a2;

    if (isGrabLocked()) {
        return;
    }

    if (D_global_asm_807FBB64 & 0x20000) {
        return;
    }
    if (!gCurrentActorPointer->unkFC) {
        return;
    }
    if (extra_player_info_pointer->unk8C) {
        return;
    }
    if (gCurrentActorPointer->unk6A & 1) {
        return;
    }
    if (!extra_player_info_pointer->unkE8) {
        return;
    }
    if ((current_map == MAP_FUNGI_DOGADON) || (current_map == MAP_AZTEC_DOGADON)) {
        var_t0 = TRUE;
    } else {
        var_t0 = FALSE;
    }
    temp_a2 = temp_v1 = !func_global_asm_806725A0(gCurrentActorPointer, gCurrentActorPointer->y_rotation);
    if ((temp_a2) || !(D_global_asm_80753E10[D_global_asm_807FD584] < gCurrentActorPointer->unkB8) || (var_t0 != 0)) {
        sp3B = func_global_asm_806CFC90(gCurrentActorPointer, &sp3C, temp_a2, var_t0 ? 30.0 : 15.0);
        func_global_asm_80666AC4(&sp38, &sp36);
        var_v1 = FALSE;
        if ((sp3B) && (gCurrentActorPointer->y_velocity < 0.0) && (sp36 >= 0x385)) {
            var_v1 = FALSE;
            if (func_global_asm_80666AEC()) {
                if ((gCurrentActorPointer->y_position - gCurrentActorPointer->floor) > 15.0f) {
                    if (var_t0) {
                        if (((D_global_asm_80753E00[D_global_asm_807FD584] + gCurrentActorPointer->y_position) < (sp3C + 15.0f)) && (((sp3C - D_global_asm_80753E00[D_global_asm_807FD584]) - gCurrentActorPointer->y_position) < 80.0f)) {
                            var_v1 = TRUE;
                        }
                    } else {
                        if (((D_global_asm_80753E00[D_global_asm_807FD584] + gCurrentActorPointer->y_position) < (sp3C - 5.0f)) && (((sp3C - D_global_asm_80753E00[D_global_asm_807FD584]) - gCurrentActorPointer->y_position) < 15.0f)) {
                            var_v1 = TRUE;
                        }
                    }
                }
            }
        }
        if (!var_v1) {
            return;
        }
        action_tag_lock = TRUE;
        if (!setAction(0xA, NULL, cc_player_index)) {
            return;
        }
        extra_player_info_pointer->unkF0_f32 = sp3C;
    }
}

// Pole Grab
RECOMP_PATCH void func_global_asm_8072F230(Actor *arg0, u8 arg1, u8 arg2) {
    s32 pad;
    f32 sp90; // sp90
    f32 sp8C; // sp8C
    f32 sp88; // sp88
    f32 dx;
    f32 dy;
    f32 sp7C; // sp7C
    f32 dz;
    f32 least;
    u8 sp73;
    u8 sp72;
    f32 sp6C; // sp6C
    Struct807FDCC0 *current;
    PlayerAdditionalActorData *PaaD; // sp64
    Struct807FDCC0 *found;
    u8 temp_s1;
    u8 var_s4;

    if (isGrabLocked()) {
        return;
    }

    PaaD = arg0->additional_actor_data;
    current = D_global_asm_807FDCC0;
    least = 9999.0f;
    found = NULL;
    var_s4 = arg0->unk58 == ACTOR_CHUNKY && character_change_array[PaaD->unk1A4].unk2C0 == 2;
    while (current) {
        temp_s1 = func_global_asm_8072F4A8(current->unk0, current->unk4, &sp90, &sp8C, &sp88);
        dx = (arg0->x_position - sp90);
        dy = (arg0->y_position - sp8C);
        dz = (arg0->z_position - sp88);
        if (sqrtf(SQ(dx) + SQ(dy) + SQ(dz)) < current->unk1C) {
            if (current->unk31 && ((current->unk6 == 1) || (arg2 && current->unk0->object_properties_bitfield & 0x04000000))) {
                if (!temp_s1 || !var_s4) {
                    if (func_global_asm_8072F59C(arg0, current, &sp7C, &sp72)) {
                        if (sp7C < least) {
                            least = sp7C;
                            found = current;
                            sp73 = sp72;
                        }
                    }
                }
            }
        }
        current = current->next;
    }
    if (found != NULL) {
        func_global_asm_8072FCC4(found, sp73, func_global_asm_8072FA14(arg0, PaaD, found, sp73), &sp6C);
        PaaD->unk138 = sp6C;
        PaaD->unk130 = found->unk0;
        PaaD->unk134 = found->unk5;
        PaaD->unk19C = 0;
        PaaD->unk19E = 0xFFF;
        arg0->unkB8 = 0.0f;
        switch (found->unk6) {
            case 0:
                action_tag_lock = TRUE;
                setAction(0xC, NULL, arg1);
                break;
            case 1:
                action_tag_lock = TRUE;
                setAction(0xB, NULL, arg1);
                break;
        }
    }
}

// Push
RECOMP_PATCH void func_global_asm_80678E6C(Actor *arg0) {
    u8 sp27;

    if ((arg0->noclip_byte & 4) && (D_global_asm_807FBE08 == 0)) {
        if (arg0->object_properties_bitfield & 0x10000) {
            arg0->unkFC = 0;
            arg0->unkFD = 0;
        }
        arg0->unkFC |= func_global_asm_8066F250(arg0, &arg0->unkF4, &arg0->unkF6, &sp27);
        sp27 |= D_global_asm_807FBC55;
        if (sp27 != 0) {
            if (!(arg0->unk6A & 0x10)) {
                arg0->unk6A |= 0x10;
                if ((arg0 == gCurrentPlayer) && (!isGrabLocked())) {
                    action_tag_lock = TRUE;
                    setAction(4, NULL, cc_player_index);
                }
            }
        }
        if (sp27 == 0) {
            arg0->unk6A &= ~0x10;
            return;
        }
    } else {
        arg0->unkFC = 0;
        arg0->unkFD = 0;
        arg0->unk6A &= ~0x10;
    }
}

// Instrument
void func_global_asm_806E52D0(void) {
    u8 temp_v1;
    u32 temp_v0;

    if ((D_global_asm_807FD610[cc_player_index].unk2C & U_CBUTTONS)
        && (object_timer >= 3U)
        && (D_global_asm_807FD568->instrument & 1)
        && !(D_global_asm_807FBB64 & 0x4000)
        && !(D_global_asm_807FBB68 & 1)
        && (character_change_array[cc_player_index].unk2C0 != 2)
        && (func_global_asm_806E5488(gCurrentActorPointer) == 0)
        && (func_global_asm_806E527C() == 0)
        && (extra_player_info_pointer->unk245 == 0)) {
        temp_v0 = func_global_asm_806E560C(gCurrentActorPointer);
        temp_v1 = temp_v0;
        if (current_map != MAP_KROOL_FIGHT_LANKY_PHASE || temp_v0) {
            if (func_global_asm_806F8AD4(7, cc_player_index) || temp_v1) {
                action_tag_lock = TRUE;
                setAction(0x53, NULL, extra_player_info_pointer->unk1A4);
                if (!(D_global_asm_807FBB68 & 2)) {
                    gCurrentActorPointer->noclip_byte = 1;
                }
                if (!temp_v1) {
                    changeCollectableCount(7, cc_player_index, -1);
                }
            }
            if (!temp_v1) {
                func_global_asm_806F8BC4(7, 0, 0);
            }
        }
    }
}

// Gun Pull
RECOMP_PATCH void func_global_asm_806E5FA0(void) {
    if (((D_global_asm_807FD610[cc_player_index].unk2C & L_CBUTTONS))
        && (D_global_asm_807FD568->weapon & 1)
        && !(D_global_asm_807FBB64 & 0x200)
        && (character_change_array[cc_player_index].unk2C0 == 1)
        && !(extra_player_info_pointer->unk1F0 & 0x30)
        && !func_global_asm_80714608(0)) {
        action_tag_lock = TRUE;
        setAction(0x15, NULL, cc_player_index);
    }
}

RECOMP_HOOK("func_global_asm_806F54E0")
void initCooldown(u8 playerIndex, s32 actorBehaviourIndex, u8 arg2) {
    if (item_cooldown < 2) {
        item_cooldown = 2;
    }
}

RECOMP_HOOK("func_global_asm_806F53EC")
void *initCooldown2(void *arg0) {
    if (item_cooldown < 15) {
        item_cooldown = 15;
    }
}