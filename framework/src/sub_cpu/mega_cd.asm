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

	include	"mcd_sub.inc"
	
	section code

; ------------------------------------------------------------------------------
; Check if we have access to Word RAM bank 0 (1M/1M)
; ------------------------------------------------------------------------------
; RETURNS:
;	eq/ne - No access/Access
; ------------------------------------------------------------------------------

	xdef CheckWordRamBank0
CheckWordRamBank0:
	btst	#0,MCD_MEM_MODE					; Check if we have access
	rts

; ------------------------------------------------------------------------------
; Check if we have access to Word RAM bank 1 (1M/1M)
; ------------------------------------------------------------------------------
; RETURNS:
;	eq/ne - No access/Access
; ------------------------------------------------------------------------------

	xdef CheckWordRamBank1
CheckWordRamBank1:
	bsr.s	CheckWordRamBank0				; Check if we have access
	eori.w	#4,sr
	rts

; ------------------------------------------------------------------------------
; Check if we have access to Word RAM (2M)
; ------------------------------------------------------------------------------
; RETURNS:
;	eq/ne - No access/Access
; ------------------------------------------------------------------------------

	xdef CheckWordRam
CheckWordRam:
	btst	#1,MCD_MEM_MODE					; Check if we have access
	rts

; ------------------------------------------------------------------------------
; Swap Word RAM banks (1M/1M)
; ------------------------------------------------------------------------------

	xdef SwapWordRamBanks
	xdef XREF_SwapWordRamBanksCmd
SwapWordRamBanks:
XREF_SwapWordRamBanksCmd:
	bsr.s	CheckWordRamBank0				; Do we have access to bank 0?
	bne.s	SetWordRamBank1					; If so, branch

; ------------------------------------------------------------------------------
; Access Word RAM bank 0 (1M/1M)
; ------------------------------------------------------------------------------

	xdef SetWordRamBank0
	xdef XREF_SetWordRamBank1Cmd
SetWordRamBank0:
XREF_SetWordRamBank1Cmd:
	bset	#0,MCD_MEM_MODE					; Access bank 0
	rts

; ------------------------------------------------------------------------------
; Access Word RAM bank 1 (1M/1M)
; ------------------------------------------------------------------------------

	xdef SetWordRamBank1
	xdef XREF_SetWordRamBank0Cmd
SetWordRamBank1:
XREF_SetWordRamBank0Cmd:
	bclr	#0,MCD_MEM_MODE					; Access bank 1
	rts

; ------------------------------------------------------------------------------
; Give Word RAM access to the Main CPU (2M)
; ------------------------------------------------------------------------------

	xdef GiveWordRam
GiveWordRam:
	bset	#0,MCD_MEM_MODE					; Give access to the Main CPU
	beq.s	GiveWordRam					; If it hasn't been given, wait
	rts

; ------------------------------------------------------------------------------
; Wait for Word RAM access (2M)
; ------------------------------------------------------------------------------

	xdef WaitWordRam
WaitWordRam:
	bsr.s	CheckWordRam					; Do we have access?
	beq.s	WaitWordRam					; If not, wait
	rts

; ------------------------------------------------------------------------------
; Check if we are in Word RAM 1M/1M mode
; ------------------------------------------------------------------------------
; RETURNS:
;	eq/ne - Not 1M/1M mode/1M/1M mode
; ------------------------------------------------------------------------------

	xdef CheckWordRam1M
CheckWordRam1M:
	btst	#2,MCD_MEM_MODE					; Check if we are in 1M/1M mode
	rts

; ------------------------------------------------------------------------------
; Check if we are in Word RAM 2M mode
; ------------------------------------------------------------------------------
; RETURNS:
;	eq/ne - Not 2M mode/2M mode
; ------------------------------------------------------------------------------

	xdef CheckWordRam2M
CheckWordRam2M:
	bsr.s	CheckWordRam1M					; Check if we are in 2M mode
	eori.w	#4,sr
	rts

; ------------------------------------------------------------------------------
; Set to Word RAM 1M/1M mode
; ------------------------------------------------------------------------------

	xdef SetWordRam1M
