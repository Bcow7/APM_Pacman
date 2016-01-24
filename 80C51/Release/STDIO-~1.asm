;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 3.0.0 #6037 (Oct 31 2010) (MINGW32)
; This file was generated Fri Jan 22 14:38:59 2016
;--------------------------------------------------------
	.module stdio_t6963c
	.optsdcc -mmcs51 --model-small
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _STDIO_startWritingAt_PARM_2
	.globl _putchar
	.globl _STDIO_startWritingAt
	.globl _STDIO_initialize
	.globl _TF1
	.globl _TR1
	.globl _TF0
	.globl _TR0
	.globl _IE1
	.globl _IT1
	.globl _IE0
	.globl _IT0
	.globl _SM0
	.globl _SM1
	.globl _SM2
	.globl _REN
	.globl _TB8
	.globl _RB8
	.globl _TI
	.globl _RI
	.globl _CY
	.globl _AC
	.globl _F0
	.globl _RS1
	.globl _RS0
	.globl _OV
	.globl _F1
	.globl _P
	.globl _RD
	.globl _WR
	.globl _T1
	.globl _T0
	.globl _INT1
	.globl _INT0
	.globl _TXD0
	.globl _TXD
	.globl _RXD0
	.globl _RXD
	.globl _P3_7
	.globl _P3_6
	.globl _P3_5
	.globl _P3_4
	.globl _P3_3
	.globl _P3_2
	.globl _P3_1
	.globl _P3_0
	.globl _P2_7
	.globl _P2_6
	.globl _P2_5
	.globl _P2_4
	.globl _P2_3
	.globl _P2_2
	.globl _P2_1
	.globl _P2_0
	.globl _P1_7
	.globl _P1_6
	.globl _P1_5
	.globl _P1_4
	.globl _P1_3
	.globl _P1_2
	.globl _P1_1
	.globl _P1_0
	.globl _P0_7
	.globl _P0_6
	.globl _P0_5
	.globl _P0_4
	.globl _P0_3
	.globl _P0_2
	.globl _P0_1
	.globl _P0_0
	.globl _PS
	.globl _PT1
	.globl _PX1
	.globl _PT0
	.globl _PX0
	.globl _EA
	.globl _ES
	.globl _ET1
	.globl _EX1
	.globl _ET0
	.globl _EX0
	.globl _BREG_F7
	.globl _BREG_F6
	.globl _BREG_F5
	.globl _BREG_F4
	.globl _BREG_F3
	.globl _BREG_F2
	.globl _BREG_F1
	.globl _BREG_F0
	.globl _TMOD
	.globl _TL1
	.globl _TL0
	.globl _TH1
	.globl _TH0
	.globl _TCON
	.globl _SP
	.globl _SCON
	.globl _SBUF0
	.globl _SBUF
	.globl _PSW
	.globl _PCON
	.globl _P3
	.globl _P2
	.globl _P1
	.globl _P0
	.globl _IP
	.globl _IE
	.globl _DP0L
	.globl _DPL
	.globl _DP0H
	.globl _DPH
	.globl _B
	.globl _ACC
	.globl _address
;--------------------------------------------------------
; special function registers
;--------------------------------------------------------
	.area RSEG    (ABS,DATA)
	.org 0x0000
_ACC	=	0x00e0
_B	=	0x00f0
_DPH	=	0x0083
_DP0H	=	0x0083
_DPL	=	0x0082
_DP0L	=	0x0082
_IE	=	0x00a8
_IP	=	0x00b8
_P0	=	0x0080
_P1	=	0x0090
_P2	=	0x00a0
_P3	=	0x00b0
_PCON	=	0x0087
_PSW	=	0x00d0
_SBUF	=	0x0099
_SBUF0	=	0x0099
_SCON	=	0x0098
_SP	=	0x0081
_TCON	=	0x0088
_TH0	=	0x008c
_TH1	=	0x008d
_TL0	=	0x008a
_TL1	=	0x008b
_TMOD	=	0x0089
;--------------------------------------------------------
; special function bits
;--------------------------------------------------------
	.area RSEG    (ABS,DATA)
	.org 0x0000
