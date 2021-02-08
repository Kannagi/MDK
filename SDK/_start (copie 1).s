#NO_APP
	.file	"start.s"
	.text
	.align	2


.equ RAMSTART,0xFF0000

.equ VDP_DATA,0xC00000
.equ VDP_CTRL,0xC00004
.equ VDP_HVCNTR,0xC00008
.equ VDP_PSG,0xC00010

.equ MD_JSCTRL1,0xA10003
.equ MD_JSCTRL2,0xA10005
.equ MD_JSEXT,0xA10007
.equ MD_CTRL1,0xA10009
.equ MD_CTRL2,0xA1000B
.equ MD_CTRL3,0xA1000D
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


    move.w  #0x2300,%sr


    tst.w HARD_RESET_ADDR
    #bne _start2

    moveq #0,%d0
    move.l 0x0000,%a0
    move.l #0x3FFF,%d1

_Clear:
    move.l %d0,-(%a0)
    move.l %d1,_Clear

    move.b HARD_VERSION_ADDR,%d0
    andi.b #0x0F,%d0
    bne TMSS

    move.w 0x0100,Z80_BUSREQ_PORT
    move.w 0x0100,Z80_RESET_PORT

.WaitZ80:
    btst #0x0000,Z80_BUSREQ_PORT
    bne .WaitZ80

    move.l #Z80InitData,%a0
    move.l Z80_RAM_ADDR,%a1
    move.w #0x29,%d0

.CopyZ80InitData:
    move.b (%a0)+,(%a1)+
    dbra %d0,.CopyZ80InitData

    move.w 0,Z80_BUSREQ_PORT
    move.w 0,Z80_RESET_PORT


    jmp _start2

Z80InitData:
   dc.w 0xaf01, 0xd91f
   dc.w 0x1127, 0x0021
   dc.w 0x2600, 0xf977
   dc.w 0xedb0, 0xdde1
   dc.w 0xfde1, 0xed47
   dc.w 0xed4f, 0xd1e1
   dc.w 0xf108, 0xd9c1
   dc.w 0xd1e1, 0xf1f9
   dc.w 0xf3ed, 0x5636
   dc.w 0xe9e9, 0x8104
   dc.w 0x8f01

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

	lea MD_JSCTRL1,%a0
	move.b #0x40,MD_CTRL1
	move.b #0x40,(%a0)
	nop
	nop
	nop
	nop
	move.b (%a0),RAMSTART+8

	move.b #0x00,(%a0)
	nop
	nop
	nop
	nop
	move.b (%a0),RAMSTART+9


	#jsr MD_VBlank

	move.b #1,RAMSTART

_VBLANK_END:
    movem.l (%a7)+,%d0-%d7/%a0-%a6
    move.w  RAMSTART+4,%sr


    rte

	.align	2
	.globl	_start
	.type	_start, @function





TMSS:
    move.l #0x53454741,0xA14000
    rts


_start2:
	moveq #0x40,%d0
	move.b %d0,MD_CTRL1
	move.b %d0,MD_JSCTRL1
	move.b %d0,MD_CTRL2
	move.b %d0,MD_JSCTRL2



	tst.w (VDP_CTRL)
	lea  VDP_CTRL,%a0

    move.w  #0x8004,(%a0)
    move.w  #0x8164,(%a0)
	move.w  #0x8B00,(%a0)
	move.w  #0x8C81,(%a0)


# SCROLL A : 0xC000 , SCROLL B : 0xE000
    move.w  #0x8200+(6<<3),(%a0)
    move.w  #0x8400+(7<<0),(%a0)


# Windows/HSCROLL/SPRITE : 0xB000/0xB800/0xBC00
    move.w  #0x8300+(0x16<<1),(%a0)
    move.w  #0x8500+(0x2F<<0),(%a0)
    move.w  #0x8D00+(0x2E<<0),(%a0)



#Background color/HINT/Auto increment/ Scroll size
	move.w  #0x8700,(%a0)
	move.w  #0x8A01,(%a0)
	move.w  #0x8F02,(%a0)
	move.w  #0x9001,(%a0)







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


	.ident	"GCC: (GNU) 8.1.1 20180626 (Red Hat Cross 8.1.1-3)"
	.section	.note.GNU-stack,"",@progbits

