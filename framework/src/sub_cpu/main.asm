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

	xdef XREF_Initialize
XREF_Initialize:
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

	bsr.w	ResetPrgRam					; Reset Program RAM
	bsr.w	ClearWordRam					; Clear Word RAM
	bra.w	InitPcm						; Initialize PCM

; ------------------------------------------------------------------------------
; Main
; ------------------------------------------------------------------------------

	xdef XREF_Main
XREF_Main:
	tst.b	MCD_MAIN_FLAG					; Has the Main CPU acknowledged us?
	bne.s	XREF_Main					; If not, wait
	clr.b	MCD_SUB_FLAG					; Acknowledge the Main CPU

	st	accept_commands					; Start accepting commands

.MainLoop:
	bsr.w	GetCdDriveStatus				; Get CD drive status
	bsr.w	RunModule					; Run module
	bra.s	.MainLoop					; Loop

; ------------------------------------------------------------------------------
; Mega Drive interrupt (command handler)
; ------------------------------------------------------------------------------

	xdef XREF_MegaDriveIrq
XREF_MegaDriveIrq:
	movem.l	d0-a6,-(sp)					; Save registers
	bsr.w	GetCdDriveStatus				; Get CD drive status

	tst.b	accept_commands					; Are we accepting commands?
	beq.s	.End						; If not, branch
	clr.b	accept_commands					; Don't accept any more commands right now

	moveq	#0,d0						; Has a command been sent?
	move.b	MCD_MAIN_FLAG,d0
	beq.s	.NoCommand					; If not, branch

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

.NoCommand:
	st	accept_commands					; Start accepting commands
	
.End:
	movem.l	(sp)+,d0-a6					; Restore registers
	rts

; ------------------------------------------------------------------------------

.Commands:
	bra.w	XREF_InitCdDriveCmd				; Initialize CD drive
	bra.w	XREF_OpenCdDriveCmd				; Open CD drive
	bra.w	XREF_PlayAllCddaCmd				; Play all CDDA tracks
	bra.w	XREF_PlayCddaCmd				; Play CDDA track
	bra.w	XREF_LoopCddaCmd				; Loop CDDA track
	bra.w	XREF_PlayCddaTimeCmd				; Play CDDA at time
	bra.w	XREF_StopCddaCmd				; Stop CDDA
	bra.w	XREF_PauseCddaCmd				; Pause CDDA
	bra.w	XREF_UnpauseCddaCmd				; Unpause CDDA
	bra.w	XREF_SetCddaSpeedCmd				; Set CDDA speed
	bra.w	XREF_SeekCddaCmd				; Seek to CDDA track
	bra.w	XREF_SeekCddaTimeCmd				; Seek to CDDA time
	bra.w	XREF_InitPcmCmd					; Initialize PCM
	bra.w	XREF_SetPcmVolumeCmd				; Set PCM channel volume
	bra.w	XREF_SetPcmPanningCmd				; Set PCM channel panning
	bra.w	XREF_SetPcmFrequencyCmd				; Set PCM channel frequency
	bra.w	XREF_SetPcmWaveStartCmd				; Set PCM channel Wave RAM start address
	bra.w	XREF_SetPcmWaveLoopCmd				; Set PCM channel Wave RAM loop address
	bra.w	XREF_PlayPcmCmd					; Play PCM channels
	bra.w	XREF_StopPcmCmd					; Stop PCM channels
	bra.w	XREF_PausePcmCmd				; Pause PCM channels
	bra.w	XREF_UnpausePcmCmd				; Unpause PCM channels
	bra.w	XREF_SwapWordRamBanksCmd			; Swap Word RAM banks
	bra.w	XREF_SetWordRamBank0Cmd				; Set Main CPU Word RAM bank 0
	bra.w	XREF_SetWordRamBank1Cmd				; Set Main CPU Word RAM bank 1
	bra.w	XREF_SetModuleRunCmd				; Run module
	bra.w	XREF_UnloadModuleCmd				; Unload module
.CommandsEnd:

; ------------------------------------------------------------------------------
; User call 3
; ------------------------------------------------------------------------------

	xdef XREF_UserCall3
XREF_UserCall3:
	rts

; ------------------------------------------------------------------------------
; Variables
; ------------------------------------------------------------------------------

accept_commands:
	dc.b	0							; Accept commands flag
	even

	xdef XREF_bios_params
XREF_bios_params:
	dcb.b	8, 0							; BIOS parameters

; ------------------------------------------------------------------------------