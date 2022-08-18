#ifndef PSXF_GUARD_BATTLE_H
#define PSXF_GUARD_BATTLE_H

#include "../psx/gfx.h"
#include "../psx/io.h"
#include "../psx/fixed.h"
#include "../fonts/font.h"

typedef struct
{
	FontData font_ut;
	
	boolean act_perm;
	u8 act_select;
	u32 sounds[6];
	char text[40];
	
	struct
	{
		fixed_t x, y, zoom;
		s16 tx, ty, tzoom;
		s8 speed;
	} camera;
	struct
	{
		fixed_t x, y, xsize, ysize;
		s16 tx, ty, txsize, tysize;
		s8 speed;
	} box;
	struct
	{
		s16 x, y, angle;
		u8 speed;
		u8 hp, hpmax;
	} soul;
} Battle;

extern Battle battle;


void Battle_DrawTex(Gfx_Tex *tex, const RECT *src, const RECT *dst);
void Battle_DrawTexRotate(Gfx_Tex *tex, const RECT *src, const RECT *dst, s16 angle, s16 hx, s16 hy);

//Battle Effects
void Flash_Tick();
void Flash();

//Battle functions
void Battle_Load();
void Battle_Unload();
void Battle_Tick();

void Soul();
void Battle_Box_Tick();
void Battle_Box_Draw();
void Attack_Hiding();
void Battle_Camera_Tick();
void Battle_HUD();

void Battle_Actions();

#endif