_BREG_F0	=	0x00f0
_BREG_F1	=	0x00f1
_BREG_F2	=	0x00f2
_BREG_F3	=	0x00f3
_BREG_F4	=	0x00f4
_BREG_F5	=	0x00f5
_BREG_F6	=	0x00f6
_BREG_F7	=	0x00f7
_EX0	=	0x00a8
_ET0	=	0x00a9
_EX1	=	0x00aa
_ET1	=	0x00ab
_ES	=	0x00ac
_EA	=	0x00af
_PX0	=	0x00b8
_PT0	=	0x00b9
_PX1	=	0x00ba
_PT1	=	0x00bb
_PS	=	0x00bc
_P0_0	=	0x0080
_P0_1	=	0x0081
_P0_2	=	0x0082
_P0_3	=	0x0083
_P0_4	=	0x0084
_P0_5	=	0x0085
_P0_6	=	0x0086
_P0_7	=	0x0087
_P1_0	=	0x0090
_P1_1	=	0x0091
_P1_2	=	0x0092
_P1_3	=	0x0093
_P1_4	=	0x0094
_P1_5	=	0x0095
_P1_6	=	0x0096
_P1_7	=	0x0097
_P2_0	=	0x00a0
_P2_1	=	0x00a1
_P2_2	=	0x00a2
_P2_3	=	0x00a3
_P2_4	=	0x00a4
_P2_5	=	0x00a5
_P2_6	=	0x00a6
_P2_7	=	0x00a7
_P3_0	=	0x00b0
_P3_1	=	0x00b1
_P3_2	=	0x00b2
_P3_3	=	0x00b3
_P3_4	=	0x00b4
_P3_5	=	0x00b5
_P3_6	=	0x00b6
_P3_7	=	0x00b7
_RXD	=	0x00b0
_RXD0	=	0x00b0
_TXD	=	0x00b1
_TXD0	=	0x00b1
_INT0	=	0x00b2
_INT1	=	0x00b3
_T0	=	0x00b4
_T1	=	0x00b5
_WR	=	0x00b6
_RD	=	0x00b7
_P	=	0x00d0
_F1	=	0x00d1
_OV	=	0x00d2
_RS0	=	0x00d3
_RS1	=	0x00d4
_F0	=	0x00d5
_AC	=	0x00d6
_CY	=	0x00d7
_RI	=	0x0098
_TI	=	0x0099
_RB8	=	0x009a
_TB8	=	0x009b
_REN	=	0x009c
_SM2	=	0x009d
_SM1	=	0x009e
_SM0	=	0x009f
_IT0	=	0x0088
_IE0	=	0x0089
_IT1	=	0x008a
_IE1	=	0x008b
_TR0	=	0x008c
_TF0	=	0x008d
_TR1	=	0x008e
_TF1	=	0x008f
;--------------------------------------------------------
; overlayable register banks
;--------------------------------------------------------
	.area REG_BANK_0	(REL,OVR,DATA)
	.ds 8
;--------------------------------------------------------
; internal ram data
;--------------------------------------------------------
	.area DSEG    (DATA)
_address::
	.ds 2
;--------------------------------------------------------
; overlayable items in internal ram 
;--------------------------------------------------------
	.area	OSEG    (OVR,DATA)
_STDIO_startWritingAt_PARM_2::
	.ds 1
;--------------------------------------------------------
; indirectly addressable internal ram data
;--------------------------------------------------------
	.area ISEG    (DATA)
;--------------------------------------------------------
; absolute internal ram data
;--------------------------------------------------------
	.area IABS    (ABS,DATA)
	.area IABS    (ABS,DATA)
;--------------------------------------------------------
; bit data
;--------------------------------------------------------
	.area BSEG    (BIT)
;--------------------------------------------------------
; paged external ram data
;--------------------------------------------------------
	.area PSEG    (PAG,XDATA)
;--------------------------------------------------------
; external ram data
;--------------------------------------------------------
	.area XSEG    (XDATA)
;--------------------------------------------------------
; absolute external ram data
;--------------------------------------------------------
	.area XABS    (ABS,XDATA)
;--------------------------------------------------------
; external initialized ram data
;--------------------------------------------------------
	.area XISEG   (XDATA)
	.area HOME    (CODE)
	.area GSINIT0 (CODE)
	.area GSINIT1 (CODE)
	.area GSINIT2 (CODE)
	.area GSINIT3 (CODE)
	.area GSINIT4 (CODE)
	.area GSINIT5 (CODE)
	.area GSINIT  (CODE)
	.area GSFINAL (CODE)
	.area CSEG    (CODE)
;--------------------------------------------------------
; global & static initialisations
;--------------------------------------------------------
	.area HOME    (CODE)
	.area GSINIT  (CODE)
	.area GSFINAL (CODE)
	.area GSINIT  (CODE)
;	../stdio-t6963c.c:5: unsigned int address = 0;
	clr	a
	mov	_address,a
	mov	(_address + 1),a
;--------------------------------------------------------
; Home
;--------------------------------------------------------
	.area HOME    (CODE)
	.area HOME    (CODE)
;--------------------------------------------------------
; code
;--------------------------------------------------------
	.area CSEG    (CODE)
