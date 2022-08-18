#include "battle.h"

#include "../psx/mem.h"
#include "../psx/io.h"
#include "../psx/gfx.h"
#include "../psx/audio.h"
#include "../psx/pad.h"
#include "../psx/archive.h"
#include "../psx/mutil.h"
#include "../psx/random.h"

#include "../fonts/font.h"

#include "../chars/sansph1/sansph1.h"

Battle battle;

Gfx_Tex tex_hud;

u8 shakesin = 0;
fixed_t shake = 0;
u8 smoothshit = 0;
u16 timer = 0;
s16 flash = 0;

static void Event()
{
	timer += 1;
	FntPrint("timer: %d", timer);
	
	if(timer == 1)
	{
		flash = 200;
		shake = 1000;
		battle.camera.zoom += FIXED_DEC(1,10);
	}
	if(timer == 120)
	{
		shake = 500;
		battle.camera.zoom += FIXED_DEC(1,10);
	}
	if(timer == 240)
	{
		shake = 500;
		battle.camera.zoom += FIXED_DEC(1,10);
	}
	if(timer == 360)
	{
		shake = 500;
		battle.camera.zoom += FIXED_DEC(1,10);
	}
	if(timer == 480)
	{
		flash = 200;
		shake = 1000;
		battle.camera.zoom += FIXED_DEC(1,10);
	}
	if(timer == 600)
	{
		shake = 500;
		battle.camera.zoom += FIXED_DEC(1,10);
	}
	if(timer == 720)
	{
		shake = 500;
		battle.camera.zoom += FIXED_DEC(1,10);
	}
	
	if(timer == 847)
	{
		shake = 1000;
		sansphase1.leftarm = 1;
		sansphase1.rightarm = 1;
		battle.camera.ty += 36;
		battle.camera.tzoom += FIXED_DEC(3,4);
		battle.camera.speed = FIXED_UNIT / 12;
	}
	if(timer == 870)
	{
		shake = 1000;
		sansphase1.head = 1;
		sansphase1.leftarm = 2;
		sansphase1.rightarm = 2;
		battle.camera.ty += 24;
		battle.camera.tzoom += FIXED_DEC(3,4);
	}
	if(timer == 900)
	{
		shake = 1000;
		sansphase1.head = 2;
		battle.camera.ty += 12;
		battle.camera.tzoom += FIXED_DEC(3,4);
	}
	if(timer == 960)
	{
		battle.camera.ty = 0;
		battle.camera.tzoom = FIXED_DEC(1,1);
		battle.camera.speed = FIXED_UNIT / 12;
	}
}

void Battle_Tick()
{
	Flash_Tick();
	
	Event();
	//Camera
	Battle_Camera_Tick();
	
	//Draw Char
	Draw_Sans();
	
	//HUD & Soul
	Soul();
	Battle_HUD();
	
	//Box & Attack Hiding
	Battle_Box_Tick();
	Battle_Box_Draw();
	Attack_Hiding();
}

void Battle_HUD()
{
	RECT hp_src = {0, 45, 2, 2};
	RECT hp_dst = {
		-23,
		70,
		battle.soul.hp / 3,
		10
	};
	Battle_DrawTex(&tex_hud, &hp_src, &hp_dst);
	
	RECT hpback_src = {4, 45, 2, 2};
	RECT hpback_dst = {
		-23,
		70,
		battle.soul.hpmax / 3,
		10
	};
	Battle_DrawTex(&tex_hud, &hpback_src, &hpback_dst);
	
	RECT hpol_src = {248, 0, 2, 2};
	RECT hpol_dst = {
		-24,
		69,
		battle.soul.hpmax / 3 + 2,
		12
	};
	Battle_DrawTex(&tex_hud, &hpol_src, &hpol_dst);
	
	Battle_Actions();
}

void Soul()
{
	if (pad_state.held & PAD_UP)
		battle.soul.y -= battle.soul.speed;
	if (pad_state.held & PAD_DOWN)
		battle.soul.y += battle.soul.speed;
	if (pad_state.held & PAD_LEFT)
		battle.soul.x -= battle.soul.speed;
	if (pad_state.held & PAD_RIGHT)
		battle.soul.x += battle.soul.speed;
	
	if(battle.soul.y < battle.box.y + (-battle.box.ysize / 2) + 6)
		battle.soul.y = battle.box.y + (-battle.box.ysize / 2) + 6;
	if(battle.soul.y > battle.box.y + (battle.box.ysize / 2) - 4)
		battle.soul.y = battle.box.y + (battle.box.ysize / 2) - 4;
	if(battle.soul.x < battle.box.x + (-battle.box.xsize / 2) + 6)
		battle.soul.x = battle.box.x + (-battle.box.xsize / 2) + 6;
	if(battle.soul.x > battle.box.x + (battle.box.xsize / 2) - 4)
		battle.soul.x = battle.box.x + (battle.box.xsize / 2) - 4;
	
	
	RECT soul_src = {225, 0, 8, 8};
	RECT soul_dst = {
		battle.soul.x,
		battle.soul.y,
		8,
		8
	};
	Battle_DrawTexRotate(&tex_hud, &soul_src, &soul_dst, 0, 4, 4);
}

