#ifndef PSXF_GUARD_MENU_H
#define PSXF_GUARD_MENU_H

#include "../psx/gfx.h"
#include "../psx/io.h"
#include "../psx/fixed.h"

typedef struct
{
	u32 sounds[3];
	u8 selection;
	struct
	{
		fixed_t zoom1, zoom2, zoom3, speed;
	} texty;
	struct
	{
		fixed_t zoom1, zoom2, zoom3, speed;
	} textx;
} Menu;

extern Menu menu;

//Battle functions
void Menu_Load();
void Menu_Unload();
void Menu_Tick();

#endif
