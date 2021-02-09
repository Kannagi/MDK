

#include "MDK.h"
#include "asm.h"

#include "MD_arge.h"

void MD_FixPal(u16 pal)
{
	MD_PAL_ID = pal;
}

void MD_SelectBG(u16 bg)
{
	if(bg == 0)
		MD_BG_ID = 0x0000;
	else
		MD_BG_ID = 0x2000;

}

void __attribute__((noinline)) MD_Print(const void *str,u16 x,u16 y)
{
	MD_arg1_u32 = (u32)str;
	MD_arg1_u16 = x;
	MD_arg2_u16 = y;

	asm (

		"lea  VDP_DATA,%a0\n"
		"lea  VDP_CTRL,%a1\n"

		"move.w	MD_arg2_u16,%d0\n	"
		"asl.w	#7,%d0\n	"
		"move.w	MD_arg1_u16,%d1\n	"
		"asl.w	#1,%d1\n	"
		"add.w	%d1,%d0\n	"
		"add.w	MD_BG_ID,%d0\n	"
		"addi.w	#0x4000,%d0\n	"
		"move.w %d0,(%a1)\n"

		"move.w	#3,(%a1)\n"


		"move.w #0x780-32,%d1\n	"
		"add.w  MD_PAL_ID,%d1\n	"
		"move.l MD_arg1_u32,%a1\n	"

		"MD_Print_loop:\n	"
			"clr.w  %d0\n	"
			"move.b (%a1)+,%d0\n	"

			//"cmp.w  %d1,%d0\n	"
			"beq.w MD_Print_end\n	"

			"add.w	%d1,%d0\n	"
			"move.w %d0,(%a0)\n	"
		"bne.w MD_Print_loop\n	"
		"MD_Print_end:\n	"


		);
}

