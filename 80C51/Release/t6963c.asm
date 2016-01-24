;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 3.0.0 #6037 (Oct 31 2010) (MINGW32)
; This file was generated Fri Jan 22 14:38:59 2016
;--------------------------------------------------------
	.module t6963c
	.optsdcc -mmcs51 --model-small
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _T6963C_calculateAddress_PARM_2
	.globl _T6963C_dataRead
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
	.globl _T6963C_readFrom_PARM_2
	.globl _T6963C_writeAt_PARM_3
	.globl _T6963C_writeAt_PARM_2
	.globl _T6963C_autoRepeat_PARM_3
	.globl _T6963C_autoRepeat_PARM_2
	.globl _T6963C_autoWrite_PARM_3
	.globl _T6963C_autoWrite_PARM_2
	.globl _T6963C_dataWrite_PARM_2
	.globl _T6963C_addressCommand_PARM_2
	.globl _T6963C_twoDataCommand_PARM_3
	.globl _T6963C_twoDataCommand_PARM_2
	.globl _T6963C_oneDataCommand_PARM_2
	.globl __t6963c
	.globl _T6963C_statusCheck
	.globl _T6963C_noDataCommand
	.globl _T6963C_oneDataCommand
	.globl _T6963C_twoDataCommand
	.globl _T6963C_addressCommand
	.globl _T6963C_dataWrite
	.globl _T6963C_statusCheckForAutoWrite
	.globl _T6963C_autoWrite
	.globl _T6963C_autoRepeat
	.globl _T6963C_calculateAddress
	.globl _T6963C_writeAt
	.globl _T6963C_readFrom
	.globl _T6963C_initialize
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
__t6963c::
	.ds 3
_T6963C_oneDataCommand_PARM_2:
	.ds 1
_T6963C_twoDataCommand_PARM_2:
	.ds 1
_T6963C_twoDataCommand_PARM_3:
	.ds 1
_T6963C_addressCommand_PARM_2:
	.ds 2
_T6963C_dataWrite_PARM_2:
	.ds 1
_T6963C_autoWrite_PARM_2:
	.ds 3
_T6963C_autoWrite_PARM_3:
	.ds 2
_T6963C_autoWrite_n_1_1:
	.ds 2
_T6963C_autoRepeat_PARM_2:
	.ds 1
_T6963C_autoRepeat_PARM_3:
	.ds 2
_T6963C_writeAt_PARM_2:
	.ds 1
_T6963C_writeAt_PARM_3:
	.ds 1
_T6963C_readFrom_PARM_2:
	.ds 1
;--------------------------------------------------------
; overlayable items in internal ram 
;--------------------------------------------------------
	.area	OSEG    (OVR,DATA)
	.area	OSEG    (OVR,DATA)
	.area	OSEG    (OVR,DATA)