void Battle_Box_Tick()
{
	battle.box.x = lerp(battle.box.x, battle.box.tx, battle.box.speed);
	battle.box.y = lerp(battle.box.y, battle.box.ty, battle.box.speed);
	battle.box.xsize = lerp(battle.box.xsize, battle.box.txsize, battle.box.speed);
	battle.box.ysize = lerp(battle.box.ysize, battle.box.tysize, battle.box.speed);
}

void Attack_Hiding()
{
	RECT boxblack_src = {248, 0, 2, 2};
	
	u16 offset = 320;
	
	RECT boxwidth_dst = {
		battle.box.x - offset,
		battle.box.y + (battle.box.ysize / 2) - (offset / 2),
		offset,
		offset
	};
	Battle_DrawTexRotate(&tex_hud, &boxblack_src, &boxwidth_dst, 0, battle.box.xsize / 2, battle.box.ysize / 2);
	
	boxwidth_dst.x += battle.box.xsize + offset;
	Battle_DrawTexRotate(&tex_hud, &boxblack_src, &boxwidth_dst, 0, battle.box.xsize / 2, battle.box.ysize / 2);
	
	RECT boxheight_dst = {
		battle.box.x + (battle.box.xsize / 2) - (offset / 2),
		battle.box.y - offset,
		offset,
		offset
	};
	Battle_DrawTexRotate(&tex_hud, &boxblack_src, &boxheight_dst, 0, battle.box.xsize / 2, battle.box.ysize / 2);
	
	boxheight_dst.y += battle.box.ysize + offset;
	Battle_DrawTexRotate(&tex_hud, &boxblack_src, &boxheight_dst, 0, battle.box.xsize / 2, battle.box.ysize / 2);
}

void Battle_Box_Draw()
{
	RECT boxwhite_src = {248, 8, 2, 2};
	
	
	RECT boxwidth_dst = {
		battle.box.x,
		battle.box.y,
		2,
		battle.box.ysize + 2
	};
	Battle_DrawTexRotate(&tex_hud, &boxwhite_src, &boxwidth_dst, 0, battle.box.xsize / 2, battle.box.ysize / 2);
	
	boxwidth_dst.x += battle.box.xsize;
	Battle_DrawTexRotate(&tex_hud, &boxwhite_src, &boxwidth_dst, 0, battle.box.xsize / 2, battle.box.ysize / 2);
	
	RECT boxheight_dst = {
		battle.box.x,
		battle.box.y,
		battle.box.xsize + 2,
		2
	};
	Battle_DrawTexRotate(&tex_hud, &boxwhite_src, &boxheight_dst, 0, battle.box.xsize / 2, battle.box.ysize / 2);
	
	boxheight_dst.y += battle.box.ysize;
	Battle_DrawTexRotate(&tex_hud, &boxwhite_src, &boxheight_dst, 0, battle.box.xsize / 2, battle.box.ysize / 2);
}

void Battle_Camera_Tick()
{
	battle.camera.x = lerp(battle.camera.x, battle.camera.tx, battle.camera.speed);
	battle.camera.y = lerp(battle.camera.y, battle.camera.ty, battle.camera.speed);
	battle.camera.zoom = lerp(battle.camera.zoom, battle.camera.tzoom, battle.camera.speed);
	
	shakesin += 25;
	shake = lerp(shake, FIXED_DEC(0,1), FIXED_UNIT / 8);
	if(shake > 10)
	{
		battle.camera.x += smooth(shakesin + 64) / (1000 - shake);
		battle.camera.y += smooth(shakesin) / (1000 - shake);
	}
}

void Battle_DrawTex(Gfx_Tex *tex, const RECT *src, const RECT *dst)
{
	Battle_DrawTexRotate(tex, src, dst, 0, 0, 0);
}

void Battle_DrawTexRotate(Gfx_Tex *tex, const RECT *src, const RECT *dst, s16 angle, s16 hx, s16 hy)
{
	fixed_t xz = dst->x;
	fixed_t yz = dst->y;
	fixed_t wz = dst->w;
	fixed_t hz = dst->h;
	
	RECT sdst = {
		SCREEN_WIDTH2 + FIXED_MUL(xz + battle.camera.x, battle.camera.zoom),
		SCREEN_HEIGHT2 + FIXED_MUL(yz + battle.camera.y, battle.camera.zoom),
		FIXED_MUL(wz, battle.camera.zoom),
		FIXED_MUL(hz, battle.camera.zoom)
	};
	Gfx_DrawTexRotate(tex, src, &sdst, angle, FIXED_MUL(hx, battle.camera.zoom), FIXED_MUL(hy, battle.camera.zoom));
}

