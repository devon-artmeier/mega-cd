; ------------------------------------------------------------------------------
; Copyright (c) 2025 Devon Artmeier
;
; Permission to use, copy, modify, and/or distribute this software
; for any purpose with or without fee is hereby granted.
;
; THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
; WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIE
; WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
; AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
; DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
; PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER 
; TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
; PERFORMANCE OF THIS SOFTWARE.
; ------------------------------------------------------------------------------

	include	"shared.inc"
	
	section init

; ------------------------------------------------------------------------------
; Hard reset
; ------------------------------------------------------------------------------

	xdef HardReset
HardReset:
	move	#$2700,sr					; Disable interrupts

	lea	.Addresses(pc),a0				; Get addresses
	movem.l	(a0)+,a1-a6
	
	moveq	#$F,d0						; Get hardware version
	and.b	IO_VERSION-(IO_CTRL_1-1)(a6),d0			; Is this a TMSS system?
	beq.s	.NoTmss						; If not, branch
	move.l	CARTRIDGE+$100,TMSS_SEGA			; If so, satisfy it

.NoTmss:
	waitDma (a5)						; Wait for DMA to finish, if there's one leftover

	moveq	#(.VdpSetupEnd-.VdpSetup)/2-1,d1		; Length of VDP setup data

.SetupVdp:
	move.w	(a0)+,(a5)					; Set VDP register
	dbf	d1,.SetupVdp					; Loop until all of them are set
	
	moveq	#0,d0						; Perform VRAM clear
	move.w	d0,(a4)
	waitDma (a5)
	move.w	(a0)+,(a5)
	
	move.l	(a0)+,(a5)					; Set CRAM write command
	moveq	#$80/4-1,d1					; Length of CRAM
	
.ClearCram:
	move.l	d0,(a4)						; Clear CRAM
	dbf	d1,.ClearCram					; Loop until CRAM is cleared
	
	move.l	(a0)+,(a5)					; Set VSRAM write command
	moveq	#$50/4-1,d1					; Length of VSRAM
	
.ClearVsram:
	move.l	d0,(a4)						; Clear VSRAM
	dbf	d1,.ClearVsram					; Loop until VSRAM is cleared
	
	moveq	#$FFFFFF9F,d2					; PSG1 silence
	moveq	#4-1,d1						; Number of PSG channels
	
.SilencePsg:
	move.b	d2,PSG_CTRL-VDP_CTRL(a5)			; Silence PSG channel
	addi.b	#$20,d2						; Next PSG channel
	dbf	d1,.SilencePsg					; Loop until all PSG channels are silenced
	
	move.w	#$100,d2					; Stop the Z80
	move.w	d2,(a2)
	move.w	d2,(a3)						; Stop Z80 reset

.WaitZ80Stop:
	btst	d0,(a2)						; Has the Z80 stopped?
	bne.s	.WaitZ80Stop					; If not, wait

	moveq	#$40,d1						; Set up I/O ports
	move.w	d1,(a6)+
	move.w	d1,(a6)+
	move.w	d1,(a6)+
	
	move.w	#.Z80PrgEnd-.Z80Prg-1,d1			; Length of Z80 program

.LoadZ80Program:
	move.b	(a0)+,(a1)+					; Load Z80 program
	dbf	d1,.LoadZ80Program				; Loop until Z80 program is loaded

	move.w	#(Z80_RAM_SIZE-(.Z80PrgEnd-.Z80Prg))-1,d1	; Remaining length of Z80 RAM

.ClearZ80Ram:
	move.b	d0,(a1)+					; Clear the rest of Z80 RAM
	dbf	d1,.ClearZ80Ram					; Loop until finished
	
	move.w	d0,(a3)						; Reset the Z80
	rol.b	#8,d0
	move.w	d0,(a2)						; Start the Z80
	move.w	d2,(a3)						; Stop Z80 reset

	movea.l	d0,a6						; Set base of work RAM
	move.l	a6,usp						; Set user stack pointer

	move.w	#WORK_RAM_SIZE/4-1,d1				; Length of work RAM
	
