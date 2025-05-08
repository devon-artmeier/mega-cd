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
; Play all CDDA tracks
; ------------------------------------------------------------------------------
; PARAMETERS:
;	$00.w - Starting track ID
; ------------------------------------------------------------------------------

	xdef INT_PlayAllCddaCmd
INT_PlayAllCddaCmd:
	lea	INT_bios_params.w,a0				; Play all CDDA tracks
	move.w	MCD_MAIN_COMM_0,(a0)
	moveq	#MSCPLAY,d0
	jmp	_CDBIOS

; ------------------------------------------------------------------------------
; Play CDDA track
; ------------------------------------------------------------------------------
; PARAMETERS:
;	$00.w - Track ID
; ------------------------------------------------------------------------------

	xdef INT_PlayCddaCmd
INT_PlayCddaCmd:
	lea	INT_bios_params.w,a0				; Play CDDA track
	move.w	MCD_MAIN_COMM_0,(a0)
	moveq	#MSCPLAY1,d0
	jmp	_CDBIOS

; ------------------------------------------------------------------------------
; Loop CDDA track
; ------------------------------------------------------------------------------
; PARAMETERS:
;	$00.w - Track ID
; ------------------------------------------------------------------------------

	xdef INT_LoopCddaCmd
INT_LoopCddaCmd:
	lea	INT_bios_params.w,a0				; Loop CDDA track
	move.w	MCD_MAIN_COMM_0,(a0)
	moveq	#MSCPLAYR,d0
	jmp	_CDBIOS

; ------------------------------------------------------------------------------
; Play CDDA at time
; ------------------------------------------------------------------------------
; PARAMETERS:
;	$00.l - Timecode
; ------------------------------------------------------------------------------

	xdef INT_PlayCddaTime
INT_PlayCddaTime:
	lea	INT_bios_params.w,a0				; Play CDDA at time
	move.l	MCD_MAIN_COMM_0,(a0)
	moveq	#MSCPLAYT,d0
	jmp	_CDBIOS

; ------------------------------------------------------------------------------
; Stop CDDA
; ------------------------------------------------------------------------------

	xdef INT_StopCddaCmd
INT_StopCddaCmd:
	moveq	#MSCSTOP,d0					; Stop CDDA
	jmp	_CDBIOS

; ------------------------------------------------------------------------------
; Pause CDDA
; ------------------------------------------------------------------------------

	xdef INT_PauseCddaCmd
INT_PauseCddaCmd:
	moveq	#MSCPAUSEON,d0					; Pause CDDA
	jmp	_CDBIOS

; ------------------------------------------------------------------------------
; Unpause CDDA
; ------------------------------------------------------------------------------

	xdef INT_UnpauseCddaCmd
INT_UnpauseCddaCmd:
	moveq	#MSCPAUSEOFF,d0					; Unpause CDDA
	jmp	_CDBIOS

; ------------------------------------------------------------------------------
; Set CDDA speed
; ------------------------------------------------------------------------------
; PARAMETERS
;	$00.b - Speed type
;	        0 - Normal
;	        1 - Fast forward
;	        2 - Fast reverse
; ------------------------------------------------------------------------------

	xdef INT_SetCddaSpeedCmd
INT_SetCddaSpeedCmd:
	moveq	#0,d0						; Set CDDA speed
	move.b	MCD_MAIN_COMM_0,d0
	add.w	d0,d0
	move.w	.FunctionIds(pc,d0.w),d0
	jmp	_CDBIOS

; ------------------------------------------------------------------------------

.FunctionIds:
	dc.w	MSCSCANOFF, MSCSCANFF, MSCSCANFR

; ------------------------------------------------------------------------------
; Seek to CDDA track
; ------------------------------------------------------------------------------
; PARAMETERS:
;	$00.w - Track ID
; ------------------------------------------------------------------------------

	xdef INT_SeekCddaCmd
INT_SeekCddaCmd:
	lea	INT_bios_params.w,a0				; Seek to CDDA track
	move.w	MCD_MAIN_COMM_0,(a0)
	moveq	#MSCSEEK,d0
	jmp	_CDBIOS

; ------------------------------------------------------------------------------
; Seek to CDDA time
; ------------------------------------------------------------------------------
; PARAMETERS:
;	$00.l - Timecode
; ------------------------------------------------------------------------------

	xdef INT_SeekCddaTimeCmd
INT_SeekCddaTimeCmd:
	lea	INT_bios_params.w,a0				; Seek to CDDA time
	move.l	MCD_MAIN_COMM_0,(a0)
	moveq	#MSCSEEKT,d0
	jmp	_CDBIOS

; ------------------------------------------------------------------------------