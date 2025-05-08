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
;	d0.w/$00.w - Starting track ID
; ------------------------------------------------------------------------------

	xdef INT_PlayAllCddaCmd
INT_PlayAllCddaCmd:
	move.w	MCD_MAIN_COMM_0,d0				; Get track ID

; ------------------------------------------------------------------------------

	xdef PlayAllCdda
PlayAllCdda:
	move.w	#MSCPLAY,-(sp)					; Play all CDDA tracks
	bra.w	BasicBiosFunctionW

; ------------------------------------------------------------------------------
; Play CDDA track
; ------------------------------------------------------------------------------
; PARAMETERS:
;	$00.w - Track ID
; ------------------------------------------------------------------------------

	xdef INT_PlayCddaCmd
INT_PlayCddaCmd:
	move.w	MCD_MAIN_COMM_0,d0				; Get track ID

; ------------------------------------------------------------------------------

	xdef PlayCdda
PlayCdda:
	move.w	#MSCPLAY1,-(sp)					; Play CDDA track
	bra.w	BasicBiosFunctionW

; ------------------------------------------------------------------------------
; Loop CDDA track
; ------------------------------------------------------------------------------
; PARAMETERS:
;	$00.w - Track ID
; ------------------------------------------------------------------------------

	xdef INT_LoopCddaCmd
INT_LoopCddaCmd:
	move.w	MCD_MAIN_COMM_0,d0				; Get track ID

; ------------------------------------------------------------------------------

	xdef LoopCdda
LoopCdda:
	move.w	#MSCPLAYR,-(sp)					; Loop CDDA track
	bra.w	BasicBiosFunctionW

; ------------------------------------------------------------------------------
; Play CDDA at time
; ------------------------------------------------------------------------------
; PARAMETERS:
;	$00.l - Timecode
; ------------------------------------------------------------------------------

	xdef INT_PlayCddaTimeCmd
INT_PlayCddaTimeCmd:
	move.l	MCD_MAIN_COMM_0,d0				; Get timecode

; ------------------------------------------------------------------------------

	xdef PlayCddaTime
PlayCddaTime:
	move.w	#MSCPLAYT,-(sp)					; Play CDDA at time
	bra.w	BasicBiosFunctionL

; ------------------------------------------------------------------------------
; Stop CDDA
; ------------------------------------------------------------------------------

	xdef StopCdda
	xdef INT_StopCddaCmd
StopCdda:
INT_StopCddaCmd:
	move.w	#MSCSTOP,-(sp)					; Stop CDDA
	bra.w	BasicBiosFunction

; ------------------------------------------------------------------------------
; Pause CDDA
; ------------------------------------------------------------------------------

	xdef PauseCdda
	xdef INT_PauseCddaCmd
PauseCdda:
INT_PauseCddaCmd:
	move.w	#MSCPAUSEON,-(sp)				; Pause CDDA
	bra.w	BasicBiosFunction

; ------------------------------------------------------------------------------
; Unpause CDDA
; ------------------------------------------------------------------------------

	xdef UnpauseCdda
	xdef INT_UnpauseCddaCmd
UnpauseCdda:
INT_UnpauseCddaCmd:
	move.w	#MSCPAUSEOFF,-(sp)				; Unpause CDDA
	bra.w	BasicBiosFunction

; ------------------------------------------------------------------------------
; Set CDDA speed
; ------------------------------------------------------------------------------
; PARAMETERS:
;	$00.w - Speed setting
;	        0 - Normal
;	        1 - Fast forward
;	        2 - Fast reverse
; ------------------------------------------------------------------------------

	xdef INT_SetCddaSpeedCmd
INT_SetCddaSpeedCmd:
	move.w	MCD_MAIN_COMM_0,d0				; Get speed setting

; ------------------------------------------------------------------------------

	xdef SetCddaSpeed
SetCddaSpeed:
	movem.l	d0-d1/a0-a1,-(sp)				; Save registers

	add.w	d0,d0						; Set CDDA speed
	move.w	.FunctionIds(pc,d0.w),d0
	jsr	_CDBIOS

	movem.l	(sp)+,d0-d1/a0-a1				; Restore registers
	rts

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
	move.w	MCD_MAIN_COMM_0,d0				; Get track ID

; ------------------------------------------------------------------------------

	xdef SeekCdda
SeekCdda:
	move.w	#MSCSEEK,-(sp)					; Seek to CDDA track
	bra.w	BasicBiosFunctionW

; ------------------------------------------------------------------------------
; Seek to CDDA time
; ------------------------------------------------------------------------------
; PARAMETERS:
;	$00.l - Timecode
; ------------------------------------------------------------------------------

	xdef INT_SeekCddaTimeCmd
INT_SeekCddaTimeCmd:
	move.l	MCD_MAIN_COMM_0,d0				; Get timecode

; ------------------------------------------------------------------------------

	xdef SeekCddaTime
SeekCddaTime:
	move.w	#MSCSEEKT,-(sp)					; Seek to CDDA time
	bra.w	BasicBiosFunctionL

; ------------------------------------------------------------------------------