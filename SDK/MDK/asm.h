
#define EQU_MD 	".equ VDP_CTRL,0xC00004\n	" \
				".equ VDP_DATA,0xC00000\n	"


asm(EQU_MD);


asm (
	".macro digit_convert id\n	"

	"cmp.w %d4,%d2\n	"
	"bmi.b MD_Print_u16_if\\id\n	"
		"sub.w %d4,%d2\n	"
		"addq.w	#1,%d0\n	"
	"MD_Print_u16_if\\id:\n	"

	".endm\n	"

	".macro digit_convertA id\n	"

	"cmp.w %d4,%d2\n	"
	"bmi.b MD_Print_u16_ifA\\id\n	"
		"sub.w %d4,%d2\n	"
		"addq.w	#1,%d0\n	"
	"MD_Print_u16_ifA\\id:\n	"

	".endm\n	"


	".macro digit_convertB id\n	"

	"cmp.w %d4,%d2\n	"
	"bmi.b MD_Print_u16_ifB\\id\n	"
		"sub.w %d4,%d2\n	"
		"addq.w	#1,%d0\n	"
	"MD_Print_u16_ifB\\id:\n	"

	".endm\n	"

	".macro digit_convertC id\n	"

	"cmp.w %d4,%d2\n	"
	"bmi.b MD_Print_u16_ifC\\id\n	"
		"sub.w %d4,%d2\n	"
		"addq.w	#1,%d0\n	"
	"MD_Print_u16_ifC\\id:\n	"

	".endm\n	"

	".macro digit_convertD id\n	"

	"cmp.w %d4,%d2\n	"
	"bmi.b MD_Print_u16_ifD\\id\n	"
		"sub.w %d4,%d2\n	"
		"addq.w	#1,%d0\n	"
	"MD_Print_u16_ifD\\id:\n	"

	".endm\n	"
	);

asm (
	".macro digit_convert5 v,id\n	"

	"cmp.w #\\v,%d2\n	"
	"bmi.b MD_Print_if\\id\n	"
		"sub.w #\\v,%d2\n	"
		"addq.w	#5,%d0\n	"
	"MD_Print_if\\id:\n	"

	".endm\n	"
	);


asm (
	".macro digit_convert1000 id\n	"

	"move.w %d3,%d0\n	"
	"move.w #1000,%d4\n	"

	"digit_convert5 5000,\\id\n	"
	"digit_convertA \\id\n	"
	"digit_convertB \\id\n	"
	"digit_convertC \\id\n	"
	"digit_convertD \\id\n	"

	"move.w  %d0,(%a0)\n	"

	".endm\n	"
	);

asm (
	".macro digit_convert100 id\n	"

	"move.w %d3,%d0\n	"
	"move.w #100,%d4\n	"

	"digit_convert5 500,\\id\n	"
	"digit_convertA \\id\n	"
	"digit_convertB \\id\n	"
	"digit_convertC \\id\n	"
	"digit_convertD \\id\n	"

	"move.w  %d0,(%a0)\n	"

	".endm\n	"
	);

asm (
	".macro digit_convert10 id\n	"

	"move.w %d3,%d0\n	"
	"move.w #10,%d4\n	"

	"digit_convert5 50,\\id\n	"
	"digit_convertA \\id\n	"
	"digit_convertB \\id\n	"
	"digit_convertC \\id\n	"
	"digit_convertD \\id\n	"

	"move.w  %d0,(%a0)\n	"

	".endm\n	"
	);

	asm (
	".macro hexa_convert id\n	"

	"andi.w	#0x0F,%d1\n	"
	"cmpi.w	#0x0A,%d1\n	"

	"bmi.b	MD_PrinthA_\\id\n	"
		"add.w	%d4,%d1\n	"
		"bra.w	MD_PrinthB_\\id\n	"
	"MD_PrinthA_\\id:\n	"
		"add.w	%d3,%d1\n	"
	"MD_PrinthB_\\id:\n	"
	"move.w %d1,(%a0)\n	"

	".endm\n	"
	);
