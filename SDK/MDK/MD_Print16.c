
#include "MDK.h"
#include "asm.h"

#include "MD_arge.h"

void __attribute__((noinline)) MD_Prints16(s16 val,u16 x,u16 y)
{
	MD_arg1_u16 = x;
	MD_arg2_u16 = y;
	MD_arg3_u16 = (u16)val;

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



		"btst #0xF,MD_arg3_u16\n	"
		"beq.w MD_Print_s16_neg\n	"
			"move.w #0x780-32+'-',%d0\n	"
			"add.w  MD_PAL_ID,%d0\n	"
			"move.w %d0,(%a0)\n	"

			"eor.w #0xFFFF,%d2\n	"
			"addq.w #0x1,%d2\n	"

		"MD_Print_s16_neg:\n	"

		"move.w %d3,%d0\n	"
		"move.w #10000,%d4\n	"
		"digit_convert 20\n	"
		"digit_convertA 20\n	"
		"digit_convertB 20\n	"
		"move.w  %d0,(%a0)\n	"

		"digit_convert1000 21\n	"
		"digit_convert100 22\n	"
		"digit_convert10 23\n	"


		"move.w %d3,%d0\n	"
		"add.w	%d2,%d0\n	"
		"move.w %d0,(%a0)\n	"


		"move.w #0,(%a0)\n	"

		"movem.l (%a7)+,%d2-%d4\n	"
		);
}

void __attribute__((noinline)) MD_Printu16(u16 val,u16 x,u16 y)
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
		"move.w #10000,%d4\n	"

		"btst #0xF,MD_arg3_u16\n	"
		"beq.b MD_Print_u16_neg\n	"
			"sub.w #30000,%d2\n	"
			"addq.w	#3,%d0\n	"
		"MD_Print_u16_neg:\n	"

		"digit_convertA 0\n	"
		"digit_convertB 1\n	"
		"digit_convertC 2\n	"

		"move.w  %d0,(%a0)\n	"


		"digit_convert1000 5\n	"
		"digit_convert100 6\n	"
		"digit_convert10 7\n	"

		"move.w %d3,%d0\n	"
		"add.w	%d2,%d0\n	"
		"move.w %d0,(%a0)\n	"

		"movem.l (%a7)+,%d2-%d4\n	"
		);
}

void __attribute__((noinline)) MD_Printh16(u16 val,u16 x,u16 y)
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

		"mov.w	%d2,%d1\n	"
		"asr.w	#8,%d1\n	"
		"asr.w	#4,%d1\n	"
		"hexa_convert 10\n	"

		"mov.w	%d2,%d1\n	"
		"asr.w	#8,%d1\n	"
		"hexa_convert 11\n	"


		"move.w	%d2,%d1\n	"
		"asr.w	#4,%d1\n	"
		"hexa_convert 1\n	"

		"move.w	%d2,%d1\n	"
		"hexa_convert 2\n	"

		"movem.l (%a7)+,%d2-%d4\n	"
		);
}


void __attribute__((noinline)) MD_Printh32(u32 val,u16 x,u16 y)
{
	MD_arg1_u16 = x;
	MD_arg2_u16 = y;
	MD_arg3_u32 = val;

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



		"move.w #0x780-32+'0',%d3\n	"
		"add.w  MD_PAL_ID,%d3\n	"

		"move.w #0x780-32+'A'-10,%d4\n	"
		"add.w  MD_PAL_ID,%d4\n	"

		"move.w MD_arg3_u32,%d2\n	"

		"mov.w	%d2,%d1\n	"
		"asr.w	#8,%d1\n	"
		"asr.w	#4,%d1\n	"
		"hexa_convert 30\n	"

		"mov.w	%d2,%d1\n	"
		"asr.w	#8,%d1\n	"
		"hexa_convert 31\n	"


		"move.w	%d2,%d1\n	"
		"asr.w	#4,%d1\n	"
		"hexa_convert 33\n	"

		"move.w	%d2,%d1\n	"
		"hexa_convert 34\n	"

		"move.w MD_arg3_u32+2,%d2\n	"

		"mov.w	%d2,%d1\n	"
		"asr.w	#8,%d1\n	"
		"asr.w	#4,%d1\n	"
		"hexa_convert 20\n	"

		"mov.w	%d2,%d1\n	"
		"asr.w	#8,%d1\n	"
		"hexa_convert 21\n	"


		"move.w	%d2,%d1\n	"
		"asr.w	#4,%d1\n	"
		"hexa_convert 23\n	"

		"move.w	%d2,%d1\n	"
		"hexa_convert 24\n	"

		"movem.l (%a7)+,%d2-%d4\n	"
		);
}
