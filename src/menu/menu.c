#include "menu.h"

#include "../main.h"
#include "../psx/mem.h"
#include "../psx/io.h"
#include "../psx/gfx.h"
#include "../psx/audio.h"
#include "../psx/pad.h"
#include "../psx/archive.h"
#include "../psx/mutil.h"
#include "../psx/random.h"

#include "../battle/battle.h"

Gfx_Tex tex_menu;

Menu menu;

void Menu_Load()
{
	Gfx_SetClear(0, 0, 0);
	
	IO_Data arc_menu = IO_Read("\\MENU.ARC;1");
	Gfx_LoadTex(&tex_menu, Archive_Find(arc_menu, "menu0.tim"), 0);
	Mem_Free(arc_menu);
	
	//Load sfx
	Audio_ClearAlloc();
	CdlFILE file;

	IO_FindFile(&file, "\\SOUNDS\\SWITCH.VAG;1");
   	u32 *data = IO_ReadFile(&file);
	menu.sounds[0] = Audio_LoadVAGData(data, file.size);
	Mem_Free(data);
	
	IO_FindFile(&file, "\\SOUNDS\\SELECT.VAG;1");
   	data = IO_ReadFile(&file);
	menu.sounds[1] = Audio_LoadVAGData(data, file.size);
	Mem_Free(data);
	
	//Audio_LoadMus("\\MUSIC\\GETUP.MUS;1");
	//Audio_PlayMus(true);
	//Audio_SetVolume(0, 0x3FFF, 0x0000);
	//Audio_SetVolume(1, 0x0000, 0x3FFF);
	
	menu.texty.zoom1 = 240* 100;
	menu.texty.zoom2 = 240* 100;
	menu.texty.zoom3 = 240* 100;
}

static void MenuSelection()
{
	if (pad_state.press & PAD_UP)
	{
		menu.selection -= 1;
		Audio_PlaySound(menu.sounds[0], 0x3fff);
	}
	if (pad_state.press & PAD_DOWN)
	{
		menu.selection += 1;
		Audio_PlaySound(menu.sounds[0], 0x3fff);
	}
	if (pad_state.press & PAD_CROSS)
	{
		Audio_PlaySound(menu.sounds[1], 0x3fff);
		//Unload menu state
		Menu_Unload();
			
		//Load new stage
		Battle_Load();
		gameloop = GameLoop_Battle;
	}
}

void Menu_Tick()
{
	RECT logo_src = {0, 0, 93, 19};
	RECT logo_dst = {
		SCREEN_WIDTH2 - logo_src.w,
		(SCREEN_HEIGHT2 / 2) - logo_src.h,
		186,
		38
	};
	
	Gfx_DrawTex(&tex_menu,&logo_src,&logo_dst);
	
	MenuSelection();
	
	//-------------------------------------------------------------

	fixed_t dzoom1y = (SCREEN_HEIGHT - 11 - 52) * 100 - menu.texty.zoom1;
	fixed_t dzoom2y = (SCREEN_HEIGHT - 11 - 35) * 100 - menu.texty.zoom2;
	fixed_t dzoom3y = (SCREEN_HEIGHT - 11 - 18) * 100 - menu.texty.zoom3;
	
	menu.texty.zoom1 += FIXED_MUL(dzoom1y, FIXED_UNIT / 12);
	menu.texty.zoom2 += FIXED_MUL(dzoom2y, FIXED_UNIT / 12);
	menu.texty.zoom3 += FIXED_MUL(dzoom3y, FIXED_UNIT / 12);
	
	fixed_t dzoom1x, dzoom2x, dzoom3x;
	
	if (menu.selection == 0)
		dzoom1x = (SCREEN_WIDTH2 - 140) * 100 - menu.textx.zoom1;
	else
		dzoom1x = (SCREEN_WIDTH2 - 150) * 100 - menu.textx.zoom1;
	if (menu.selection == 1)
		dzoom2x = (SCREEN_WIDTH2 - 140) * 100 - menu.textx.zoom2;
	else
		dzoom2x = (SCREEN_WIDTH2 - 150) * 100 - menu.textx.zoom2;
	if (menu.selection == 2)
		dzoom3x = (SCREEN_WIDTH2 - 140) * 100 - menu.textx.zoom3;
	else
		dzoom3x = (SCREEN_WIDTH2 - 150) * 100 - menu.textx.zoom3;
	
	menu.textx.zoom1 += FIXED_MUL(dzoom1x, FIXED_UNIT / 12);
	menu.textx.zoom2 += FIXED_MUL(dzoom2x, FIXED_UNIT / 12);
	menu.textx.zoom3 += FIXED_MUL(dzoom3x, FIXED_UNIT / 12);
	
	RECT play_src = {94, 0, 32, 11};
	RECT play_dst = {
		menu.textx.zoom1 / 100,
		menu.texty.zoom1 / 100,
		play_src.w,
		play_src.h
	};
	
	Gfx_DrawTex(&tex_menu,&play_src,&play_dst);
	
	RECT phases_src = {192, 0, 48, 11};
	RECT phases_dst = {
		menu.textx.zoom2 / 100,
		menu.texty.zoom2 / 100,
		phases_src.w,
		phases_src.h
	};
	
	Gfx_DrawTex(&tex_menu,&phases_src,&phases_dst);
	
	RECT stgs_src = {127, 0, 64, 11};
	RECT stgs_dst = {
		menu.textx.zoom3 / 100,
		menu.texty.zoom3 / 100,
		stgs_src.w,
		stgs_src.h
	};
	
	Gfx_DrawTex(&tex_menu,&stgs_src,&stgs_dst);
	
	//-------------------------------------------------------------
	
	RECT sans_src = {40, 88, 166, 168};
	RECT sans_dst = {
		SCREEN_WIDTH2 - (sans_src.w / 2),
		SCREEN_HEIGHT - sans_src.h,
		sans_src.w,
		sans_src.h
	};
	
	Gfx_DrawTex(&tex_menu,&sans_src,&sans_dst);
}

void Menu_Unload()
{
	Gfx_SetClear(0, 0, 0);
}