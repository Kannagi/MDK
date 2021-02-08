
#include "MDK.h"
#include "asm.h"

#include "MD_arge.h"


void MD_ClearSAT()
{
	int i;

	for(i = 0;i < 79;i++)
	{
		MD_Sprite[i].y = 0x100;
		MD_Sprite[i].link = i+1;
	}

	MD_Sprite[i].y = 0x100;
	MD_Sprite[i].link = 0;
}

void MD_ClearRAM()
{
	asm (

	"lea  0xFF0020,%a0\n"

	"clr.l %d1\n"
	"move.w #0x7F8-1,%d0\n	"

	"MD_ClearRAM1:\n	"
		"move.l  %d1,(%a0)+\n	"
		"move.l  %d1,(%a0)+\n	"
		"move.l  %d1,(%a0)+\n	"
		"move.l  %d1,(%a0)+\n	"

		"move.l  %d1,(%a0)+\n	"
		"move.l  %d1,(%a0)+\n	"
		"move.l  %d1,(%a0)+\n	"
		"move.l  %d1,(%a0)+\n	"
	"dbra %d0,MD_ClearRAM1\n	"

	);
}


void MD_ClearCRAM()
{
	asm (

	"clr.l %d1\n"
	"move.w #0xC000,VDP_CTRL\n"
	"move.w %d1,VDP_CTRL\n"

	"lea  VDP_DATA,%a0\n"

	"move.w #4-1,%d0\n	"

	"MD_ClearCRAM1:\n	"
		"move.l  %d1,(%a0)\n	"
		"move.l  %d1,(%a0)\n	"
		"move.l  %d1,(%a0)\n	"
		"move.l  %d1,(%a0)\n	"

		"move.l  %d1,(%a0)\n	"
		"move.l  %d1,(%a0)\n	"
		"move.l  %d1,(%a0)\n	"
		"move.l  %d1,(%a0)\n	"
	"dbra %d0,MD_ClearCRAM1\n	"

	);
}


void MD_ClearVRAM()
{
	asm (

	"clr.l %d1\n"
	"move.w #0x4000,VDP_CTRL\n"
	"move.w %d1,VDP_CTRL\n"

	"lea  VDP_DATA,%a0\n"

	"move.w #0x800-1,%d0\n	"

	"MD_ClearVRAM1:\n	"
		"move.l  %d1,(%a0)\n	"
		"move.l  %d1,(%a0)\n	"
		"move.l  %d1,(%a0)\n	"
		"move.l  %d1,(%a0)\n	"

		"move.l  %d1,(%a0)\n	"
		"move.l  %d1,(%a0)\n	"
		"move.l  %d1,(%a0)\n	"
		"move.l  %d1,(%a0)\n	"
	"dbra %d0,MD_ClearVRAM1\n	"

	);
}

void MD_ClearVSRAM()
{
	asm (

	"clr.l %d1\n"
	"move.l #0x40000010,VDP_CTRL\n"

	"lea  VDP_DATA,%a0\n"

	"move.w #5-1,%d0\n	"

	"MD_ClearVSRAM1:\n	"
		"move.l  %d1,(%a0)\n	"
		"move.l  %d1,(%a0)\n	"

		"move.l  %d1,(%a0)\n	"
		"move.l  %d1,(%a0)\n	"
	"dbra %d0,MD_ClearVSRAM1\n	"

	);
}
