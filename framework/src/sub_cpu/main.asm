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

	section main

; ------------------------------------------------------------------------------
; Initialization
; ------------------------------------------------------------------------------

	xdef INT_Initialize
INT_Initialize:
	bsr.w	SetWordRam2M					; Set Word RAM to 2M mode
	bsr.w	DisableWordRamPriority				; Disable Word RAM priority
	
	lea	MCD_SUB_COMMS,a0				; Set up communication registers
	moveq	#0,d0
	move.l	d0,(a0)+
	move.l	d0,(a0)+
	move.l	d0,(a0)+
	move.l	d0,(a0)+

	lea	MCD_SUB_FLAG-(MCD_SUB_COMMS+$10)(a0),a0		; Get communication flags
	moveq	#"S",d1						; Mark as initializing
	move.b	d1,(a0)

.WaitMainAck:
	cmp.b	MCD_MAIN_FLAG-MCD_SUB_FLAG(a0),d1		; Has the Main CPU acknowledged us?
	bne.s	.WaitMainAck					; If not, wait
	move.b	#"I",(a0)					; Acknowledge the Main CPU
	
	bsr.w	WaitWordRam					; Wait for Word RAM access

	lea	INT_ProgramEnd(pc),a0				; Clear rest of RAM
	move.w	#INT_PRG_RAM_CLEAR+(WORD_RAM_2M_SIZE/$20)-1,d1

.ClearRam:
	rept $20/4
		move.l	d0,(a0)+
	endr
	dbf	d1,.ClearRam

	bra.w	InitPcm						; Initialize PCM

; ------------------------------------------------------------------------------
; Main
; ------------------------------------------------------------------------------

	xdef INT_Main
INT_Main:
	tst.b	MCD_MAIN_FLAG					; Is the Main CPU ready for commands?
	bne.s	INT_Main					; If not, wait
	clr.b	MCD_SUB_FLAG					; Acknowledge the Main CPU

; ------------------------------------------------------------------------------

.MainLoop:
	moveq	#0,d0						; Reset command ID

.WaitCommand:
	move.b	MCD_MAIN_FLAG,d0				; Has a command been sent?
	beq.s	.WaitCommand					; If not, wait
	move.b	#"C",MCD_SUB_FLAG				; Acknowledge command

.WaitMainAck:
	tst.b	MCD_MAIN_FLAG					; Has the Main CPU acknowledged us?
	bne.s	.WaitMainAck					; If so, branch

	cmpi.b	#(.CommandsEnd-.Commands)/4,d0			; Is it a valid command?
	bcc.s	.FinishCommand					; If not, branch

	add.w	d0,d0						; Run command
	add.w	d0,d0
	jsr	.Commands-4(pc,d0.w)

.FinishCommand:
	clr.b	MCD_SUB_FLAG					; Mark as finished
	bra.s	.MainLoop					; Loop

; ------------------------------------------------------------------------------

.Commands:
	bra.w	INT_InitCdDriveCmd				; Initialize CD drive
	bra.w	INT_OpenCdDriveCmd				; Open CD drive
	bra.w	INT_GetCdDriveStatusCmd				; Get CD drive status
	bra.w	INT_PlayAllCddaCmd				; Play all CDDA tracks
	bra.w	INT_PlayCddaCmd					; Play CDDA track
	bra.w	INT_LoopCddaCmd					; Loop CDDA track
	bra.w	INT_PlayCddaTimeCmd				; Play CDDA at time
	bra.w	INT_StopCddaCmd					; Stop CDDA
	bra.w	INT_PauseCddaCmd				; Pause CDDA
	bra.w	INT_UnpauseCddaCmd				; Unpause CDDA
	bra.w	INT_SetCddaSpeedCmd				; Set CDDA speed
	bra.w	INT_SeekCddaCmd					; Seek to CDDA track
	bra.w	INT_SeekCddaTimeCmd				; Seek to CDDA time
	bra.w	INT_SwapWordRamBanksCmd				; Swap Word RAM banks
	bra.w	INT_SetWordRamBank0Cmd				; Set Main CPU Word RAM bank 0
	bra.w	INT_SetWordRamBank1Cmd				; Set Main CPU Word RAM bank 1
	bra.w	INT_StartModuleCmd				; Start module
.CommandsEnd:

; ------------------------------------------------------------------------------
; Mega Drive interrupt
; ------------------------------------------------------------------------------

	xdef INT_MegaDriveIrq
INT_MegaDriveIrq:
	movem.l	d0-a6,-(sp)					; Save registers
	bsr.w	INT_UpdateModule				; Update module
	movem.l	(sp)+,d0-a6					; Restore registers
	rts

; ------------------------------------------------------------------------------
; User call 3
; ------------------------------------------------------------------------------

	xdef INT_UserCall3
INT_UserCall3:
	rts

; ------------------------------------------------------------------------------
; Variables
; ------------------------------------------------------------------------------

	section bss

	xdef INT_bios_params
INT_bios_params		ds.b 8					; BIOS parameters

; ------------------------------------------------------------------------------