_T6963C_calculateAddress_PARM_2::
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
;	../t6963c.c:4: unsigned char *_t6963c = (unsigned char __xdata *) 0x2000;
	mov	__t6963c,#0x00
	mov	(__t6963c + 1),#0x20
	mov	(__t6963c + 2),#0x00
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
;Allocation info for local variables in function 'T6963C_statusCheck'
;------------------------------------------------------------
;status                    Allocated to registers r2 
;------------------------------------------------------------
;	../t6963c.c:21: void T6963C_statusCheck() {
;	-----------------------------------------
;	 function T6963C_statusCheck
;	-----------------------------------------
_T6963C_statusCheck:
	ar2 = 0x02
	ar3 = 0x03
	ar4 = 0x04
	ar5 = 0x05
	ar6 = 0x06
	ar7 = 0x07
	ar0 = 0x00
	ar1 = 0x01
;	../t6963c.c:23: do {
00101$:
;	../t6963c.c:24: status = _t6963c[CD_COMMAND];
	mov	a,#0x01
	add	a,__t6963c
	mov	r2,a
	clr	a
	addc	a,(__t6963c + 1)
	mov	r3,a
	mov	r4,(__t6963c + 2)
	mov	dpl,r2
	mov	dph,r3
	mov	b,r4
	lcall	__gptrget
	mov	r2,a
;	../t6963c.c:25: status &= STA0_STA1;
	anl	ar2,#0x03
;	../t6963c.c:26: } while (status != STA0_STA1);
	cjne	r2,#0x03,00101$
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'T6963C_noDataCommand'
;------------------------------------------------------------
;command                   Allocated to registers r2 
;------------------------------------------------------------
;	../t6963c.c:33: void T6963C_noDataCommand(unsigned char command) {
;	-----------------------------------------
;	 function T6963C_noDataCommand
;	-----------------------------------------
_T6963C_noDataCommand:
	mov	r2,dpl
;	../t6963c.c:34: T6963C_statusCheck();
	push	ar2
	lcall	_T6963C_statusCheck
	pop	ar2
;	../t6963c.c:35: _t6963c[CD_COMMAND] = command;
	mov	a,#0x01
	add	a,__t6963c
	mov	r3,a
	clr	a
	addc	a,(__t6963c + 1)
	mov	r4,a
	mov	r5,(__t6963c + 2)
	mov	dpl,r3
	mov	dph,r4
	mov	b,r5
	mov	a,r2
	ljmp	__gptrput
;------------------------------------------------------------
;Allocation info for local variables in function 'T6963C_oneDataCommand'
;------------------------------------------------------------
;data1                     Allocated with name '_T6963C_oneDataCommand_PARM_2'
;command                   Allocated to registers r2 
;------------------------------------------------------------
;	../t6963c.c:43: void T6963C_oneDataCommand(unsigned char command, unsigned char data1) {
;	-----------------------------------------
;	 function T6963C_oneDataCommand
;	-----------------------------------------
_T6963C_oneDataCommand:
	mov	r2,dpl
;	../t6963c.c:44: T6963C_statusCheck();
	push	ar2
	lcall	_T6963C_statusCheck
;	../t6963c.c:45: _t6963c[CD_DATA] = data1;
	mov	r3,__t6963c
	mov	r4,(__t6963c + 1)
	mov	r5,(__t6963c + 2)
	mov	dpl,r3
	mov	dph,r4
	mov	b,r5
	mov	a,_T6963C_oneDataCommand_PARM_2
	lcall	__gptrput
;	../t6963c.c:46: T6963C_statusCheck();
	lcall	_T6963C_statusCheck
	pop	ar2
;	../t6963c.c:47: _t6963c[CD_COMMAND] = command;
	mov	a,#0x01
	add	a,__t6963c
	mov	r3,a
	clr	a
	addc	a,(__t6963c + 1)
	mov	r4,a
	mov	r5,(__t6963c + 2)
	mov	dpl,r3
	mov	dph,r4
	mov	b,r5
	mov	a,r2
	ljmp	__gptrput
;------------------------------------------------------------
;Allocation info for local variables in function 'T6963C_twoDataCommand'
;------------------------------------------------------------
;data1                     Allocated with name '_T6963C_twoDataCommand_PARM_2'
;data2                     Allocated with name '_T6963C_twoDataCommand_PARM_3'
;command                   Allocated to registers r2 
;------------------------------------------------------------
;	../t6963c.c:56: void T6963C_twoDataCommand(unsigned char command, 
;	-----------------------------------------
;	 function T6963C_twoDataCommand
;	-----------------------------------------
_T6963C_twoDataCommand:
	mov	r2,dpl
;	../t6963c.c:59: T6963C_statusCheck();
	push	ar2
	lcall	_T6963C_statusCheck
;	../t6963c.c:60: _t6963c[CD_DATA] = data1;
	mov	r3,__t6963c
	mov	r4,(__t6963c + 1)
	mov	r5,(__t6963c + 2)
	mov	dpl,r3
	mov	dph,r4
	mov	b,r5
	mov	a,_T6963C_twoDataCommand_PARM_2
	lcall	__gptrput
;	../t6963c.c:61: T6963C_statusCheck();
	lcall	_T6963C_statusCheck
;	../t6963c.c:62: _t6963c[CD_DATA] = data2;
	mov	r3,__t6963c
	mov	r4,(__t6963c + 1)
	mov	r5,(__t6963c + 2)
	mov	dpl,r3
	mov	dph,r4
	mov	b,r5
	mov	a,_T6963C_twoDataCommand_PARM_3
	lcall	__gptrput
;	../t6963c.c:63: T6963C_statusCheck();
	lcall	_T6963C_statusCheck
	pop	ar2
;	../t6963c.c:64: _t6963c[CD_COMMAND] = command;
	mov	a,#0x01
	add	a,__t6963c
	mov	r3,a
	clr	a
	addc	a,(__t6963c + 1)
	mov	r4,a
	mov	r5,(__t6963c + 2)
	mov	dpl,r3
	mov	dph,r4
	mov	b,r5
	mov	a,r2
	ljmp	__gptrput
;------------------------------------------------------------
;Allocation info for local variables in function 'T6963C_addressCommand'
;------------------------------------------------------------
;address                   Allocated with name '_T6963C_addressCommand_PARM_2'
;command                   Allocated to registers r2 
;b                         Allocated to registers 
;------------------------------------------------------------
;	../t6963c.c:72: void T6963C_addressCommand(unsigned char command, 
;	-----------------------------------------
;	 function T6963C_addressCommand
;	-----------------------------------------
_T6963C_addressCommand:
	mov	r2,dpl
;	../t6963c.c:74: unsigned char *b = (unsigned char *) &address;
;	../t6963c.c:75: T6963C_statusCheck();
	push	ar2
	lcall	_T6963C_statusCheck
;	../t6963c.c:76: _t6963c[CD_DATA] = b[0];
	mov	r3,__t6963c
	mov	r4,(__t6963c + 1)
	mov	r5,(__t6963c + 2)
	mov	r6,_T6963C_addressCommand_PARM_2
	mov	dpl,r3
	mov	dph,r4
	mov	b,r5
	mov	a,r6
	lcall	__gptrput
;	../t6963c.c:77: T6963C_statusCheck();
	lcall	_T6963C_statusCheck
;	../t6963c.c:78: _t6963c[CD_DATA] = b[1];
	mov	r3,__t6963c
	mov	r4,(__t6963c + 1)
	mov	r5,(__t6963c + 2)
	mov	dptr,#(_T6963C_addressCommand_PARM_2 + 0x0001)
	mov	b,#0x40
	lcall	__gptrget
	mov	dpl,r3
	mov	dph,r4
	mov	b,r5
	lcall	__gptrput
;	../t6963c.c:79: T6963C_statusCheck();
	lcall	_T6963C_statusCheck
	pop	ar2
;	../t6963c.c:80: _t6963c[CD_COMMAND] = command;
	mov	a,#0x01
	add	a,__t6963c
	mov	r3,a
	clr	a
	addc	a,(__t6963c + 1)
	mov	r4,a
	mov	r5,(__t6963c + 2)
	mov	dpl,r3
	mov	dph,r4
	mov	b,r5
	mov	a,r2
	ljmp	__gptrput
;------------------------------------------------------------
;Allocation info for local variables in function 'T6963C_dataWrite'
;------------------------------------------------------------
;data1                     Allocated with name '_T6963C_dataWrite_PARM_2'
;address                   Allocated to registers 
;------------------------------------------------------------
;	../t6963c.c:89: void T6963C_dataWrite(unsigned int address,unsigned char data1) {
;	-----------------------------------------
;	 function T6963C_dataWrite
;	-----------------------------------------
_T6963C_dataWrite:
	mov	_T6963C_addressCommand_PARM_2,dpl
	mov	(_T6963C_addressCommand_PARM_2 + 1),dph
;	../t6963c.c:90: T6963C_addressCommand(0x24,address);
	mov	dpl,#0x24
	lcall	_T6963C_addressCommand
;	../t6963c.c:91: T6963C_oneDataCommand(0xC0,data1);
	mov	_T6963C_oneDataCommand_PARM_2,_T6963C_dataWrite_PARM_2
	mov	dpl,#0xC0
	ljmp	_T6963C_oneDataCommand
;------------------------------------------------------------
;Allocation info for local variables in function 'T6963C_dataRead'
;------------------------------------------------------------
;address                   Allocated to registers 
;------------------------------------------------------------
;	../t6963c.c:99: unsigned char T6963C_dataRead(unsigned int address) {
;	-----------------------------------------
;	 function T6963C_dataRead
;	-----------------------------------------
_T6963C_dataRead:
	mov	_T6963C_addressCommand_PARM_2,dpl
	mov	(_T6963C_addressCommand_PARM_2 + 1),dph
;	../t6963c.c:100: T6963C_addressCommand(0x24,address);
	mov	dpl,#0x24
	lcall	_T6963C_addressCommand
;	../t6963c.c:101: T6963C_noDataCommand(0xC1);
	mov	dpl,#0xC1
	lcall	_T6963C_noDataCommand
;	../t6963c.c:102: return _t6963c[CD_DATA];
	mov	r2,__t6963c
	mov	r3,(__t6963c + 1)
	mov	r4,(__t6963c + 2)
	mov	dpl,r2
	mov	dph,r3
	mov	b,r4
	lcall	__gptrget
	mov	dpl,a
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'T6963C_statusCheckForAutoWrite'
;------------------------------------------------------------
;status                    Allocated to registers r2 
;------------------------------------------------------------
;	../t6963c.c:108: void T6963C_statusCheckForAutoWrite() {
;	-----------------------------------------
;	 function T6963C_statusCheckForAutoWrite
;	-----------------------------------------
_T6963C_statusCheckForAutoWrite:
;	../t6963c.c:110: do {
00101$:
;	../t6963c.c:111: status = _t6963c[CD_COMMAND];  // Pour activer C
	mov	a,#0x01
	add	a,__t6963c
	mov	r2,a
	clr	a
	addc	a,(__t6963c + 1)
	mov	r3,a
	mov	r4,(__t6963c + 2)
	mov	dpl,r2
	mov	dph,r3
	mov	b,r4
	lcall	__gptrget
	mov	r2,a
;	../t6963c.c:112: status &= STA_3;          // Vérifie STA3
	anl	ar2,#0x08
;	../t6963c.c:113: } while (status != STA_3);
	cjne	r2,#0x08,00101$
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'T6963C_autoWrite'
;------------------------------------------------------------
;data1                     Allocated with name '_T6963C_autoWrite_PARM_2'
;size                      Allocated with name '_T6963C_autoWrite_PARM_3'
;address                   Allocated to registers r2 r3 
;n                         Allocated with name '_T6963C_autoWrite_n_1_1'
;------------------------------------------------------------
;	../t6963c.c:124: unsigned int T6963C_autoWrite(unsigned int address, 
;	-----------------------------------------
;	 function T6963C_autoWrite
;	-----------------------------------------
_T6963C_autoWrite:
	mov	r2,dpl
	mov	r3,dph
;	../t6963c.c:128: T6963C_addressCommand(0x24, address);
	mov	_T6963C_addressCommand_PARM_2,r2
	mov	(_T6963C_addressCommand_PARM_2 + 1),r3
	mov	dpl,#0x24
	push	ar2
	push	ar3
	lcall	_T6963C_addressCommand
;	../t6963c.c:129: T6963C_noDataCommand(0xB0);
	mov	dpl,#0xB0
	lcall	_T6963C_noDataCommand
	pop	ar3
	pop	ar2
;	../t6963c.c:130: for(n=0 ; n<size ; n++) {
	clr	a
	mov	_T6963C_autoWrite_n_1_1,a
	mov	(_T6963C_autoWrite_n_1_1 + 1),a
00101$:
	clr	c
	mov	a,_T6963C_autoWrite_n_1_1
	subb	a,_T6963C_autoWrite_PARM_3
	mov	a,(_T6963C_autoWrite_n_1_1 + 1)
	subb	a,(_T6963C_autoWrite_PARM_3 + 1)
	jnc	00104$
;	../t6963c.c:131: address++;
	inc	r2
	cjne	r2,#0x00,00111$
	inc	r3
00111$:
;	../t6963c.c:132: T6963C_statusCheckForAutoWrite();
	push	ar2
	push	ar3
	lcall	_T6963C_statusCheckForAutoWrite
	pop	ar3
	pop	ar2
;	../t6963c.c:133: _t6963c[CD_DATA] = data1[n];
	mov	r6,__t6963c
	mov	r7,(__t6963c + 1)
	mov	r0,(__t6963c + 2)
	mov	a,_T6963C_autoWrite_n_1_1
	add	a,_T6963C_autoWrite_PARM_2
	mov	r1,a
	mov	a,(_T6963C_autoWrite_n_1_1 + 1)
	addc	a,(_T6963C_autoWrite_PARM_2 + 1)
	mov	r4,a
	mov	r5,(_T6963C_autoWrite_PARM_2 + 2)
	mov	dpl,r1
	mov	dph,r4
	mov	b,r5
	lcall	__gptrget
	mov	r1,a
	mov	dpl,r6
	mov	dph,r7
	mov	b,r0
	lcall	__gptrput
;	../t6963c.c:130: for(n=0 ; n<size ; n++) {
	inc	_T6963C_autoWrite_n_1_1
	clr	a
	cjne	a,_T6963C_autoWrite_n_1_1,00101$
	inc	(_T6963C_autoWrite_n_1_1 + 1)
	sjmp	00101$
00104$:
;	../t6963c.c:135: T6963C_noDataCommand(0xB2);
	mov	dpl,#0xB2
	push	ar2
	push	ar3
	lcall	_T6963C_noDataCommand
	pop	ar3
	pop	ar2
;	../t6963c.c:136: return address;
	mov	dpl,r2
	mov	dph,r3
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'T6963C_autoRepeat'
;------------------------------------------------------------
;data1                     Allocated with name '_T6963C_autoRepeat_PARM_2'
;repeats                   Allocated with name '_T6963C_autoRepeat_PARM_3'
;address                   Allocated to registers r2 r3 
;n                         Allocated to registers r4 r5 
;------------------------------------------------------------
;	../t6963c.c:146: unsigned int T6963C_autoRepeat(unsigned int address, 
;	-----------------------------------------
;	 function T6963C_autoRepeat
;	-----------------------------------------
_T6963C_autoRepeat:
	mov	r2,dpl
	mov	r3,dph
;	../t6963c.c:150: T6963C_addressCommand(0x24, address);
	mov	_T6963C_addressCommand_PARM_2,r2
	mov	(_T6963C_addressCommand_PARM_2 + 1),r3
	mov	dpl,#0x24
	push	ar2
	push	ar3
	lcall	_T6963C_addressCommand
;	../t6963c.c:151: T6963C_noDataCommand(0xB0);
	mov	dpl,#0xB0
	lcall	_T6963C_noDataCommand
	pop	ar3
	pop	ar2
;	../t6963c.c:152: for(n=0 ; n<repeats ; n++) {
	mov	r4,#0x00
	mov	r5,#0x00
00101$:
	clr	c
	mov	a,r4
	subb	a,_T6963C_autoRepeat_PARM_3
	mov	a,r5
	subb	a,(_T6963C_autoRepeat_PARM_3 + 1)
	jnc	00104$
;	../t6963c.c:153: address++;
	inc	r2
	cjne	r2,#0x00,00111$
	inc	r3
00111$:
;	../t6963c.c:154: T6963C_statusCheckForAutoWrite();
	push	ar2
	push	ar3
	push	ar4
	push	ar5
	lcall	_T6963C_statusCheckForAutoWrite
	pop	ar5
	pop	ar4
	pop	ar3
	pop	ar2
;	../t6963c.c:155: _t6963c[CD_DATA] = data1;
	mov	r6,__t6963c
	mov	r7,(__t6963c + 1)
	mov	r0,(__t6963c + 2)
	mov	dpl,r6
	mov	dph,r7
	mov	b,r0
	mov	a,_T6963C_autoRepeat_PARM_2
	lcall	__gptrput
;	../t6963c.c:152: for(n=0 ; n<repeats ; n++) {
	inc	r4
	cjne	r4,#0x00,00101$
	inc	r5
	sjmp	00101$
00104$:
;	../t6963c.c:157: T6963C_noDataCommand(0xB2);
	mov	dpl,#0xB2
	push	ar2
	push	ar3
	lcall	_T6963C_noDataCommand
	pop	ar3
	pop	ar2
;	../t6963c.c:158: return address;
	mov	dpl,r2
	mov	dph,r3
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'T6963C_calculateAddress'
;------------------------------------------------------------
;y                         Allocated with name '_T6963C_calculateAddress_PARM_2'
;x                         Allocated to registers r2 
;------------------------------------------------------------
;	../t6963c.c:167: unsigned int T6963C_calculateAddress(unsigned char x, 
;	-----------------------------------------
;	 function T6963C_calculateAddress
;	-----------------------------------------
_T6963C_calculateAddress:
	mov	r2,dpl
;	../t6963c.c:169: return T6963C_ZONE_TEXTE + y * T6963C_COLONNES + x;
	mov	a,_T6963C_calculateAddress_PARM_2
	mov	b,#0x1E
	mul	ab
	mov	r3,a
	mov	r4,b
	mov	r5,#0x00
	mov	a,r2
	add	a,r3
	mov	dpl,a
	mov	a,r5
	addc	a,r4
	mov	dph,a
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'T6963C_writeAt'
;------------------------------------------------------------
;y                         Allocated with name '_T6963C_writeAt_PARM_2'
;c                         Allocated with name '_T6963C_writeAt_PARM_3'
;x                         Allocated to registers 
;address                   Allocated to registers 
;------------------------------------------------------------
;	../t6963c.c:178: void T6963C_writeAt(unsigned char x, 
;	-----------------------------------------
;	 function T6963C_writeAt
;	-----------------------------------------
_T6963C_writeAt:
;	../t6963c.c:181: unsigned int address = T6963C_calculateAddress(x, y);
	mov	_T6963C_calculateAddress_PARM_2,_T6963C_writeAt_PARM_2
	lcall	_T6963C_calculateAddress
;	../t6963c.c:182: T6963C_dataWrite(address, c);
	mov	_T6963C_dataWrite_PARM_2,_T6963C_writeAt_PARM_3
	ljmp	_T6963C_dataWrite
;------------------------------------------------------------
;Allocation info for local variables in function 'T6963C_readFrom'
;------------------------------------------------------------
;y                         Allocated with name '_T6963C_readFrom_PARM_2'
;x                         Allocated to registers 
;address                   Allocated to registers 
;------------------------------------------------------------
;	../t6963c.c:191: unsigned char T6963C_readFrom(unsigned char x, 
;	-----------------------------------------
;	 function T6963C_readFrom
;	-----------------------------------------
_T6963C_readFrom:
;	../t6963c.c:193: unsigned int address = T6963C_calculateAddress(x, y);
	mov	_T6963C_calculateAddress_PARM_2,_T6963C_readFrom_PARM_2
	lcall	_T6963C_calculateAddress
;	../t6963c.c:194: return T6963C_dataRead(address);
	ljmp	_T6963C_dataRead
;------------------------------------------------------------
;Allocation info for local variables in function 'T6963C_initialize'
;------------------------------------------------------------
;------------------------------------------------------------
;	../t6963c.c:200: void T6963C_initialize() {
;	-----------------------------------------
;	 function T6963C_initialize
;	-----------------------------------------
_T6963C_initialize:
;	../t6963c.c:201: T6963C_addressCommand(0x40, T6963C_ZONE_TEXTE);
	clr	a
	mov	_T6963C_addressCommand_PARM_2,a
	mov	(_T6963C_addressCommand_PARM_2 + 1),a
	mov	dpl,#0x40
	lcall	_T6963C_addressCommand
;	../t6963c.c:202: T6963C_addressCommand(0x42, T6963C_ZONE_GRAPHIQUE);
	mov	_T6963C_addressCommand_PARM_2,#0x00
	mov	(_T6963C_addressCommand_PARM_2 + 1),#0x02
	mov	dpl,#0x42
	lcall	_T6963C_addressCommand
;	../t6963c.c:203: T6963C_twoDataCommand(0x22, T6963C_ZONE_CG / 2048,0); 
	mov	_T6963C_twoDataCommand_PARM_2,#0x03
	mov	_T6963C_twoDataCommand_PARM_3,#0x00
	mov	dpl,#0x22
	lcall	_T6963C_twoDataCommand
;	../t6963c.c:204: T6963C_twoDataCommand(0x41, T6963C_COLONNES,0);
	mov	_T6963C_twoDataCommand_PARM_2,#0x1E
	mov	_T6963C_twoDataCommand_PARM_3,#0x00
	mov	dpl,#0x41
	lcall	_T6963C_twoDataCommand
;	../t6963c.c:205: T6963C_twoDataCommand(0x43, T6963C_COLONNES,0);     
	mov	_T6963C_twoDataCommand_PARM_2,#0x1E
	mov	_T6963C_twoDataCommand_PARM_3,#0x00
	mov	dpl,#0x43
	lcall	_T6963C_twoDataCommand
;	../t6963c.c:208: T6963C_noDataCommand(0x9C);
	mov	dpl,#0x9C
	lcall	_T6963C_noDataCommand
;	../t6963c.c:210: T6963C_noDataCommand(0x80);
	mov	dpl,#0x80
	ljmp	_T6963C_noDataCommand
	.area CSEG    (CODE)
	.area CONST   (CODE)
	.area XINIT   (CODE)
	.area CABS    (ABS,CODE)