SetWordRam1M:
	bset	#2,MCD_MEM_MODE					; Set to 1M/1M mode
	rts

; ------------------------------------------------------------------------------
; Set to Word RAM 2M mode
; ------------------------------------------------------------------------------

	xdef SetWordRam2M
SetWordRam2M:
	bclr	#2,MCD_MEM_MODE					; Set to 2M mode
	rts

; ------------------------------------------------------------------------------
; Get Word RAM priority mode
; ------------------------------------------------------------------------------
; RETURNS:
;	d0.b - Word RAM priority mode
;	       0 - Off
;	       1 - Overwrite
;	       2 - Underwrite
; ------------------------------------------------------------------------------

	xdef GetWordRamPriority
GetWordRamPriority:
	move.b	MCD_MEM_MODE,d0					; Get priority mode
	lsr.b	#3,d0
	andi.b	#3,d0
	rts

; ------------------------------------------------------------------------------
; Disable Word RAM priority
; ------------------------------------------------------------------------------

	xdef DisableWordRamPriority
DisableWordRamPriority:
	andi.b	#~$18,MCD_MEM_MODE				; Disable priority
	rts

; ------------------------------------------------------------------------------
; Set Word RAM priority to overwrite
; ------------------------------------------------------------------------------

	xdef SetWordRamOverwrite
SetWordRamOverwrite:
	bsr.s	DisableWordRamPriority				; Set overwrite
	ori.b	#8,MCD_MEM_MODE
	rts

; ------------------------------------------------------------------------------
; Set Word RAM priority to underwrite
; ------------------------------------------------------------------------------

	xdef SetWordRamUnderwrite
SetWordRamUnderwrite:
	bsr.s	DisableWordRamPriority				; Set overwrite
	ori.b	#$10,MCD_MEM_MODE
	rts

; ------------------------------------------------------------------------------
; Reset Program RAM
; ------------------------------------------------------------------------------

	xdef ResetPrgRam
ResetPrgRam:
	movem.l	d0-d1/a0,-(sp)					; Save registers

	lea	XREF_ProgramEnd.w,a0				; Clear non-program parts of Program RAM
	moveq	#0,d0
	move.w	#XREF_PRG_RAM_CLEAR-1,d1

.Clear:
	rept $20/4
		move.l	d0,(a0)+
	endr
	dbf	d1,.Clear
	
	bsr.w	UnloadModule					; Unload module
	movem.l	(sp)+,d0-d1/a0					; Restore registers
	rts

; ------------------------------------------------------------------------------
; Clear Word RAM bank (1M/1M)
; ------------------------------------------------------------------------------

	xdef ClearWordRamBank
ClearWordRamBank:
	bsr.w	CheckWordRam1M					; Are we in 1M/1M mode?
	beq.s	.End						; If not, branch

	movem.l	d0-d1/a0,-(sp)					; Save registers

	lea	WORD_RAM_1M,a0					; Clear Word RAM bank
	moveq	#0,d0
	move.w	#(WORD_RAM_1M_SIZE/$20)-1,d1

.Clear:
	rept $20/4
		move.l	d0,(a0)+
	endr
	dbf	d1,.Clear

	movem.l	(sp)+,d0-d1/a0					; Restore registers

.End:
	rts

; ------------------------------------------------------------------------------
; Clear Word RAM (2M)
; ------------------------------------------------------------------------------

	xdef ClearWordRam
ClearWordRam:
	bsr.w	CheckWordRam2M					; Are we in 2M mode?
	beq.s	.End						; If not, branch

	movem.l	d0-d1/a0,-(sp)					; Save registers

	lea	WORD_RAM_2M,a0					; Clear Word RAM bank
	moveq	#0,d0
	move.w	#(WORD_RAM_2M_SIZE/$20)-1,d1

.Clear:
	rept $20/4
		move.l	d0,(a0)+
	endr
	dbf	d1,.Clear
	
	movem.l	(sp)+,d0-d1/a0					; Restore registers

.End:
	rts

; ------------------------------------------------------------------------------