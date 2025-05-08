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

	section code_main

; ------------------------------------------------------------------------------
; Initialization
; ------------------------------------------------------------------------------

	xdef INT_Initialize, INT_UserCall3
INT_Initialize:
	andi.b	#%11100010,MCD_MEM_MODE				; Set Word RAM to 2M mode and disable priority

	lea	INT_ProgramEnd(pc),a0				; Clear rest of Program RAM and Word RAM
	moveq	#0,d0
	move.w	#INT_PRG_RAM_CLEAR+(WORD_RAM_2M_SIZE/$20)-1,d1

.ClearPrgRam:
	rept $20/4
		move.l	d0,(a0)+
	endr
	dbf	d1,.ClearPrgRam

	lea	MCD_SUB_COMMS,a0				; Clear communication registers
	move.b	d0,MCD_SUB_FLAG-MCD_SUB_COMMS(a0)
	rept $10/4
		move.l	d0,(a0)+
	endr

INT_UserCall3:
	rts

; ------------------------------------------------------------------------------
; Main
; ------------------------------------------------------------------------------

	xdef INT_Main
INT_Main:
.GiveWordRam:
	bset	#0,MCD_MEM_MODE					; Give Word RAM access to the Main CPU
	beq.s	.GiveWordRam					; Wait until it's given

	move.b	#"I",MCD_SUB_FLAG				; Mark as initialized

.WaitMainInit:
	cmpi.b	#"I",MCD_MAIN_FLAG				; Has the Main CPU initialized?
	bne.s	.WaitMainInit					; If not, wait

	clr.b	MCD_SUB_FLAG					; Acknowledge Main CPU

.WaitMainAck:
	tst.b	MCD_MAIN_FLAG					; Has the Main CPU acknowledged us?
	bne.s	.WaitMainAck					; If not, wait

; ------------------------------------------------------------------------------

.MainLoop:
	moveq	#0,d0						; Reset command ID

.WaitCommand:
	move.b	MCD_MAIN_FLAG,d0				; Has a command been sent?
	beq.s	.WaitCommand					; If not, wait

	move.b	#"C",MCD_SUB_FLAG				; Acknowledge command

.WaitMainCmdAck:
	tst.b	MCD_MAIN_FLAG					; Has the Main CPU acknowledged us?
	bne.s	.WaitMainCmdAck					; If so, branch

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
	bra.w	INT_PlayCddaAllCmd				; Play all CDDA tracks
	bra.w	INT_PlayCddaCmd					; Play CDDA track
	bra.w	INT_LoopCddaCmd					; Loop CDDA track
	bra.w	INT_PlayCddaTime				; Play CDDA at time
	bra.w	INT_StopCddaCmd					; Stop CDDA
	bra.w	INT_PauseCddaCmd				; Pause CDDA
	bra.w	INT_UnpauseCddaCmd				; Unpause CDDA
	bra.w	INT_SeekCddaCmd					; Seek to CDDA track
	bra.w	INT_SeekCddaTimeCmd				; Seek to CDDA time
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
; Variables
; ------------------------------------------------------------------------------

	section bss

	xdef bios_params
bios_params		ds.b 8					; BIOS parameters

; ------------------------------------------------------------------------------