
#include "MDK.h"
#include "asm.h"

#include "MD_arge.h"

void __attribute__((noinline)) MD_Prints8(s8 val,u16 x,u16 y)
{
	MD_arg1_u16 = x;
	MD_arg2_u16 = y;
	MD_arg3_u16 = (u8)val;

	asm (
		"movem.l %d2-%d4,-(%a7)\n	"

		//ADRESS
		"lea  VDP_CTRL,%a1\n"

		"move.w	MD_arg2_u16,%d0\n	"
		"asl.w	#7,%d0\n	"
		"move.w	MD_arg1_u16,%d1\n	"
		"asl.w	#1,%d1\n	"
		"add.w	%d1,%d0\n	"
		"add.w	MD_BG_ID,%d0\n	"
		"addi.w	#0x4000,%d0\n	"
		"move.w %d0,(%a1)\n"

		"move.w #3,(%a1)\n"

		//DATA
		"lea  VDP_DATA,%a0\n"

		"move.w MD_arg3_u16,%d2\n	"

		"move.w #0x780-32+'0',%d3\n	"
		"add.w  MD_PAL_ID,%d3\n	"




		"cmpi #129,%d2\n	"
		"bmi.b MD_Print_s8_neg\n	"
			"move.w #0x780-32+'-',%d0\n	"
			"add.w  MD_PAL_ID,%d0\n	"
			"move.w %d0,(%a0)\n	"

			"eor.w #0xFF,%d2\n	"
			"addq.w #0x1,%d2\n	"

		"MD_Print_s8_neg:\n	"


		"move.w %d3,%d0\n	"
		"move.w #100,%d4\n	"

		"digit_convertA 111\n	"

		"move.w  %d0,(%a0)\n	"


		"digit_convert10 110\n	"

		"move.w %d3,%d0\n	"
		"add.w	%d2,%d0\n	"
		"move.w %d0,(%a0)\n	"


		"move.w #0,(%a0)\n	"

		"movem.l (%a7)+,%d2-%d4\n	"
		);
}

void __attribute__((noinline)) MD_Printu8(u8 val,u16 x,u16 y)
{
	MD_arg1_u16 = x;
	MD_arg2_u16 = y;
	MD_arg3_u16 = val;

	asm (
		"movem.l %d2-%d4,-(%a7)\n	"

		//ADRESS
		"lea  VDP_CTRL,%a1\n"

		"move.w	MD_arg2_u16,%d0\n	"
		"asl.w	#7,%d0\n	"
		"move.w	MD_arg1_u16,%d1\n	"
		"asl.w	#1,%d1\n	"
		"add.w	%d1,%d0\n	"
		"add.w	MD_BG_ID,%d0\n	"
		"addi.w	#0x4000,%d0\n	"
		"move.w %d0,(%a1)\n"

		"move.w #3,(%a1)\n"

		//DATA
		"lea  VDP_DATA,%a0\n"

		"move.w MD_arg3_u16,%d2\n	"

		"move.w #0x780-32+'0',%d3\n	"
		"add.w  MD_PAL_ID,%d3\n	"


		"move.w %d3,%d0\n	"
		"move.w #100,%d4\n	"

		"digit_convertA 101\n	"
		"digit_convertB 101\n	"

		"move.w  %d0,(%a0)\n	"


		"digit_convert10 102\n	"

		"move.w %d3,%d0\n	"
		"add.w	%d2,%d0\n	"
		"move.w %d0,(%a0)\n	"


		"move.w #0,(%a0)\n	"

		"movem.l (%a7)+,%d2-%d4\n	"
		);
}

void __attribute__((noinline)) MD_Printh8(u8 val,u16 x,u16 y)
{
	MD_arg1_u16 = x;
	MD_arg2_u16 = y;
	MD_arg3_u16 = val;

	asm (
		"movem.l %d2-%d4,-(%a7)\n	"

		//ADRESS
		"lea  VDP_CTRL,%a1\n"

		"move.w	MD_arg2_u16,%d0\n	"
		"asl.w	#7,%d0\n	"
		"move.w	MD_arg1_u16,%d1\n	"
		"asl.w	#1,%d1\n	"
		"add.w	%d1,%d0\n	"
		"add.w	MD_BG_ID,%d0\n	"
		"addi.w	#0x4000,%d0\n	"
		"move.w %d0,(%a1)\n"

		"move.w #3,(%a1)\n"

		//DATA
		"lea  VDP_DATA,%a0\n"

		"move.w MD_arg3_u16,%d2\n	"

		"move.w #0x780-32+'0',%d3\n	"
		"add.w  MD_PAL_ID,%d3\n	"

		"move.w #0x780-32+'A'-10,%d4\n	"
		"add.w  MD_PAL_ID,%d4\n	"


		"move.w	%d2,%d1\n	"
		"asr.w	#4,%d1\n	"
		"hexa_convert 12\n	"

		"move.w	%d2,%d1\n	"
		"hexa_convert 13\n	"

		"movem.l (%a7)+,%d2-%d4\n	"
		);
}
