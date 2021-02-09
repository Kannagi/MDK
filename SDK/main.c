
/*
$linker --oformat binary -Ttext -0x00 -Tbss 0xFF0020 $libdirs -o $exe_output $link_objects $link_resobjects $link_options $libs

m68k-linux-gnu-ld --oformat binary -Ttext -0x00 -Tbss 0xFF0020 -L/usr/local/SDK/NeoGeo/lib -o bin/MDK.bin
obj/_start.o obj/main.o obj/MDK/MD.o obj/MDK/MD_Clear.o obj/MDK/MD_Load.o
*/
#include "MDK/MDK.h"
#include "MDK/asm.h"

#include "res/tile1pal.inc"
#include "res/tile1.inc"
#include "res/map.inc"

#include "res/megaman.inc"
#include "res/megamanpal.inc"


#include "res/fontpal.inc"
#include "res/font.inc"



int main()
{

	//char *text = "hello world";

	MD_LoadPal(tile1pal_data,MD_PAL0); //charge par bloc de 16 couleurs
	MD_LoadPal(fontpal_data,MD_PAL1);
	MD_LoadPal(megamanpal_data,MD_PAL2);
	//MD_LoadPalN(ship_pal_data,0,1); // charge par nombre de pixel


	MD_LoadVRAM(font_data,0xF000,(font_size>>4)-1);


	MD_LoadVRAM(megaman_data,0x8000,(megaman_size>>4)-1);

	MD_LoadVRAM(tile1_data,0x0020,(tile1_size>>4)-1);

	const void *offset = map_data+4;
	MD_LoadVRAM(offset,0xE000,(map_size>>4)-1);

	MD_ScrollBx = 0x00;
	MD_ScrollBy = 0x00;

	MD_Joypads joypad;
	MD_JoypadInit(&joypad);

	MD_Sprite[0].x = 0x90;
	MD_Sprite[0].y = 0x90;
	MD_Sprite[0].size = 0x03F;
	MD_Sprite[0].tileflag = (0x8200>>5) | MD_SPRPAL2;

	MD_Sprite[1].x = 0x90;
	MD_Sprite[1].y = 0x100;
	MD_Sprite[1].size = 0x03F;
	MD_Sprite[1].tileflag = (0x8000>>5) | MD_SPRPAL2;


	MD_SelectBG(0); //selection le BG pour le print
	MD_FixPal(MD_SPRPAL1);
	MD_Print("Hello World !",12,8);

	MD_Prints8(-1,1,1);
	MD_Printu8(142,1,2);
	MD_Printh8(0x92,1,3);


	MD_Prints16(-16000,20,1);
	MD_Printu16(64666,20,2);
	MD_Printh16(0X12DF,20,3);

	MD_Printh32(0XFFFF48CA,20,5);

	while(1)
	{

		MD_Joypad1(&joypad);

		if(joypad.UP == MD_BUTTON_DOWNW)
			MD_ScrollBy--;

		if(joypad.DOWN == MD_BUTTON_DOWNW)
			MD_ScrollBy++;


		if(joypad.LEFT == MD_BUTTON_DOWNW)
			MD_ScrollBx++;

		if(joypad.RIGHT == MD_BUTTON_DOWNW)
			MD_ScrollBx--;


		if(joypad.A == MD_BUTTON_DOWNW)
			MD_Sprite[1].x++;

		if(joypad.B == MD_BUTTON_DOWNW)
			MD_Sprite[1].x--;


		MD_WaitVBlank();
		MD_ScrollB();

	}
    return 0;
}


void __attribute__((noinline)) MD_VBlank()
{
	MD_LoadVRAM(MD_Sprite,0xDC00,(79*2*4)>>4);
	//MD_DMAVRAM(tile1_data,0x3000,tile1_size>>6);
}
