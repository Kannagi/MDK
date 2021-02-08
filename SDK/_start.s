#NO_APP
	.file	"start.s"
	.text
	.align	2


.equ RAMSTART,0xFF0000

.equ VDP_DATA,0xC00000
.equ VDP_CTRL,0xC00004
.equ VDP_HVCNTR,0xC00008
.equ VDP_PSG,0xC00010

.equ MD_IODATA1,0xA10003
.equ MD_IODATA2,0xA10005
.equ MD_IODATA3,0xA10007
.equ MD_IOCTRL1,0xA10009
.equ MD_IOCTRL2,0xA1000B
.equ MD_IOCTRL3,0xA1000D
.equ MD_TxDATA1,0xA1000F
.equ MD_RxDATA1,0xA10011
.equ MD_SCTRL1,0xA10013
.equ MD_SCTRL3,0xA1001F
.equ MD_LOCK,0xA14000

.equ HARD_RESET_ADDR,0xA1000C
.equ HARD_VERSION_ADDR,0xA10001
.equ Z80_BUSREQ_PORT,0xA11100
.equ Z80_RESET_PORT,0xA11200
.equ Z80_RAM_ADDR,0xA00000

.org 0
.dc.l 0-8,_start,_INT,_INT,_INT,_INT,_INT,_INT
.dc.l _INT,_INT,_INT,_INT,_INT,_INT,_INT,_INT
.dc.l _INT,_INT,_INT,_INT,_INT,_INT,_INT,_INT
.dc.l _INT,_INT,_INT,_INT,_HBLANK,_INT,_VBLANK,_INT

.dc.l _INT,_INT,_INT,_INT,_INT,_INT,_INT,_INT
.dc.l _INT,_INT,_INT,_INT,_INT,_INT,_INT,_INT
.dc.l _INT,_INT,_INT,_INT,_INT,_INT,_INT,_INT
.dc.l _INT,_INT,_INT,_INT,_INT,_INT,_INT,_INT

#      "0123456789ABCDEF"
.ascii "SEGA MEGA DRIVE "
.ascii "(C)SEGA 2021.XXX"

#      "0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF"
.ascii "MGDK                                            "
.ascii "MGDK                                            "

#      "0123456789ABCDEF"
.ascii "GM 00000000-10"
.word   0x0000
.ascii  "J               "
.long   0x00000000,0x00080000-1
.long   0x00FF0000,0x00FFFFFF

.long   0x00000000
.long   0x00000000
.long   0x00000000
.long   0x00000000
.long   0x00000000
.long   0x00000000

#      "0123456789ABCDEF0123456789ABCDEF01234567"
.ascii "MGDK                                    "

#      "0123456789ABCDEF"
.ascii "JUE             "

_start:
	jmp _start3

_INT:
move.b #1,RAMSTART
	nop
	rte

_INT2:

	nop
	rte



#RAMSTART 0-3 : Vblank
#RAMSTART 4-5 : SR


_HBLANK:
	addq.b #1,RAMSTART+1
	rte

_VBLANK:
	move.w  %sr,RAMSTART+4
	movem.l %d0-%d7/%a0-%a6,-(%a7)

	cmp.b #0,RAMSTART
	bne _VBLANK_END




	jsr MD_VBlank

	move.b #1,RAMSTART

_VBLANK_END:
    movem.l (%a7)+,%d0-%d7/%a0-%a6
    move.w  RAMSTART+4,%sr


    rte

	.align	2
	.globl	_start
	.type	_start, @function




SEGA_STRING:
.ascii "SEGA"
TMSS:
    move.b  HARD_VERSION_ADDR,%d0
    andi.b  #0x0F,%d0
    beq     1f
    move.l  #SEGA_STRING, %a1
    move.l  (%a1), 0xA14000
1:  rts


_start3:
	move.w  #0x2300,%sr
	jsr TMSS

	moveq #0x40,%d0
	move.b %d0,MD_IOCTRL1
	move.b %d0,MD_IODATA1
	move.b %d0,MD_IOCTRL2
	move.b %d0,MD_IODATA2



	tst.w (VDP_CTRL)
	lea  VDP_CTRL,%a0

    move.w  #0x8004,(%a0)
    move.w  #0x8164,(%a0)
	move.w  #0x8B00,(%a0)
	move.w  #0x8C81,(%a0)


# SCROLL A : 0xC000 , SCROLL B : 0xE000
    move.w  #0x8200+(6<<3),(%a0)
    move.w  #0x8400+(7<<0),(%a0)


# Windows/SPRITE/HSCROLL : 0xD000/0xDC00/0xD800
    move.w  #0x8300+(0x1A<<1),(%a0)
    move.w  #0x8500+(0x6E<<0),(%a0)
    move.w  #0x8D00+(0x36<<0),(%a0)



#Background color/HINT/Auto increment/ Scroll size
	move.w  #0x8700,(%a0)
	move.w  #0x8A01,(%a0)
	move.w  #0x8F02,(%a0)
	move.w  #0x9001,(%a0)

#Windows X/Y
	move.w  #0x9100,(%a0)
	move.w  #0x9200,(%a0)


	jsr MD_ClearVRAM
	jsr MD_ClearVSRAM
	jsr MD_ClearCRAM

	jsr MD_ClearSAT

    clr.l RAMSTART
	move.b #1,RAMSTART

    jsr main

_start_end:
	nop
    bra _start
	rts

	.size	_start, .-_start



	.align	2
	.globl	MD_WaitVBlank
	.type	MD_WaitVBlank, @function


MD_WaitVBlank:
	clr.l RAMSTART

MG_wait:
	addq.w #1,RAMSTART+2
	cmpi.b #0,RAMSTART
    beq MG_wait

	move.b #1,RAMSTART

    rts

    .size	MD_WaitVBlank, .-MD_WaitVBlank



	.align	2
	.globl	MD_UploadJoypad1
	.type	MD_UploadJoypad1, @function

MD_UploadJoypad1:

	lea MD_IODATA1,%a0

	move.b #0x40,(%a0)
	nop
	nop
	move.b (%a0),%d0


	move.b #0x00,(%a0)
	nop
	nop
	move.b (%a0),%d1

	andi.b  #0x3f,%d0
    andi.b  #0x30,%d1
    lsl.b   #2,%d1
    or.b    %d1,%d0

	not.b %d0
	move.b %d0,RAMSTART+8

	rts

	move.b #0x40,(%a0)
	nop
	nop
	move.b #0x00,(%a0)
	nop
	nop
	move.b #0x40,(%a0)
	nop
	nop
	move.b (%a0),RAMSTART+8
	move.b #0x00,(%a0)

    .size	MD_UploadJoypad1, .-MD_UploadJoypad1

	.globl	MD_UploadJoypad2
	.type	MD_UploadJoypad2, @function

MD_UploadJoypad2:

	lea MD_IODATA2,%a0

	move.b #0x40,(%a0)
	nop
	nop
	move.b (%a0),%d0
	not.b %d0
	move.b %d0,RAMSTART+10

	move.b #0x00,(%a0)
	nop
	nop
	move.b (%a0),RAMSTART+11

	rts

    .size	MD_UploadJoypad2, .-MD_UploadJoypad2

	.ident	"GCC: (GNU) 8.1.1 20180626 (Red Hat Cross 8.1.1-3)"
	.section	.note.GNU-stack,"",@progbits

