#include "../../battle/battle.h"
#include "../../psx/mutil.h"
#include "sansph1.h"

SansPhase1 sansphase1;

void Load_Sans(void)
{
	Gfx_LoadTex(&sansphase1.tex, IO_Read("\\CHARS\\SANSPH1.TIM;1"), GFX_LOADTEX_FREE);
}

static const u8 sanshead[3][4] = {
	{0,0,31,30},
	{32,0,31,30},
	{64,0,31,30}
};

static const u8 leftarm[3][6] = {
	{0,85,18,35,14,11},
	{19,85,27,18,22,12},
	{47,85,26,18,21,12}
};

static const u8 rightarm[3][6] = {
	{0,121,18,36,1,12},
	{19,121,27,18,2,12},
	{47,121,27,18,2,12}
};

void Draw_Sans(void)
{
	s16 position[2] = {0,-10};
	sansphase1.timer += 2;
	u8 timer = sansphase1.timer;
	u8 head = sansphase1.head;
	u8 larm = sansphase1.leftarm;
	u8 rarm = sansphase1.rightarm;
	
	RECT head_src = {sanshead[head][0], sanshead[head][1], sanshead[head][2], sanshead[head][3]};
	RECT head_dst = {
		0 + position[0],
		-44 + position[1] + (smooth(timer) / 500),
		head_src.w,
		head_src.h
	};
	Battle_DrawTexRotate(&sansphase1.tex, &head_src, &head_dst, 0, 15, 27);

	RECT knot_src = {0, 31, 13, 19};
	RECT knot_dst = {
		0 + position[0],
		-20 + position[1] + (smooth(timer) / 750),
		knot_src.w,
		knot_src.h
	};
	Battle_DrawTexRotate(&sansphase1.tex, &knot_src, &knot_dst, (smooth(timer / 2) / 50), 5, 5);

	RECT torso_src = {0, 51, 35, 33};
	RECT torso_dst = {
		0 + position[0],
		-22 + position[1] + (smooth(timer) / 750),
		torso_src.w,
		torso_src.h
	};
	Battle_DrawTexRotate(&sansphase1.tex, &torso_src, &torso_dst, 0, 17, 27);
	
	RECT leftarm_src = {leftarm[larm][0], leftarm[larm][1], leftarm[larm][2], leftarm[larm][3]};
	RECT leftarm_dst = {
		-16 + position[0],
		-36 + position[1] + (smooth(timer) / 600),
		leftarm_src.w,
		leftarm_src.h
	};
	Battle_DrawTexRotate(&sansphase1.tex, &leftarm_src, &leftarm_dst, 0, leftarm[larm][4], leftarm[larm][5]);
	
	RECT rightarm_src = {rightarm[rarm][0], rightarm[rarm][1], rightarm[rarm][2], rightarm[rarm][3]};
	RECT rightarm_dst = {
		15 + position[0],
		-36 + position[1] + (smooth(timer) / 600),
		rightarm_src.w,
		rightarm_src.h
	};
	Battle_DrawTexRotate(&sansphase1.tex, &rightarm_src, &rightarm_dst, 0, rightarm[rarm][4], rightarm[rarm][5]);
	
	RECT legs_src = {0, 158, 46, 26};
	RECT legs_dst = {
		0 + position[0],
		0 + position[1],
		legs_src.w,
		legs_src.h
	};
	Battle_DrawTexRotate(&sansphase1.tex, &legs_src, &legs_dst, 0, 24, 21);
}