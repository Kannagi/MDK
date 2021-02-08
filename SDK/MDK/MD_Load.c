
#include "MDK.h"
#include "asm.h"

#include "MD_arge.h"

void MD_LoadPal(const void *palette,u16 address)
{
	MD_arg1_u32 = (u32)palette;
	MD_arg1_u16 = address;
	asm (

	"move.w	MD_arg1_u16,%d0\n	"
	"addi.w	#0xC000,%d0\n	"
	"move.w %d0,VDP_CTRL\n"

	"move.w #0x0000,VDP_CTRL\n"

	"move.l MD_arg1_u32,%a0\n"
	"lea  VDP_DATA,%a1\n"

	"move.l  (%a0)+,(%a1)\n	"
	"move.l  (%a0)+,(%a1)\n	"
	"move.l  (%a0)+,(%a1)\n	"
	"move.l  (%a0)+,(%a1)\n	"

	"move.l  (%a0)+,(%a1)\n	"
	"move.l  (%a0)+,(%a1)\n	"
	"move.l  (%a0)+,(%a1)\n	"
	"move.l  (%a0)+,(%a1)\n	"

	);
}


void MD_LoadPalN(const void *palette,u16 address,u16 n)
{
	MD_arg1_u32 = (u32)palette;
	MD_arg1_u16 = address;
	MD_arg2_u16 = n;
	asm (

	"move.w	MD_arg1_u16,%d0\n	"
	"addi.w	#0xC000,%d0\n	"
	"move.w %d0,VDP_CTRL\n"

	"move.w #0x0000,VDP_CTRL\n"


	"move.l MD_arg1_u32,%a0\n"
	"lea  VDP_DATA,%a1\n"

	"move.w MD_arg2_u16,%d0\n	"

	"MD_LoadPalN1:\n	"
		"move.w  (%a0)+,(%a1)\n	"
	"dbra %d0,MD_LoadPalN1\n	"

	);
}


void MD_LoadVRAM(const void *data,u16 address,u16 n)
{
	MD_arg1_u32 = (u32)data;
	MD_arg1_u16 = address;
	MD_arg2_u16 = n;
	asm (

	"move.w	MD_arg1_u16,%d0\n	"
	"andi.w	#0x3FFF,%d0\n	"
	"addi.w	#0x4000,%d0\n	"
	"move.w %d0,VDP_CTRL\n"

	"move.b	MD_arg1_u16,%d0\n	"
	"lsr.b	#6,%d0\n	"
	"andi.w	#0x3,%d0\n	"
	"move.w %d0,VDP_CTRL\n"

	"move.l MD_arg1_u32,%a0\n"
	"lea  VDP_DATA,%a1\n"

	"move.w MD_arg2_u16,%d0\n	"

	"MD_LoadVRAM1:\n	"
		"move.l  (%a0)+,(%a1)\n	"
		"move.l  (%a0)+,(%a1)\n	"

		"move.l  (%a0)+,(%a1)\n	"
		"move.l  (%a0)+,(%a1)\n	"
	"dbra %d0,MD_LoadVRAM1\n	"

	);
}