;------------------------------------------------------------
;Allocation info for local variables in function 'STDIO_initialize'
;------------------------------------------------------------
;------------------------------------------------------------
;	../stdio-t6963c.c:11: void STDIO_initialize() {
;	-----------------------------------------
;	 function STDIO_initialize
;	-----------------------------------------
_STDIO_initialize:
	ar2 = 0x02
	ar3 = 0x03
	ar4 = 0x04
	ar5 = 0x05
	ar6 = 0x06
	ar7 = 0x07
	ar0 = 0x00
	ar1 = 0x01
;	../stdio-t6963c.c:12: T6963C_initialize();
	ljmp	_T6963C_initialize
;------------------------------------------------------------
;Allocation info for local variables in function 'STDIO_startWritingAt'
;------------------------------------------------------------
;y                         Allocated with name '_STDIO_startWritingAt_PARM_2'
;x                         Allocated to registers r2 
;------------------------------------------------------------
;	../stdio-t6963c.c:21: void STDIO_startWritingAt(unsigned char x, unsigned char y) {
;	-----------------------------------------
;	 function STDIO_startWritingAt
;	-----------------------------------------
_STDIO_startWritingAt:
	mov	r2,dpl
;	../stdio-t6963c.c:22: address = x + y * T6963C_COLONNES;
	mov	r3,#0x00
	mov	a,_STDIO_startWritingAt_PARM_2
	mov	b,#0x1E
	mul	ab
	add	a,r2
	mov	_address,a
	mov	a,r3
	addc	a,b
	mov	(_address + 1),a
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'putchar'
;------------------------------------------------------------
;c                         Allocated to registers r2 
;------------------------------------------------------------
;	../stdio-t6963c.c:29: char putchar(char c) {
;	-----------------------------------------
;	 function putchar
;	-----------------------------------------
_putchar:
	mov	r2,dpl
;	../stdio-t6963c.c:30: switch(c) {
	cjne	r2,#0xE0,00115$
	sjmp	00105$
00115$:
	cjne	r2,#0xE9,00116$
	sjmp	00104$
00116$:
	cjne	r2,#0x09,00117$
	sjmp	00103$
00117$:
	cjne	r2,#0x0A,00118$
	sjmp	00101$
00118$:
	cjne	r2,#0x0D,00119$
	sjmp	00102$
00119$:
;	../stdio-t6963c.c:31: case '\n':
	sjmp	00106$
00101$:
;	../stdio-t6963c.c:32: address += T6963C_COLONNES;
	mov	a,#0x1E
	add	a,_address
	mov	_address,a
	clr	a
	addc	a,(_address + 1)
	mov	(_address + 1),a
;	../stdio-t6963c.c:33: break;
	ljmp	00107$
;	../stdio-t6963c.c:35: case '\r':
00102$:
;	../stdio-t6963c.c:36: address /= T6963C_COLONNES;
	mov	__divuint_PARM_2,#0x1E
	mov	(__divuint_PARM_2 + 1),#0x00
	mov	dpl,_address
	mov	dph,(_address + 1)
	push	ar2
	lcall	__divuint
	mov	_address,dpl
	mov	(_address + 1),dph
;	../stdio-t6963c.c:37: address *= T6963C_COLONNES;
	mov	__mulint_PARM_2,_address
	mov	(__mulint_PARM_2 + 1),(_address + 1)
	mov	dptr,#0x001E
	lcall	__mulint
	mov	_address,dpl
	mov	(_address + 1),dph
	pop	ar2
;	../stdio-t6963c.c:38: break;
;	../stdio-t6963c.c:40: case '\t':
	sjmp	00107$
00103$:
;	../stdio-t6963c.c:41: address += 3;
	mov	a,#0x03
	add	a,_address
	mov	_address,a
	clr	a
	addc	a,(_address + 1)
	mov	(_address + 1),a
;	../stdio-t6963c.c:42: break;
;	../stdio-t6963c.c:44: case 'é':
	sjmp	00107$
00104$:
;	../stdio-t6963c.c:45: T6963C_dataWrite(T6963C_ZONE_TEXTE + address++, 0x62);
	mov	dpl,_address
	mov	dph,(_address + 1)
	inc	_address
	clr	a
	cjne	a,_address,00120$
	inc	(_address + 1)
00120$:
	mov	_T6963C_dataWrite_PARM_2,#0x62
	push	ar2
	lcall	_T6963C_dataWrite
	pop	ar2
;	../stdio-t6963c.c:46: break;
;	../stdio-t6963c.c:48: case 'à':
	sjmp	00107$
00105$:
;	../stdio-t6963c.c:49: T6963C_dataWrite(T6963C_ZONE_TEXTE + address++, 0x65);
	mov	dpl,_address
	mov	dph,(_address + 1)
	inc	_address
	clr	a
	cjne	a,_address,00121$
	inc	(_address + 1)
00121$:
	mov	_T6963C_dataWrite_PARM_2,#0x65
	push	ar2
	lcall	_T6963C_dataWrite
	pop	ar2
;	../stdio-t6963c.c:50: break;
;	../stdio-t6963c.c:52: default:
	sjmp	00107$
00106$:
;	../stdio-t6963c.c:53: T6963C_dataWrite(T6963C_ZONE_TEXTE + address++, c - 32);
	mov	dpl,_address
	mov	dph,(_address + 1)
	inc	_address
	clr	a
	cjne	a,_address,00122$
	inc	(_address + 1)
00122$:
	mov	a,r2
	add	a,#0xe0
	mov	_T6963C_dataWrite_PARM_2,a
	push	ar2
	lcall	_T6963C_dataWrite
	pop	ar2
;	../stdio-t6963c.c:55: }
00107$:
;	../stdio-t6963c.c:56: return c;
	mov	dpl,r2
	ret
	.area CSEG    (CODE)
	.area CONST   (CODE)
	.area XINIT   (CODE)
	.area CABS    (ABS,CODE)
