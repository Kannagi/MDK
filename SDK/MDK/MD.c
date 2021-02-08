
#include "MDK.h"
#include "asm.h"

#include "MD_arg.h"


static inline void Joypad(u16 joypad,u8 *event,u16 test)
{
	if(joypad&test)
	{
		if(*event == 1)
			*event = 2;

		if(*event == 0)
			*event = 1;
	}else
	{
		if(*event == 3)
			*event = 0;

		if(*event == 2)
			*event= 3;
	}
}


void MD_JoypadInit(MD_Joypads *pad)
{
	pad->UP = 0;
	pad->DOWN = 0;
	pad->LEFT = 0;
	pad->RIGHT = 0;
	pad->A = 0;
	pad->B = 0;
	pad->C = 0;
	pad->X = 0;
	pad->Y = 0;
	pad->Z = 0;

	pad->START = 0;
	pad->MODE = 0;
}

u16 MD_Joypad1(MD_Joypads *pad)
{
	MD_UploadJoypad1();
	u16 joypad = RW_REGISTER_U16(0xFF0008);

	Joypad(joypad,&pad->UP,0x0100);
	Joypad(joypad,&pad->DOWN,0x0200);
	Joypad(joypad,&pad->LEFT,0x0400);
	Joypad(joypad,&pad->RIGHT,0x0800);

	Joypad(joypad,&pad->B,0x1000);
	Joypad(joypad,&pad->C,0x2000);

	Joypad(joypad,&pad->A,0x4000);
	Joypad(joypad,&pad->START,0x8000);

	return joypad;
}

u16 MD_Joypad2(MD_Joypads *pad)
{
	MD_UploadJoypad2();
	u16 joypad = RW_REGISTER_U16(0xFF000A);

	Joypad(joypad,&pad->UP,0x0100);
	Joypad(joypad,&pad->DOWN,0x0200);
	Joypad(joypad,&pad->LEFT,0x0400);
	Joypad(joypad,&pad->RIGHT,0x0800);

	Joypad(joypad,&pad->B,0x1000);
	Joypad(joypad,&pad->C,0x2000);

	Joypad(joypad,&pad->A,0x4000);
	Joypad(joypad,&pad->START,0x8000);

	return joypad;
}

void MD_Scroll()
{
	asm (

	"lea  VDP_DATA,%a0\n"
	"lea  VDP_CTRL,%a1\n"

	"move.l #0x40000000+(0x18000000)+3,(%a1)\n"
	"move.w  MD_Scrollx,(%a0)\n	"

	"move.l #0x40000000+(0x10),(%a1)\n"
	"move.w  MD_Scrolly,(%a0)\n	"
	);
}




void MD_DMAVRAM(const void *data,u16 address,u16 n)
{
	MD_arg1_u32 = (u32)data>>1;
	MD_arg1_u16 = address;
	MD_arg2_u16 = n;
	asm (

	"lea  VDP_CTRL,%a0\n	"
	"move.w #0x00FF,%d1\n	"

	"move.w	(%a0), %d0\n	"
	"btst	#1, %d0\n	"
	"bne MD_DMAVRAM_END\n	"

	"move.w 0x8174,(%a0)\n"
	"move.w 0x8F02,(%a0)\n"

	//Lengh
	"move.w	MD_arg2_u16,%d0\n	"
	"and.w	%d1,%d0\n	"
	"addi.w	#0x9300,%d0\n	"
	"move.w %d0,(%a0)\n"

	"move.b	MD_arg2_u16,%d0\n	"
	"and.w	%d1,%d0\n	"
	"addi.w	#0x9400,%d0\n	"
	"move.w %d0,(%a0)\n"

	//Source
	"move.w	MD_arg1_u32+2,%d0\n	"
	"and.w	%d1,%d0\n	"
	"addi.w	#0x9500,%d0\n	"
	"move.w %d0,(%a0)\n"

	"move.w	MD_arg1_u32+2,%d0\n	"
	"lsr.w	#8,%d0\n	"
	"and.w	%d1,%d0\n	"
	"addi.w	#0x9600,%d0\n	"
	"move.w %d0,(%a0)\n"

	"move.w	MD_arg1_u32,%d0\n	"
	"andi.w	#0x7F,%d0\n	"
	"addi.w	#0x9700,%d0\n	"
	"move.w %d0,(%a0)\n"

	//Destination
	"move.w	MD_arg1_u16,%d0\n	"
	"andi.w	#0x3FFF,%d0\n	"
	"addi.w	#0x4000,%d0\n	"
	"move.w %d0,(%a0)\n"

	"move.b	MD_arg1_u16,%d0\n	"
	"lsr.b	#6,%d0\n	"
	"andi.w	#0x3,%d0\n	"
	"addi.w	#0x0080,%d0\n	"
	"move.w %d0,(%a0)\n"


	"move.w 0x8164,(%a0)\n"
	"MD_DMAVRAM_END:\n	"

	);
}
