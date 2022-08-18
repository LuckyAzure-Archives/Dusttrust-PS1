#ifndef PSXF_GUARD_SANSPH1_H
#define PSXF_GUARD_SANSPH1_H

typedef struct
{
	Gfx_Tex tex;
	u8 timer;
	u8 head, leftarm, rightarm;
} SansPhase1;

extern SansPhase1 sansphase1;

void Load_Sans();
void Draw_Sans();

#endif