void Battle_Load()
{
	Gfx_SetClear(0, 0, 0);
	
	Load_Sans();
	
	FontData_Load(&battle.font_ut, Font_UT);
	strcpy(battle.text, "* testing lol it works\n* sussy baka");
	
	battle.act_perm = false;
	battle.act_select = 1;
	
	battle.soul.hpmax = 48;
	battle.soul.hp = 24;
	
	IO_Data arc_battle = IO_Read("\\BATTLE.ARC;1");
	Gfx_LoadTex(&tex_hud, Archive_Find(arc_battle, "hud0.tim"), 0);
	Mem_Free(arc_battle);
	
	battle.camera.x = 0;
	battle.camera.y = 0;
	battle.camera.zoom = FIXED_DEC(1,1);
	battle.camera.tx = 0;
	battle.camera.ty = 0;
	battle.camera.tzoom = FIXED_DEC(1,1);
	battle.camera.speed = FIXED_UNIT / 32;
	
	battle.box.x = 0;
	battle.box.y = 32;
	battle.box.xsize = 60;
	battle.box.ysize = 60;
	battle.box.tx = 0;
	battle.box.ty = 32;
	battle.box.txsize = 300;
	battle.box.tysize = 60;
	battle.box.speed = FIXED_UNIT / 12;
	
	battle.soul.x = 0;
	battle.soul.y = 0;
	battle.soul.speed = 1;
	
	//Load sfx
	Audio_ClearAlloc();
	CdlFILE file;

	IO_FindFile(&file, "\\SOUNDS\\SWITCH.VAG;1");
   	u32 *data = IO_ReadFile(&file);
	battle.sounds[0] = Audio_LoadVAGData(data, file.size);
	Mem_Free(data);
	
	IO_FindFile(&file, "\\SOUNDS\\SELECT.VAG;1");
   	data = IO_ReadFile(&file);
	battle.sounds[1] = Audio_LoadVAGData(data, file.size);
	Mem_Free(data);
	
	Audio_LoadMus("\\MUSIC\\PHASE1B.MUS;1");
	Audio_PlayMus(true);
	Audio_SetVolume(0, 0x3FFF, 0x0000);
	Audio_SetVolume(1, 0x0000, 0x3FFF);
}

void Battle_Actions()
{
	if (battle.act_perm)
	{
		battle.font_ut.draw(&battle.font_ut,
			battle.text,
			battle.box.x - battle.box.xsize / 2 + 6,
			battle.box.y - battle.box.ysize / 2 + 6,
			FontAlign_Left
		);
		
		if (pad_state.press & PAD_LEFT)
		{
			battle.act_select -= 1;
			Audio_PlaySound(battle.sounds[0], 0x3fff);
		}
		if (pad_state.press & PAD_RIGHT)
		{
			battle.act_select += 1;
			Audio_PlaySound(battle.sounds[0], 0x3fff);
		}
		if (battle.act_select < 1)
			battle.act_select = 4;
		if (battle.act_select > 4)
			battle.act_select = 1;
	}
	
	RECT fight_src = {0, (battle.act_select == 1 && battle.act_perm) ? 22 : 0, 57, 23};
	RECT fight_dst = {
		-145,
		85,
		fight_src.w,
		fight_src.h
	};
	Battle_DrawTex(&tex_hud, &fight_src, &fight_dst);
	
	RECT act_src = {56, (battle.act_select == 2 && battle.act_perm) ? 22 : 0, 57, 23};
	RECT act_dst = {
		-69,
		85,
		act_src.w,
		act_src.h
	};
	Battle_DrawTex(&tex_hud, &act_src, &act_dst);
	
	RECT item_src = {112, (battle.act_select == 3 && battle.act_perm) ? 22 : 0, 57, 23};
	RECT item_dst = {
		11,
		85,
		item_src.w,
		item_src.h
	};
	Battle_DrawTex(&tex_hud, &item_src, &item_dst);
	
	RECT mercy_src = {168, (battle.act_select == 4 && battle.act_perm) ? 22 : 0, 57, 23};
	RECT mercy_dst = {
		89,
		85,
		mercy_src.w,
		mercy_src.h
	};
	Battle_DrawTex(&tex_hud, &mercy_src, &mercy_dst);
}
	
void Battle_Unload()
{
	Gfx_SetClear(0, 0, 0);
}

void Flash_Tick()
{
	static const RECT dst = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
	u8 flash_col = flash;
	Gfx_BlendRect(&dst, flash_col, flash_col, flash_col, 1);
	if(flash > 0)
		flash -= 4;
	else
		flash = 0;
}