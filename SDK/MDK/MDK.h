#ifndef __MDK__
#define __MDK__

#define RW_REGISTER_U8(REG) 	*((volatile unsigned char  *)(REG))
#define RW_REGISTER_U16(REG) 	*((volatile unsigned short *)(REG))
#define RW_REGISTER_U32(REG) 	*((volatile unsigned int   *)(REG))
#define RW_REGISTER_U64(REG) 	*((volatile unsigned long  *)(REG))

#define u8  unsigned char
#define u16 unsigned short
#define u32 unsigned int

#define s8  signed char
#define s16 signed short
#define s32 signed int

#define ftoi2(ft2) (u16)(ft2*4)
#define ftoi4(ft4) (u16)(ft4*16)
#define ftoi7(ft7) (u16)(ft7*128)

#define ftol2(ft2) (u32)(ft2*4)
#define ftol4(ft4) (u32)(ft4*16)
#define ftol7(ft7) (u32)(ft4*128)
#define ftol8(ft8) (u32)(ft8*256)
#define ftol12(ft12) (u32)(ft12*4096)
#define ftol16(ft16) (u32)(ft16*65536)

#define itoi2(it2) ( it2 >>2)
#define itoi4(it4) ( it4 >>4)
#define itoi7(it7) ( it7 >>7)
#define itoi8(it8) ( it8 >>8)
#define itoi12(it12) ( it12 >>12)
#define itoi16(it16) ( it16 >>16)


#define MD_BUTTON_DOWN   1
#define MD_BUTTON_DOWNW  2
#define MD_BUTTON_UP     3

#define MD_SPRPAL0  0x0000
#define MD_SPRPAL1  0x2000
#define MD_SPRPAL2  0x4000
#define MD_SPRPAL3  0x6000
#define MD_SPRPRIO  0x8000
#define MD_SPRFLIPH 0x0800
#define MD_SPRFLIPV 0x1000

typedef struct
{
    u16 y;
    u8 size,link;
    u16 tileflag,x;
}MD_Sprites;

typedef struct
{
    u8 A,B,C,X,Y,Z,UP,RIGHT,LEFT,DOWN,START,MODE;
}MD_Joypads;

extern MD_Sprites MD_Sprite[80];
extern u16 MD_Scrollx;
extern u16 MD_Scrolly;

u16 MD_Joypad1(MD_Joypads *pad);
u16 MD_Joypad2(MD_Joypads *pad);
void MD_JoypadInit(MD_Joypads *pad);
void MD_UploadJoypad1(void);
void MD_UploadJoypad2(void);

void MD_WaitVBlank(void);

void MD_ClearVRAM(void);
void MD_ClearCRAM(void);
void MD_ClearVSRAM(void);
void MD_ClearRAM(void);
void MD_ClearSAT(void);

void MD_Scroll(void);

void MD_LoadPal(const void *palette,u16 address);
void MD_LoadPalN(const void *palette,u16 address,u16 n);

void MD_LoadVRAM(const void *data,u16 address,u16 n);

void MD_DMAVRAM(const void *data,u16 address,u16 n);
#endif
