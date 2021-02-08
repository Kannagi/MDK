
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

int main()
{

	//char *text = "hello world";

	MD_LoadPal(tile1pal_data,0); //charge par bloc de 16 couleurs
	//MD_LoadPalN(ship_pal_data,0,1); // charge par nombre de pixel

	MD_LoadVRAM(tile1_data,0x0020,tile1_size>>4);

	const void *offset = map_data+4;
	MD_LoadVRAM(offset,0xC000,(map_size-5)>>4);


	MD_Scrollx = 0x00;

	MD_Joypads joypad;
	MD_JoypadInit(&joypad);


	MD_Sprite[0].x = 0x90;
	MD_Sprite[0].y = 0x90;
	MD_Sprite[0].tileflag = 0x0002 | MD_SPRPAL0;

	while(1)
	{

		MD_Joypad1(&joypad);

		if(joypad.UP == MD_BUTTON_DOWNW)
			MD_Scrolly--;

		if(joypad.DOWN == MD_BUTTON_DOWNW)
			MD_Scrolly++;


		if(joypad.LEFT == MD_BUTTON_DOWNW)
			MD_Scrollx++;

		if(joypad.RIGHT == MD_BUTTON_DOWNW)
			MD_Scrollx--;


		MD_WaitVBlank();
		MD_Scroll();

	}
    return 0;
}


void __attribute__((optimize("-O0"),noinline)) MD_VBlank()
{
	MD_LoadVRAM(MD_Sprite,0xDC00,(79*2*4)>>4);
	//MD_DMAVRAM(tile1_data,0x3000,tile1_size>>6);
}