.ClearWorkRam:
	move.l	d0,-(a6)					; Clear work RAM
	dbf	d1,.ClearWorkRam				; Loop until work RAM is cleared

	lea	CARTRIDGE+$200,a1				; Start address for checksum check

	move.l	CARTRIDGE+$1A4,d1				; Get length in words
	addq.l	#1,d1
	sub.l	a1,d1
	lsr.l	#1,d1
	move.l	d1,d2

	lsr.l	#4,d1						; Get number of blocks
	subq.w	#1,d1

.ChecksumBlock:
	rept $10						; Calculate checksum
		add.w	(a1)+,d0
	endr
	dbf	d1,.ChecksumBlock				; Loop until finished

	andi.w	#$F,d2						; Get number of leftover words
	subq.w	#1,d2
	bmi.s	.CheckChecksum					; If there are none left, branch

.ChecksumLeftover:
	add.w	(a1)+,d0					; Calculate checksum
	dbf	d2,.ChecksumLeftover				; Loop until finished

.CheckChecksum:
	cmp.w	CARTRIDGE+$18E,d0				; Is the checksum correct?
	beq.s	.ChecksumGood					; If so, branch

	vdpCmd move.l,0,CRAM,WRITE,(a5)				; Display red
	move.w	#$E,(a4)
	bra.w	*						; Halt

.ChecksumGood:
	lea	SubCpuProgram,a0				; Initialize Sub CPU
	move.l	#SUB_CPU_PROGRAM_SIZE,d0
	bsr.w	McdLib+InitSubCpu
	beq.s	.GoToMain					; If it was successful, branch

	vdpCmd move.l,0,CRAM,WRITE,(a5)				; Display yellow
	move.w	#$EE,(a4)
	bra.w	*						; Halt

.GoToMain:
	movem.l	(a6),d0-a6					; Clear registers
	jmp	Main						; Go to main

; ------------------------------------------------------------------------------
; Addresses
; ------------------------------------------------------------------------------

.Addresses:
	dc.l	Z80_RAM						; a1: Z80 RAM
	dc.l	Z80_BUS						; a2: Z80 bus port
	dc.l	Z80_RESET					; a3: Z80 reset port
	dc.l	VDP_DATA					; a4: VDP data port
	dc.l	VDP_CTRL					; a5: VDP control port
	dc.l	IO_CTRL_1-1					; a6: I/O control port 1

; ------------------------------------------------------------------------------
; VDP setup data
; ------------------------------------------------------------------------------

.VdpSetup:
	dc.w	$8000|%00000100					; Disable H-BLANK interrupt
	dc.w	$8100|%00110100					; Enable DMA and V-BLANK interrupt, disable display
	dc.w	$8200|($C000>>10)				; Plane A VRAM address
	dc.w	$8300|($D000>>10)				; Window plane VRAM address
	dc.w	$8400|($E000>>13)				; Plane B VRAM address
	dc.w	$8500|($F800>>9)				; Sprite table VRAM address
	dc.w	$8700						; Background color
	dc.w	$8ADF						; H-BLANK interrupt counter
	dc.w	$8B00|%00000000					; Full screen scroll, disable external interrupt
	dc.w	$8C00|%10000001					; H40 mode, disable shadow/highlight and interlacing
	dc.w	$8D00|($FC00>>10)				; Hortizontal scroll table VRAM address
	dc.w	$8F01						; Auto-increment (for VRAM clear)
	dc.w	$9100						; Window horizontal position
	dc.w	$9200						; Window vertical position
	dc.w	$93FF						; DMA length (for VRAM clear)
	dc.w	$94FF
	dc.w	$9780						; DMA mode (for VRAM clear)
	vdpCmd dc.l,0,VRAM,DMA					; DMA command (for VRAM clear)
.VdpSetupEnd:
	dc.w	$8F02						; Auto-increment
	vdpCmd dc.l,0,CRAM,WRITE				; CRAM write command
	vdpCmd dc.l,0,VSRAM,WRITE				; VSRAM write command

; ------------------------------------------------------------------------------
; Z80 program
; ------------------------------------------------------------------------------

.Z80Prg:
	dc.b	$F3						; di
	dc.b	$F3						; di
	dc.b	$C3, $00, $00					; jp 0000h
.Z80PrgEnd:
	even

; ------------------------------------------------------------------------------